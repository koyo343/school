#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 50000
#define BUF_SIZE 80

int main() {
    int sockfd_s, sockfd_c;
    struct sockaddr_in addr_s, addr_c;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    char buf[BUF_SIZE + 1];
    char gakuseki[64];
    FILE *fp;

    // 1. ソケット作成
    sockfd_s = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_s < 0) { perror("socket"); exit(1); }

    // 2. ソケットへの名前付け
    addr_s.sin_family = AF_INET;
    addr_s.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_s.sin_port = htons(PORT);
    if (bind(sockfd_s, (struct sockaddr *)&addr_s, sizeof(addr_s)) < 0) {
        perror("bind"); close(sockfd_s); exit(1);
    }

    // 3. 要求受入の準備
    if (listen(sockfd_s, 5) < 0) { perror("listen"); close(sockfd_s); exit(1); }
    printf("FTPサーバ起動(port %d)\n", PORT);

    while (1) {
        // 4. 接続要求の許可
        sockfd_c = accept(sockfd_s, (struct sockaddr *)&addr_c, &addrlen);
        if (sockfd_c < 0) { perror("accept"); continue; }
        printf("クライアント接続\n");

        // 5. クライアントから学籍番号受信（1行）
        memset(gakuseki, 0, sizeof(gakuseki));
        int n = read(sockfd_c, gakuseki, sizeof(gakuseki)-1);
        if (n <= 0) { close(sockfd_c); continue; }
        gakuseki[strcspn(gakuseki, "\r\n")] = 0; // 改行除去

        // 6. ファイル名生成
        char filename[128];
        snprintf(filename, sizeof(filename), "%s.txt", gakuseki);
        printf("要求ファイル: %s\n", filename);

        // 7. ファイル送信（80文字単位）
        fp = fopen(filename, "r");
        if (!fp) {
            snprintf(buf, sizeof(buf), "ERROR: ファイルがありません\n");
            write(sockfd_c, buf, strlen(buf));
        } else {
            while (1) {
                int len = fread(buf, 1, BUF_SIZE, fp);
                if (len <= 0) break;
                buf[len] = '\0';
                write(sockfd_c, buf, len);
            }
            fclose(fp);
        }
        // ファイル送信後、exit_sendを送信
        strcpy(buf, "exit_send");
        write(sockfd_c, buf, strlen(buf));

        close(sockfd_c);
    }
    close(sockfd_s);
    return 0;
}