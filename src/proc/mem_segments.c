#include <stdio.h>
#include <stdlib.h>

char glo_buff[65535];
int primes[] = {2, 3, 5, 7};

static int square(int x) {
    int result;
    result = x * x;
    return result;
}

static void do_calc(int val) {
    printf("The square of %d is %d\n", val, square(val));
    if (val < 1000) {
        int t;
        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int main(int argc, char* argv[]) {
    static int key = 9973;
    static char mbuf[10240000];
    char *p;
    p = malloc(1024);
    do_calc(key);
    printf("gloBuf: %p \t primes: %p \t square: %p \t do_calc: %p\n", glo_buff, primes, square, do_calc);
    printf("key: %p \t mbuf: %p \t p: %p\n", &key, mbuf, p);
    exit(EXIT_SUCCESS);
}