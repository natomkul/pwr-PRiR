#!/bin/bash
set -e

cd "$(dirname "$0")"
mkdir -p csv
cd build

declare -A seen

for P in 1 2 4 8 16; do
    output=$(mpirun -np "$P" --oversubscribe ./app)

    while IFS= read -r line; do
        [ -z "$line" ] && continue

        plik=$(echo "$line" | grep -oP 'plik: \K\S+')
        time=$(echo "$line" | grep -oP 'czas: \K[0-9.]+')
        length=$(echo "$line" | grep -oP 'najlepsza dlugosc: \K[0-9.]+')

        instance=$(basename "$plik" .tsp)
        csv="../csv/results_${instance}.csv"

        if [ -z "${seen[$instance]}" ]; then
            echo "processes,time,length" > "$csv"
            seen[$instance]=1
        fi

        echo "$P,$time,$length" >> "$csv"
    done <<< "$output"
done
