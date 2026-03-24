#!/usr/bin/env bash
set -euo pipefail

STATS="fuzz/out/default/fuzzer_stats"
MIN_HOURS=24

if [[ ! -f "$STATS" ]]; then
    echo "No fuzzer_stats found"
    exit 1
fi

# Extract values
start_time=$(grep start_time "$STATS" | awk '{print $3}')
last_update=$(grep last_update "$STATS" | awk '{print $3}')
execs_done=$(grep execs_done "$STATS" | awk '{print $3}')
execs_per_sec=$(grep execs_per_sec "$STATS" | awk '{print $3}')
unique_crashes=$(grep saved_crashes "$STATS" | awk '{print $3}')
unique_hangs=$(grep saved_hangs "$STATS" | awk '{print $3}')

runtime=$((last_update - start_time))
hours=$(awk "BEGIN { printf \"%.2f\", $runtime / 3600 }")

echo "=== AFL Fuzzing Report ==="
echo "Runtime:           ${hours} hours"
echo "Executions:        ${execs_done}"
echo "Exec/sec:          ${execs_per_sec}"
echo "Unique crashes:    ${unique_crashes}"
echo "Unique hangs:      ${unique_hangs}"

if (( $(bc <<< "$hours < $MIN_HOURS") )); then
    echo "Fuzzing time too short"
    exit 1
fi

if [[ $unique_crashes -gt 0 ]]; then
    echo "Crashes detected"
    exit 1
fi
