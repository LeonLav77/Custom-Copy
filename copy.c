#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <source_file> <destination_file> <buffer_size>\n", argv[0]);
        printf("Example: %s input.txt output.txt 1024\n", argv[0]);
        return 1;
    }

    char fileName[256];
    char newFileName[256];
    strcpy(fileName, argv[1]);
    strcpy(newFileName, argv[2]);

    int bufferSize = atoi(argv[3]);

    FILE *entryFile;
    FILE *outputFile;
    entryFile = fopen(fileName, "rb");
    outputFile = fopen(newFileName, "w+");

    if (entryFile == NULL) {
        perror("Error opening source file");
        return 1;
    }
    if (outputFile == NULL) {
        perror("Error opening destination file");
        return 1;
    }

    fseek(entryFile, 0, SEEK_END);
    int lengthOfFile = ftell(entryFile);
    fseek(entryFile, 0, SEEK_SET);

    printf("Length of file in bytes: %d\n", lengthOfFile);

    unsigned char buffer[bufferSize];

    for (size_t i = 0; i < lengthOfFile; i += bufferSize) {
        size_t bytesRead = fread(buffer, 1, bufferSize, entryFile);
        fwrite(buffer, 1, bytesRead, outputFile);
    }

    fclose(entryFile);
    fclose(outputFile);

    return 0;
}
