#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tail_main(int argc, char **argv) {
    char buf[1024][256];
    int n = 10, i = 0, count = 0;
    FILE *fp = stdin;

    if (argc > 2) fp = fopen(argv[2], "r");
    if (!fp) return 1;

    while (fgets(buf[i % 1024], 256, fp)) {
        i++;
        count++;
    }
    
    int start = (count > 10) ? (i - 10) : 0;
    for (int j = 0; j < (count > 10 ? 10 : count); j++) {
        printf("%s", buf[(start + j) % 1024]);
    }

    if (fp != stdin) fclose(fp);
    return 0;
}
