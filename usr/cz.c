#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

static void cz_compress(FILE *in, FILE *out) {
    unsigned char buf[128];
    int c, next, i;

    fwrite("CZ1", 1, 3, out);

    c = fgetc(in);
    while (c != EOF) {
        buf[0] = (unsigned char)c;
        next = fgetc(in);

        if (next == c) {
            int count = 2;
            while (count < 127 && (next = fgetc(in)) == c) count++;
            unsigned char header = (unsigned char)(count | 0x80);
            fputc(header, out);
            fputc((unsigned char)c, out);
            c = next;
        } else {
            int count = 1;
            while (count < 127 && next != EOF) {
                int peek = fgetc(in);
                if (peek == next) {
                    ungetc(peek, in);
                    break;
                }
                buf[count++] = (unsigned char)next;
                next = peek;
            }
            fputc((unsigned char)count, out);
            fwrite(buf, 1, count, out);
            c = next;
        }
    }
}

static void cz_decompress(FILE *in, FILE *out) {
    char magic[3];
    int header, c;

    if (fread(magic, 1, 3, in) != 3 || memcmp(magic, "CZ1", 3) != 0) {
        fprintf(stderr, "cz: invalid format\n");
        return;
    }

    while ((header = fgetc(in)) != EOF) {
        if (header & 0x80) {
            int count = header & 0x7F;
            if ((c = fgetc(in)) != EOF) {
                for (int i = 0; i < count; i++) fputc(c, out);
            }
        } else {
            for (int i = 0; i < header; i++) {
                if ((c = fgetc(in)) != EOF) fputc(c, out);
            }
        }
    }
}

int cz_main(int argc, char **argv) {
    int dflag = 0, opt;
    FILE *in = stdin, *out = stdout;

    optind = 1;
    while ((opt = getopt(argc, argv, "d")) != -1) {
        if (opt == 'd') dflag = 1;
        else return 1;
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
    return 0;
}
}
