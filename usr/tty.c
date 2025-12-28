#include <stdio.h>
#include <unistd.h>

int tty_main(int argc, char **argv) {
    char *t = ttyname(STDIN_FILENO);
    if (t) {
        printf("%s\n", t);
        return 0;
    }
    printf("not a tty\n");
    return 1;
}
