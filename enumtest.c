#include <stdio.h>

typedef enum {
    eStateNotStarted,
    eStateStarted,
    eStateNormal,
    eStateAbnormal
} STATE_t;


#define ENUM(n) (TIMER_##f)

int main(int argc, char** argv) {

    STATE_t state;

    state = eStateStarted;

    printf ("%s\n", ENUM(state));
    return 0;
}
