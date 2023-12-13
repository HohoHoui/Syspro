#include <stdio.h>
#include <unistd.h>

int main(){
	printf("my process ID : [%d]\n", getpid());
	printf("my parent ID : [%d]\n", getppid());

}
