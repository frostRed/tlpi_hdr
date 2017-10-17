#define _GNU_SOURCE
#include <stdlib.h>
#include "tlpi_hdr.h"

extern char** environ;

int main(int argc, char* argv[]) {
    int j;
    char** ep;

    clearenv(); // 相当于 environ = NULL，会有一点内存泄漏
    for (j = 1; j != argc; ++j) {
        if (putenv(argv[j]) != 0) {
            err_exit("putenv: %s", argv[j]);
        }
    }

    if (setenv("GREET", "Hello world", 0) == -1) {
        err_exit("setenv");
    }
    unsetenv("BYE");

    for (ep = environ; *ep != NULL; ++ep) {
        puts(*ep);
    }
    exit(EXIT_SUCCESS);

}