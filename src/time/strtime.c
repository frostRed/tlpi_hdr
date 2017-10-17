#define _XOPEN_SOURCE
#include <time.h>
#include <locale.h>
#include "tlpi_hdr.h"

#define SBUF_SIZE 1000

int main(int argc, char* argv[]) {
    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        usage_err("%s input-date-time in-format [out-format]\n", argv[0]);
    }
    if (setlocale(LC_ALL, "") == NULL) {
        err_exit("setlocale");
    }

    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    if (strptime(argv[1], argv[2], &tm) == NULL) {
        fatal("strptime");
    }

    tm.tm_isdst = -1;
    printf("calendar time (seconds sin Epoch): %ld\n", (long) mktime(&tm));

    char* ofmt = (argc > 3) ? argv[3] : "%H:%M:%S %A, %d %B %Y %Z";
    char sbuf[SBUF_SIZE];
    if (strftime(sbuf, SBUF_SIZE, ofmt, &tm) == 0) {
        fatal("strftime returned 0");
    }
    printf("strftime() yields: %s\n", sbuf);

    return 0;
}