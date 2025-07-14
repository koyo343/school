#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "/tmp/myfifo"
#define BUFFER_SIZE 256

int main() {
    int pipe_fd;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    printf("クライアント: サーバーがパイプを開くのを待っています...\n");
    pipe_fd = open(FIFO_NAME, O_RDONLY);
    if (pipe_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    printf("クライアント: 接続完了。サーバーからのデータを受信します...\n\n");

    while ((bytes_read = read(pipe_fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) == -1) {
            perror("write");
            close(pipe_fd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1) {
        perror("read");
    }
    close(pipe_fd);
    printf("\nクライアント: 読み込み完了。パイプを閉じました。\n");
    unlink(FIFO_NAME);

    return 0;
}