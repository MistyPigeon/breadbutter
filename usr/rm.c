#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>

static int rflag = 0;
static int fflag = 0;

static int rm_rf(const char *path) {
    struct stat st;
    DIR *dir;
    struct dirent *de;
    char subpath[PATH_MAX];
    int status = 0;

    if (lstat(path, &st) < 0) {
        if (fflag) return 0;
        fprintf(stderr, "rm: %s: %s\n", path, strerror(errno));
        return 1;
    }

    if (S_ISDIR(st.st_mode) && rflag) {
        if (!(dir = opendir(path))) {
            fprintf(stderr, "rm: %s: %s\n", path, strerror(errno));
            return 1;
        }
        while ((de = readdir(dir))) {
            if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
                continue;
            if (snprintf(subpath, sizeof(subpath), "%s/%s", path, de->d_name) >= sizeof(subpath)) {
                fprintf(stderr, "rm: path too long\n");
                status = 1;
                continue;
            }
            status |= rm_rf(subpath);
        }
        closedir(dir);
        if (rmdir(path) < 0) {
            fprintf(stderr, "rm: %s: %s\n", path, strerror(errno));
            return 1;
        }
    } else {
        if (unlink(path) < 0) {
            if (fflag && errno == ENOENT) return 0;
            fprintf(stderr, "rm: %s: %s\n", path, strerror(errno));
            return 1;
        }
    }
    return status;
}

int rm_main(int argc, char **argv) {
    int opt, i;
    int status = 0;

    rflag = fflag = 0;
    optind = 1;

    while ((opt = getopt(argc, argv, "rfR")) != -1) {
        switch (opt) {
            case 'r':
            case 'R':
                rflag = 1;
                break;
            case 'f':
                fflag = 1;
                break;
            default:
                fprintf(stderr, "usage: rm [-rfR] file ...\n");
                return 1;
        }
    }

    argv += optind;
    argc -= optind;

    if (argc < 1) {
        if (fflag) return 0;
        fprintf(stderr, "rm: missing operand\n");
        return 1;
    }

    for (i = 0; i < argc; i++) {
        status |= rm_rf(argv[i]);
    }

    return status;
}
