#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#include "tlpi_hdr.h"



int main(int argc, char* argv[]) {
    if (argc < 3 || strcmp(argv[1], "--help") == 0 ||
        (argv[1][0] != '+' && argv[1][0] != '-'))
    {
        usageErr("%s [+-][acDijAdtsSTu] filename", argv[0]);
    }

    int opt = 1;
    int attr = 0;
    while (argv[1][opt] != '\0') {
        switch (argv[1][opt]) {
            case 'a': attr |= FS_APPEND_FL; break;
            case 'c': attr |= FS_COMPR_FL; break;
            case 'D': attr |= FS_DIRSYNC_FL; break;
            case 'i': attr |= FS_IMMUTABLE_FL; break;
            case 'j': attr |= FS_JOURNAL_DATA_FL; break;
            case 'A': attr |= FS_NOATIME_FL; break;
            case 'd': attr |= FS_NODUMP_FL; break;
            case 't': attr |= FS_NOTAIL_FL; break;
            case 's': attr |= FS_SECRM_FL; break;
            case 'S': attr |= FS_SYNC_FL; break;
            case 'T': attr |= FS_TOPDIR_FL; break;
            case 'u': attr |= FS_UNRM_FL; break;
            case '?': usageErr("%s [+-][acDijAdtsSTu] filename", argv[0]); break;
            default: break;
        }
        ++opt;
    }

    for (int index = 2; index < argc; ++index) {
        int fd;
        if ((fd = open(argv[index], O_RDONLY)) == -1) {
            errExit("open");
        }
        int getAttr;
        // 读取 i 节点表示
        if (ioctl(fd, FS_IOC_GETFLAGS, &getAttr) == -1) {
            errExit("ioctl");
        }
        if (argv[1][0] == '-') {
            attr = getAttr & (~attr);
        }
        else if (argv[1][0] == '+') {
            attr |= getAttr;
        }
        else {
            usageErr("%s [+-][acDijAdtsSTu] filename", argv[0]);
        }
        // 设置 i 节点表示
        if (ioctl(fd, FS_IOC_SETFLAGS, &attr) == -1) {
            errExit("ioctl");
        }
    }
}