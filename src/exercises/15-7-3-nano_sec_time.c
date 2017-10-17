#define _BSD_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "file_perms.h"
#include <tlpi_hdr.h>

static void displayStatInfo(const struct stat* sb) {
    printf("File type:      ");
    switch (sb->st_mode & S_IFMT) {
        case S_IFREG: printf("regular file\n"); break;
        case S_IFDIR: printf("directory\n"); break;
        case S_IFCHR: printf("character device\n"); break;
        case S_IFBLK: printf("block device\n"); break;
        case S_IFLNK: printf("symbolic (soft) link\n"); break;
        case S_IFIFO: printf("FIFO or pipe\n"); break;
        case S_IFSOCK: printf("socket\n"); break;
        default: printf("unknown file type?\n");
    }

    printf("Device containing i-node: major=%ld minor=%ld\n", (long) major(sb->st_dev), (long) minor(sb->st_dev));
    printf("I-node number:  %ld\n", (long) sb->st_ino);
    printf("Mode:   %lo (%s)\n", (unsigned long) sb->st_mode, file_perm_str(sb->st_mode, 0));

    if (sb->st_mode & (S_ISUID | S_ISGID | S_ISVTX)) {
        printf("    special bits set:   %s%s%s\n", (sb->st_mode & S_ISUID) ? "set-UID" : "",
            (sb->st_mode & S_ISGID) ? "set-GID" : "",
            (sb->st_mode & S_ISVTX ? "sticky" : ""));
    }

    printf("Number of (hard) links: %ld\n", (long) sb->st_nlink);
    printf("Ownership:  UID=%ld GID=%ld\n", (long) sb->st_uid, (long) sb->st_gid);

    if (S_ISCHR(sb->st_mode) || S_ISBLK(sb->st_mode)) {
        printf("Device number (st_rdev): major=%ld; minor=%ld\n", (long) major(sb->st_rdev), (long) minor(sb->st_rdev));
    }

    printf("File size:  %lld bytes\n", (long long) sb->st_size);
    printf("Optimal I/O block size: %ld bytes\n", (long) sb->st_blksize);
    printf("512B bolcks allocated:  %lld\n", (long long) sb->st_blocks);

    struct tm* nowtm;
    char tmbuf[64];
    nowtm = localtime(&sb->st_atime);
    size_t num = strftime(tmbuf, sizeof tmbuf, "%a %b %d %X %Y", nowtm);
    if (num == 0) {
        err_exit("strftime");
    } 
    printf("Last file access:   %s.%.9ld\n", tmbuf, sb->st_atim.tv_nsec);

    nowtm = localtime(&sb->st_mtime);
    num = strftime(tmbuf, sizeof tmbuf, "%a %b %d %X %Y", nowtm);
    if (num == 0) {
        err_exit("strftime");
    } 
    printf("Last file modification:   %s.%.9ld\n", tmbuf, sb->st_mtim.tv_nsec);

    nowtm = localtime(&sb->st_ctime);
    num = strftime(tmbuf, sizeof tmbuf, "%a %b %d %X %Y", nowtm);
    if (num == 0) {
        err_exit("strftime");
    } 
    printf("Last status change:   %s.%.9ld\n", tmbuf, sb->st_ctim.tv_nsec);
}

int main(int argc, char* argv[]) {
    Boolean statLink = (argc > 1) && strcmp(argv[1], "-l") == 0;
    int fname = statLink ? 2 : 1;
    if (fname >= argc || (argc > 1 && strcmp(argv[1], "--help") == 0)) {
        usage_err("%s [-l] file\n" " -l = use lstat() instead of stat()\n", argv[0]);
    }

    struct stat sb;
    if (statLink) {
        if (lstat(argv[fname], &sb) == -1) {
            err_exit("lstat");
        }
    }
    else {
        if (stat(argv[fname], &sb) == -1) {
            err_exit("stat");
        }
    }
    displayStatInfo(&sb);
}