#include <stdio.h>
#include <unistd.h>

int logname_main(int argc, char **argv) {
    char *name = getlogin();
    if (name) {
        printf("%s\n", name);
        return 0;
    }
    return 1;
}
