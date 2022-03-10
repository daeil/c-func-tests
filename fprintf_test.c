#include <stdio.h>
#include <stdint.h>

int main(int argc, char** argv) {
    uint8_t v[] = {0x41, 0x30, 0x30};

    FILE *fp = fopen("v", "w");
    fprintf(fp, "%c%c%c%c", v[0], '.', v[1], v[2]);
    fclose(fp);

    fp = fopen("v", "r");
    int8_t r[4];
    fscanf(fp, "%c%c%c%c\n", &r[0], &r[1], &r[2], &r[3]);
    fclose(fp);

    printf("v : %c(%d) %c(%d) %c(%d)\n", v[0], v[0], v[1], v[1], v[2], v[2]);
    printf("r : %c(%d) %c(%d) %c(%d) %c(%d)\n", r[0], r[0], r[1], r[1], r[2], r[2], r[3], r[3]);
    return 0;
}
