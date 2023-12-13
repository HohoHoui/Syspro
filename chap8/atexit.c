#include <stdio.h>
#include <stdlib.h>

static void exit_handler1(void), exit_handler2(void);

int main(void){
	if(atexit(exit_handler1) != 0)
		perror("unable to exit_handler1");
	if(atexit(exit_handler2) != 0)
		perror("unalbe to exit_handler2");
	printf("main finish\n");
	exit(0);
}

static void exit_handler1(void){
	printf("first exit handler\n");
}

static void exit_handler2(void){
	printf("second exit handler\n");
}
