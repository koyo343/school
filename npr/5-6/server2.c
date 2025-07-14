#include <stdio.h>
#include <stdlib.h>
#include <string.h>        // strlen()
#include <fcntl.h>         // open(), creat()
#include <unistd.h>        // read(), write(), close()
#define PIPE "/tmp/mypipe" // 名前付きパイプの指定
#define END "Etou"

int main() {
    char buf[80];
    int fd;

    fd = open(PIPE, O_WRONLY);
    if (fd == -1) {
        fprintf(stderr, "PIPE does not exist!\n");
        exit(1);
    }

    while (1) {
        printf("Enter a string: ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0'; // Remove newline character

        write(fd, buf, strlen(buf) + 1);

        if (strcmp(buf, END) == 0){
            break;
        }
    }

    close(fd);
    return 0;
}