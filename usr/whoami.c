#include <stdio.h>
#include <pwd.h>
#include <unistd.h>

int whoami_main(int argc, char **argv) {
    struct passwd *pw = getpwuid(geteuid());
    if (pw) printf("%s\n", pw->pw_name);
    return 0;
}
