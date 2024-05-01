#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444
#define BUF_SIZE 2000

int main(int argc, char **argv) {
    int sockfd, ret;
    struct sockaddr_in addr;
    char buffer[BUF_SIZE];

    if (argc < 2) {
        printf("Usage: %s <server IP>\n", argv[0]);
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket!");
        exit(1);
    }

    printf("Socket created...\n");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, argv[1], &addr.sin_addr);

    ret = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        perror("Error connecting to the server!");
        exit(1);
    }

    printf("Connected to the server...\n");

    close(sockfd);
    return 0;
}
