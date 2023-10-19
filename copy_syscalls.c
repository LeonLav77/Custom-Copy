#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 
#include <fcntl.h> 
#include <unistd.h> 

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

    unsigned char buffer[bufferSize]; // Use the provided buffer size

    int inputFileDescriptor = open(fileName, O_RDONLY);
    int outputFileDescriptor = open(newFileName, O_CREAT | O_WRONLY, 0644);

    if (inputFileDescriptor == -1 || outputFileDescriptor == -1) { 
        printf("Error Number % d\n", errno); 
        perror("Program"); 
    } 

    int bytesRead;
    int bytesWritten;
    
    while ((bytesRead = read(inputFileDescriptor, buffer, bufferSize)) > 0) {
        bytesWritten = write(outputFileDescriptor, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Write error");
            break;
        }
    }

    close(inputFileDescriptor);

    return 0;
}