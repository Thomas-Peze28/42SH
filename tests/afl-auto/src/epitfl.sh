#!/bin/bash

##
## EPITECH PROJECT, 2025
## AFL Auto Fuzzer
## File description:
## Main script for automating AFL++ fuzzing
##

MAKEFILE="${MAKEFILE:-Makefile}"
OUTPUT_BINARY="fuzzed_binary"
OUTPUT_MAKEFILE="Makefile.afl"
INPUT_OPTION="${INPUT_OPTION:--m none -c 0}"

NB_COEURS=$(echo "$(nproc) * 0.8" | bc | awk '{print int($1)}')
LUNCH_TIME=${LUNCH_TIME:-300}
DELAY=${DELAY:-500}

# Modifications du Makefile
cp $MAKEFILE $OUTPUT_MAKEFILE
sed -i 's/gcc/afl-clang-fast/g' $OUTPUT_MAKEFILE
sed -i "s/-o [^ ]*/-o $OUTPUT_BINARY/g" $OUTPUT_MAKEFILE

# Suppression et recréation du dossier outputafl
[ -d "outputafl" ] && rm -rf outputafl
mkdir -p outputafl

[ -d "output_final" ] && rm -rf output_final

[ ! -d "tests" ] && mkdir -p tests
[ ! -d "tests/testcases" ] && mkdir -p tests/testcases

# Compilation du code avec afl-clang-fast et gcov
make -f $OUTPUT_MAKEFILE

# Vérification de l'existence du binaire $OUTPUT_BINARY
[ ! -f $OUTPUT_BINARY ] && exit 1

# Execution de l'analyse de AFL++
clear
if [ "$(ls -A tests/testcases)" ]; then
    if [ -n "$DISPLAY" ]; then
        tmux new-session -d -s afl "timeout $LUNCH_TIME afl-fuzz -i tests/testcases -o outputafl $INPUT_OPTION -t $DELAY+ -M fuzzer01 -- ./$OUTPUT_BINARY @@"
        for ((i=2; i<=$NB_COEURS; i++)); do
            tmux new-window -t afl "timeout $LUNCH_TIME afl-fuzz -i tests/testcases -o outputafl $INPUT_OPTION -t $DELAY+ -S fuzzer$(printf "%02d" $i) -- ./$OUTPUT_BINARY @@"
        done
        tmux attach-session -t afl
    else
        timeout $LUNCH_TIME afl-fuzz -i tests/testcases -o outputafl $INPUT_OPTION -t $DELAY+ -M fuzzer01 -- ./$OUTPUT_BINARY @@ &
        for ((i=2; i<=$NB_COEURS; i++)); do
            timeout $LUNCH_TIME afl-fuzz -i tests/testcases -o outputafl $INPUT_OPTION -t $DELAY+ -S fuzzer$(printf "%02d" $i) -- ./$OUTPUT_BINARY @@ &
        done
        wait
    fi
else
    echo "Aucun fichier de test trouvé dans tests/testcases. Veuillez ajouter des fichiers de test."
    exit 1
fi

wait

# Vérification de l'existence des dossiers nécessaires dans outputafl
for dir in "outputafl" "outputafl/crashes" "outputafl/hangs" "outputafl/queue"; do
    [ ! -d "$dir" ] && mkdir -p "$dir"
done

mkdir -p output_final

for instance_dir in outputafl/*; do
    if [ -d "$instance_dir" ]; then
        for sub_dir in crashes hangs queue; do
            if [ -d "$instance_dir/$sub_dir" ]; then
                mkdir -p "output_final/$sub_dir"
                cp -r "$instance_dir/$sub_dir/"* "output_final/$sub_dir/" 2>/dev/null
            fi
        done
    fi
done

# Nettoyage des fichiers/dossiers créés pendant les tests sauf output_final
make -f $OUTPUT_MAKEFILE fclean > /dev/null
rm -rf $OUTPUT_BINARY > /dev/null
rm -rf $OUTPUT_MAKEFILE > /dev/null
rm -rf tests/testcases > /dev/null
rm -rf outputafl > /dev/null
rm -rf $OUTPUT_BINARY > /dev/null

echo "Analyse de fuzzing terminée. Les résultats sont disponibles dans le dossier output_final."
