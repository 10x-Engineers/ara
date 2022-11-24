// A customized test to check narrowing instruction (vnsrl.wi)

#include "vector_macros.h"

void TEST_CASE1(void) {

  VSET(16, e32, m1);

  VCLEAR(v24);
  VCLEAR(v28);

  VLOAD_64(v24, 0x3fffffffffffffff, 0x003ffffffffffffc, 0x3ffffffffffffffc, 0xfffffffffffffffc,
  0x3ffffffffffffffc, 0x003ffffffffffffc, 0x3ffffffffffffffc, 0xfffffffffffffffc,
  0x3ffffffffffffffc, 0x003ffffffffffffc, 0x3ffffffffffffffc, 0xfffffffffffffffc,
  0x3ffffffffffffffc, 0x003ffffffffffffc, 0x3ffffffffffffffc, 0xfffffffffffffffc);

  asm volatile("vnsrl.wi v28, v24, 22");

  VCMP_U32(1, v28, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
           0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
           0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
           0xffffffff);
};

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();

  EXIT_CHECK();
}
