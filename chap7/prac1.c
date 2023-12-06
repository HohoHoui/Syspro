#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int locks(int fd, int type, off_t offset, int whence, off_t len){

	struct flock fl;

	fl.l_type = type;
	fl.l_start = offset;
	fl.l_whence = whence;
	fl.l_len = len;
	fl.l_pid = getpid();
	
	if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("fcntl");
        return -1;
    }

    printf("Lock set by process %d\n", fl.l_pid);
    return 0;

}
int main(int argc, char **argv){
	static struct flock lock;
	int fd, ret, c, aa;
	
	if(argc < 5){
		fprintf(stderr, "How to use : %s file type offset whence len\n", argv[0]);
		exit(1);
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

	//aa = locks(fd, lock.l_type, lock.l_start, lock.l_whence, lock.l_len);
	if(aa < 0){
		lock.l_type = F_WRLCK;
		lock.l_start = 0;
		lock.l_whence = SEEK_SET;
		lock.l_len = 0;
	}
	lock.l_type = F_WRLCK;
	lock.l_start = 0;
	lock.l_whence = SEEK_SET;
	lock.l_len = 0;
	lock.l_pid = getpid();
	
	ret = fcntl(fd, F_SETLKW, &lock);
	if(ret == 0){
		c = getchar();
	}
	//close(fd);

	return 0;

}
