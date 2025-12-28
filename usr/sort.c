#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sort_compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int sort_main(int argc, char **argv) {
    char *lines[10240];
    char buf[2048];
    int n = 0;
    while (n < 10240 && fgets(buf, sizeof(buf), stdin)) {
        lines[n++] = strdup(buf);
    }
    qsort(lines, n, sizeof(char *), sort_compare);
    for (int i = 0; i < n; i++) {
        fputs(lines[i], stdout);
        free(lines[i]);
    }
    return 0;
}
