#include <stdio.h>
#include "bookInfo.h"
#include <stdbool.h>
int main(int argc, char *argv[]){
	struct book rec;
	FILE *fp;
	int answer;
	while(true){
		printf("0 - show all data\n");
		printf("1 - you can read those book\n");

		scanf("%d", &answer);

		if((answer == 0) || (answer == 1))
			break;
	}
	
	if (answer == 0){
		while(fread(&rec, sizeof(rec), 1, fp) > 0)
			if(rec.ID != 0)
				printf("%d %-7s %-5s %-4d %2d %2d\n", rec.ID, rec.name, rec.writer, rec.date, rec.cnt, rec.TF);
		printf("------------------------------------------\n");
	}
	else if (answer == 1){
		while(fread(&rec, sizeof(rec), 1, fp) > 0)
			if(rec.TF != 0)
				printf("%d %-7s %-5s %-4d %2d %2d\n", rec.ID, rec.name, rec.writer, rec.date, rec.cnt, rec.TF);
		printf("------------------------------------------\n");
	}
	
	fclose(fp);
	return 0;
}
