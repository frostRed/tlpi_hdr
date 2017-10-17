#include "file_perms.h"
#include "tlpi_hdr.h"
#include <fcntl.h>
#include <sys/stat.h>

#define MYFILE "myfile"
#define MYDIR "mydir"
#define FILE_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define DIR_PERMS (S_IRWXU | S_IRWXG | S_IRWXO)
#define UMASK_SETTING (S_IWGRP | S_IXGRP | S_IWOTH | S_IXOTH)

int main(int argc, char* argv[])
{
    umask(UMASK_SETTING);
    int fd = open(MYFILE, O_RDWR | O_CREAT | O_EXCL, FILE_PERMS);
    if (fd == -1) {
        err_exit("open-%s", MYFILE);
    }
    if (mkdir(MYDIR, DIR_PERMS) == -1) {
        err_exit("mkdir-%s", MYDIR);
    }

    mode_t u = umask(0);

    struct stat sb;
    if (stat(MYFILE, &sb) == -1) {
        err_exit("stat-%s", MYFILE);
    }

    printf("Requested file perms: %s\n", file_perm_str(FILE_PERMS, 0));
    printf("Process umask:  %s\n", file_perm_str(u, 0));
    printf("Actual file perms:  %s\n", file_perm_str(sb.st_mode, 0));

    if (stat(MYDIR, &sb) == -1) {
        err_exit("stat-%s", MYDIR);
    }
    printf("Requested dir. perms: %s\n", file_perm_str(DIR_PERMS, 0));
    printf("Process umask:  %s\n", file_perm_str(u, 0));
    printf("Actual dir. perms:  %s\n", file_perm_str(sb.st_mode, 0));

    if (unlink(MYFILE) == -1) {
        err_msg("unlink-%s", MYFILE);
    }
    if (unlink(MYDIR) == -1) {
        err_msg("unlink-%s", MYDIR);
    }

    return 0;
}
