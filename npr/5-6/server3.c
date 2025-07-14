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
    int sockfd_s, sockfd_c;
    struct sockaddr_in address_s, address_c;
    char buf[BUF_SIZE];
    socklen_t addrlen = sizeof(struct sockaddr_in);

    // 1. ソケット作成
    sockfd_s = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_s < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. ソケットへの名前付け
    address_s.sin_family = AF_INET;
    address_s.sin_addr.s_addr = htonl(INADDR_ANY); // どのインターフェースでも受け付ける
    address_s.sin_port = htons(PORT);

    if (bind(sockfd_s, (struct sockaddr *)&address_s, sizeof(address_s)) < 0) {
        perror("Bind failed");
        close(sockfd_s);
        exit(EXIT_FAILURE);
    }

    // 3. 要求受入の準備
    if (listen(sockfd_s, 5) < 0) {
        perror("Listen failed");
        close(sockfd_s);
        exit(EXIT_FAILURE);
    }
    printf("server waits\n");

    // 4. 接続要求の許可
    sockfd_c = accept(sockfd_s, (struct sockaddr *)&address_c, &addrlen);
    if (sockfd_c < 0) {
        perror("Accept failed");
        close(sockfd_s);
        exit(EXIT_FAILURE);
    }
    printf("\n * request from client IP: %s, port: %d\n",
           inet_ntoa(address_c.sin_addr), ntohs(address_c.sin_port));

    // 5. データ送受信
    memset(buf, 0, sizeof(buf));
    read(sockfd_c, buf, sizeof(buf));
    printf("\n * message from client : %s \n", buf);

    strcpy(buf, "From Server via socket");
    write(sockfd_c, buf, strlen(buf));

    // 6. ソケットの除去
    close(sockfd_c);
    close(sockfd_s);

    return 0;
}