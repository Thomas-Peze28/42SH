#!/usr/bin/env bash
set -u
IFS=$'\n\t'

# Usage: ./test_crash.sh [CHEMIN_VERS_BINARY] [CHEMIN_VERS_TESTS]
BINARY="${1:-./42sh}"
TESTS_DIR="${2:-./42sh_combined_tests}"

if [ ! -x "$BINARY" ]; then
  echo "Erreur : binaire non trouvé ou non exécutable : $BINARY" >&2
  exit 1
fi
if [ ! -d "$TESTS_DIR" ]; then
  echo "Erreur : dossier de tests introuvable : $TESTS_DIR" >&2
  exit 1
fi

LOGFILE="crash_tests.log"
: > "$LOGFILE"

crash_count=0
total=0

while IFS= read -r -d '' testfile; do
  (( total++ ))
  "$BINARY" < "$testfile" > /dev/null 2>&1
  status=$?
  if [ "$status" -ge 128 ]; then
    echo "❌ Crash détecté sur : $testfile (exit code $status)" | tee -a "$LOGFILE"
    (( crash_count++ ))
  fi
done < <(find "$TESTS_DIR" -type f -name '*.txt' -print0)

echo
echo "🔍 Total de tests exécutés : $total"
if [ "$crash_count" -eq 0 ]; then
  echo "✅ Aucun crash détecté."
else
  echo "⚠️  $crash_count crash(s) détecté(s). Voir $LOGFILE pour les détails."
fi
