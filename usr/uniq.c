#include <stdio.h>
#include <string.h>

int uniq_main(int argc, char **argv) {
    char cur[2048], prev[2048] = "";
    FILE *fp = (argc > 1) ? fopen(argv[1], "r") : stdin;
    if (!fp) return 1;
    while (fgets(cur, sizeof(cur), fp)) {
        if (strcmp(cur, prev)) {
            fputs(cur, stdout);
            strcpy(prev, cur);
        }
    }
    if (fp != stdin) fclose(fp);
    return 0;
}
