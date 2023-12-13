#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	//int pid;

	printf("my process number : [%d]\n", getpid()); //parent porcess run descendant porcess

	printf("my parent's process number : [%d]\n", getppid()); //parent is shell process
	system("ps"); //system() : command run function, ps : process execution status

	return 0;
}
