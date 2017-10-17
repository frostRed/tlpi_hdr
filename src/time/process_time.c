#include <sys/times.h>
#include <time.h>
#include "tlpi_hdr.h"

static void display_process_times(const char* msg) {
    if (msg != NULL) {
        printf("%s", msg);
    }

    static long clock_ticks = 0;
    if (clock_ticks == 0) {
        clock_ticks = sysconf(_SC_CLK_TCK);
        if (clock_ticks == -1) {
            err_exit("sysconf");
        }
    }

    clock_t clock_time = clock();
    if (clock_time == -1) {
        err_exit("clock");
    }
    printf("    clock() returns: %ld clock-per-sec (%.2f secs)\n", (long) clock_time, (double) clock_time / CLOCKS_PER_SEC);

    struct tms t;
    if (times(&t) == -1) {
        err_exit("times");
    }
    printf("    times() yields: user CPU=%.2f; system CPU: %.2f\n", (double) t.tms_utime / clock_ticks,
            (double) t.tms_stime / clock_ticks);
}

int main(int argc, char* argv[]) {
    printf("CLOCK_PER_SEC=%ld sysconf(_SC_CLK_TCK)=%ld\n\n", (long) CLOCKS_PER_SEC, sysconf(_SC_CLK_TCK));

    display_process_times("At program start:\n");

    int numCalls = (argc > 1) ? get_int(argv[1], GN_GT_0, "num-calls"): 100000000;
    for (int j = 0; j != numCalls; ++j) {
        (void) getppid();
    }

    display_process_times("After getppid() loop:\n");
    return 0;
}