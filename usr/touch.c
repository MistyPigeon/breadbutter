#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>

int touch_main(int argc, char **argv) {
    int i, fd, status = 0;
    struct utimbuf {
        time_t actime;
        time_t modtime;
    } *times = NULL;

    if (argc < 2) {
        fprintf(stderr, "usage: touch file ...\n");
        return 1;
    }

    for (i = 1; i < argc; i++) {
        if (utimes(argv[i], NULL) < 0) {
            if (errno == ENOENT) {
                fd = open(argv[i], O_CREAT | O_WRONLY, 0666);
                if (fd < 0) {
                    fprintf(stderr, "touch: %s: %s\n", argv[i], strerror(errno));
                    status = 1;
                    continue;
                }
                close(fd);
            } else {
                fprintf(stderr, "touch: %s: %s\n", argv[i], strerror(errno));
                status = 1;
            }
        }
    }
    return status;
}
