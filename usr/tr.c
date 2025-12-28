#include <stdio.h>
#include <string.h>

int tr_main(int argc, char **argv) {
    if (argc < 3) return 1;
    int c;
    char map[256];
    for (int i = 0; i < 256; i++) map[i] = i;
    for (int i = 0; argv[1][i] && argv[2][i]; i++)
        map[(unsigned char)argv[1][i]] = argv[2][i];
    while ((c = getchar()) != EOF) putchar(map[c]);
    return 0;
}
