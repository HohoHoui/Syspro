#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]){
	int child, pid, status;
	
	pid = fork();
	
	if(pid == 0){
		execvp(argv[1], &argv[1]);
		fprintf(stderr, "%s : execute error\n", argv[1]);
	}else{
		child = wait(&status);
		printf("end >> %d\n", status >> 8);
	}
}
