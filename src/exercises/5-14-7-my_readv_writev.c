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

    struct stat myStruct;
    int x;
    #define STR_SIZE 100
    char str[STR_SIZE];

    ssize_t numRead, toRequired;

    if (argc != 2 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s, file\n", argv[0]);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        errExit("open");
    }

    toRequired = 0;
    iov[0].iov_base = &myStruct;
    iov[0].iov_len = sizeof(myStruct);
    toRequired += iov[0].iov_len;

    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);
    toRequired += iov[1].iov_len;

    iov[2].iov_base = str;
    iov[2].iov_len = STR_SIZE;
    toRequired += iov[2].iov_len;
    
    numRead = myreadv(fd, iov, 3);
    if (numRead == -1) {
        errExit("redv");
    }
    if (numRead < toRequired) {
        printf("Read fewer bytes than requested\n");
    }

    printf("total bytes requested: %ld; bytes read: %ld\n", (long) toRequired, (long) numRead);

    exit(EXIT_SUCCESS);
}
ssize_t myreadv(int fd, const struct iovec* iov, int iovcnt) {
    int required = 0;
    for (int i = 0; i != iovcnt; ++i) {
        required += iov[i].iov_len;
    }
    void* tmpRoom = malloc(required);

    ssize_t numRead;
    if ((numRead = read(fd, tmpRoom, required)) == -1) {
        errExit("read");
    }
    size_t index = 0;
    for (int i = 0; i != iovcnt && index < numRead; ++i) {
        memcpy(iov[i].iov_base, tmpRoom + index, iov[i].iov_len);
        index += iov[i].iov_len;
    }

    free(tmpRoom);

    return numRead;
}

ssize_t mywritev(int fd, const struct iovec* iov, int ivocnt) {
    int provided = 0;
    for (int i = 0; i != ivocnt; ++i) {
        provided += iov[i].iov_len;
    }
    void* tmpRoom = malloc(provided);
    size_t index = 0;
    for (int i = 0; i != ivocnt; ++i) {
        memcpy(tmpRoom + index, iov[i].iov_base, iov[i].iov_len);
        index += iov[i].iov_len;
    }
    ssize_t written = 0;
    if ((written = write(fd, tmpRoom, provided)) == -1) {
        errExit("write");
    }
    free(tmpRoom);

    return written;
}