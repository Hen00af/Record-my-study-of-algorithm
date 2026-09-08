#!/usr/bin/env bash
set -euo pipefail
root="$(cd "$(dirname "$0")" && pwd)"
if [[ ! -x "$root/.venv/bin/python" ]]; then
    echo 'Atcoder/README.md のセットアップを実行してください。' >&2
    exit 1
fi
exec "$root/.venv/bin/python" "$root/scripts/test.py" "$@"
