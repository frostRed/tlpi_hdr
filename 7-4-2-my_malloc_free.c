#include "tlpi_hdr.h"

#include <unistd.h>
#include <stdio.h>

// todo: malloc一开始就有 128KB 的大小，怎么可移植地获取堆起始地址
extern char etext, edata, end;
int main() {
    printf("etext=%10p\tedata=%10p\tend=%10p\tsbrk=%10p\n", &etext, &edata, &end, sbrk(0));
    printf("%10p\n", sbrk(0) - (void *)&end);
    void* p = malloc(1);
    printf("%10p\n", sbrk(0) - p);
    return 0;
}