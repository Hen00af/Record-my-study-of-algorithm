"""Compile a C++ solution and run cached AtCoder samples with oj."""
import argparse
import os
from pathlib import Path
import re
import shlex
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def contest_id(name):
    name = name.lower().replace('-', '').replace('_', '')
    if re.fullmatch(r'\d+', name):
        return 'abc' + name.zfill(3)
    match = re.fullmatch(r'(abc|arc|agc)(\d+)', name)
    if match:
        return match[1] + match[2].zfill(3)
    return None


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', help='A, A.cpp, 474/A.cpp, ABC430/A/main.cpp')
    parser.add_argument('url', nargs='?', help='explicit problem URL')
    parser.add_argument('--contest', help='contest ID, e.g. abc474 or typical90')
    parser.add_argument('--problem', help='task suffix, e.g. a or 001')
    parser.add_argument('--dry-run', action='store_true', help='show resolved paths and URL only')
    parser.add_argument('--refresh', action='store_true', help='download again, backing up existing cases')
    args = parser.parse_args()

    source = Path(args.source).expanduser()
    if not source.suffix:
        source = source.with_suffix('.cpp')
    source = source.resolve()
    if not source.is_file() or source.suffix not in ('.cpp', '.cc', '.cxx'):
        parser.error(f'C++ source not found: {source}')
    if ROOT not in source.parents:
        parser.error('ソースは Atcoder ディレクトリ内を指定してください。')

    contest = args.contest
    if not contest:
        for parent in source.parents:
            if parent == ROOT:
                break
            contest = contest_id(parent.name)
            if contest:
                break
    if not contest and not args.url:
        parser.error('コンテストを判定できません。--contest abc474 または問題URLを指定してください。')
    problem = args.problem or (source.parent.name if re.fullmatch(r'[A-Za-z]', source.parent.name) or source.stem.lower() in ('main', 'solution') else source.stem)
    problem = problem.lower()
    if not re.fullmatch(r'[a-z0-9_]+', problem):
        parser.error('--problem で問題記号を指定してください。')
    if contest:
        contest = contest_id(contest) or contest.lower()
        if not re.fullmatch(r'[a-z0-9_-]+', contest):
            parser.error('不正なコンテストIDです。')
    url = args.url or f'https://atcoder.jp/contests/{contest}/tasks/{contest}_{problem}'
    if not re.fullmatch(r'https://atcoder\.jp/contests/[a-zA-Z0-9_-]+/tasks/[a-zA-Z0-9_-]+', url):
        parser.error('AtCoderの問題URLを指定してください（クエリ文字列は不要です）。')

    cases = source.parent / 'tests' / source.stem
    binary = source.parent / '.build' / source.stem
    print(f'Source: {source}\nURL:    {url}\nCases:  {cases}', flush=True)
    if args.dry_run:
        return 0
    compiler = os.environ.get('CXX')
    if not compiler:
        candidates = [p for base in ('/opt/homebrew/bin', '/usr/local/bin')
                      for p in Path(base).glob('g++-*') if re.fullmatch(r'g\+\+-\d+', p.name)]
        compiler = str(max(candidates, key=lambda p: int(p.name.split('-')[-1]))) if candidates else 'g++'
    binary.parent.mkdir(exist_ok=True)
    subprocess.run([compiler, '-std=c++17', '-O2', '-Wall', '-Wextra', str(source), '-o', str(binary)], check=True)

    oj = str(ROOT / '.venv/bin/oj')
    marker = cases / '.url'
    cached = marker.is_file() and marker.read_text().strip() == url and any(cases.glob('*.in'))
    if args.refresh or not cached:
        cases.parent.mkdir(exist_ok=True)
        temporary = Path(tempfile.mkdtemp(prefix='.download-', dir=cases.parent))
        try:
            subprocess.run([oj, 'download', url, '-d', str(temporary)], check=True)
            inputs = list(temporary.glob('*.in'))
            if not inputs or any(not p.with_suffix('.out').is_file() for p in inputs):
                raise RuntimeError('完全なサンプル入出力が取得できませんでした。')
            (temporary / '.url').write_text(url + '\n')
            if cases.exists():
                backup = temporary.with_name(temporary.name + '.previous')
                cases.rename(backup)
                print(f'Previous cases: {backup}', flush=True)
            temporary.rename(cases)
        finally:
            if temporary.exists():
                shutil.rmtree(temporary)
    return subprocess.run([oj, 'test', '-c', shlex.quote(str(binary)), '-d', str(cases),
                           '-N', '-t', os.environ.get('TIME_LIMIT', '2')]).returncode


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (OSError, RuntimeError, subprocess.CalledProcessError) as exc:
        print(f'Error: {exc}', file=sys.stderr)
        sys.exit(1)
