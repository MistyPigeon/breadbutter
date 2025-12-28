#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

int nohup_main(int argc, char **argv) {
    if (argc < 2) return 1;
    signal(SIGHUP, SIG_IGN);
    if (isatty(STDOUT_FILENO)) {
        int fd = open("nohup.out", O_WRONLY | O_CREAT | O_APPEND, 0600);
        if (fd != -1) {
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
    }
    execvp(argv[1], &argv[1]);
    return 1;
}
