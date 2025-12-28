#include <stdio.h>
#include <unistd.h>

int getconf_main(int argc, char **argv) {
    if (argc < 2) return 1;
    if (strcmp(argv[1], "PATH_MAX") == 0)
        printf("%ld\n", sysconf(_SC_MAX_CANON));
    return 0;
}
