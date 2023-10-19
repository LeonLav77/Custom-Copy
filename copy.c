#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void modifyFileName(const char *originalFileName, char *newFileName) {
    // Find the last dot in the originalFileName
    const char *lastDot = strrchr(originalFileName, '.');

    if (lastDot != NULL) {
        // Copy the part of the originalFileName up to the last dot into newFileName
        strncpy(newFileName, originalFileName, lastDot - originalFileName);
        newFileName[lastDot - originalFileName] = '\0'; // Ensure null-termination

        // Append "_copy" and the portion of the originalFileName after the dot to newFileName
        strcat(newFileName, "_copy");
        strcat(newFileName, lastDot);
    } else {
        // If there's no dot in the originalFileName, just append "_copy" to the end
        strcpy(newFileName, originalFileName);
        strcat(newFileName, "_copy");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("\n\nNo argument passed through the command line!");
        return 1;
    }
    char fileName[256]; // Assuming a maximum filename length of 255 characters
    char newFileName[256];
    strcpy(fileName, argv[1]);

    int bufferSize = atoi(argv[2]);
    modifyFileName(fileName, newFileName);

    FILE *entryFile;
    FILE *outputFile;
    entryFile = fopen(fileName, "rb");
    outputFile = fopen(newFileName, "w+");
    unsigned char buffer[bufferSize]; // Use the provided buffer size

    if (entryFile == NULL) {
        perror("Error opening file");
        return 1;
    }

    fseek(entryFile, 0, SEEK_END);
    int lengthOfFile = ftell(entryFile);
    fseek(entryFile, 0, SEEK_SET);

    printf("Length of file in bytes: %d \n", lengthOfFile);

    for (size_t i = 0; i < lengthOfFile; i += bufferSize) {

        size_t bytesRead = fread(buffer, 1, bufferSize, entryFile);

        fwrite(buffer, 1, bytesRead, outputFile);

        // for (size_t j = 0; j < bytesRead; j++) {
        //     printf("Byte %zu: 0x%02X\n", i + j, buffer[j]);
        // }
    }

    fclose(entryFile);
    fclose(outputFile);

    return 0;
}
