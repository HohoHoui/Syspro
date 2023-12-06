#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

pid_t lockt(int fd, int type, off_t offset, int whence, off_t len){

	struct flock fl;
	pid_t owner;
	
	fl.l_type = type;
	fl.l_start = offset;
	fl.l_whence = whence;
	fl.l_len = len;
	
	if(fcntl(fd, F_GETLK, &fl) == -1){
		perror("fcntl");
		return -1;
	}
	if(fl.l_type == F_UNLCK){
		printf("result is 0\n");
		return 0;
	}
	else{
		//printf("process is locked\n");
		owner = fl.l_pid;
		return owner;
		
	}
	return 0;

}
int main(int argc, char **argv){
	static struct flock lock;
	int fd, ret, c;

	if(argc < 6){
		fprintf(stderr, "How to use : %s file type offset whence len\n", argv[0]);
		exit(0);
	}

	fd = open(argv[1], O_WRONLY);
	if(fd == -1){
		printf("file open failed\n");
		exit(1);
	}


	//locks(fd, argv[2], argv[3], argv[4], argv[5]);

	if(strcmp(argv[2],"F_WRLCK")){
		lock.l_type = F_WRLCK;
		printf("type is %s\n", argv[2]);
	}
	else if(strcmp(argv[2],"F_RDLCK")){
		lock.l_type = F_RDLCK;
		printf("type is %s\n", argv[2]);
	}
	else if(strcmp(argv[2], "F_UNLCK")){
		lock.l_type = F_UNLCK;
		printf("type is %s\n", argv[2]);
	}

	lock.l_start = atol(argv[3]);

	printf("start is %ld\n", lock.l_start);

	if(strcmp(argv[4], "SEEK_SET")){
		lock.l_whence = SEEK_SET;
		printf("whence is %s\n", argv[4]);
	}
	else if(strcmp(argv[4],"SEEK_CUR")){
		lock.l_whence = SEEK_CUR;
		printf("whence is %s\n", argv[4]);
	}
	else if(strcmp(argv[4], "SEEK_END")){
		lock.l_whence = SEEK_END;
		printf("whence is %s\n", argv[4]);
	}

	lock.l_len = atol(argv[5]);
	printf("len is %ld\n", lock.l_len);

	pid_t result = lockt(fd, lock.l_type, lock.l_start, lock.l_whence, lock.l_len);
	
	if(result == 0){
		printf("you can change.\n");
	}
	else if(result > 0){
		printf("already locked of process %d\n", result);
	} else{
		printf("error\n");
	}
	
	close(fd);
	return 0;
}
