#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(server_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(atoi(argv[4]));
    client_addr.sin_addr.s_addr = inet_addr(argv[3]);

    bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    while (1)
    {
        printf("Enter message: ");
        fgets(buffer, 1024, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        printf("Client IP: %s, Sent: \"Hello\"\n", argv[3]);
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, addr_len);

        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &addr_len);
        printf("Received from Server IP: %s, Port: %s, Message: \"%s\"\n", argv[1], argv[2], buffer);
    }

    close(sockfd);
    return 0;
}
