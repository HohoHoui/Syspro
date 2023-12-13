#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, int g, int G, int h);
void byte(float n);

/* 디렉터리 내용을 자세히 리스트한다. */
int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    int g=0, G=0, h=0;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ+1];
    if (argc == 1 || argc==2){
        dir = ".";
        if (argc==2){
            for (int i=1; i<strlen(argv[1]); i++){
                switch (argv[1][i]) {
                    case 'g':
                        g++;
                        break;
                    case 'G' :
                        G++;
                        break;
                    case 'h':
                        h++;
                }
            }
        }
    }
    else dir = argv[1];

    if ((dp = opendir(dir)) == NULL) // 디렉터리 열기
        perror(dir);

    while ((d = readdir(dp)) != NULL) { // 디렉터리의 각 파일에 대해
        sprintf(path, "%s/%s", dir, d->d_name); // 파일경로명 만들기
        if (lstat(path, &st) < 0) // 파일 상태 정보 가져오기
            perror(path);
        else
            printStat(path, d->d_name, &st, g, G, h); // 상태 정보 출력
    }
    closedir(dp);
    exit(0);
}
void byte (float n){
    int i=0;
    char unit='\0';
    for (i=0; i<4; i++){
        if (n<1024)
            break;
        n/=1024;
    }
    switch (i) {
        case 1 :
            unit='K';
            break;
        case 2 :
            unit='M';
            break;
        case 3 :
            unit='G';
            break;
    }
    i? (n-(int)n)? printf("%6.1f%c ", n, unit): printf("%6.f%c ", n, unit) : printf("%7.f  ", n);
}
void printStat(char *pathname, char *file, struct stat *st, int g, int G, int h)
{
    printf("%5ld ", st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3ld ", st->st_nlink);
    g? : printf("%s ", getpwuid(st->st_uid)->pw_name);
    G? : printf("%s ", getgrgid(st->st_gid)->gr_name);
    h? byte((float)st->st_size): printf("%9ld ", st->st_size);
    printf("%.12s ", ctime(&st->st_mtime)+4);
    printf("%s\n", file);
}
char type(mode_t mode)
{
    if (S_ISREG(mode))
        return('-');
    if (S_ISDIR(mode))
        return('d');
    if (S_ISCHR(mode))
        return('c');
    if (S_ISBLK(mode))
        return('b');
    if (S_ISLNK(mode))
        return('l');
    if (S_ISFIFO(mode))
        return('p');
    if (S_ISSOCK(mode))
        return('s');
}
char* perm(mode_t mode)
{
    static char perms[10];
    strcpy(perms, "---------");

    for (int i=0; i < 3; i++) {
        if (mode & (S_IRUSR >> i*3))
            perms[i*3] = 'r';
        if (mode & (S_IWUSR >> i*3))
            perms[i*3+1] = 'w';
        if (mode & (S_IXUSR >> i*3))
            perms[i*3+2] = 'x';
    }
    return(perms);
}

