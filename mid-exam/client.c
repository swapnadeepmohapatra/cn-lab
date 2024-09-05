// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

void main()
{
    int sockfd;
    int n = 5;
    int numbers[n];
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    printf("Enter 5 numbers: ");
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &numbers[i]);
    }

    sendto(sockfd, numbers, sizeof(numbers), 0, (const struct sockaddr *)&server_addr, addr_len);

    int results[3];

    recvfrom(sockfd, results, sizeof(results), 0, (struct sockaddr *)&server_addr, &addr_len);

    printf("Server details: IP %s, Port %d\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));

    printf("Sum: %d\n", results[0]);
    printf("Mean: %d\n", results[1]);
    printf("Median: %d\n", results[2]);

    close(sockfd);
}
