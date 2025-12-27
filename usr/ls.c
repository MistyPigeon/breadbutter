#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

static int aflag = 0;

static int filter(const struct dirent *d) {
    if (!aflag && d->d_name[0] == '.')
        return 0;
    return 1;
}

static void listdir(const char *name) {
    struct dirent **namelist;
    int n;

    n = scandir(name, &namelist, filter, alphasort);
    if (n < 0) {
        fprintf(stderr, "ls: %s: %s\n", name, strerror(errno));
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("%s%s", namelist[i]->d_name, (i + 1 < n) ? "  " : "");
        free(namelist[i]);
    }
    printf("\n");
    free(namelist);
}

int ls_main(int argc, char **argv) {
    int opt;
    int status = 0;

    aflag = 0;
    optind = 1; 

    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
            case 'a':
                aflag = 1;
                break;
            default:
                fprintf(stderr, "usage: ls [-a] [file ...]\n");
                return 1;
        }
    }

    argc -= optind;
    argv += optind;

    if (argc == 0) {
        listdir(".");
    } else {
        for (int i = 0; i < argc; i++) {
            struct stat st;
            if (stat(argv[i], &st) < 0) {
                fprintf(stderr, "ls: %s: %s\n", argv[i], strerror(errno));
                status = 1;
                continue;
            }

            if (S_ISDIR(st.st_mode)) {
                if (argc > 1) printf("%s:\n", argv[i]);
                listdir(argv[i]);
                if (i + 1 < argc) printf("\n");
            } else {
                printf("%s\n", argv[i]);
            }
        }
    }

    return status;
}
