#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

static int cp_file(const char *src, const char *dst) {
    int sfd, dfd;
    char buf[8192];
    ssize_t n;
    struct stat st;

    if ((sfd = open(src, O_RDONLY)) < 0) return -1;
    fstat(sfd, &st);
    if ((dfd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode)) < 0) {
        close(sfd);
        return -1;
    }

    while ((n = read(sfd, buf, sizeof(buf))) > 0) {
        if (write(dfd, buf, n) != n) break;
    }

    close(sfd);
    close(dfd);
    return (n < 0) ? -1 : 0;
}

int cp_main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "usage: cp src dst\n");
        return 1;
    }
    if (cp_file(argv[1], argv[2]) < 0) {
        fprintf(stderr, "cp: %s\n", strerror(errno));
        return 1;
    }
    return 0;
}
