#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/uio.h>
#include "tlpi_hdr.h"

ssize_t myreadv(int fd, const struct iovec* iov, int iovcnt);
ssize_t mywritev(int fd, const struct iovec* iov, int ivocnt);

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
    
    num_read = myreadv(fd, iov, 3);
    if (num_read == -1) {
        err_exit("redv");
    }
    if (num_read < to_required) {
        printf("Read fewer bytes than requested\n");
    }

    printf("total bytes requested: %ld; bytes read: %ld\n", (long) to_required, (long) num_read);

    exit(EXIT_SUCCESS);
}
ssize_t myreadv(int fd, const struct iovec* iov, int iovcnt) {
    int required = 0;
    for (int i = 0; i != iovcnt; ++i) {
        required += iov[i].iov_len;
    }
    void* tmp_room = malloc(required);

    ssize_t num_read;
    if ((num_read = read(fd, tmp_room, required)) == -1) {
        err_exit("read");
    }
    size_t index = 0;
    for (int i = 0; i != iovcnt && index < num_read; ++i) {
        memcpy(iov[i].iov_base, tmp_room + index, iov[i].iov_len);
        index += iov[i].iov_len;
    }

    free(tmp_room);

    return num_read;
}

ssize_t mywritev(int fd, const struct iovec* iov, int ivocnt) {
    int provided = 0;
    for (int i = 0; i != ivocnt; ++i) {
        provided += iov[i].iov_len;
    }
    void* tmp_room = malloc(provided);
    size_t index = 0;
    for (int i = 0; i != ivocnt; ++i) {
        memcpy(tmp_room + index, iov[i].iov_base, iov[i].iov_len);
        index += iov[i].iov_len;
    }
    ssize_t written = 0;
    if ((written = write(fd, tmp_room, provided)) == -1) {
        err_exit("write");
    }
    free(tmp_room);

    return written;
}