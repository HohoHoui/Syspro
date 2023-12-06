
#include <unistd.h>
#include <stdio.h>

int main(){
	int sec = 0;

	alarm(5);
	printf("endless loop\n");
	while(1){
		sleep(1);
		printf(" %d sec\n", ++sec);
	}
	printf("start faild\n");
}
