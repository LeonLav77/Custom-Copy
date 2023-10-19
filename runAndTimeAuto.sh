#!/bin/bash

numberOfBytes=(100 1024)
filesBySize=("files/small_file.txt" "files/medium_file.txt" "files/big_file.txt")

numberOfBytesLength=${#numberOfBytes[@]}
filesBySizeLength=${#filesBySize[@]}

for ((i = 0; i < filesBySizeLength; i++)); do
    currentFileName=${filesBySize[i]}

    for ((j = 0; j < numberOfBytesLength; j++)); do
        currentNumberOfBytes=$((numberOfBytes[j] * 1024))
        /bin/bash runAndTime.sh "$currentFileName" $currentNumberOfBytes 20 $1
    done
done
