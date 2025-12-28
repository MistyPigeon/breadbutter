#include <stdio.h>
#include <ctype.h>

int wc_main(int argc, char **argv) {
    FILE *fp;
    int c, i = 1;
    long nl, nw, nb;

    do {
        fp = (argc == 1) ? stdin : fopen(argv[i], "r");
        if (!fp) continue;
        nl = nw = nb = 0;
        int inw = 0;
        while ((c = fgetc(fp)) != EOF) {
            nb++;
            if (c == '\n') nl++;
            if (isspace(c)) inw = 0;
            else if (!inw) { inw = 1; nw++; }
        }
        printf("%7ld %7ld %7ld %s\n", nl, nw, nb, argc == 1 ? "" : argv[i]);
        if (fp != stdin) fclose(fp);
    } while (++i < argc);
    return 0;
}
