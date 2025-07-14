#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 50000
#define BUF_SIZE 80

int main() {
    int sockfd;
    struct sockaddr_in address;
    char buf[BUF_SIZE];

    // 1. ソケットの生成
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // ローカルホストのIPアドレス
    address.sin_port = htons(PORT);

    // 2. 接続要求の発信
    if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Connect failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("\n * server IP: %s, port: %d\n",
           inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    // 3. データ送受信
    strcpy(buf, "client will connect to server");
    write(sockfd, buf, strlen(buf));

    memset(buf, 0, sizeof(buf));
    read(sockfd, buf, sizeof(buf));
    printf("\n * message from server : %s \n", buf);

    // 4. ソケットの除去
    close(sockfd);

    return 0;
}