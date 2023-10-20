#!/bin/bash
if [ ! -d "results" ]; then
    mkdir "results"
fi

filesBySizeName=("files/small_file.txt" "files/medium_file.txt" "files/big_file.txt")
filesBySizeCopiedName=("files/small_file_copy.txt" "files/medium_file_copy.txt" "files/big_file_copy.txt")
filesBySizeLength=${#filesBySizeName[@]}
numberOfTests=$1

for ((i = 0; i < filesBySizeLength; i++)); do
    currentFileName=${filesBySizeName[i]}
    currentFileNameDestination=${filesBySizeCopiedName[i]}
    output_file="results/cp_execution_times_$(basename "$currentFileName").txt"

    # Create or empty the output file
    > "$output_file"
    
    for ((j = 0; j < numberOfTests; j++)); do
        # Use 'time' command to measure execution time and 'cp -f' to force overwrite
        exec_time=$(/usr/bin/time -f "%e" -o "$output_file" -a cp -f "$currentFileName" "$currentFileNameDestination" 2>&1)
        echo "Iteration $j done"
    done
done
