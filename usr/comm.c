#include <stdio.h>
#include <string.h>

int comm_main(int argc, char **argv) {
    char b1[2048], b2[2048];
    FILE *f1, *f2;
    if (argc < 3) return 1;
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "r");
    if (!f1 || !f2) return 1;

    char *l1 = fgets(b1, sizeof(b1), f1);
    char *l2 = fgets(b2, sizeof(b2), f2);

    while (l1 || l2) {
        int diff = (l1 && l2) ? strcmp(l1, l2) : (l1 ? -1 : 1);
        if (diff == 0) {
            printf("\t\t%s", l1);
            l1 = fgets(b1, sizeof(b1), f1);
            l2 = fgets(b2, sizeof(b2), f2);
        } else if (diff < 0) {
            printf("%s", l1);
            l1 = fgets(b1, sizeof(b1), f1);
        } else {
            printf("\t%s", l2);
            l2 = fgets(b2, sizeof(b2), f2);
        }
    }
    fclose(f1); fclose(f2);
    return 0;
}
