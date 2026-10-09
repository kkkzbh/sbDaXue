#!/usr/bin/env bash
set -euo pipefail

build_dir="${BUILD_DIR:-build-ninja}"

gen="${CMAKE_GENERATOR:-Ninja}"

cmake -S . -B "$build_dir" -G "$gen" -DCMAKE_BUILD_TYPE=Debug
cmake --build "$build_dir"

exe="$build_dir/src/kk"

tmp_out="$build_dir/lex.out"

for input in design/test/v1/main.kk design/test/v1/math.kk; do
  base="$(basename "$input")"
  expected="tests/lex/v1/${base}.tokens"

  "$exe" lex "$input" >"$tmp_out"
  diff -u "$expected" "$tmp_out"
done

echo "lex tests: ok"
