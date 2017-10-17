#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[]) {
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        usage_err("%s filename num-bytes [x]", argv[0]);
    }

    int fd;
    if (argc == 3) {
        fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
        int num_bytes = atoi(argv[2]);
        if (num_bytes < 0) {
            err_exit("num-bytes must >= 0\n");
        }
        for (int i = 0; i != num_bytes; ++i) {
            if (write(fd, "x", 1) == -1) {
                err_exit("write");
            }
        }
    }
    else if (argc == 4 && strcmp(argv[3], "x") == 0) {
        fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        int num_bytes = atoi(argv[2]);
        if (num_bytes < 0) {
            err_exit("num-bytes must >= 0\n");
        }
        for (int i = 0; i != num_bytes; ++i) {
            if (lseek(fd, 0, SEEK_END) == -1) {
                err_exit("lseek");
            }
            if (write(fd, "x", 1) == -1) {
                err_exit("write");
            }
        }
    }
    else {
        usage_err("%s only need 3 or 4 arguments", argv[0]);
    }

    exit(EXIT_SUCCESS);
}