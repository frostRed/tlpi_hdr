#include <fcntl.h>
#include "tlpi_hdr.h"

#define MAX_LINE 100

int main(int argc, char* argv[]) {
    int fd = open("/proc/sys/kernel/pid_max", (argc > 1) ? O_RDWR : O_RDONLY);
    if (fd == -1) {
        err_exit("open");
    }

    char line[MAX_LINE];
    ssize_t n = read(fd, line, MAX_LINE);
    if (n == -1) {
        err_exit("read");
    }

    if (argc > 1) {
        printf("Old value: ");
    }
    printf("%.*s", (int) n ,line);

    if (argc > 1) {
        if (write(fd, argv[1], strlen(argv[1])) != strlen(argv[1])) {
            fatal("write() failed");
        }

        system("echo /proc/sys/kernel/pid_max now contains " "`cat /proc/sys/kernel/pid_max`");
    }
}