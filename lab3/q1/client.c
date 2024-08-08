#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    printf("Socket created\n");

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    // servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1)
    {
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        printf("--------------------\n");
        printf("Message Sent\n");

        sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        printf("Client sent: %s\n", buffer);

        int msg_length;
        socklen_t len = sizeof(servaddr);
        recvfrom(sockfd, &msg_length, sizeof(int), MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
        printf("Client received message length: %d\n", msg_length);
    }

    close(sockfd);
    return 0;
}
