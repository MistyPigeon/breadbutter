#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

static int mkpath(char *path, mode_t mode) {
    char *p = path;

    if (*p == '/') p++;

    while ((p = strchr(p, '/')) != NULL) {
        *p = '\0';

        if (mkdir(path, mode | 0300) != 0 && errno != EEXIST) {
            return -1;
        }

        *p = '/';
        p++;
    }

    return (mkdir(path, mode) != 0 && errno != EEXIST) ? -1 : 0;
}

int mkdir_main(int argc, char **argv) {
    int opt, pflag = 0;
    mode_t mode = 0777;
    int status = 0;

    while ((opt = getopt(argc, argv, "pm:")) != -1) {
        switch (opt) {
            case 'p':
                pflag = 1;
                break;
            case 'm':
                mode = (mode_t)strtol(optarg, NULL, 8);
                break;
            default:
                fprintf(stderr, "usage: mkdir [-p] [-m mode] directory ...\n");
                return 1;
        }
    }

    argc -= optind;
    argv += optind;

    if (argc < 1) {
        fprintf(stderr, "mkdir: missing operand\n");
        return 1;
    }

    for (int i = 0; i < argc; i++) {
        if (pflag) {
            if (mkpath(argv[i], mode) < 0) {
                fprintf(stderr, "mkdir: %s: %s\n", argv[i], strerror(errno));
                status = 1;
            }
        } else {
            if (mkdir(argv[i], mode) < 0) {
                fprintf(stderr, "mkdir: %s: %s\n", argv[i], strerror(errno));
                status = 1;
            }
        }
    }

    return status;
}
