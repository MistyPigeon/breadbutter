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
    {"echo", echo_main},     {"mkdir", mkdir_main},
    {"cat", cat_main},       {"ls", ls_main},
    {"rm", rm_main},         {"pwd", pwd_main},
    {"chmod", chmod_main},   {"cz", cz_main},
    {"touch", touch_main},   {"ln", ln_main},
    {"cp", cp_main},         {"mv", mv_main},
    {"head", head_main},     {"tail", tail_main},
    {"grep", grep_main},     {"df", df_main},
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
