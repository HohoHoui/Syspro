/*#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]){
	int child, pid, status;
	
	//pid = fork();
	
	if(fork() == 0){
		execvp(argv[1], &argv[1]);
		fprintf(stderr, "%s : execute error\n", argv[1]);
		exit(1);
		}
	if(fork() == 0){
		execvp(argv[2], &argv[2]);
		fprintf(stderr, "%s : execute error\n", argv[2]);
		exit(2);
	}
	if(fork() == 0){
		execvp(argv[3], &argv[3]);
		fprintf(stderr, "%s : execute error\n", argv[3]);
		exit(3);
	}
	printf("end\n");
}*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int status;

    for (int i = 1; i <= 3; i++) {
        if ((pid = fork()) == 0) {
            // Child process
            execvp(argv[i], &argv[i]);
            perror("execvp");
            exit(i);
        } else if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    // 부모 프로세스에서 각 자식 프로세스의 종료를 기다림
    for (int i = 1; i <= 3; i++) {
        pid = waitpid(-1, &status, 0);
        if (pid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        /*if (WIFEXITED(status)) {
            printf("Child %d exited with status %d\n", pid, WEXITSTATUS(status));
        } else {
            printf("Child %d did not exit normally\n", pid);
        }*/
    }

    printf("end\n");
    return 0;
}

