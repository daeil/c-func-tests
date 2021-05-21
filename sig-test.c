#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static volatile int eof;

void sig_handler(int signo) {
    printf("received SIGINT\n");
    eof = 1;
}

int main(int argc, char** argv) {

    signal(SIGINT, sig_handler);
    signal(SIGUSR1, sig_handler);
    signal(SIGTERM, sig_handler);

    while (!eof) {
    }

    printf("ended\n");
    sleep(1);
    return 0;
}
