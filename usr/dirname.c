#include <stdio.h>
#include <libgen.h>

int dirname_main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: dirname path\n");
        return 1;
    }
    printf("%s\n", dirname(argv[1]));
    return 0;
}
