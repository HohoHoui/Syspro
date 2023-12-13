#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

int main(){
	printf("my real user ID : %d(%s)\n", getuid(), getpwuid(getuid()) -> pw_name);
	printf("my valid user ID : %d(%s)\n", geteuid(), getpwuid(geteuid()) -> pw_name);
	printf("my real group ID : %d(%s)\n", getgid(), getgrgid(getgid())-> gr_name);
	printf("mym valid group ID : %d(%s)", getgid(), getgrgid(getegid())->gr_name);
}
