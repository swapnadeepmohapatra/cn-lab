// Write a sender and receiver program in C by passing the IP address and the
// port number of each other through the command line arguments using
// connection less socket. Both of them will exchange messages with each other
// continuously. If any one of them will receive the “exit” message from the
// other end then both of them will close the connection. (Assume both the client
// and server are running with in the same host)

// This is the server program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8000

int main(){
    int sockfd;
    int bind1;
    char buffer[1024];
    char* response = "Hello from server";
    int bytes_received;
    int bytes_sent;

    struct sockaddr_in server_addr, client_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    int length = sizeof(client_addr);

    printf("Creating socket\n");

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);

    printf("Socket created\n");

    bind1 = bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr));

    printf("Server listening on port %d\n", PORT);

    bytes_received = recvfrom(sockfd, (char *) buffer, 1024, MSG_WAITALL, (struct sockaddr *) &client_addr, &length);

    printf("Message from client: %s\n", buffer);

    bytes_sent = sendto(sockfd, (const char *) response, strlen(response), 0, (const struct sockaddr *) &client_addr, length);

    printf("Hello Message sent to client\n");
    close(sockfd);

    return 0;
}