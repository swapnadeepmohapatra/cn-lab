#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    int port = atoi(argv[1]);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 10);

    printf("Server listening on port %d\n", port);

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &address.sin_addr, client_ip, INET_ADDRSTRLEN);
    printf("Connected to client: IP = %s, Port = %d\n", client_ip, ntohs(address.sin_port));

    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);
        read(new_socket, buffer, BUFFER_SIZE);

        printf("Client: %s\n", buffer);

        if (strncmp(buffer, "exit", 4) == 0)
        {
            printf("Client closed the connection\n");
            break;
        }

        printf("Write a message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        send(new_socket, buffer, sizeof(BUFFER_SIZE), 0);

        if (strncmp(buffer, "exit", 4) == 0)
        {
            printf("Closing the connection\n");
            break;
        }
    }
    close(new_socket);
    close(server_fd);
    return 0;
}
