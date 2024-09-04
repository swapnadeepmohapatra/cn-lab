#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    int port = atoi(argv[1]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    // serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Connected to server Port = %d\n", port);

    while (1)
    {
        printf("Write a message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        send(sockfd, buffer, BUFFER_SIZE, 0);

        if (strncmp(buffer, "exit", 4) == 0)
        {
            printf("Closing the connection\n");
            break;
        }

        recv(sockfd, buffer, sizeof(BUFFER_SIZE), 0);

        printf("Server Sent: %s\n", buffer);

        if (strncmp(buffer, "exit", 4) == 0)
        {
            printf("Server closed the connection\n");
            break;
        }
    }
    close(sockfd);
    return 0;
}
