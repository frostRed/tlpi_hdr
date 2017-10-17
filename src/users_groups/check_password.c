// 读取 shadow password file 需要 sudo
// crypt() 编译时需要加 -lcrypt 参数
#define _DEFAULT_SOURCE // 从 unistd.h 中获取 getpass()
#define _XOPEN_SOURCE // 从 unistd.h 中获取 crypt()

#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[]) {
    // 获取用户名最大长度
    long lnmax = sysconf(_SC_LOGIN_NAME_MAX);
    if (lnmax == -1) {
        lnmax = 256;
    }

    char* username = malloc(lnmax);
    if (username == NULL) {
        err_exit("malloc");
    }
    printf("Username: ");
    fflush(stdout);
    if (fgets(username, lnmax, stdin) == NULL) {
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(username);
    if (username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    // 获取输入的密码
    struct passwd* pwd = getpwnam(username);
    if (pwd == NULL) {
        fatal("couldn't get password record");
    }

    struct spwd* spwd = getspnam(username);
    if (spwd == NULL && errno == EACCES) {
        fatal("no permission to read shadow password file");
    }
    if (spwd != NULL) {
        pwd->pw_passwd = spwd->sp_pwdp;
    }

    char* password = getpass("Password: ");
    char* encrypted = crypt(password, pwd->pw_passwd); // 密文中前两个字母就是 crypt() 第二个参数所需的盐
    for (char*p = password; *p != '\0'; ++p) {
        // 尽快将内存中保存的密码清除
        *p = '\0';
    }

    // 对比验证
    if (encrypted == NULL) {
        err_exit("crypt");
    }
    Boolean authOk = strcmp(encrypted, pwd->pw_passwd) == 0;
    if (!authOk) {
        printf("Incorrect password\n");
        exit(EXIT_FAILURE);
    }
    printf("Successfully authenticated: UID=%ld\n", (long) pwd->pw_uid);

    exit(EXIT_SUCCESS);


}