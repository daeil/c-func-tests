#include <stdio.h>
#include <string.h>

typedef struct _ST {
    char name[10];
} ST;

int main(int argc, char** argv) {
    ST st;
    strcpy(st.name, "TEST");
    printf("%s\n", st.name);

    return 0;
}
