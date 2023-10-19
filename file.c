#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <output_file_name> <file_size_in_megabytes>\n", argv[0]);
        return 1;
    }

    const char *output_file_name = argv[1];
    long long requested_size_in_megabytes = atoll(argv[2]);
    const long long file_size = requested_size_in_megabytes * 1024LL * 1024LL;

    FILE *file = fopen(output_file_name, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    srand(time(NULL));

    long long remaining = file_size;
    char printable_chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

    while (remaining > 0) {
        fputc(printable_chars[rand() % (sizeof(printable_chars) - 1)], file);
        remaining--;
    }

    fclose(file);
    printf("%lldMB text file filled with random characters created: %s\n", requested_size_in_megabytes, output_file_name);
    return 0;
}
