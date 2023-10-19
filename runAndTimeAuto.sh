#!/bin/bash

numberOfBytes=(100 1024)
filesBySizeName=("files/small_file.txt" "files/medium_file.txt" "files/big_file.txt")
filesBySizeCopiedName=("files/small_file_copy.txt" "files/medium_file_copy.txt" "files/big_file_copy.txt")
numberOfBytesLength=${#numberOfBytes[@]}
filesBySizeLength=${#filesBySizeName[@]}
programName="$1"

for ((i = 0; i < filesBySizeLength; i++)); do
    currentFileName=${filesBySizeName[i]}
    currentFileNameDestination=${filesBySizeCopiedName[i]}

    for ((j = 0; j < numberOfBytesLength; j++)); do
        currentNumberOfBytes=$((numberOfBytes[j] * 1024))
        /bin/bash runAndTime.sh "$currentFileName" "$currentFileNameDestination" $currentNumberOfBytes 1 $programName
    done
done
