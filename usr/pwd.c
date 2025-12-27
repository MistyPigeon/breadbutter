#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

int pwd_main(int argc, char **argv) {
    char buf[PATH_MAX];

    if (getcwd(buf, sizeof(buf))) {
        printf("%s\n", buf);
        return 0;
    }

    fprintf(stderr, "pwd: %s\n", strerror(errno));
    return 1;
}
