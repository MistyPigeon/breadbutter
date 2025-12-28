#include <stdio.h>
#include <signal.h>

int tee_main(int argc, char **argv) {
    int c, i;
    FILE *fps[argc];
    fps[0] = stdout;
    for (i = 1; i < argc; i++) fps[i] = fopen(argv[i], "w");
    while ((c = getchar()) != EOF) {
        for (i = 0; i < argc; i++) if (fps[i]) fputc(c, fps[i]);
    }
    for (i = 1; i < argc; i++) if (fps[i]) fclose(fps[i]);
    return 0;
}
