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
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    printf("Socket created\n");

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    // servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");;
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("Client listening on port %d\n", PORT);

    while (1) {
        socklen_t len = sizeof(cliaddr);
        int n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        printf("Server received: %s\n", buffer);

        // Open file
        FILE *file = fopen(buffer, "r");
        if (file == NULL) {
            printf("File not found\n");

            int response = -1;

            sendto(sockfd, &response, sizeof(int), 0, (const struct sockaddr *)&cliaddr, len);
            continue;
    
        }

        fscanf(file, "%[^\0]", buffer);

        printf("File Reads: %s\n", buffer);

        sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&cliaddr, len);
        // printf("Server sent file length as: %d\n", file_size);
    }

    close(sockfd);
    return 0;
}
