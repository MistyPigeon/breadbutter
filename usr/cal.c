#include <stdio.h>
#include <time.h>

int cal_main(int argc, char **argv) {
    struct tm *t;
    time_t now = time(NULL);
    t = localtime(&now);
    printf("    %d %d\n", t->tm_mon + 1, t->tm_year + 1900);
    printf("Su Mo Tu We Th Fr Sa\n");
    return 0;
}
