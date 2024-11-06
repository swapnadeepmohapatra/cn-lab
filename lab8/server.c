// Design a connection oriented concurrent chat server using fork() in C where the server will serve multiple chart clients simultaneously.When the chat
// server receives a "logout" message from a particular client then it terminates
// the respective connection with that chat client.
// server.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define MAX_CLIENTS 5

int process_count = 0;

int main(int argc, char *argv[])
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    int port;

    port = atoi(argv[1]);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(server_fd, 5);

    printf("Server listening on port %d...\n", port);

    while (1)
    {
        client_len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

        if (fork() == 0)
        {
            close(server_fd);

            process_count++;

            char buffer[BUFFER_SIZE];
            ssize_t n;

            while (1)
            {
                n = recv(client_fd, buffer, BUFFER_SIZE, 0);

                buffer[n] = '\0';

                if (strncmp(buffer, "logout", 6) == 0)
                {
                    printf("Client closed the connection\n");
                    break;
                }

                printf("%d Client: %s\n", process_count, buffer);
                send(client_fd, buffer, n, 0);
            }

            close(client_fd);
            exit(0);
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}