#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num_child;

    printf("type num of childs : ");
    scanf("%d", &num_child);

    
    pid_t last_child_pid;

    
    for (int i = 0; i < num_child; ++i) {
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            sleep(i + 1);

            printf("[child %d] : Started! pid = %d, sleep=%d\n", i, getpid(), i + 1);
            printf("[child %d] : Killed! pid = %d, sleep=%d\n", i, getpid(), i + 1);
            exit(EXIT_SUCCESS);
        } else {
            last_child_pid = child_pid;
        }
    }
    
    int status;
    waitpid(last_child_pid, &status, 0);

    printf("parent killed - last child id = %d\n", last_child_pid);
    return 0;
}

