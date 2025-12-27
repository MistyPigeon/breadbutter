#include <stdio.h>
#include <sys/utsname.h>
int uname_main(int argc, char **argv) {
    struct utsname u;
    uname(&u);
    printf("%s %s %s %s %s\n", u.sysname, u.nodename, u.release, u.version, u.machine);
    return 0;
}
