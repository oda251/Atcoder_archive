#!/bin/bash

outfile="./lib.cpp"

std="./.lib/std.cpp"

# 出力ファイルを初期化
cat "$std" > "$outfile"
# 現在のディレクトリから始めて再帰的にすべてのファイルを見つける
for file in $(find ./.lib -type f); do
    # 結合したくないファイルを除外する
    if [[ $file != $std ]]; then
        cat "$file" >> "$outfile"
    fi
done
