#include <stdio.h>
#include <stdint.h>

int cksum_main(int argc, char **argv) {
    FILE *fp;
    uint32_t crc = 0;
    int c;
    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "rb");
        if (!fp) continue;
        while ((c = fgetc(fp)) != EOF) crc += c; /* Simplified checksum */
        printf("%u %s\n", crc, argv[i]);
        fclose(fp);
    }
    return 0;
}
