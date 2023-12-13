#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#define DEFAULT_PROTOCOL 0
#define MAXLINE 100

int readLine(int fd, char *str);

// 파일 클라이언트 프로그램

int main(int argc, char *argv[]) {
    int cfd, port, result;
    char *host, inmsg[MAXLINE], outmsg[MAXLINE];
    struct sockaddr_in serverAddr;
    struct hostent *hp;
    FILE *fp;

    if (argc != 3) {
        fprintf(stderr, "How to use : %s <host> <port> \n", argv[0]);
        exit(0);
    }

    host = argv[1];
    port = atoi(argv[2]);

    cfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

    if ((hp = gethostbyname(host)) == NULL) {
        perror("gethostbyname error");
        exit(EXIT_FAILURE);
    }

    bzero((char *)&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    bcopy((char *)hp->h_addr_list[0], (char *)&serverAddr.sin_addr.s_addr, hp->h_length);
    serverAddr.sin_port = htons(port);

    do {
        result = connect(cfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
        if (result == -1) {
            sleep(1);
        }
    } while (result == -1);

    printf("name of download : ");
    scanf("%s", inmsg);

    write(cfd, inmsg, strlen(inmsg) + 1);

    // 파일 열기
    fp = fopen("output.txt", "w"); // 수정: 파일을 쓰기 전용으로 열기
    if (fp == NULL) {
        perror("file open error");
        close(cfd);
        exit(EXIT_FAILURE);
    }

    while (readLine(cfd, outmsg)) {
        fprintf(fp, "%s", outmsg);
    }

    fclose(fp); // 수정: 파일을 닫기
    close(cfd);
    exit(0);
}

int readLine(int fd, char *str) {
    int n;
    do {
        n = read(fd, str, 1);
    } while (n > 0 && *str++ != '\0'); // 수정: 문자열의 끝은 '\0'으로 표시
    return (n > 0);
}

