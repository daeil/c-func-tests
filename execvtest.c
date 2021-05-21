#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>


#define SIZE (1 * 1024 * 1024)
int main(int argc, char *argv[])
{
    struct rlimit l;
    int ret = getrlimit(RLIMIT_STACK, &l);
    printf("ret=%d, l.rlim_cur:%lu l.rlim_max:%lu\n", ret, l.rlim_cur, l.rlim_max);

    if (l.rlim_cur != SIZE) {
        l.rlim_cur = SIZE;
        char *newenv[] = { NULL };
        printf("set new stack size(%d)\n", SIZE);
        setrlimit(RLIMIT_STACK, &l);
        execve(argv[0], argv, newenv);
    }
    printf("size is same\n");
    return 0;
}
