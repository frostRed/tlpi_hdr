#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define ST_NBLOCKSIZE 4096

// todo: 如何区分空洞和故意写入的\0
int main(int argc, char* argv[]) {
    int input_fd, output_fd, open_flags;
    mode_t file_perms;
    ssize_t num_read;
    char buf[ST_NBLOCKSIZE];

    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        usage_err("%s old-file new-file\n", argv[0]);
    }

    struct stat statbuff;  
    if(stat(argv[1], &statbuff) < 0){  
        err_exit("stat");
    }
    Boolean has_hole = FALSE;
    if (S_ISREG (statbuff.st_mode) &&
        statbuff.st_size / ST_NBLOCKSIZE > statbuff.st_blocks) {
               has_hole = TRUE;
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

    char zero[ST_NBLOCKSIZE] = {0};
    while ((num_read = read(input_fd, buf, ST_NBLOCKSIZE)) > 0) {
        // 若全是 0，则认为这一次读到的全是洞，那就只需 lseek，不用写数据
        if (has_hole && memcmp(buf, zero, num_read) == 0) {
            lseek(output_fd, num_read, SEEK_CUR);
        }
        else if (write(output_fd, buf, num_read) != num_read) {
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