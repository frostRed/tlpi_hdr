#include "tlpi_hdr.h"
#include <fcntl.h>


int main(int argc, char* argv[]) {
    int num = 10;

    int fd;
    int opt;
    char* nptr = NULL;
    while ((opt = getopt(argc, argv, ":n:")) != -1) {
        switch (opt) {
            case 'n':
                nptr = optarg;
                break;
            case ':':
                // -n 缺少参数
            case '?':
                // -a 未知选项 
                usage_err("%s [-n num]", argv[0]);
                break;
            default:
                fatal("getopt");
        }
    }

    if (nptr != NULL) {
        num = atoi(nptr);
    }
    if (optind < argc) {
        fd = open(argv[optind], O_RDONLY);
        if (fd == -1) {
            err_exit("open");
        }
    }

    // 定位到最末字节
    if (lseek(fd, -1, SEEK_END) == -1) {
        err_exit("lseek");
    }

    char buf[2];
    buf[1] = '\0';
    // 若最末字节为回车，则这个回车不算，统计的回车个数要加 1
    if (read(fd, buf, 1) == -1) {
        err_exit("read");
    }
    // 注意 read 后 lseek 已经往后走了一个字节
    if (lseek(fd, -1, SEEK_CUR) == -1) {
        err_exit("lseek");
    }
    if (strcmp(buf, "\n") == 0) {
        ++num;
    }

    // 统计回车个数
    int cnt = 0;
    Boolean enough_rows = FALSE;
    while (TRUE) {
        if (lseek(fd, 0, SEEK_CUR) == 0) {
            break;
        }

        if (read(fd, buf, 1) == -1) {
            err_exit("read");
        }
        if (strcmp(buf, "\n") == 0) {
            ++cnt;
            if (cnt == num) {
                enough_rows = TRUE;
                break;
            }
        }

        if (lseek(fd, -2, SEEK_CUR) == -1) {
            err_exit("lseek");
        }
    }

    // 要区分是回车全找到了，还是已经到起始位置才跳出循环的
    if (enough_rows) {
        if (lseek(fd, 1, SEEK_CUR) == -1) {
            err_exit("lseek");
        }
    }

    char lineBuf[512 + 1];
    ssize_t  num_read;
    while ((num_read = read(fd, lineBuf, 512)) != -1) {
        if (num_read == 0) {
            break;
        }
        lineBuf[num_read] = '\0';
        if (write(STDOUT_FILENO, lineBuf, num_read) != num_read) {
            err_exit("write");
        }
    }
    if (num_read == -1) {
        err_exit("read");
    }
}