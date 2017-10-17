#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[]) {
    int fd;
    struct iovec iov[3];

    struct stat st;
    int x;
    #define STR_SIZE 100
    char str[STR_SIZE];

    ssize_t num_read, to_required;

    if (argc != 2 || strcmp(argv[1], "--help") == 0) {
        usage_err("%s, file\n", argv[0]);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        err_exit("open");
    }

    to_required = 0;
    iov[0].iov_base = &st;
    iov[0].iov_len = sizeof(st);
    to_required += iov[0].iov_len;

    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);
    to_required += iov[1].iov_len;

    iov[2].iov_base = str;
    iov[2].iov_len = STR_SIZE;
    to_required += iov[2].iov_len;
    
    num_read = readv(fd, iov, 3);
    if (num_read == -1) {
        err_exit("redv");
    }
    if (num_read < to_required) {
        printf("Read fewer bytes than requested\n");
    }

    printf("total bytes requested: %ld; bytes read: %ld\n", (long) to_required, (long) num_read);

    exit(EXIT_SUCCESS);
}