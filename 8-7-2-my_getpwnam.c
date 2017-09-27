#include <pwd.h>
#include <stddef.h>
#include <string.h>

#include <stdio.h>

struct passwd* my_getpwnam(const char* name);
int main() {
    char name[128];
    if (fgets(name, 128, stdin) == NULL) {
        printf("can't input name\n");
    }
    name[strlen(name) - 1] = '\0';

    struct passwd* pwd = my_getpwnam(name);
    if (pwd != NULL) {
        printf("UID = %ld\n", (long) pwd->pw_uid);
    }
    return 0;
}
struct passwd* my_getpwnam(const char* name) {
    struct passwd* pwd;
    while ((pwd = getpwent()) != NULL) {
        if (strcmp(pwd->pw_name, name) == 0) {
            return pwd;
        }
    }
    endpwent();
    return NULL;
}