#include <locale.h>
#include <time.h>
#include <sys/time.h>
#include "tlpi_hdr.h"

#define SECONDS_INTROPICAL_YEAR (356.24219 * 24 * 60 * 60)

int main(int argc, char* argv[]) {
    time_t t = time(NULL);
    printf("Seconds since the Epoch (1 Jan 1970): %ld", (long) t);
    printf(" (about %6.3f years)\n", t / SECONDS_INTROPICAL_YEAR);

    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1) {
        err_exit("gettimeofday");
    }
    printf(" gettimeofday() return %ld sec, %ld microsecs\n", (long) tv.tv_sec, (long) tv.tv_usec);

    struct tm* gm_ptr = gmtime(&t);
    if (gm_ptr == NULL) {
        err_exit("gmtime");
    }
    struct tm gm = *gm_ptr;
    printf("Broken down by gmtime():\n");
    printf(" year=%d mon=%d mday=%d hour=%d min=%d sec=%d ", gm.tm_year, gm.tm_mon, gm.tm_mday, gm.tm_hour, gm.tm_min, gm.tm_sec);
    printf("wday=%d yday=%d isdst=%d\n", gm.tm_wday, gm.tm_yday, gm.tm_isdst);

    struct tm* loc_ptr = localtime(&t);
    if (loc_ptr == NULL) {
        err_exit("localtime");
    }
    struct tm loc = *loc_ptr;
    printf("Broken down by localtime():\n");
    printf(" year=%d mon=%d mday=%d hour=%d min=%d sec=%d ", loc.tm_year, loc.tm_mon, loc.tm_mday, loc.tm_hour, loc.tm_min, loc.tm_sec);
    printf("wday=%d yday=%d isdst=%d\n", loc.tm_wday, loc.tm_yday, loc.tm_isdst);

    printf("asctime() formats the gmtime() value as: %s", asctime(&gm));
    printf("asctime() formats the time() value as: %s", ctime(&t));

    printf("mktime() of gmtime() value:    %ld secs\n", (long) mktime(&gm));
    printf("mktime() of localtime() value:    %ld secs\n", (long) mktime(&loc));
    return 0;
}