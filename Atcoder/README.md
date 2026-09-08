# AtCoder 共通テスト環境

`Atcoder` 直下の `test.sh` と `.venv` を全コンテストで共用します。

```sh
# Atcoder 直下から
./test.sh 474/A.cpp
./test.sh ABC-456/C.cpp

# 各コンテストのフォルダから
cd 474
../test.sh A
```

初回はサンプル取得・C++17でのコンパイル・ojでのテストを行います。
2回目以降は保存済みサンプルを使います。

## コンテストと問題の判定

ソースの親フォルダから上にたどり、最初に一致する名前を使います。

| フォルダ名 | コンテストID |
| --- | --- |
| `474` | `abc474`（数字だけならABCとして扱う） |
| `ABC-456` / `ABC456` / `abc456` | `abc456` |
| `ARC-200` | `arc200` |
| `AGC070` | `agc070` |

`A.cpp` は問題 `a`、`A/main.cpp` や `A/solution.cpp` は親フォルダの `a` を使います。
`ABC` のように番号がないフォルダは自動判定できないため、IDを指定してください。

```sh
./test.sh ABC/C/main.cpp --contest abc456
./test.sh 474/A.cpp --dry-run
./test.sh 474/A.cpp --refresh
```

任意のコンテスト・問題記号の指定もできます。
古いコンテストなどURLの命名が異なる場合は問題ページのURLを指定してください。

```sh
./test.sh path/to/main.cpp --contest typical90 --problem 001
./test.sh 474/A.cpp https://atcoder.jp/contests/abc474/tasks/abc474_a
```

テストはソースと同じフォルダの `tests/<ソース名>/` に保存します。
`custom-1.in` と `custom-1.out` のペアで独自ケースを追加できます。
URL変更時・`--refresh` 時は以前のケースを `.download-*.previous` に退避します。
実行ファイルはソースと同じフォルダの `.build/` に保存します。
既存の `474/tests/A` もそのまま利用します。

空白・改行の違いは無視し、1ケースの制限時間は2秒です。
浮動小数点や複数の正解がある問題は、問題に応じた判定を別途指定してください。
サンプルでの成功は提出時のACを保証しません。

```sh
TIME_LIMIT=5 ./test.sh 474/A.cpp
CXX=/opt/homebrew/bin/g++-15 ./test.sh 474/A.cpp
```

## セットアップの再実行

Atcoder直下で実行します。

```sh
uv venv .venv --python python3
uv pip install --python .venv/bin/python -r requirements-test.txt
```

GCCを自動検出します。Python 3.12以降の互換性のためsetuptoolsも入れています。
`oj` を直接使う場合は `source .venv/bin/activate` を実行してください。

公式: https://github.com/online-judge-tools/oj

## 全問題の準備（ローカル改造版 oj）

```sh
./oj.sh 474
./oj.sh arc200
./oj.sh 474 --dry-run
```

Atcoder直下に `474/A/課題内容.md`、`474/B/課題内容.md` のように全問題を作成します。
日本語本文（なければ英語）、制約、入出力、サンプルを保存します。
数式はMarkdownの `$...$`、画像は元のURLへのリンクです。
既存の課題内容.mdと解答コードは上書きしません。解答コードは自分で作成します。
取得に失敗した場合はエラー終了し、その回の新規ファイルは作成しません。

これはインストール済みoj本体に `prepare` サブコマンドを追加するローカル改造です。
問題一覧・本文の取得処理は `tools/oj-local/prepare.py` に保存しています。

```sh
source .venv/bin/activate
oj prepare 474
# ojを再インストール・更新した後は改造を再適用
.venv/bin/python tools/oj-local/install.py
```

`oj prepare` を直接使う場合は実行場所にコンテストフォルダを作成します。
`oj.sh` 経由なら常にAtcoder直下に作成します。`-d` で保存先を指定できます。
テスト実行は引き続き `./test.sh 474/A.cpp` を使います。
問題フォルダに `main.cpp` を作った場合は `./test.sh 474/A/main.cpp` でも実行できます。
