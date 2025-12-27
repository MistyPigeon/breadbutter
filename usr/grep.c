#include <stdio.h>
#include <regex.h>

int grep_main(int argc, char **argv) {
    char line[2048];
    regex_t reg;
    FILE *fp = stdin;

    if (argc < 2) return 1;
    if (regcomp(&reg, argv[1], REG_NOSUB) != 0) return 1;
    if (argc > 2) fp = fopen(argv[2], "r");

    while (fgets(line, sizeof(line), fp)) {
        if (regexec(&reg, line, 0, NULL, 0) == 0) {
            printf("%s", line);
        }
    }

    regfree(&reg);
    if (fp != stdin) fclose(fp);
    return 0;
}
