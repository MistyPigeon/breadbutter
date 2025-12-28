#include <stdio.h>
#include <unistd.h>

extern char **environ;

int env_main(int argc, char **argv) {
    if (argc == 1) {
        for (char **e = environ; *e; e++)
            printf("%s\n", *e);
        return 0;
    }
    execvp(argv[1], &argv[1]);
    return 1;
}
