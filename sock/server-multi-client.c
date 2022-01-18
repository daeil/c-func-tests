#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>


static struct sockaddr_in addr;
static void
init_addr(int port) {
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
}

static int __accept(int fd, int port) {
    socklen_t addrlen = sizeof(struct sockaddr_in);
    printf("waiting accept\n");
    return accept(fd, (struct sockaddr *)addr, &addrlen);
}

static int sock_fd;
int create_socket(int port) {
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    init_addr(port);
    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
                   &opt, sizeof(opt)))
    {
        printf("socket sockopt failed: %s\n", strerror(errno));
        exit(-1);
    }

    if (bind(fd, (struct sockaddr *)addr, sizeof(struct sockaddr)) < 0) {
        printf("socket bind failed: %s\n", strerror(errno));
        exit(-1);
        return -1;
    }
    if (listen(fd, 1) != 0) {
        printf("socket listen failed: %s\n", strerror(errno));
        exit(-1);
    }
    return __accept(sock_fd, port);
}

#define PORT 6001

int main( int argc, char *argv[] ) {
    int fd = create_socket(PORT);
    char buf[1024] = {0};
    while (1) {
        ssize_t len = read(fd, buf, sizeof(buf));
        if (len <= 0) {
            close(fd);
        }
        fd = __accept(sock_fd, PORT);
    }
    return 0;
}

