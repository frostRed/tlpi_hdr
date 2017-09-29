// sudo chown root proc
// sudo chmod u+s proc
#include <sys/types.h>
#include <grp.h>sudo chown root ./build/debug
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include "tlpi_hdr.h"
#include "ugid_functions.h"

#include <pwd.h>

int my_initgroups(const char* user, gid_t group);

int main() {
    int i = 10;
    char user[128];
    if (fgets(user, 128, stdin) == -1) {
        errExit("fgets");
    }
    user[strlen(user) - 1] = '\0';

    gid_t gid;
    if ((gid = groupIdFromName(user)) == -1) {
        errExit("groupIdFromName");
    }
    if (my_initgroups(user, gid) == -1) {
        errExit("my_initgroups");
    }

    long grouplist_max = sysconf(_SC_NGROUPS_MAX);
    gid_t grouplist[grouplist_max + 1];
    if (getgroups(grouplist_max, grouplist) == -1) {
        errExit("getgroups");
    }
    Boolean has_0 = FALSE;
    for (int i = 0; i != grouplist_max; ++i) {
        if (has_0 && grouplist[i] == 0) break;
        if (grouplist[i] == 0) has_0 = TRUE;
        printf("%ld\n", (long) grouplist[i]);
    }

    exit(EXIT_SUCCESS);
}

int my_initgroups(const char* user, gid_t group) {
    struct group* grp;
    long grouplist_max = sysconf(_SC_NGROUPS_MAX);

    gid_t grouplist[grouplist_max + 1];
    size_t index = 0;

    while ((grp = getgrent()) != NULL) {
        char** gr_mem = grp->gr_mem;
        while (*gr_mem != NULL) {
            if (strcmp(user, *gr_mem) == 0) {
                if (group != grp->gr_gid) {
                    grouplist[index++] = grp->gr_gid;
                }
                break;
            }
            gr_mem = gr_mem + 1;
        }
    }
    endgrent();

    grouplist[index++] = group;
    //for (int i = 0; i != index; ++i) printf("%ld\n", (long) grouplist[i]);

    if (setgroups(index, grouplist) == -1) {
        return -1;
    }
    return 0;
}
