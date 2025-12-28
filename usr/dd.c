#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int dd_main(int argc, char **argv) {
    char buf[512];
    ssize_t n;
    int ifd = STDIN_FILENO, ofd = STDOUT_FILENO;
    while ((n = read(ifd, buf, sizeof(buf))) > 0) {
        write(ofd, buf, n);
    }
    return 0;
}
