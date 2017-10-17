#include "tlpi_hdr.h"

static void fpathconf_print(const char* msg, int fd, int name) {
    errno = 0;
    long lim = fpathconf(fd, name);
    if (lim != -1) {
        printf("%s %ld\n", msg, lim);
    }
    else {
        if (errno == 0) {
            printf("%s (indeterminate)\n", msg);
        }
        else {
            err_exit("fpathconf %s", msg);
        }
    }
}

int main() {
    fpathconf_print("_PC_NAME_MAX:", STDIN_FILENO, _PC_NAME_MAX);
    fpathconf_print("_PC_PATH_MAX:", STDIN_FILENO, _PC_PATH_MAX);
    fpathconf_print("_PC_PIPE_BUF", STDIN_FILENO, _PC_PIPE_BUF);
}