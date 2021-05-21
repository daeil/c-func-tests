#include <stdio.h>
#include <stdint.h>

static float u2f(uint32_t u) {
  union {
    float f;
    uint32_t i;
  } tmp;
  tmp.i = u;
  return tmp.f;
}

static uint32_t f2u(float d) {
  union {
    float f;
    uint32_t i;
  } tmp;
  tmp.f = d;
  return tmp.i;
}

int main (int argc, char** argv) {
    int d = 10000;
    float f = 0.12345;
    printf("0x%08x=%f\n", d, u2f(d));
    printf("%f=0x%08x\n", f, f2u(f));

}
