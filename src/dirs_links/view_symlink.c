#include "tlpi_hdr.h"
#include <limits.h>
#include <sys/stat.h>

#define BUF_SIZE PATH_MAX

int main(int argc, char* argv[])
{
    if (argc != 2 || strcmp(argv[1], "--hlep") == 0) {
        usage_err("%s pathname\n", argv[0]);
    }

    struct stat stat_buf;
    if (lstat(argv[1], &stat_buf) == -1) {
        err_exit("lstat");
    }
    if (!S_ISLNK(stat_buf.st_mode)) {
        fatal("%s is not symbolic link", argv[1]);
    }

    char buf[BUF_SIZE];
    ssize_t num_bytes = readlink(argv[1], buf, BUF_SIZE - 1);
    if (num_bytes == -1) {
        err_exit("readlink");
    }
    buf[num_bytes] = '\0';
    printf("readlink: %s --> %s\n", argv[1], buf);

    // todo: `ln -s README ./build/readme`
    // `./build/view_symlink ./build/readme` realpath 会报错
    if (realpath(argv[1], buf) == NULL) {
        err_exit("realpath");
    }
    printf("realpath: %s -->  %s\n", argv[1], buf);

    exit(EXIT_SUCCESS);
}
