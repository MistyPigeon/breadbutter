#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int awk_main(int argc, char **argv) {
    char line[4096];
    int field_idx = 0;

    if (argc > 1 && argv[1][0] == '{') {
        char *p = strstr(argv[1], "$");
        if (p) field_idx = atoi(p + 1);
    }

    if (field_idx <= 0) {
        fprintf(stderr, "usage: awk '{print $N}'\n");
        return 1;
    }

    while (fgets(line, sizeof(line), stdin)) {
        int current = 1;
        char *token = strtok(line, " \t\n");
        while (token) {
            if (current == field_idx) {
                printf("%s\n", token);
                break;
            }
            token = strtok(NULL, " \t\n");
            current++;
        }
    }
    return 0;
}
