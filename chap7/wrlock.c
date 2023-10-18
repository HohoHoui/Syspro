#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[]){
	int fd, id;
	struct student record;
	struct flock lock;

	if(argc < 2){
		fprintf(stderr, "How to use : %s file \n", argv[0]);
		exit(1);
	}
	if((fd = open(argv[1], O_RDWR)) == -1){
		perror(argv[1]);
		exit(2);
	}
	printf("enter student ID to modifing : ");
	while(scanf("%d", &id) == 1){
		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = (id-START_ID)*sizeof(record);
		lock.l_len = sizeof(record);
		if(fcntl(fd, F_SETLKW, &lock) == -1){
			perror(argv[1]);
			exit(3);
		}
		lseek(fd, (long)(id-START_ID)*sizeof(record), SEEK_SET);
		if((read(fd, (char*) &record, sizeof(record)) > 0) && (record.id != 0)){
			printf("name : %s\t ID : %d\t score : %d\n", record.name, record.id, record.score);
		}
		else printf("record %d is not exist\n", id);

		printf("new score : ");
		scanf("%d", &record.score);
		lseek(fd, (long) -sizeof(record), SEEK_CUR);
		write(fd, (char *) &record, sizeof(record));

		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);
		printf("enter student ID to modifing : ");
	}
	close(fd);
	exit(0);
}
