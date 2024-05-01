#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char* argv[]) {
    struct sockaddr_in server, client;

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Error in socket()");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Error in bind()");
        exit(1);
    }

    char buffer[100];
    socklen_t server_len = sizeof(server);
    printf("Server waiting...\n");

    if (recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, &server_len) < 0) {
        perror("Error in recvfrom()");
        exit(1);
    }

    printf("Received message: %s\n", buffer);

    return 0;
}
