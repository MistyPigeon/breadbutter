#include <stdio.h>
#include <stdlib.h>

int head_main(int argc, char **argv) {
    int n = 10, c;
    FILE *fp = stdin;

    if (argc > 1 && argv[1][0] == '-') n = atoi(&argv[1][1]);
    if (argc > 2) fp = fopen(argv[2], "r");

    if (!fp) return 1;
    while (n > 0 && (c = fgetc(fp)) != EOF) {
        putchar(c);
        if (c == '\n') n--;
    }
    if (fp != stdin) fclose(fp);
    return 0;
}
