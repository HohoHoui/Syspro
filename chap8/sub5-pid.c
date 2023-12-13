#include <stdio.h>
#include <unistd.h>

int main(){
	printf("my process ID : [%d]\n", getpid());
	printf("parent process ID : [%d]\n", getppid());
	return 0;
}
