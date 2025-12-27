#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int chmod_main(int argc, char **argv) {
    mode_t mode;
    int i, status = 0;

    if (argc < 3) {
        fprintf(stderr, "usage: chmod mode file ...\n");
        return 1;
    }

    mode = (mode_t)strtol(argv[1], NULL, 8);

    for (i = 2; i < argc; i++) {
        if (chmod(argv[i], mode) < 0) {
            fprintf(stderr, "chmod: %s: %s\n", argv[i], strerror(errno));
            status = 1;
        }
    }

    return status;
}
