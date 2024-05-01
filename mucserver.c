#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444
#define BUF_SIZE 2000

int main() {
    int sockfd, ret;
    struct sockaddr_in addr;
    char buffer[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket!");
        exit(1);
    }

    printf("Socket created...\n");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        perror("Error binding!");
        exit(1);
    }

    printf("Binding done...\n");

    listen(sockfd, 5);
    printf("Waiting for a connection...\n");

    while (1) {
        struct sockaddr_in cl_addr;
        socklen_t len = sizeof(cl_addr);
        int newsockfd = accept(sockfd, (struct sockaddr *)&cl_addr, &len);
        if (newsockfd < 0) {
            perror("Error accepting connection!");
            exit(1);
        }

        inet_ntop(AF_INET, &(cl_addr.sin_addr), buffer, INET_ADDRSTRLEN);
        printf("Connection accepted from %s:%d\n", buffer, ntohs(cl_addr.sin_port));

        close(newsockfd); // For simplicity, just accepting and closing connections
    }

    close(sockfd);
    return 0;
}
