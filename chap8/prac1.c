#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	char **ptr;
	extern char **environ;
	
	
	if(strcmp(argv[1], "-e") == 0){
		if(argv[2] == NULL){
			for(ptr = environ; *ptr != 0 ; ptr++){
				printf("%s \n", *ptr);
			}
		} else if (argv[2] != NULL){
			char *ptrr;
			ptrr = getenv(argv[2]);
			printf("%s = %s\n", argv[2], ptrr);
		}
	}
	else if(strcmp(argv[1], "-u") == 0){
		printf("executing process real user ID : %d, valid ID : %d\n", getuid(), geteuid());
	}
	else if(strcmp(argv[1], "-g") == 0){
		printf("executing process real group ID : %d, valid ID : %d\n", getgid(), getegid());
	}
	else if(strcmp(argv[1], "-i") == 0){
		printf("process ID : %d\n", getpid());
	}
	else if(strcmp(argv[1], "-p") == 0){
		printf("parent process ID : %d\n", getppid());
	}
}
