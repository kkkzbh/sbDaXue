#!/usr/bin/env bash
set -euo pipefail

build_dir="${BUILD_DIR:-build-ninja}"

gen="${CMAKE_GENERATOR:-Ninja}"

cmake -S . -B "$build_dir" -G "$gen" -DCMAKE_BUILD_TYPE=Debug
cmake --build "$build_dir"

exe="$build_dir/src/kk"

mkdir -p tests/lex/v1

"$exe" lex design/test/v1/main.kk > tests/lex/v1/main.kk.tokens
"$exe" lex design/test/v1/math.kk > tests/lex/v1/math.kk.tokens

echo "updated golden outputs"
