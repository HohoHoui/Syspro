#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarmHandler(int signo);

int main(){
	int sec = 0; 

	signal(SIGALRM, alarmHandler);
	alarm(5);

	printf("endless loop\n");
	while(1){
		sleep(1);
		printf("%d sec\n", ++sec);
	}
	printf("start faild\n");
}

void alarmHandler(int signo){
	printf("wake up\n");
	exit(0);
}
