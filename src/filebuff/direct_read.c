#define _GNU_SOURCE
#include <fcntl.h>
#include <malloc.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[]) {
    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        usage_err("%s file length [offset [alignment]]\n", argv[0]);
    }

    size_t length = get_long(argv[2], GN_ANY_BASE, "length");
    off_t offset = (argc > 3) ? get_long(argv[2], GN_ANY_BASE, "offset") : 0;
    size_t alignment = (argv > 4) ? get_long(argv[4], GN_ANY_BASE, "alignment") : 4096;

    int fd = open(argv[1], O_RDONLY | O_DIRECT);
    if (fd == -1) {
        err_exit("open");
    }

    void* buf = (char*) memalign(alignment * 2, length + alignment) + alignment;
    if (buf == NULL) {
        err_exit("memalign");
    }

    if (lseek(fd, offset, SEEK_SET) == -1) {
        err_exit("lseek");
    }

    ssize_t num_read = read(fd, buf, length);
    if (num_read == -1) {
        err_exit("read");
    }
    printf("Read %ld bytes\n", (long) num_read);
}