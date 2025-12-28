#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cut_main(int argc, char **argv) {
    char line[2048], *p;
    int col = 1;
    if (argc > 1 && argv[1][0] == '-') col = atoi(&argv[1][1]);
    while (fgets(line, sizeof(line), stdin)) {
        int i = 1;
        p = strtok(line, " \t\n");
        while (p) {
            if (i == col) { printf("%s\n", p); break; }
            p = strtok(NULL, " \t\n");
            i++;
        }
    }
    return 0;
}
