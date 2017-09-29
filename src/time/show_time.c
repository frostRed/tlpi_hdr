#include <time.h>
#include <locale.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 200

int main(int argc, char* argv[]) {
    //setenv("TZ", "Pacific/Auckland", 1);

    if (setlocale(LC_ALL, "") == NULL) {
        errExit("setlocale");
    }

    time_t t = time(NULL);
    printf("ctime() of time() value is: %s", ctime(&t));

    struct tm* loc = localtime(&t);
    if (loc == NULL) {
        errExit("localtime");
    }
    printf("asctime() of local time is    %s", asctime(loc));

    char buf[BUF_SIZE];
    if (strftime(buf, BUF_SIZE, "%A, %d %B %Y, %H:%M:%S %Z", loc) == 0) {
        fatal("strftime returned 0");
    }
    printf("strftime() of local time is: %s\n", buf);
    return 0;
}