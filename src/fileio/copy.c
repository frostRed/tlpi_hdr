#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char* argv[]) {
    int input_fd, output_fd, open_flags;
    mode_t file_perms;
    ssize_t num_read;
    char buf[BUF_SIZE];

    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        usage_err("%s old-file new-file\n", argv[0]);
    }

    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1) {
        err_exit("opening file %s", argv[1]);
    }

    open_flags = O_CREAT | O_WRONLY | O_TRUNC;
    // rw-rw-rw，分别为用户、群组、其他人
    file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;

    output_fd = open(argv[2], open_flags, file_perms);
    if (output_fd == -1) {
        err_exit("opening file %s", argv[2]);
    }

    while ((num_read = read(input_fd, buf, BUF_SIZE)) > 0) {
        if (write(output_fd, buf, num_read) != num_read) {
            fatal("couldn't write whole buffer");
        }
    }
    if (num_read == -1) {
        err_exit("read");
    }

    if (close(input_fd) == -1) {
        err_exit("close input");
    }
    if (close(output_fd) == -1) {
        err_exit("close output");
    }
    exit(EXIT_SUCCESS);
}