#include <stdio.h>
#include <dirent.h>
#include <string.h>

void find_dir(const char *path) {
    DIR *d = opendir(path);
    if (!d) return;
    struct dirent *de;
    while ((de = readdir(d))) {
        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")) continue;
        printf("%s/%s\n", path, de->d_name);
        char sub[1024];
        snprintf(sub, sizeof(sub), "%s/%s", path, de->d_name);
        if (de->d_type == DT_DIR) find_dir(sub);
    }
    closedir(d);
}

int find_main(int argc, char **argv) {
    find_dir(argc > 1 ? argv[1] : ".");
    return 0;
}
