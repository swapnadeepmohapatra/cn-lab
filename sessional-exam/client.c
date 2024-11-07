#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFFER_SIZE 1024

void main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr;

    char *server_ip = argv[1];
    int port = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    char buffer[BUFFER_SIZE];
    ssize_t n;

    recv(sockfd, buffer, BUFFER_SIZE, 0);

    printf("%s", buffer);

    int opt;
    scanf("%d", &opt);

    send(sockfd, &opt, sizeof(opt), 0);

    int ans;

    recv(sockfd, &ans, sizeof(ans), 0);

    printf("Result: %d\n", ans);

    close(sockfd);
}