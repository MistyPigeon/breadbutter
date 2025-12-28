#include <stdio.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <unistd.h>

int time_main(int argc, char **argv) {
    struct tms t1, t2;
    clock_t start, end;
    if (argc < 2) return 1;
    start = times(&t1);
    if (fork() == 0) {
        execvp(argv[1], &argv[1]);
        _exit(1);
    }
    wait(NULL);
    end = times(&t2);
    printf("real %ld\nuser %ld\nsys %ld\n", 
           end - start, t2.tms_cutime - t1.tms_cutime, t2.tms_cstime - t1.tms_cstime);
    return 0;
}
