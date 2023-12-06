#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

void executeCommand(char *args[], int background) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("[%d] child process start\n", pid);
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }else{
        	printf("SUCCESS\n");
        }
        printf("[%d] child process end %d\n", getpid(), pid);
    } else {
        // Parent process
        printf("[%d] parent process start\n", getpid());
        if (!background) {
            // Wait for the child process to finish if not running in the background
            waitpid(pid, NULL, 0);
        }else{        
            printf("[%d] child process end %d\n", getpid(), pid);
        }
        
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARG_SIZE];
    int background, pid;
    pid = fork();
    
    int cnt = 0;
    
    while (cnt < 3) {
        cnt++;
        // Print prompt and get user input
        printf("Plz enter cmd : ");
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline character
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        // Check if the command should run in the background
        background = 0;
        if (len > 1 && input[len - 2] == '&') {
            background = 1;
            input[len - 2] = '\0'; // Remove the '&' from the input 
        }

        // Tokenize the input into arguments
        char *token;
        int i = 0;

        token = strtok(input, " ");
        while (token != NULL && i < MAX_ARG_SIZE - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL; // Null-terminate the argument list

        // Execute the command
        if (i > 0) {
            executeCommand(args, background);
        }
        
        
    }

    return 0;
}

