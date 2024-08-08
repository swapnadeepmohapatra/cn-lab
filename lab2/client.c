// Write a sender and receiver program in C by passing the IP address and the
// port number of each other through the command line arguments using
// connection less socket. Both of them will exchange messages with each other
// continuously. If any one of them will receive the “exit” message from the
// other end then both of them will close the connection. (Assume both the client
// and server are running with in the same host)

// This is the client program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

void main(){
    int sockfd;
    int connection;
    char buffer[1024];
    char* message = "Hello from client";
    int bytes_received;
    int bytes_sent;

    struct sockaddr_in server_addr, client_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    int length = sizeof(client_addr);

    printf("Creating socket\n");

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);

    connection = connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr));

    printf("Socket created\n");

    // bytes_sent = sendto(sockfd, (const char *) message, strlen(message), MSG_OOB, (const struct sockaddr *) &server_addr, length);

    bytes_sent = send(sockfd, (const char *) message, strlen(message), MSG_OOB);

    printf("Message sent to server\n");

    bytes_received = recv(sockfd, (char *) buffer, 1024, MSG_WAITALL);

    printf("Bytes received: %d\n", bytes_received);

    buffer[bytes_received] = '\0';

    printf("Message from server: %s\n", buffer);

    close(sockfd);
}