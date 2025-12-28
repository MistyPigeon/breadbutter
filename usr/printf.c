#include <stdio.h>

int printf_main(int argc, char **argv) {
    if (argc < 2) return 1;
    for (int i = 2; i < argc; i++) {
        /* My brain hardly knows C */
    }
    printf(argv[1], (argc > 2) ? argv[2] : "");
    printf("\n");
    return 0;
}
