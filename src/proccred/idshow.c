// sudo chown root proc
// sudo chmod u+s proc
#define _GNU_SOURCE

#include <unistd.h>
#include <sys/fsuid.h>
#include <limits.h>
#include "ugid_functions.h"
#include "tlpi_hdr.h"

#define SG_SIZE (NGROUPS_MAX + 1)

int main(int argc, char* argv[]) {
    uid_t ruid, euid, suid, fsuid;
    if (getresuid(&ruid, &euid, &suid) == -1) {
        err_exit("getresuid");
    }
    gid_t rgid, egid, sgid, fsgid;
    if (getresgid(&rgid, &egid, &sgid) == -1) {
        err_exit("getresgid");
    }
    // 只能通过返回值获取文件系统 ID
    fsuid = setfsuid(0);
    fsgid = setfsgid(0);

    printf("UID: ");
    char* p = user_name_from_id(ruid);
    printf("real=%s (%ld); ", (p == NULL) ? "???" : (long) p, ruid);
    p = user_name_from_id(euid);
    printf("eff=%s (%ld); ", (p == NULL) ? "???" : (long) p, euid);
    p = user_name_from_id(suid);
    printf("saved=%s (%ld); ", (p == NULL) ? "???" : (long) p, suid);
    p = user_name_from_id(fsuid);
    printf("fs=%s (%ld); ", (p == NULL) ? "???" : (long) p, fsuid);
    printf("\n");


    printf("GID: ");
    p = group_name_from_id(rgid);
    printf("real=%s (%ld); ", (p == NULL) ? "???" : (long) p, rgid);
    p = group_name_from_id(egid);
    printf("eff=%s (%ld); ", (p == NULL) ? "???" : (long) p, egid);
    p = group_name_from_id(sgid);
    printf("saved=%s (%ld); ", (p == NULL) ? "???" : (long) p, sgid);
    p = group_name_from_id(fsgid);
    printf("fs=%s (%ld); ", (p == NULL) ? "???" : (long) p, fsgid);
    printf("\n");

    gid_t suppGroups[SG_SIZE];
    int numGroups = getgroups(SG_SIZE, suppGroups);
    if (numGroups == -1) {
        err_exit("getgroups");
    }
    printf("Supplementary groups (%d): ", numGroups);
    for (int j = 0; j != numGroups; ++j) {
        p = group_name_from_id(suppGroups[j]);
        printf("%s (%ld)", (p == NULL) ? "???" : p, (long) suppGroups[j]);
    }
    printf("\n");

    exit(EXIT_SUCCESS);
}