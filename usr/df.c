#include <stdio.h>
#include <sys/statvfs.h>

int df_main(int argc, char **argv) {
    struct statvfs s;
    const char *path = (argc > 1) ? argv[1] : ".";

    if (statvfs(path, &s) < 0) return 1;

    unsigned long total = s.f_blocks * s.f_frsize;
    unsigned long free = s.f_bfree * s.f_frsize;
    unsigned long used = total - free;

    printf("Total: %lu KB\nUsed:  %lu KB\nFree:  %lu KB\n", 
            total/1024, used/1024, free/1024);
    return 0;
}
