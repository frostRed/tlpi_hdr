#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char* argv[]) {
    size_t len;
    int fd = -2;
    char buf[BUF_SIZE];
    ssize_t num_read, num_written;

    int openFlags = O_RDWR | O_CREAT | O_TRUNC;
    int opt;
    while ((opt = getopt(argc, argv, ":a")) != -1) {
        switch (opt) {
            case 'a':
                openFlags = O_RDWR | O_CREAT | O_APPEND;
                break;
            case ':':
                cmd_line_err("Option -%c miss argument", optopt);
                break;
            case '?':
                cmd_line_err("-%c is unrecognized option", optopt);
                break;
            default:
                fatal("Unexpected case in switch()");
        }
    }

    fd = open(argv[optind], openFlags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    if (fd == -1) {
        err_exit("open");
    }

    while ((num_read = read(STDIN_FILENO, buf, BUF_SIZE)) != -1) {
        if ((num_written = write(fd, buf, num_read)) != num_read) {
            err_exit("write");
        }
    }

    if (close(fd) == -1) {
        err_exit("close output");
    }

    exit(EXIT_SUCCESS);

}