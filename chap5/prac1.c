#include <stdio.h>
#include <string.h>

#define MAXLINE 100
#define MAXSTRING 10000

int main(int argc, char *argv[]) {
    FILE *fp;
    int line = 1, i = 0, num;
    char buffer[MAXSTRING];
    char string[MAXLINE][MAXSTRING];
    int lineNum[100] = {0,};
    int nc = 0;
    if (argc != 2) {
        fprintf(stderr, "사용법:./명령어 파일이름\n");
        return 1;
    }
    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "파일 열기 오류\n");
        return 2;
    }
    while (fgets(buffer, MAXLINE, fp) != NULL) { // 한 줄 읽기
        strcpy(string[line++], buffer);
    }
    printf("File read success\n Total Line : %d\n", --line);
    printf("You can choose 1~%d Line\n", line);
    printf("Pls 'Enter' the line to select(* | n | n-m | n, m) : ");
    scanf("%[^\n]s", buffer);
    if (buffer[0] == '*') {
        for (i = 0; i <= line; i++) {
            printf("%s", string[i]);
        }
        return 0;
    }
    i = 0;
    while (buffer[i] >= '0' && buffer[i] <= '9') {
        i++;
    }
    if (buffer[i] == '-') {
        for (int j = 0; j < i; j++) {
            num = buffer[j] - 48;
            for (int k = j; k < i - 1; k++)
                num *= 10;
            lineNum[0] += num;
        }
        for (int j = i + 1; j < strlen(buffer); j++) {
            num = buffer[j] - 48;
            for (int k = j; k < strlen(buffer) - 1; k++)
                num *= 10;
            lineNum[1] += num;
        }
        for (int j = lineNum[0]; j <= lineNum[1]; j++) {
            printf("%s", string[j]);
        }
    } else if (buffer[i] == ',') {
        for (int j = 0; j < i; j++) {
            num = buffer[j] - 48;
            for (int k = j; k < i - 1; k++)
                num *= 10;
            lineNum[nc] += num;
        }
        int finish = 1;
        int c = 0;
        nc+=1;
        for (int j = i+2; j <= strlen(buffer); j++) {
            if (buffer[j] >= '0' && buffer[j] <= '9')
                c++;
            else {
                j--;
                for (int k = 0; k < c; k++) {
                    num = buffer[j - k] - '0';
                    for (int l = 0; l < k; l++)
                        num *= 10;
                    lineNum[nc] += num;
                }
                c = 0;
                nc+=1;
                j+=2;
            }
        }
        /*while (finish){
            nc++;
            i+=2;
            c=i;
            while (buffer[i]!=','){
                i++;
                if (buffer[i]=='\0'){
                    finish--;
                    break;
                }
            }
            for (int j = c; j < i; j++) {
                num = buffer[j] - 48;
                for (int k = j; k < (i-1); k++)
                    num *= 10;
                lineNum[nc] += num;
            }
        }*/
        for (int j = 0; j < nc; j++) {
            printf("%s", string[lineNum[j]]);
        }
    } else {
        for (int j = 0; j < i; j++) {
            num = buffer[j] - 48;
            for (int k = j; k < i - 1; k++)
                num *= 10;
            lineNum[0] += num;
        }
        printf("%s", string[lineNum[0]]);
    }
    return 0;
}

