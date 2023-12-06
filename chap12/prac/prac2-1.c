#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#define BUFFER_SIZE 256

int main() {
    int pipefd[2]; 
    pid_t child_pid1, child_pid2;


    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }


    if ((child_pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid1 == 0) {
        
        close(pipefd[0]); 

        
        char input[BUFFER_SIZE];
        printf("parent process start\n");
        printf("Enter a string: ");
        fgets(input, sizeof(input), stdin);
        write(pipefd[1], input, strlen(input) + 1);
        close(pipefd[1]); 

        exit(EXIT_SUCCESS);
    }

    
    if ((child_pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid2 == 0) {
        
        close(pipefd[1]); 

        
        char received[BUFFER_SIZE];
        read(pipefd[0], received, sizeof(received));
        for (int i = 0; i < strlen(received); i++) {
            putchar(toupper(received[i]));
        }
        printf("\n");
        close(pipefd[0]); 

        exit(EXIT_SUCCESS);
    }

   
    close(pipefd[0]); 
    close(pipefd[1]); 
    
    waitpid(child_pid1, NULL, 0);
    waitpid(child_pid2, NULL, 0);

    return 0;
}

