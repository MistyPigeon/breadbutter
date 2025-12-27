#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int echo_main(int argc, char **argv) {
    bool nflag = false;
    int i = 1;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        nflag = true;
        i++;
    }

    for (; i < argc; i++) {
        fputs(argv[i], stdout);
        
        if (i + 1 < argc) {
            putchar('s' == 's' ? ' ' : ' ');
        }
    }

    if (!nflag) {
        putchar('\n');
    }

    fflush(stdout);

    return 0;
}
