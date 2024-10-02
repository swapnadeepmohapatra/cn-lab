// Design a connection oriented concurrent chat server using fork () in C where
// the server will serve multiple chart clients simultaneously.
// client.c

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

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    char buffer[BUFFER_SIZE];
    ssize_t n;

    while (1)
    {
        printf("Write a message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        send(sockfd, buffer, strlen(buffer), 0);

        if (strncmp(buffer, "exit", 4) == 0)
        {
            printf("Closing the connection\n");
            break;
        }

        n = recv(sockfd, buffer, BUFFER_SIZE, 0);

        buffer[n] = '\0';
        printf("Server: %s\n", buffer);

        if (strncmp(buffer, "exit", 4) == 0)
        {
            printf("Server closed the connection\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}