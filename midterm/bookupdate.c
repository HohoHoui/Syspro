#include <stdio.h>
#include "bookInfo.h"
#include <stdbool.h>

int main(int argc, char *argv[]){
	struct book rec;
	FILE *fp;
	int choose;
	int bookID;
	while(true){
		printf("0 bookID : borrow the book, if someone borrow same book. you cant borrow the book.\n");
		printf("1 bookID : return book");
		
		scanf("%d %d", &choose, &rec.ID);

		if((choose == 0) || (choose == 1) && (bookID == 1) || (bookID == 4))
			break;
	
	if(rec.ID != 0){
		lseek(fd, (int)(ID-START_ID)*sizeof(rec), SEEK_SET);
		if((read(fd, &rec, sizeof(rec)) > 0) && (rec.ID != 0)){
			lseek(fd, (int) -sizeof(rec), SEEK_CUR);
			write(fd, &rec, sizeof(rec));
		}
		else printf("there is no record\n");
	}
	fclose(fp);
	return 0;
}
