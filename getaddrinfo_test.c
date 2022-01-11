#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char** argv) {

    const char* ip = "1.2.3.5";

    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int s = getaddrinfo(ip, argv[1], &hints, &result);
    printf("%s\n", argv[1]);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in *addr = (struct sockaddr_in *)&result;

    printf("addr=0x%08x\n", addr->sin_addr.s_addr);
    printf("addr=0x%08x\n", inet_addr(ip));
    printf("port=%u\n", ntohs(addr->sin_port));
    printf("port=%u\n", addr->sin_port);

    freeaddrinfo(result);           /* No longer needed */
    return 0;
}

