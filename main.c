#include <stdio.h>
#include <string.h>
#include <libgen.h>


int echo_main(int argc, char **argv);
int mkdir_main(int argc, char **argv);
int cat_main(int argc, char **argv);
int ls_main(int argc, char **argv);
int rm_main(int argc, char **argv);
int pwd_main(int argc, char **argv);
int chmod_main(int argc, char **argv);
int cz_main(int argc, char **argv);
int touch_main(int argc, char **argv);
int ln_main(int argc, char **argv);
int cp_main(int argc, char **argv);
int mv_main(int argc, char **argv);
int head_main(int argc, char **argv);
int tail_main(int argc, char **argv);
int grep_main(int argc, char **argv);
int df_main(int argc, char **argv);

struct applet {
    const char *name;
    int (*func)(int argc, char **argv);
};

/* The dispatch table */
struct applet applets[] = {
    {"echo", echo_main}, {"mkdir", mkdir_main}, {"cat", cat_main},
    {"ls", ls_main}, {"rm", rm_main}, {"pwd", pwd_main},
    {"chmod", chmod_main}, {"cz", cz_main}, {"touch", touch_main},
    {"ln", ln_main}, {"cp", cp_main}, {"mv", mv_main},
    {"head", head_main}, {"tail", tail_main}, {"grep", grep_main},
    {"df", df_main}, {"true", true_main}, {"false", false_main},
    {"id", id_main}, {"kill", kill_main}, {"date", date_main},
    {"du", du_main}, {"uname", uname_main}, {"sleep", sleep_main},
    {"basename", basename_main}, {"dirname", dirname_main}, {"env", env_main},
    {"wc", wc_main}, {"tee", tee_main}, {"uniq", uniq_main},
    {"whoami", whoami_main}, {"printf", printf_main}, {"tr", tr_main},
    {"find", find_main}, {"comm", comm_main}, {"cut", cut_main},
    {"logname", logname_main}, {"nohup", nohup_main}, {"sort", sort_main},
    {"xargs", xargs_main}, {"sed", sed_main}, {"awk", awk_main},
    {"alias", alias_main}, {"unalias", unalias_main}, {"cal", cal_main},
    {"cd", cd_main}, {"cksum", cksum_main}, {"diff", diff_main},
    {"getconf", getconf_main}, {"logger", logger_main}, {"mesg", mesg_main},
    {"pathchk", pathchk_main}, {"time", time_main}, {"expr", expr_main},
    {"test", test_main}, {"tty", tty_main}, {"dd", dd_main}, {"ps", ps_main},
    {NULL, NULL}
};


int main(int argc, char **argv) {
    char *name = basename(argv[0]);

    for (int i = 0; applets[i].name != NULL; i++) {
        if (strcmp(name, applets[i].name) == 0) {
            return applets[i].func(argc, argv);
        }
    }

    printf("err: command '%s' not found\n", name);
    return 1;
}
