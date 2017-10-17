#include <dirent.h>
#include "tlpi_hdr.h"

static void list_files(const char* dir_path) {
    Boolean is_current = strcmp(dir_path, ".") == 0;
    DIR* dirp = opendir(dir_path);
    if (dirp == NULL) {
        errMsg("opendir failed on '%s'", dir_path);
        return;
    }

    struct dirent* dp = NULL;
    for ( ; ; ) {
        errno = 0;
        dp = readdir(dirp);
        if (dp == NULL) {
            break;
        }

        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            // 跳过目录中的 . 和 .. 两项
            continue;
        }

        if (!is_current) {
            printf("%s/", dir_path);
        }
        printf("%s\n", dp->d_name);
    }

    if (errno != 0) {
        errExit("readdir");
    }
    if (closedir(dirp) == -1) {
        errMsg("closedir");
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        usageErr("%s [dir...]\n", argv[0]);
    }

    if (argc == 1) {
        list_files(".");
    }
    else {
        for (argv++; *argv != NULL; ++argv) {
            list_files(*argv);
        }
    }
    exit(EXIT_SUCCESS);
}