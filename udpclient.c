#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char* argv[]) {
    struct sockaddr_in server;

    if (argc != 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        exit(1);
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Error in socket()");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(atoi(argv[2]));

    char buffer[100];
    printf("Enter a message to be sent to the server:\n");
    fgets(buffer, sizeof(buffer), stdin);

    if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Error in sendto()");
        exit(1);
    }

    printf("Message sent successfully.\n");

    return 0;
}
