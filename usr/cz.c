#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

static void cz_compress(FILE *in, FILE *out) {
    int current, next, count;

    fwrite("CZ0", 1, 3, out);

    current = fgetc(in);
    while (current != EOF) {
        count = 1;
        while ((next = fgetc(in)) == current && count < 255) {
            count++;
        }
        fputc((unsigned char)count, out);
        fputc((unsigned char)current, out);
        current = next;
    }
}

static void cz_decompress(FILE *in, FILE *out) {
    char magic[3];
    int count, data;

    if (fread(magic, 1, 3, in) != 3 || memcmp(magic, "CZ0", 3) != 0) {
        fprintf(stderr, "cz: not a cz file\n");
        return;
    }

    while ((count = fgetc(in)) != EOF) {
        if ((data = fgetc(in)) == EOF) break;
        for (int i = 0; i < count; i++) {
            fputc(data, out);
        }
    }
}

int cz_main(int argc, char **argv) {
    int dflag = 0, opt;
    FILE *in = stdin, *out = stdout;

    optind = 1;
    while ((opt = getopt(argc, argv, "d")) != -1) {
        switch (opt) {
            case 'd': dflag = 1; break;
            default: fprintf(stderr, "usage: cz [-d] [file]\n"); return 1;
        }
    }

    if (argv[optind]) {
        in = fopen(argv[optind], "rb");
        if (!in) {
            fprintf(stderr, "cz: %s: %s\n", argv[optind], strerror(errno));
            return 1;
        }
    }

    if (dflag) cz_decompress(in, out);
    else cz_compress(in, out);

    if (in != stdin) fclose(in);
    fflush(out);

    return 0;
}
