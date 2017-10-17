#include <sys/xattr.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[]) {
    int opt;
    char* path_name = NULL;
    char* attr_name = NULL;
    char* attr_value = NULL;
    while ((opt = getopt(argc, argv, ":p:n:v:")) != -1) {
        switch (opt) {
            case 'p': path_name = optarg;
                break;
            case 'n': attr_name = optarg;
                break;
            case 'v': attr_value = optarg;
                break;
            case ':': usage_err("%s Missing argumment,\
                Usage: %s [-p pathname] [-n attrname] [-v attrvalue]",
                argv[0], argv[0]);
                break;
            case '?': usage_err("%s Unrecognized option,\
                Usage: %s [-p pathname] [-n attrname] [-v attrvalue]",
                argv[0], argv[0]);
                break;
            default: usage_err("%s [-p pathname] [-n attrname] [-v attrvalue]",
                argv[0]);
                break;
        }
    }
    if (setxattr(path_name, attr_name, attr_value, strlen(attr_value), 0) == -1) {
        err_exit("setxattr");
    }
    return 0;
}