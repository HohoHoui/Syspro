#include <stdio.h>
#include "bookInfo.h"

int main(int argc, char *argv[]){
	FILE *fp;
	struct book rec;

	fp = fopen(argv[1], "wb");
	printf("%-9s %-9s %-9s %-9s %4s %4s\n", "ID", "Name", "Writer", "publish", "use cnt", "useing");
	while(scanf("%d %s %s %d %d %d", &rec.ID, rec.name, rec.writer, &rec.date, &rec.cnt, &rec.TF) == 6)
		fwrite(&rec, sizeof(rec), 1, fp);

	fclose(fp);
	return 0;
}
