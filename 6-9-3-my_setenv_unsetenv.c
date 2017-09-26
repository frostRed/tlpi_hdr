#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "tlpi_hdr.h"

extern char** environ;
int mysetenv(const char* name, const char* value, int overwrite);
int myunsetenv(const char* name);
int main(int argc, char* argv[]) {
    int j;
    char** ep;

    clearenv(); // 相当于 environ = NULL，会有一点内存泄漏
    for (j = 1; j != argc; ++j) {
        if (putenv(argv[j]) != 0) {
            errExit("putenv: %s", argv[j]);
        }
    }

    if (setenv("GREET", "Hello world", 0) == -1) {
        errExit("setenv");
    }
    unsetenv("BYE");

    for (ep = environ; *ep != NULL; ++ep) {
        puts(*ep);
    }
    exit(EXIT_SUCCESS);
}
int mysetenv(const char* name, const char* value, int overwrite) {
    if (overwrite == 0 && getenv(name) != NULL) {
        return 0;
    }
    size_t name_len = (size_t) strlen(name);
    size_t value_len = (size_t) strlen(value);
    char* key_value = malloc(name_len + value_len + 2);

    strcpy(key_value, name);
    key_value[name_len] = '=';

    strcpy(key_value + name_len + 1, value);
    key_value[name_len + value_len + 1] = '\0';

    if (putenv(key_value) != 0) {
        return -1;
    }
    return 0;
}

int myunsetenv(const char* name) {
    // 环境变量中对同一个 name 可能有多个定义
    while (getenv(name) != NULL) {
        // putenv(中间不带=的字符串)会删除这个环境变量，这是glic的非标准扩展
        // 也可遍历环境变量，然后重建，排除掉所有要删掉的条目
        if (putenv(name) != 0) {
            return -1;
        }
    }
    return 0;
}