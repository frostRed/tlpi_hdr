#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
int mydup(int oldfd);
int mydup2(int oldfd, int newfd);

int main() {
    int newfd = mydup(1);
    if (newfd == 3) {
        printf("mydup\n");
    }
    newfd = mydup2(1, 2);
    if (newfd == 2) {
        printf("mydup2\n");
    }

}

int mydup(int oldfd) {
   int newfd = fcntl(oldfd, F_DUPFD, 0); 
   return newfd;
}
int mydup2(int oldfd, int newfd) {
    // 检查 oldfd 是否有效
    if (fcntl(oldfd, F_GETFL) == -1) {
        errno = EBADF;
        return -1;
    }
    else if (oldfd == newfd) {
        return oldfd;
    }
    else {
        close(newfd);
        newfd = fcntl(oldfd, F_DUPFD, newfd); 
        return newfd;
    }
}