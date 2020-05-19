#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[]) {
    char *src_path = argv[1];
    char *dst_path = argv[2];

    umask(0);
    int fd = open(src_path, O_RDWR|O_CREAT|O_TRUNC, FILE_MODE);
    int fd2 = open(dst_path, O_WRONLY|O_CREAT|O_TRUNC, FILE_MODE);

    int n;
    char buf;
    char buf2[] = "abcdefghijklmnopqrstuvwxyz";

    // 给文件创建空洞
    lseek(fd, 1000, SEEK_SET);
    if (write(fd, buf2, 26) < 0)
        err_sys("write source file error");
    lseek(fd, 0, SEEK_SET);

    while((n = read(fd, &buf, 1)) == 1) {
        if (buf == '\0')
            continue;
        if (write(fd2, &buf, 1) != 1)
            err_sys("write error");
    }
    close(fd);
    close(fd2);
    exit(0);
}