#include <stdio.h>
#include <stdlib.h>

char gloBuff[65535];
int primes[] = {2, 3, 5, 7};

static int square(int x) {
    int result;
    result = x * x;
    return result;
}

static void doCalc(int val) {
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
    doCalc(key);
    printf("gloBuf: %p \t primes: %p \t square: %p \t doCalc: %p\n", gloBuff, primes, square, doCalc);
    printf("key: %p \t mbuf: %p \t p: %p\n", &key, mbuf, p);
    exit(EXIT_SUCCESS);
}