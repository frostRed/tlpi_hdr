#include <pwd.h>
#include <grp.h>
#include "ugid_functions.h"
#include "tlpi_hdr.h"

int main(int argc, char* argv[]) {
    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        usage_err("%s owner group [file...]\n"
        "   owner or goup can be '-',"
        "meaning leave unchaged\n", argv[0]);
    }

    uid_t uid;
    if (strcmp(argv[1], "-") == 0) {
        uid = -1;
    }
    else {
        uid = user_id_from_name(argv[1]);
        if (uid == -1) {
            fatal("No such user (%s)", argv[1]);
        }
    }

    gid_t gid;
    if (strcmp(argv[2], "-") == 0) {
        gid = -1;
    }
    else {
        gid = group_id_from_name(argv[2]);
        if (gid == -1) {
            fatal("No such group user (%s)", argv[1]);
        }
    }

    Boolean errFnd = FALSE;
    for (int j = 3; j != argc; ++j) {
        if (chown(argv[j], uid, gid) == -1) {
            err_msg("chown: %s", argv[j]);
            errFnd = TRUE;
        }
    }

    exit(errFnd ? EXIT_FAILURE : EXIT_SUCCESS);
}