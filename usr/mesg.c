#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int mesg_main(int argc, char **argv) {
    struct stat st;
    stat(ttyname(STDOUT_FILENO), &st);
    if (argc == 1) {
        printf("is %c\n", (st.st_mode & S_IWGRP) ? 'y' : 'n');
    } else if (argv[1][0] == 'n') {
        chmod(ttyname(STDOUT_FILENO), st.st_mode & ~S_IWGRP);
    } else {
        chmod(ttyname(STDOUT_FILENO), st.st_mode | S_IWGRP);
    }
    return 0;
}
