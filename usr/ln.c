#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int ln_main(int argc, char **argv) {
    int sflag = 0, opt;
    int (*linkfunc)(const char *, const char *);

    optind = 1;
    while ((opt = getopt(argc, argv, "s")) != -1) {
        if (opt == 's') sflag = 1;
        else return 1;
    }

    if (argc - optind < 2) {
        fprintf(stderr, "usage: ln [-s] target linkname\n");
        return 1;
    }

    linkfunc = sflag ? symlink : link;

    if (linkfunc(argv[optind], argv[optind + 1]) < 0) {
        fprintf(stderr, "ln: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
