#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 50000
#define BUF_SIZE 80

void *handle_client(void *arg)
{
    int sockfd_c = *(int *)arg;
    char buf[BUF_SIZE];
    int i;

    for (i = 0; i <= 10; i++)
    {
        snprintf(buf, sizeof(buf), "%d", i);
        write(sockfd_c, buf, strlen(buf));
        sleep(1);
    }

    close(sockfd_c);
    free(arg);
    return NULL;
}

int main()
{
    int sockfd_s, *sockfd_c;
    struct sockaddr_in address_s, address_c;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    pthread_t tid;

    // 1. ソケット作成
    sockfd_s = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_s < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. ソケットへの名前付け
    address_s.sin_family = AF_INET;
    address_s.sin_addr.s_addr = htonl(INADDR_ANY);
    address_s.sin_port = htons(PORT);

    if (bind(sockfd_s, (struct sockaddr *)&address_s, sizeof(address_s)) < 0)
    {
        perror("Bind failed");
        close(sockfd_s);
        exit(EXIT_FAILURE);
    }

    // 3. 要求受入の準備
    if (listen(sockfd_s, 5) < 0)
    {
        perror("Listen failed");
        close(sockfd_s);
        exit(EXIT_FAILURE);
    }
    printf("server waits\n");

    while (1)
    {
        // 4. 接続要求の許可
        sockfd_c = malloc(sizeof(int));
        *sockfd_c = accept(sockfd_s, (struct sockaddr *)&address_c, &addrlen);
        if (*sockfd_c < 0)
        {
            perror("Accept failed");
            free(sockfd_c);
            continue;
        }
        printf("\n * request from client IP: %s, port: %d\n",
               inet_ntoa(address_c.sin_addr), ntohs(address_c.sin_port));

        // Create a new thread to handle the client
        pthread_create(&tid, NULL, handle_client, sockfd_c);
        pthread_detach(tid);
    }

    close(sockfd_s);
    return 0;
}