#include <stdio.h>
#include "copy.h"
#include <string.h>

char line[MAXLINE]; //input line
char longest[MAXLINE]; //longest line

int main(){
	int len;
	int max = 0;

	while(fgets(line, MAXLINE, stdin) != NULL){
		len = strlen(line);
		if(len > max){
			max = len;
			copy(line, longest);
		}
	}

	if(max > 0){ //if input has something
		printf("%s", longest);
	}

	return 0;
}
