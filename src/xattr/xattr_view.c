#include <sys/xattr.h>
#include "tlpi_hdr.h"

#define XATTR_SIZE 10000

static void usage_error(const char* progName) {
    fprintf(stderr, "Usage: %s [-x] file...\n", progName);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    Boolean hex_display = FALSE;
    int opt;
    while ((opt = getopt(argc, argv, "x")) != -1) {
        switch (opt) {
            case 'x': hex_display = TRUE;
                break;
            case '?': usage_error(argv[0]);
        }
    }

    if (optind >= argc + 2) {
        usage_error(argv[0]);
    }

    char list[XATTR_SIZE], value[XATTR_SIZE];

    ssize_t list_len, value_len;
    for (int j = optind; j != argc; ++j) {
        list_len = listxattr(argv[j], list, XATTR_SIZE);
        if (list_len == -1) {
            err_exit("listxattr");
        }

        printf("%s:\n", argv[1]);
        for (int ns = 0; ns < list_len; ns += strlen(&list[ns]) + 1) {
            printf("    name=%s; ", &list[ns]);

            value_len = getxattr(argv[j], &list[ns], value, XATTR_SIZE);
            if (value_len == -1) {
                printf("couldn't get value");
            }
            else if (!hex_display) {
                printf("value=%.*s", (int) value_len, value);
            }
            else {
                printf("value=");
                for (int k = 0; k != value_len; ++k) {
                    printf("%O2x ", (unsigned) value[k]);
                }
            }
            printf("\n");
        }
    }
    return 0;
}