#!/usr/bin/env bash
set -euo pipefail
root="$(cd "$(dirname "$0")" && pwd)"
cd "$root"
exec "$root/.venv/bin/oj" prepare "$@"
