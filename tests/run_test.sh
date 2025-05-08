#!/usr/bin/env bash
SHELL_BIN="./42sh"
TEST_FILE="tests/tests.txt"

set -o pipefail

OK=$'\e[32mOK\e[0m'
KO=$'\e[31mFAIL\e[0m'

while IFS= read -r line; do
  [[ -z "$line" || "$line" =~ ^[[:space:]]*# ]] && continue

  expected="${line%%:*}"
  cmd="${line#*: }"

  output=$(printf "%s\n" "$cmd" | $SHELL_BIN 2>&1 | cat -e)
  code=$?

  if [[ "$code" -eq "$expected" ]]; then
    printf "%s expected=%s got=%s : %s\n" "$OK" "$expected" "$code" "$cmd"
  else
    printf "%s expected=%s got=%s : %s\n" "$KO" "$expected" "$code" "$cmd"
  fi

  echo "    output: $output"
done < "$TEST_FILE"