#include <syslog.h>
#include <stdio.h>

int logger_main(int argc, char **argv) {
    openlog("mybox", LOG_PID, LOG_USER);
    for (int i = 1; i < argc; i++) syslog(LOG_INFO, "%s", argv[i]);
    closelog();
    return 0;
}
