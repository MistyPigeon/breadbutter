#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int xargs_main(int argc, char **argv) {
    char arg[1024];
    char *cmd = (argc > 1) ? argv[1] : "echo";
    while (scanf("%1023s", arg) != EOF) {
        if (fork() == 0) {
            execlp(cmd, cmd, arg, (char *)NULL);
            _exit(1);
        }
        wait(NULL);
    }
    return 0;
}
