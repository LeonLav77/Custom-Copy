#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 
#include <fcntl.h> 
#include <unistd.h> 

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <source_file> <destination_file> <buffer_size>\n", argv[0]);
        printf("Example: %s input.txt output.txt 1024\n", argv[0]);
        return 1;
    }

    char fileName[256]; // Assuming a maximum filename length of 255 characters
    char newFileName[256];
    strcpy(fileName, argv[1]);
    strcpy(newFileName, argv[2]);

    int bufferSize = atoi(argv[3]);

    unsigned char buffer[bufferSize];

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