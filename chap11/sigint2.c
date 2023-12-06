#include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct sigaction newact;
struct sigaction oldact;
void sigint_handler(int signo);

int main(){
	newact.sa_handler = sigint_handler;
	sigfillset(&newact.sa_mask);

	sigaction(SIGINT, &newact, &oldact);
	while(1){
		printf("press Ctrl-C!\n");
		sleep(1);
	}
}

void sigint_handler(int signo){
	printf("processing signal no.%d", signo);
	printf("power off when you press again\n");
	sigaction(SIGINT, &oldact, NULL);
}
