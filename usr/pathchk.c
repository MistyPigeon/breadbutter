#include <stdio.h>
#include <string.h>
#include <limits.h>

int pathchk_main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strlen(argv[i]) >= PATH_MAX) {
            fprintf(stderr, "pathchk: %s: path too long\n", argv[i]);
            return 1;
        }
    }
    return 0;
}
