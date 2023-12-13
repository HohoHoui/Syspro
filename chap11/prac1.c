#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void alarmHandler(int signo)
{
    printf("일어나세요\n");
    exit(0);

}

int main() {
    signal(SIGALRM, alarmHandler);
    alarm(5);
    printf("endless loop\n");
    int i=1;
    while (i>0) {
        sleep(1);
        printf("%dsec\n", i);
        i++;
    }
    printf("unexecute \n");

    return 0;
}

