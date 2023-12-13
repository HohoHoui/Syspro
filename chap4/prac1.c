#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file1, *file2;

    file1 = fopen("file1.txt", "r");
    if (file1 == NULL) {
        perror("file1.txt");
        exit(EXIT_FAILURE);
    }

    file2 = fopen("file2.txt", "a");
    if (file2 == NULL) {
        perror("file2.txt");
        fclose(file1);
        exit(EXIT_FAILURE);
    }

    int ch;
    while ((ch = fgetc(file1)) != EOF) {
        fputc(ch, file2);
    }

    fclose(file1);
    fclose(file2);


    return 0;
}

