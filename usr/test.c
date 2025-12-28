#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int test_main(int argc, char **argv) {
    if (argc < 2) return 1;
    if (strcmp(argv[1], "-f") == 0 && argc > 2) {
        struct stat st;
        return (stat(argv[2], &st) == 0 && S_ISREG(st.st_mode)) ? 0 : 1;
    }
    if (argc == 4 && strcmp(argv[2], "=") == 0) {
        return (strcmp(argv[1], argv[3]) == 0) ? 0 : 1;
    }
    return 0;
}
