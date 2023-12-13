#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100

int readLine(int fd, char *str);
void toUpper(char *in, char *out);

int main(){
	int sfd, cfd, clientlen;
	char inmsg[MAXLINE], outmsg[MAXLINE];
	struct sockaddr_un serverAddr, clientAddr;
	
	signal(SIGCHLD, SIG_IGN);
	clientlen = sizeof(clientAddr);
	
	sfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
	serverAddr.sun_family = AF_UNIX;
	strcpy(serverAddr.sun_path, "convert");
	unlink("convert");
	bind(sfd, (struct sockaddr *)&clientAddr, &clientlen);
	if(fork() == 0){
		readLine(cfd, inmsg);
		toUpper(inmsg, outmsg);
		write(cfd, outmsg, strlen(outmsg)+1);
		close(cfd);
		exit(0);
	}else close(cfd);
	
	toUpper(char* in, char* out){
		int i;
		for(i = 0 ; i < strlen(in); i++){
			if(islower(in[i])){
				out[i] = toupper(in[i]);
			}else{
				out[i] = NULL;
			}
			out[i] = NULL;
		}
			
	}
}
