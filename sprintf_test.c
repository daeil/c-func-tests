#include <stdio.h>
#include <string.h>




static void printBuf(char* data, int count) {
    int len = 0;
    char buf[1024];
    for (int i = 0; i < count; i++) {
        len += snprintf(buf + len, sizeof(buf) - len, "0x%02x ", *(data + i));
    }
    printf("%s\n", buf);
}



int main(int argc, char** argv) {

    char str1[1024] = {0};
    char str2[1024];
    int j = 10;
    for (int i=0; i<10; i++) {
        char substr[1024] = {0};
        sprintf(substr, "[%d]: %d", i, j);
        strcat(str1, substr);
    }

    {
    int l = 0;
    char buf[1024];
    for(int i=0;i<10;i++) {
        l += snprintf(buf + l, sizeof(buf) - l,  "%d ", i);
    }
    }
    {
    char buf[14] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    printBuf(buf, 14);
    }

    printf("str=%s\n", str1);
    return 0;
}

