#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

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

        FILE *file = fopen("received_file.txt", "w");

        char buffer[BUFFER_SIZE];
        ssize_t n;

        n = recv(client_fd, buffer, BUFFER_SIZE, 0);

        fwrite(buffer, 1, n, file);

        fclose(file);

        strcpy(buffer, "File received successfully");

        send(client_fd, buffer, strlen(buffer), 0);

        printf("File received and processed\n");

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
