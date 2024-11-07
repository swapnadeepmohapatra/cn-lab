#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFFER_SIZE 1024

void main(int argv, char *argc[])
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    int port = atoi(argc[1]);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(server_fd, 5);

    while (1)
    {
        client_len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

        if (fork() == 0)
        {
            close(server_fd);

            char buffer[BUFFER_SIZE];
            ssize_t n;

            strcpy(buffer, "Enter Option: \n1. Add \n2. Subtract \n3. Multiply \n4. Divide\n");

            send(client_fd, buffer, strlen(buffer), 0);

            printf("Enter Two Numbers: ");
            int a, b;
            scanf("%d %d", &a, &b);

            int opt;

            recv(client_fd, &opt, sizeof(opt), 0);

            int result;

            if (opt == 1)
            {
                result = a + b;
            }
            else if (opt == 2)
            {
                result = a - b;
            }
            else if (opt == 3)
            {
                result = a * b;
            }
            else if (opt == 4)
            {
                result = a / b;
            }
            else
            {
                result = 0;
            }

            send(client_fd, &result, sizeof(result), 0);

            close(client_fd);
            exit(0);
        }

        close(client_fd);
    }
    close(server_fd);
}