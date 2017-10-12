#include <unistd.h>
#include <sys/stat.h>
#include "tlpi_hdr.h"

int my_euidaccess(const char* pathname, int mode);

int main(int argc, char* argv[]) {
    if (argc <=1 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s filename", argv[0]);
    }
    int result = my_euidaccess(argv[1], R_OK);
    // printf("%d\n", result);
    if (result == 0) {
        printf("OK\n");
    }
    return 0;
}
int my_euidaccess(const char* pathname, int mode) {
    struct stat sb;
    int ret = stat(pathname, &sb);
    // F_OK，文件是否存在
    if (mode == 0) {
        // printf("mode=%d\n", mode);
        // printf("ret=%d\n", ret);
        if (ret == 0) {
            return 0;
        }
        else if (ret == -1) {
            return -1;
        }

    }

    uid_t file_uid = sb.st_uid;
    gid_t file_gid = sb.st_gid;

    uid_t proc_euid = geteuid();
    gid_t proc_egid = getegid();

    if (file_uid == proc_egid) {
        mode_t perm = 0;
        switch (mode) {
            case 1: perm = S_IXUSR; break;
            case 2: perm = S_IWUSR; break;
            case 3: perm = S_IXUSR | S_IWUSR; break;
            case 4: perm = S_IRUSR; break;
            case 5: perm = S_IXUSR | S_IRUSR; break;
            case 6: perm = S_IWUSR | S_IRUSR; break;
            case 7: perm = S_IXUSR | S_IWUSR | S_IRUSR; break;
            default: return -1; break;
        }
        if (sb.st_mode & perm) {
            return 0;
        }
        else {
            return -1;
        }
    }
    else if (file_gid == proc_egid) {
        int perm = 0;
        switch (mode) {
            case 1: perm = S_IXGRP; break;
            case 2: perm = S_IWGRP; break;
            case 3: perm = S_IXGRP | S_IWGRP; break;
            case 4: perm = S_IRGRP; break;
            case 5: perm = S_IXGRP | S_IRGRP; break;
            case 6: perm = S_IWGRP | S_IRGRP; break;
            case 7: perm = S_IXGRP | S_IWGRP | S_IRGRP; break;
            default: return -1; break;
        }
        if (sb.st_mode & perm) {
            return 0;
        }
        else {
            return -1;
        }
    }
}