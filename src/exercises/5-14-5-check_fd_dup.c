#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[]) {
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s filename\n", argv[0]);
    }
    int fd = open(argv[1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        errExit("open");
    }
    if (lseek(fd, 10, SEEK_CUR) == -1) {
        errExit("lseek");
    }
    
    int newfd = dup(fd);
    printf("fd's seek = %ld, newfd's seek = %ld\n", lseek(fd, 0, SEEK_CUR), lseek(newfd, 0, SEEK_CUR));

    int oldflags = fcntl(fd, F_GETFL);
    int newflags = fcntl(newfd, F_GETFL);
    if (!(oldflags ^ newflags)) {
        printf("fd's flags == newfd's flags\n");
    }

}