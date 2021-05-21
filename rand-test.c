#include <stdio.h>

static unsigned long int next = 1;

int rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % (unsigned int) (120 * 1e3);
}

float frand(void)
{
    return rand() * 1e-3;
}

void srand(unsigned int seed)
{
    next = seed;
}


int main(int argc, char** argv)
{

    for (int i=0; i<10; i++) {
        printf("%f\n", frand());
    }
    return 0;
}

