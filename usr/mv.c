#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int mv_main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "usage: mv src dst\n");
        return 1;
    }
    if (rename(argv[1], argv[2]) < 0) {
        if (errno == EXDEV) {
            /* Cross-device move logic: simplified here */
            fprintf(stderr, "mv: cross-device move not supported in this stub\n");
        } else {
            fprintf(stderr, "mv: %s\n", strerror(errno));
        }
        return 1;
    }
    return 0;
}
