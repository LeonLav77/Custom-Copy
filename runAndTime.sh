#!/bin/bash

if [ $# -ne 5 ]; then
    echo "Usage: $0 <copiedFile> <copiedFileDestination> <numberOfBytesCopied> <num_iterations> <filename>"
    exit 1
fi

copiedFile="$1"
copiedFileDestination="$2"
numberOfBytesCopied="$3"
num_iterations="$4"
file_name="$5"

# Compile the C program (add error checking)
if ! gcc -o copy "$file_name"; then
    echo "Compilation of $file_name failed"
    exit 1
fi

output_file="${copiedFile}_execution_times_${numberOfBytesCopied}.txt"

# Clear the contents of the output file or create it if it doesn't exist
> "$output_file"

for ((i = 1; i <= num_iterations; i++)); do
    # Measure the execution time of the C program
    exec_time=$( /usr/bin/time -f "%e" -o "$output_file" -a ./copy "$copiedFile" "$copiedFileDestination" "$numberOfBytesCopied" 2>&1 )
    echo "Iteration $i: Execution time = $exec_time"
done

echo "Execution times for $num_iterations iterations saved to $output_file"

# Calculate the average execution time
total_time=$(awk '{ sum += $1 } END { print sum }' "$output_file")
average_time=$(echo "scale=4; $total_time / $num_iterations" | bc)

echo "Average Execution Time for $num_iterations iterations: $average_time seconds"
