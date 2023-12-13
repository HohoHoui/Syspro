#include <stdio.h>
<<<<<<< HEAD
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
=======
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	char *ptr;

	if(strcmp(argv[1],"-e") == 0){
		ptr = getenv(argv[2]);
		printf("%s %s\n", argv[1], argv[2]);
		printf("PATH = %s\n", ptr);
	}
	else if(strcmp(argv[1],"-u") == 0){
		printf("%s  EMPTY\n", argv[1]);
		printf("My Realistic User ID : %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
		printf("My Valid User ID : %d(%s)\n", getuid(), getpwuid(geteuid())->pw_name);
	}
	else if(strcmp(argv[1],"-g") == 0){
		printf("%s EMPTY\n", argv[1]);
		printf("My Realistic Group ID : %d(%s)\n", getgid(), getgrgid(getgid())->gr_name);
		printf("My Valid Group ID : %d(%s)\n", getgid(), getgrgid(getegid())->gr_name);
	}
	else if(strcmp(argv[1], "-i") == 0){
		printf("%s EMPTY\n", argv[1]);
		printf("My Process number : [%d]\n", getpid());
	}

	else if(strcmp(argv[1], "-p") == 0){
		printf("%s EMPTY\n", argv[1]);
		printf("My parent's process number : [%d]\n", getppid());
	}
	exit(0);
	
>>>>>>> d57144fb2e81b97c772554f38aae25bef94bbe9a
}
