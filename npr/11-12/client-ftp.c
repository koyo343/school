#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "172.22.163.216"
#define PORT 50000
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in addr;
    char buf[BUF_SIZE];
    char gakuseki[16];
    char filename[256];

    // 1. サーバ情報表示
    printf("サーバIP: %s, ポート: %d\n", SERVER_IP, PORT);

    // 2. ソケット生成
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    addr.sin_port = htons(PORT);

    // 3. 接続要求
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect"); close(sockfd); exit(1);
    }
    printf("サーバに接続しました。\n");

    // 4. 学籍番号入力・送信
    printf("学籍番号を半角8文字で入力してください: ");
    fgets(gakuseki, sizeof(gakuseki), stdin);
    gakuseki[strcspn(gakuseki, "\r\n")] = 0;
    if (strlen(gakuseki) != 8) {
        printf("学籍番号は8文字で入力してください。\n");
        close(sockfd);
        return 1;
    }
    write(sockfd, gakuseki, strlen(gakuseki));

    // 5. 取得ファイル名生成・送信
    snprintf(filename, sizeof(filename), "%s-copy.txt", gakuseki);
    printf("取得ファイル名: %s\n", filename);
    write(sockfd, filename, strlen(filename));

    // 6. サーバからファイル内容受信・表示（exit_sendが来るまで）
    printf("---- ファイル内容 ----\n");
    while (1) {
        int n = read(sockfd, buf, sizeof(buf)-1);
        if (n <= 0) break;
        buf[n] = '\0';
        if (strstr(buf, "exit_send") != NULL) {
            // exit_sendが含まれていたら終了
            char *p = strstr(buf, "exit_send");
            *p = '\0';
            printf("%s", buf);
            break;
        }
        printf("%s", buf);
    }
    printf("\n----------------------\n");

    close(sockfd);
    return 0;
}