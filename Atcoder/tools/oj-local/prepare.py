"""Local oj extension: prepare AtCoder problem statements."""
import argparse
from pathlib import Path
import re
import time
from urllib.parse import urljoin, urlparse

from bs4 import BeautifulSoup, NavigableString
import onlinejudge_command.utils as utils


def add_subparser(subparsers):
    parser = subparsers.add_parser('prepare', help='create AtCoder problem directories and Markdown')
    parser.add_argument('contest', help='474, abc474, ARC-200, or a contest URL')
    parser.add_argument('-d', '--directory', type=Path, help='output contest directory')
    parser.add_argument('--dry-run', action='store_true', help='list planned files without writing')


def normalize(value):
    if value.startswith('https://atcoder.jp/contests/'):
        value = urlparse(value).path.rstrip('/').split('/')[-1]
    value = value.lower()
    if value.isdigit():
        value = 'abc' + value.zfill(3)
    match = re.fullmatch(r'(abc|arc|agc)[-_]?(\d+)', value)
    if match:
        value = match[1] + match[2].zfill(3)
    if not re.fullmatch(r'[a-z0-9][a-z0-9_-]*', value):
        raise ValueError('Invalid contest ID')
    return value


def markdown(node, url):
    if isinstance(node, NavigableString):
        return re.sub(r'\s+', ' ', str(node))
    name = node.name
    if name in ('script', 'style'):
        return ''
    if name == 'pre':
        content = node.get_text().strip('\r\n')
        fence = '`' * max(3, max((len(x) + 1 for x in re.findall(r'`+', content)), default=3))
        return f'\n\n{fence}text\n{content}\n{fence}\n\n'
    if name == 'var':
        return '$' + node.get_text() + '$'
    if name == 'img':
        return f'![{node.get("alt", "")}]({urljoin(url, node.get("src", ""))})'
    if name == 'table':
        # Retain table structure where Markdown cannot represent merged cells.
        return '\n\n' + str(node) + '\n\n'
    inner = ''.join(markdown(child, url) for child in node.children)
    if name in ('h1', 'h2', 'h3', 'h4', 'h5', 'h6'):
        return '\n\n' + '#' * max(2, int(name[1])) + ' ' + inner.strip() + '\n\n'
    if name == 'a':
        return f'[{inner}]({urljoin(url, node.get("href", ""))})'
    if name in ('strong', 'b'):
        return '**' + inner + '**'
    if name == 'code':
        return '`' + inner + '`'
    if name == 'br':
        return '  \n'
    if name == 'li':
        return '\n- ' + inner.strip() + '\n'
    if name in ('p', 'div', 'section', 'ul', 'ol'):
        return '\n\n' + inner.strip() + '\n\n'
    return inner


def fetch(session, url):
    response = session.get(url, timeout=30)
    response.raise_for_status()
    if '/login' in response.url:
        raise RuntimeError('ログインが必要です。oj login https://atcoder.jp/ を実行してください。')
    return BeautifulSoup(response.content, 'html.parser')


def task_list(soup, contest):
    result = []
    seen = set()
    for row in soup.select('table tbody tr'):
        links = row.select('a[href]')
        links = [a for a in links if re.fullmatch(
            rf'/contests/{re.escape(contest)}/tasks/[a-zA-Z0-9_-]+', a['href'])]
        if not links or links[0]['href'] in seen:
            continue
        label = links[0].get_text(strip=True)
        if not re.fullmatch(r'[A-Za-z0-9_-]+', label):
            raise RuntimeError(f'Unsupported task label: {label}')
        seen.add(links[0]['href'])
        result.append((label, links[-1].get_text(strip=True), urljoin('https://atcoder.jp', links[0]['href'])))
    if not result:
        raise RuntimeError('問題一覧が見つかりません。コンテストID・公開状態・ログイン状態を確認してください。')
    return result


def statement(soup, label, title, url):
    body = soup.select_one('#task-statement .lang-ja')
    if body is None:
        body = soup.select_one('#task-statement .lang-en')
    if body is None:
        body = soup.select_one('#task-statement')
    if body is None or not body.get_text(strip=True):
        raise RuntimeError(f'問題文が見つかりません: {url}')
    text = markdown(body, url).strip()
    return f'# {label} - {title}\n\n[問題ページ]({url})\n\n{text}\n'


def run(args):
    contest = normalize(args.contest)
    folder = contest[3:] if contest.startswith('abc') and contest[3:].isdigit() else contest
    destination = (args.directory or Path(folder)).resolve()
    with utils.new_session_with_our_user_agent(path=args.cookie) as session:
        tasks = task_list(fetch(session, f'https://atcoder.jp/contests/{contest}/tasks'), contest)
        prepared = []
        for label, title, url in tasks:
            target = destination / label / '課題内容.md'
            if target.exists():
                print(f'SKIP {target}')
                continue
            print(f'CREATE {target}', flush=True)
            if args.dry_run:
                continue
            time.sleep(1)
            prepared.append((target, statement(fetch(session, url), label, title, url)))
        # Fetch all missing pages successfully before creating files.
        for target, content in prepared:
            target.parent.mkdir(parents=True, exist_ok=True)
            try:
                with target.open('x', encoding='utf-8') as stream:
                    stream.write(content)
            except FileExistsError:
                print(f'SKIP {target}')
    print(f'{len(tasks)} tasks: {destination}')
    return True
