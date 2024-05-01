#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <time.h>

int main(int argc, char* argv[]) {
    int sockfd, port, n;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024];
    time_t ct;

    if (argc != 2) {
        printf("\nUsage: %s <port>\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[1]);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind error");
        exit(1);
    }

    printf("Server waiting for client...\n");

    while (1) {
        n = sizeof(cliaddr);
        memset(buffer, 0, sizeof(buffer));

        if (recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &n) < 0) {
            perror("Error in recvfrom");
            continue;
        }

        ct = time(NULL);
        sprintf(buffer, "%s", ctime(&ct));

        if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, n) < 0) {
            perror("Error in sendto");
            continue;
        }
    }

    close(sockfd);
    return 0;
}
