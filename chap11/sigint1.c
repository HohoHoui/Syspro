#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void intHandler(int signo);

int main(){
	signal(SIGINT, intHandler);

	while(1)
		pause();
	printf("start faild\n");
}

void intHandler(int signo){
	printf("processing interrupt signal\n");
	printf("signal num : %d\n", signo);
	exit(0);
}
