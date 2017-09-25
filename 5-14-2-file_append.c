#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
// 如果文件以O_APPEND标志打开，则lseek对该文件的写将不起作用
// 因为无论lseek怎样调整当前文件偏移量，在写入时仍然会被设为文件长度而将内容添加在文件尾
// 但是，对于读来说，O_APPEND就不起作用了
int main(int argc, char* argv[]) {
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s filename\n", argv[0]);
    }

    int fd;
    fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND);
    if (fd == -1) {
        errExit("open");
    }
    if (lseek(fd, 0, SEEK_SET) == -1) {
        errExit("lseek");
    }
    if (write(fd, "test", 4) == -1) {
        errExit("write");
    }
    if(close(fd) == -1) {
        errExit("close");
    }

    exit(EXIT_SUCCESS);
}
