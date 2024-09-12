#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr;

    char *server_ip = argv[1];
    int port = atoi(argv[2]);
    char *file_name = argv[3];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    FILE *file = fopen(file_name, "r");

    char buffer[BUFFER_SIZE];

    size_t n;
    n = fread(buffer, 1, BUFFER_SIZE, file);

    send(sockfd, buffer, n, 0);

    fclose(file);

    int n = recv(sockfd, buffer, BUFFER_SIZE, 0);

    buffer[n] = '\0';
    printf("Server: %s\n", buffer);

    close(sockfd);
    return 0;
}