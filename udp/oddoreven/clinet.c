// Client-side (client.c)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in server_addr;
    int num;
    char buffer[256];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        exit(1);
    }

    num = atoi(argv[1]);

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with server IP if needed
    server_addr.sin_port = htons(PORT);

    // Send number to server
    num = htonl(num);
    sendto(sockfd, &num, sizeof(int), 0, (struct sockaddr *) &server_addr, sizeof(server_addr));

    // Receive response from server
    recvfrom(sockfd, buffer, 255, 0, NULL, NULL);
    printf("Server response: %s\n", buffer);

    close(sockfd);
    return 0;
}