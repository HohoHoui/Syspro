#include <stdio.h>
#include <stdlib.h>

struct student{
	int id;
	char name[20];
};

int main(){
	struct student *ptr;
	int n, i;

	printf("How many student? : ");
	scanf("%d", &n);

	if( n <= 0){
		fprintf(stderr, "error: unable student count\n");
		fprintf(stderr, "program off\n");
		exit(1);
	}

	ptr = (struct student *)malloc(n * sizeof(struct student));
	if(ptr == NULL){
		perror("malloc");
		exit(2);
	}
	printf("enter student ID and name of %d.\n", n);
	for(i = 0 ; i < n ; i++){
		scanf("%d %s\n", &ptr[i].id, ptr[i].name);
	}

	printf("\n* backword student information *\n");
	for(i = n - 1 ; i >= 0 ; i--){
		printf("%d %s\n", ptr[i].id, ptr[i].name);
	}
	printf("\n");
	exit(0);
}
