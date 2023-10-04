#include <stdio.h>
#include "student.h"

int main(int argc, char* argv[]){
	struct student rec;
	FILE *fp;
	
	int i = 0;

	if(argc != 2){
		fprintf(stderr, "how to use: %s [filename]\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "w");
	printf("%-9s %-7s %-4s\n", "id", "name", "score");

	while(scanf("%d %s %d", &rec.id, rec.name, &rec.score) == 3){
		fprintf(fp, "%d %s %d ", rec.id, rec.name, rec.score);
		i += 1;
	}

	fclose(fp);
	return 0;
}
