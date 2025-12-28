#include <stdio.h>
#include <string.h>

int diff_main(int argc, char **argv) {
    char b1[2048], b2[2048];
    FILE *f1, *f2;
    if (argc < 3) return 1;
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "r");
    if (!f1 || !f2) return 1;
    while (fgets(b1, sizeof(b1), f1) && fgets(b2, sizeof(b2), f2)) {
        if (strcmp(b1, b2)) printf("< %s> %s", b1, b2);
    }
    fclose(f1); fclose(f2);
    return 0;
}
