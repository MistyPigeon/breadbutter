#include <stdio.h>
#include <dirent.h>
#include <ctype.h>

int ps_main(int argc, char **argv) {
    DIR *d = opendir("/proc");
    struct dirent *de;
    printf("  PID TTY          TIME CMD\n");
    while ((de = readdir(d))) {
        if (isdigit(de->d_name[0])) {
            printf("%5s ?        00:00:00 %s\n", de->d_name, de->d_name);
        }
    }
    closedir(d);
    return 0;
}
