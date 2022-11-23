#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "ioctl.h"

int main(int argc, char *argv[]) {
    int fd, ret;
    info_t info;

    if(argc != 2) {
        printf("syntax 1: %s clear\n", argv[0]);
        printf("syntax 2: %s info\n", argv[0]);
        _exit(1);
    }

    fd = open("/dev/pchar0", O_RDWR);
    if(fd < 0) {
        perror("open() failed");
        _exit(1);
    }

    if(strcmp(argv[1], "clear") == 0) {
        ret = ioctl(fd, FIFO_CLEAR);
        if(ret < 0)
            perror("ioctl() failed to clear fifo");
        else
            printf("fifo is cleared.\n");
    }
    else if(strcmp(argv[1], "info") == 0) {
        ret = ioctl(fd, FIFO_GET_INFO, &info);
        if(ret < 0)
            perror("ioctl() failed to get fifo info");
        else
            printf("fifo details: size = %d, length = %d, available = %d\n", info.size, info.len, info.avail);
    }
    else
        printf("unsupported operation!\n");
    close(fd);
    return 0;
}

// gcc pchar_test.c -o pchar_test.out
// sudo ./pchar_test.out clear
// sudo ./pchar_test.out info
