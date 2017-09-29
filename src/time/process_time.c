#include <sys/times.h>
#include <time.h>
#include "tlpi_hdr.h"

static void displayProcessTimes(const char* msg) {
    if (msg != NULL) {
        printf("%s", msg);
    }

    static long clockTicks = 0;
    if (clockTicks == 0) {
        clockTicks = sysconf(_SC_CLK_TCK);
        if (clockTicks == -1) {
            errExit("sysconf");
        }
    }

    clock_t clockTime = clock();
    if (clockTime == -1) {
        errExit("clock");
    }
    printf("    clock() returns: %ld clock-per-sec (%.2f secs)\n", (long) clockTime, (double) clockTime / CLOCKS_PER_SEC);

    struct tms t;
    if (times(&t) == -1) {
        errExit("times");
    }
    printf("    times() yields: user CPU=%.2f; system CPU: %.2f\n", (double) t.tms_utime / clockTicks,
            (double) t.tms_stime / clockTicks);
}

int main(int argc, char* argv[]) {
    printf("CLOCK_PER_SEC=%ld sysconf(_SC_CLK_TCK)=%ld\n\n", (long) CLOCKS_PER_SEC, sysconf(_SC_CLK_TCK));

    displayProcessTimes("At program start:\n");

    int numCalls = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-calls"): 100000000;
    for (int j = 0; j != numCalls; ++j) {
        (void) getppid();
    }

    displayProcessTimes("After getppid() loop:\n");
    return 0;
}