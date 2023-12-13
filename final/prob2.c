#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void create_child(int depth, int max_depth);

int main() {
    create_child(0, 3);

    return 0;
}

void create_child(int depth, int max_depth) {
    if (depth > max_depth) {
        return;
    }

    pid_t child_pid1, child_pid2;

    printf("p%d: Hello\n", depth);

    if (depth < max_depth) {
        
        child_pid1 = fork();
        if (child_pid1 == 0) {
            create_child(depth + 1, max_depth);
            return;
        }

        child_pid2 = fork();
        if (child_pid2 == 0) {
            create_child(depth + 1, max_depth);
            return;
        }
    }

    if (depth > 0) {
        waitpid(child_pid1, NULL, 0);
        waitpid(child_pid2, NULL, 0);
    }
}

