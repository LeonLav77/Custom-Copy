#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 
#include <fcntl.h> 
#include <unistd.h> 

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("\n\nNo argument passed through the command line!");
        return 1;
    }
    char fileName[256]; // Assuming a maximum filename length of 255 characters
    char newFileName[256];
    strcpy(fileName, argv[1]);
    strcpy(newFileName, argv[2]);


    int bufferSize = atoi(argv[3]);

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