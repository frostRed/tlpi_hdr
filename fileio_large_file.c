#define _LARGEFILE64_SOURCE // 这种方式在 open 和 lseek 后要加 64 后缀
// 更好的方式是不用更改系统调用，只需使用 #define _FILE_OFFSET_BITS 64，这时打印 off_t 时 long 可能不够，最好转为 long long 
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[]) {
    int fd;
    off64_t off;
    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s pathname offset\n", argv[0]);
    }

    fd = open64(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == 1) {
        errExit("open");
    }

    off = atoll(argv[2]);
    if (lseek64(fd, off, SEEK_SET) == -1) {
        errExit("lssek64");
    }

    if (write(fd, "test", 4) == -1) {
        errExit("write");
    }
    exit(EXIT_SUCCESS);
}