#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define CMD_SIZE 200
#define BUF_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        usage_err("%s temp-file [num-1kb-blokcs] \n", argv[0]);
    }

    int num_blocks = (argc > 2) ? get_int(argv[2], GN_GT_0, "num-1kb-blokcs") : 100000;
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        err_exit("open");
    }

    if (unlink(argv[1]) == -1) {
        err_exit("unlink");
    }

    char buf[BUF_SIZE];
    for (int j = 0; j != num_blocks; ++j) {
        if (write(fd, buf, BUF_SIZE) != BUF_SIZE) {
            err_exit("partial/failed write");
        }
    }

    char shell_cmd[CMD_SIZE];
    snprintf(shell_cmd, CMD_SIZE, "df -k `dirname %s`", argv[1]);
    system(shell_cmd);

    if (close(fd) == -1) {
        err_exit("close");
    }
    printf("************ Close file descriptor\n");

    system(shell_cmd);
    exit(EXIT_SUCCESS);
}