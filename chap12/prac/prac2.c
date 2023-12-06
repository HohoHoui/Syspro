#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 100

int main(int argc, char *argv[]){
	char line[MAXLINE];
	int n, pid, fd[2];

	pipe(fd);

	if((pid = fork()) == 0){

		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		printf("parent process start\n");
		while(fgets(line, MAXLINE, stdin) != NULL);


	}else{
		close(fd[1]);
		
	}
	return 0;
}
