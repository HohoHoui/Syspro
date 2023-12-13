 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <signal.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <sys/un.h>
 #define DEFAULT_PROTOCOL 0
 #define MAXLINE 100
 
 int readLine(int fd, char* str);
 
 int main(){
 	int cfd, result;
 	char inmsg[MAXLINE], outmsg[MAXLINE];
 	
 	struct sockaddr_un serverAddr;
 	
 	cfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
 	serverAddr.sun_family = AF_UNIX;
 	strcpy(serverAddr.sun_path, "convert");
 	
 	do {
 		result = connect(cfd, &serverAddr, sizeof(serverAddr));
 		if (result == -1) sleep(1);
 	} while (result == -1);
 	
 	printf("변환할 문자열 입력:\n");
 	
 	fgets(inmsg, MAXLINE, stdin);
 	write(cfd, inmsg, strlen(inmsg)+1);
 	
 	readLine(cfd, outmsg);
 	printf("%s --> \n%s", inmsg, outmsg);
 	
 	close(cfd);
 	exit(0);
 }
