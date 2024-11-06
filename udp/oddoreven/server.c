// Server-side (server.c)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    int num;
    char buffer[256];

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Receive number from client
        recvfrom(sockfd, &num, sizeof(int), 0, (struct sockaddr *) &client_addr, &client_len);
        num = ntohl(num);

        // Check if even or odd
        sprintf(buffer, "%s", (num % 2 == 0) ? "Even" : "Odd");

        // Send response to client
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &client_addr, client_len);
    }

    close(sockfd);
    return 0;
}