#!/usr/bin/env bash

set -euo pipefail

CRASH_DIR="fuzz/out/default/crashes"
OUT_DIR="tests/fuzzregression"

mkdir -p "$OUT_DIR"

# Iterate safely over files
find "$CRASH_DIR" -maxdepth 1 -type f -print0 | while IFS= read -r -d '' file; do
    base="$(basename "$file")"

    # Skip AFL metadata
    if [[ "$base" == "README.txt" ]]; then
        continue
    fi

    # Extract id:XXXXXX
    if [[ "$base" =~ id:([0-9]+) ]]; then
        id="${BASH_REMATCH[1]}"

        # Remove leading zeros (optional, keep if you prefer fixed width)
        id_num=$((10#$id))

        printf -v num "%03d" "$id_num"
        dest="$OUT_DIR/crash_${num}.s"

        if [[ -e "$dest" ]]; then
            echo "Skipping existing $dest"
        else
            mv "$file" "$dest"
            echo "Moved $file -> $dest"
        fi
    else
        echo "Skipping unrecognised file: $file"
    fi
done

echo "Done."
