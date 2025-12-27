#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

static void concat(int fd, const char *fname) {
    char buf[4096];
    ssize_t n;

    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            fprintf(stderr, "cat: write error: %s\n", strerror(errno));
            return;
        }
    }
    if (n < 0) {
        fprintf(stderr, "cat: %s: %s\n", fname, strerror(errno));
    }
}

int cat_main(int argc, char **argv) {
    int i, fd;
    int status = 0;

    if (argc == 1) {
        concat(STDIN_FILENO, "<stdin>");
        return 0;
    }

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-") == 0) {
            concat(STDIN_FILENO, "<stdin>");
            continue;
        }

        fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            fprintf(stderr, "cat: %s: %s\n", argv[i], strerror(errno));
            status = 1;
            continue;
        }

        concat(fd, argv[i]);
        close(fd);
    }

    return status;
}
