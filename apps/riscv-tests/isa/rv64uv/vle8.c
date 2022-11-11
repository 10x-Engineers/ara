#include "vector_macros.h"

#define AXI_DWIDTH 128

static volatile uint8_t ALIGNED_I8[16] __attribute__((aligned(AXI_DWIDTH))) = {
    0xe0, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88,
    0x88, 0xae, 0x08, 0x91, 0x02, 0x59, 0x11, 0x89};

//**********Checking functionality of vle8 with different destination
// registers********//
void TEST_CASE1(void) {
  VSET(15, e8, m1);
  asm volatile("vle8.v v0, (%0)" ::"r"(&ALIGNED_I8[1]));
  VCMP_U8(1, v0, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88, 0x88, 0xae, 0x08,
          0x91, 0x02, 0x59, 0x11, 0x89);
}

void TEST_CASE2(void) {
  VSET(15, e8, m1);
  asm volatile("vle8.v v1, (%0)" ::"r"(&ALIGNED_I8[1]));
  VCMP_U8(2, v1, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88, 0x88, 0xae, 0x08,
          0x91, 0x02, 0x59, 0x11, 0x89);
}

//******Checking functionality of vle8 with illegal destination register
// specifier for EMUL********//
// If destination register is changed to any odd number register it will give
// runtime error
void TEST_CASE3(void) {
  VSET(15, e16, m4);
  asm volatile("vle8.v v2, (%0)" ::"r"(&ALIGNED_I8[1]));
  VCMP_U8(3, v2, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88, 0x88, 0xae, 0x08,
          0x91, 0x02, 0x59, 0x11, 0x89);
}

//*******Checking functionality of vle8 with different values of masking
// register******//
void TEST_CASE4(void) {
  VSET(16, e8, m1);
  VCLEAR(v3);
  VLOAD_8(v0, 0xFF, 0xFF);
  asm volatile("vle8.v v3, (%0), v0.t" ::"r"(&ALIGNED_I8[0]));
  VCMP_U8(4, v3, 0xe0, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88, 0x88, 0xae,
          0x08, 0x91, 0x02, 0x59, 0x11, 0x89);
}

void TEST_CASE5(void) {
  VSET(16, e8, m1);
  VCLEAR(v3);
  VLOAD_8(v0, 0x00, 0x00);
  asm volatile("vle8.v v3, (%0), v0.t" ::"r"(&ALIGNED_I8[0]));
  VCMP_U8(5, v3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

void TEST_CASE6(void) {
  VSET(16, e8, m1);
  VCLEAR(v3);
  VLOAD_8(v3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vle8.v v3, (%0), v0.t" ::"r"(&ALIGNED_I8[0]));
  VCMP_U8(6, v3, 1, 0xd3, 3, 0xd1, 5, 0x48, 7, 0x88, 9, 0xae, 11, 0x91, 13,
          0x59, 15, 0x89);
}

//******Checking functionality with different combinations of vta and vma*****//
void TEST_CASE7(void) {
  uint64_t avl;
  VSET(16, e8, m1);
  VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  __asm__ volatile("vsetivli %[A], 12, e8, m1, ta, ma" : [A] "=r"(avl));
  asm volatile("vle8.v v4, (%0), v0.t" ::"r"(&ALIGNED_I8[0]));
  VSET(16, e8, m1);
  VCMP_U8(7, v4, 1, 0xd3, 3, 0xd1, 5, 0x48, 7, 0x88, 9, 0xae, 11, 0x91, 13, 14,
          15, 16);
}

void TEST_CASE8(void) {
  uint64_t avl;
  VSET(16, e8, m1);
  VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  __asm__ volatile("vsetivli %[A], 12, e8, m1, ta, mu" : [A] "=r"(avl));
  asm volatile("vle8.v v4, (%0), v0.t" ::"r"(&ALIGNED_I8[0]));
  VSET(16, e8, m1);
  VCMP_U8(8, v4, 1, 0xd3, 3, 0xd1, 5, 0x48, 7, 0x88, 9, 0xae, 11, 0x91, 13, 14,
          15, 16);
}

void TEST_CASE9(void) {
  uint64_t avl;
  VSET(16, e8, m1);
  VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  __asm__ volatile("vsetivli %[A], 12, e8, m1, tu, ma" : [A] "=r"(avl));
  asm volatile("vle8.v v4, (%0), v0.t" ::"r"(&ALIGNED_I8[0]));
  VSET(16, e8, m1);
  VCMP_U8(9, v4, 1, 0xd3, 3, 0xd1, 5, 0x48, 7, 0x88, 9, 0xae, 11, 0x91, 13, 14,
          15, 16);
}

void TEST_CASE10(void) {
  uint64_t avl;
  VSET(16, e8, m1);
  VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  __asm__ volatile("vsetivli %[A], 12, e8, m1, tu, mu" : [A] "=r"(avl));
  asm volatile("vle8.v v4, (%0), v0.t" ::"r"(&ALIGNED_I8[0]));
  VSET(16, e8, m1);
  VCMP_U8(10, v4, 1, 0xd3, 3, 0xd1, 5, 0x48, 7, 0x88, 9, 0xae, 11, 0x91, 13, 14,
          15, 16);
}

//*******Checking functionality if encoded EEW is not supported for given SEW
// and LMUL values because EMUL become out of range*****// If LMUL is changed to
// mf8 it will give error because emul become out of range
void TEST_CASE11(void) {
  VSET(15, e32, mf2);
  asm volatile("vle8.v v5, (%0)" ::"r"(&ALIGNED_I8[1]));
  VCMP_U8(11, v5, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88, 0x88, 0xae, 0x08,
          0x91, 0x02, 0x59, 0x11, 0x89);
}

//******Checking functionality with different values of vl******//
void TEST_CASE12(void) {
  VSET(16, e8, m1);
  VLOAD_8(v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VSET(16, e8, m1);
  asm volatile("vle8.v v6, (%0)" ::"r"(&ALIGNED_I8[0]));
  VSET(16, e8, m1);
  VCMP_U8(12, v6, 0xe0, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88, 0x88, 0xae,
          0x08, 0x91, 0x02, 0x59, 0x11, 0x89);
}

void TEST_CASE13(void) {
  uint64_t avl;
  VSET(16, e8, m1);
  VLOAD_8(v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  __asm__ volatile("vsetivli %[A], 0, e8, m1, ta, ma" : [A] "=r"(avl));
  asm volatile("vle8.v v6, (%0)" ::"r"(&ALIGNED_I8[0]));
  VSET(16, e8, m1);
  VCMP_U8(13, v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
}

void TEST_CASE14(void) {
  VSET(16, e8, m1);
  VLOAD_8(v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VSET(13, e8, m1);
  asm volatile("vle8.v v6, (%0)" ::"r"(&ALIGNED_I8[0]));
  VSET(16, e8, m1);
  VCMP_U8(14, v6, 0xe0, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88, 0x88, 0xae,
          0x08, 0x91, 0x02, 14, 15, 16);
}

//******Checking functionality with different vstart value*****//
void TEST_CASE15(void) {
  VSET(16, e8, m1);
  VLOAD_8(v7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  write_csr(vstart, 2);
  asm volatile("vle8.v v7, (%0)" ::"r"(&ALIGNED_I8[0]));
  VSET(16, e8, m1);
  VCMP_U8(15, v7, 1, 2, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88, 0x88, 0xae, 0x08,
          0x91, 0x02, 0x59, 0x11, 0x89);
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  printf("*****Running tests for vle8.v*****\n");
  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();
  TEST_CASE5();
  TEST_CASE6();
  TEST_CASE7();
  TEST_CASE8();
  TEST_CASE9();
  TEST_CASE10();
  TEST_CASE11();
  TEST_CASE12();
  TEST_CASE13();
  TEST_CASE14();
  TEST_CASE15();

  EXIT_CHECK();
}
