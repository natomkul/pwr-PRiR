#!/bin/bash
set -e

cd "$(dirname "$0")"
mkdir -p csv
cd build

CSV="../csv/results.csv"
echo "processes,time,length" > "$CSV"

for P in 1 2 4 8 16; do
    output=$(mpirun -np "$P" --oversubscribe ./app)
    time=$(echo "$output" | grep -oP 'czas: \K[0-9.]+')
    length=$(echo "$output" | grep -oP 'najlepsza dlugosc: \K[0-9.]+')
    echo "$P,$time,$length" >> "$CSV"
done
