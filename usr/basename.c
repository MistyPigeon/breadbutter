#include <stdio.h>
#include <string.h>
#include <libgen.h>

int basename_main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: basename path [suffix]\n");
        return 1;
    }
    char *b = basename(argv[1]);
    if (argc == 3) {
        size_t blen = strlen(b), slen = strlen(argv[2]);
        if (blen > slen && !strcmp(b + blen - slen, argv[2]))
            b[blen - slen] = '\0';
    }
    printf("%s\n", b);
    return 0;
}
