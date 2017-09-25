#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define ST_NBLOCKSIZE 4096

int main(int argc, char* argv[]) {
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[ST_NBLOCKSIZE];

    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s old-file new-file\n", argv[0]);
    }

    struct stat statbuff;  
    if(stat(argv[1], &statbuff) < 0){  
        errExit("stat");
    }
    Boolean has_hole = FALSE;
    if (S_ISREG (statbuff.st_mode) &&
        statbuff.st_size / ST_NBLOCKSIZE > statbuff.st_blocks) {
               has_hole = TRUE;
    }

    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1) {
        errExit("opening file %s", argv[1]);
    }

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    // rw-rw-rw，分别为用户、群组、其他人
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;

    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1) {
        errExit("opening file %s", argv[2]);
    }

    char zero[ST_NBLOCKSIZE] = {0};
    while ((numRead = read(inputFd, buf, ST_NBLOCKSIZE)) > 0) {
        // 若全是 0，则认为这一次读到的全是洞，那就只需 lseek，不用写数据
        if (has_hole && memcmp(buf, zero, numRead) == 0) {
            lseek(outputFd, numRead, SEEK_CUR);
        }
        else if (write(outputFd, buf, numRead) != numRead) {
            fatal("couldn't write whole buffer");
        }
    }
    if (numRead == -1) {
        errExit("read");
    }

    if (close(inputFd) == -1) {
        errExit("close input");
    }
    if (close(outputFd) == -1) {
        errExit("close output");
    }
    exit(EXIT_SUCCESS);
}