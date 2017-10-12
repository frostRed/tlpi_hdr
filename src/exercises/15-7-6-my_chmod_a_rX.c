#include <sys/stat.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[]) {
    if (argc == 1 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s file...", argv[0]);
    }

    struct stat sb;
    for (int i = 1; i != argc; ++i) {
        if (stat(argv[i], &sb) == -1) {
            errExit("stat");
        }

        // 全部赋予可读权限
        mode_t mode = sb.st_mode | S_IRUSR | S_IRGRP | S_IROTH;

        if (S_ISREG(sb.st_mode) ||
            (sb.st_mode & S_IXUSR) || (sb.st_mode & S_IXGRP) || (sb.st_mode & S_IXOTH)) {

            mode = mode | S_IXUSR | S_IXGRP | S_IXOTH;
            if (chmod(argv[i], mode) == -1) {
                errExit("chmod");
            }
        }
    }
    return 0;
}