#include <stdio.h>
#include <string.h>
#define MAXLINE 100

char line[MAXLINE]
char longest[MAXLINE]

void copy(char from[], char to[]);

int main(){
	int len, max = 0;

	while(fgets(line, MAXLINE, stdin) != NULL){
		len = strlen(line);
		if(len > max){
			max = len;
			copy(line, longest);
		}
	}
	return 0;
}

void copy(char from[], char to[]){
	int i = 0;

	while((to[i] = from[i]) != '\0'){
		++i;
	}	
}
