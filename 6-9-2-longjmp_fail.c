#include <setjmp.h>

static jmp_buf env;

static void f1() {
    int i = 1000;
    char buf[1000]; //不加这个打乱栈枕，程序是可以正常运行的
    setjmp(env);
}
static void f2() {
    int j = 9;
    longjmp(env ,1);
    j = 9999;
}
int main() {
    f1();
    f2();
    return 0;
}