#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int fd, col = 0, row = 0;
	char buf;
	char saveText[10][100];
	int n = 0;
	
	
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }
    if((fd = open(argv[1], O_RDWR)) == -1){
    	fprintf(stderr, "file open error\n");
    	exit(2);
    }

	while(read(fd, &buf, 1) > 0){
		if(buf == '\n'){
			saveText[row][col] = buf;
			row ++;
			col = 0;
		}
		else{
			saveText[row][col] = buf;
			col++;
		}	
	}
    n = row;
    while(n >= 0){
    	printf("%s", saveText[n]);
    	n--;
    }
    
    close(fd);
    exit(0);

}

