#!/usr/bin/env bash
set -euo pipefail

if command -v rg >/dev/null 2>&1; then
  if rg -n --glob '*.{h,cpp}' '(\bclass\b|\bvirtual\b|\bprivate:|\bprotected:)' src tests; then
    echo "style_guard: forbidden tokens detected"
    exit 1
  fi
else
  if grep -R -n -E '(\bclass\b|\bvirtual\b|\bprivate:|\bprotected:)' src tests; then
    echo "style_guard: forbidden tokens detected"
    exit 1
  fi
fi

echo "style_guard: pass"
