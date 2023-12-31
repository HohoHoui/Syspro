#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
        static struct flock lock;
        int fd, ret, c;

        if(argc < 2){
                fprintf(stderr, "How to use : %s file\n", argv[0]);
                exit(1);
        }

        fd = open(argv[1], O_WRONLY);
        if(fd == -1){
                printf("file open is failed\n");
                exit(1);
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
} 
