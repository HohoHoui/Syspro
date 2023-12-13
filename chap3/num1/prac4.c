#include <stdio.h>
#include <string.h>
#include "copy.h"
#include "copy.c"
char line[MAXLINE]; // 입력 줄
char longest[MAXLINE]; // 가장 긴 줄

int main (){
    char strings [5][100] = {0,}, string[100];
    int stringlens [5]={0,};
    for (int i=0; i<5; i++) {
        scanf("%s", strings[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4 - i; j++)
        {
            if (strlen(strings[j]) > strlen(strings[j + 1]))
            {
                copy(strings[j], string);
                copy(strings[j + 1], strings[j]);
                copy(string, strings[j + 1]);

            }
        }
    }
    for (int i=0; i<5; i++){
        printf("%s\n", strings[i]);
    }
    return  0;
}

