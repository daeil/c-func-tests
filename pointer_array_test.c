#include <stdio.h>

struct tests_t
{
    int id;
    char name[1024];
};


static struct tests_t t0 = { .id=0 };
static struct tests_t t1 = { .id=1 };
static struct tests_t t2 = { .id=2 };

int main(int argc, char** argv) {
    struct tests_t *t012[3] = { NULL };
    t012[0] = &t0;
    t012[1] = &t1;
    t012[2] = &t2;

    return 0;
}
