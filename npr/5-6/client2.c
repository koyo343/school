#include <stdio.h>
#include <stdlib.h>
#include <string.h>        // strlen()
#include <fcntl.h>         // open(), creat()
#include <unistd.h>        // read(), write(), close()
#define PIPE "/tmp/mypipe" // 名前付きパイプの指定

int main() {
    char buf[80];
    int fd;

    fd = open(PIPE, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "PIPE does not exist!\n");
        exit(1);
    }

    while (1) {
        read(fd, buf, sizeof(buf));
        printf("Received from server: %s\n", buf);

        if (strcmp(buf, "Etou") == 0){
            break;
        }
    }

    close(fd);
    return 0;
}