#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAXLINE 100

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t child_pid;

    // 파이프 생성
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 자식 프로세스 생성
    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // 자식 프로세스 (ls)
        close(pipefd[0]); // 읽기용 파이프를 사용하지 않음

        // 파이프의 표준 출력을 자신의 표준 출력에 연결
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]); // 복사가 끝났으므로 파이프 닫음

        // ls 명령어 실행
        execlp("ls", "ls", NULL);
        perror("execlp (ls)");
        exit(EXIT_FAILURE);
    } else {
        // 부모 프로세스
        close(pipefd[1]); // 쓰기용 파이프를 사용하지 않음

        // 파이프의 표준 입력을 자신의 표준 입력에 연결
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); // 복사가 끝났으므로 파이프 닫음

        // wc 명령어 실행
        if (argc == 1) {
            execlp("wc", "wc", NULL);
        } else {
            // 명령어 인자가 있을 경우 실행
            execvp(argv[1], &argv[1]);
        }

        perror("exec");
        exit(EXIT_FAILURE);
    }

    return 0;
}

