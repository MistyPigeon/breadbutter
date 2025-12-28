#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int cd_main(int argc, char **argv) {
    const char *path = (argc > 1) ? argv[1] : getenv("HOME");
    if (chdir(path) < 0) {
        fprintf(stderr, "cd: %s: %s\n", path, strerror(errno));
        return 1;
    }
    return 0;
}
