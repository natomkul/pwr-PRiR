#!/bin/bash
set -e

cd "$(dirname "$0")"
mkdir -p csv
rm -f csv/results_*.csv
cd build

for P in 1 2 4 8 16; do
    output=$(mpirun -np "$P" --oversubscribe ./app)

    while IFS= read -r line; do
        [ -z "$line" ] && continue

        plik=$(echo "$line" | grep -oP 'plik: \K\S+')
        time=$(echo "$line" | grep -oP 'czas: \K[0-9.]+')
        length=$(echo "$line" | grep -oP 'najlepsza dlugosc: \K[0-9.]+')

        instance=$(basename "$plik" .tsp)
        csv="../csv/results_${instance}.csv"

        if [ ! -f "$csv" ]; then
            echo "processes,time,length" > "$csv"
        fi

        echo "$P,$time,$length" >> "$csv"
    done <<< "$output"
done
