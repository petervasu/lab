#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>

int main(int argc, char* argv[]) {
    int sockfd, port, n;
    struct sockaddr_in servaddr;
    char buffer[1024];

    if (argc != 3) {
        printf("Usage: %s <server-addr> <port>\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    strcpy(buffer, "TIME");

    if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Error in sendto");
        exit(1);
    }

    n = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
    if (n < 0) {
        perror("Error in recvfrom");
        exit(1);
    }

    buffer[n] = '\0';
    printf("Current Time: %s\n", buffer);

    close(sockfd);
    return 0;
}
