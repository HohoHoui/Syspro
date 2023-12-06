#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void){
	int n, fd[2], pid;
	char message[100], line[100];
	pipe(fd);

	if((pid = fork()) == 0){
		close(fd[0]);
		sprintf(message, "Hello from PID %d\n", getpid());
		printf("Send: [%d] %s", getpid(), message);
		write(fd[1], message, strlen(message) + 1);
	}else{
		close(fd[1]);
		n = read(fd[0], line, 100);
		printf("Recv: [%d] %s", getpid(), line);
	}
}
