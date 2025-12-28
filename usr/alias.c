#include <stdio.h>

int alias_main(int argc, char **argv) {
    if (argc == 1) return 0;
    for (int i = 1; i < argc; i++)
        printf("alias %s\n", argv[i]);
    return 0;
}
