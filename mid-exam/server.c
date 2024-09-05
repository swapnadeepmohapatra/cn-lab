// server.c
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
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr));

    recvfrom(sockfd, numbers, sizeof(numbers), 0, (struct sockaddr *)&client_addr, &addr_len);

    printf("Client details: IP %s, Port %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += numbers[i];
    }
    int mean = sum / n;
    int median = numbers[n / 2];

    int results[3];

    results[0] = sum;
    results[1] = mean;
    results[2] = median;

    printf("Sum: %d\n", sum);
    printf("Mean: %d\n", mean);
    printf("Median: %d\n", median);

    sendto(sockfd, results, sizeof(results), 0, (const struct sockaddr *)&client_addr, addr_len);

    close(sockfd);
}
