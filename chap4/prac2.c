#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 80

void printFileWithLineNumber(FILE *file) {
    int ch;
    int lineNumber = 1;

    while ((ch = fgetc(file)) != EOF) {
        printf("%6d  ", lineNumber++);
        putchar(ch);

        if (ch == '\n') {
            lineNumber = 1;
        }
    }
}

int main(int argc, char *argv[]) {
	FILE *file = fopen(argv[2], "r");
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-n] file1 file2 ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char buffer[MAXLINE];
    int startIdx = 1;
    int lineNumbering = 0;
    int line = 0;
    
    if (argc > 1 && argv[1][0] == '-') {
        if (argv[1][1] == 'n') {
            while(fgets(buffer, MAXLINE, file) != NULL){
            	line++;
            	printf("%3d %s", line, buffer);
            }
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = startIdx; i < argc; ++i) {
        file = fopen(argv[i], "r");

        if (file == NULL) {
            perror(argv[i]);
            continue;
        }

        if (lineNumbering) {
            printf("-- %s --\n", argv[i]);
            printFileWithLineNumber(file);
        } else {
            printf("-- %s --\n", argv[i]);
            int ch;
            while ((ch = fgetc(file)) != EOF) {
                putchar(ch);
            }
        }

        fclose(file);
    }

    return 0;
}

