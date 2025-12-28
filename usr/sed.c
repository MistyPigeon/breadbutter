#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sed_subst(const char *line, const char *find, const char *repl) {
    const char *p = line;
    size_t find_len = strlen(find);
    while (*p) {
        const char *match = strstr(p, find);
        if (match) {
            fwrite(p, 1, match - p, stdout);
            fputs(repl, stdout);
            p = match + find_len;
        } else {
            fputs(p, stdout);
            break;
        }
    }
}

int sed_main(int argc, char **argv) {
    char line[4096];
    if (argc < 2 || strncmp(argv[1], "s/", 2) != 0) {
        fprintf(stderr, "usage: sed s/find/replace/g\n");
        return 1;
    }

    char *find = strdup(argv[1] + 2);
    char *delim = strchr(find, '/');
    if (!delim) return 1;
    *delim = '\0';
    char *repl = delim + 1;
    char *end = strchr(repl, '/');
    if (end) *end = '\0';

    while (fgets(line, sizeof(line), stdin)) {
        sed_subst(line, find, repl);
    }
    free(find);
    return 0;
}
