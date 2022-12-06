#include "vector_macros.h"

#define AXI_DWIDTH 128

// Exception Handler for rtl

void mtvec_handler(void) {
  asm volatile("csrr t0, mcause"); // Read mcause

  // Read mepc
  asm volatile("csrr t1, mepc");

  // Increment return address by 4
  asm volatile("addi t1, t1, 4");
  asm volatile("csrw mepc, t1");

  // Filter with mcause and handle here

  asm volatile("mret");
}

// Exception Handler for spike
void handle_trap(void) {
  // Read mepc
  asm volatile("csrr t1, mepc");

  // Increment return address by 4
  asm volatile("addi t1, t1, 4");
  asm volatile("csrw mepc, t1");

  asm volatile("ld ra, 8(sp)");
  asm volatile("ld sp, 16(sp)");
  asm volatile("ld gp, 24(sp)");
  asm volatile("ld tp, 32(sp)");
  asm volatile("ld t0, 40(sp)");
  asm volatile("ld t0, 40(sp)");
  asm volatile("ld t1, 48(sp)");
  asm volatile("ld t2, 56(sp)");
  asm volatile("ld s0, 64(sp)");
  asm volatile("ld s1, 72(sp)");
  asm volatile("ld a0, 80(sp)");
  asm volatile("ld a1, 88(sp)");
  asm volatile("ld a2, 96(sp)");
  asm volatile("ld a3, 104(sp)");
  asm volatile("ld a4, 112(sp)");
  asm volatile("ld a5, 120(sp)");
  asm volatile("ld a6, 128(sp)");
  asm volatile("ld a7, 136(sp)");
  asm volatile("ld s2, 144(sp)");
  asm volatile("ld s3, 152(sp)");
  asm volatile("ld s4, 160(sp)");
  asm volatile("ld s5, 168(sp)");
  asm volatile("ld s6, 176(sp)");
  asm volatile("ld s7, 184(sp)");
  asm volatile("ld s8, 192(sp)");
  asm volatile("ld s9, 200(sp)");
  asm volatile("ld s10, 208(sp)");
  asm volatile("ld s11, 216(sp)");
  asm volatile("ld t3, 224(sp)");
  asm volatile("ld t4, 232(sp)");
  asm volatile("ld t5, 240(sp)");
  asm volatile("ld t6, 248(sp)");

  // Read mcause
  asm volatile("csrr t3, mcause");

  asm volatile("addi sp, sp, 272");

  // Filter with mcause and handle here

  asm volatile("mret");
}

static volatile uint8_t INP1[16] __attribute__((aligned(AXI_DWIDTH))) = {
    0x9f, 0xe4, 0x19, 0x20, 0x8f, 0x2e, 0x05, 0xe0,
    0xf9, 0xaa, 0x71, 0xf0, 0xc3, 0x94, 0xbb, 0xd3};
    
void TEST_CASE1(void) {
  VSET(8, e8, m1);
  uint64_t stride = 2;
  asm volatile("vlse8.v v0, (%0), %1" ::"r"(INP1), "r"(stride));
  VCMP_U8(1, v0, 0x9f, 0x19, 0x8f, 0x05, 0xf9, 0x71, 0xc3, 0xbb);
}

//******Checking functionality of  with illegal destination register
// specifier for EMUL********//
// In this test case EMUL=2 and register is v1 which will cause illegal
// instruction exception and set mcause = 2

void TEST_CASE2(void) {
  uint8_t mcause;
  uint64_t stride = 2;
  VSET(8, e16, m4);
  asm volatile("vlse8.v v1, (%0), %1" ::"r"(INP1), "r"(stride));
  asm volatile("addi %[A], t3, 0" : [A] "=r"(mcause));
  XCMP(2, mcause, 2);
}

//*******Checking functionality of vle8 with different values of masking
// register******//
void TEST_CASE3(void) {
  uint64_t stride = 2;
  VSET(8, e8, m1);
  VCLEAR(v3);
  VLOAD_8(v0, 0xFF, 0xFF);
  asm volatile("vlse8.v v3, (%0), %1, v0.t" ::"r"(INP1), "r"(stride));
  VCMP_U8(3, v3, 0x9f, 0x19, 0x8f, 0x05, 0xf9, 0x71, 0xc3, 0xbb);
}

void TEST_CASE4(void) {
  uint64_t stride = 2;
  VSET(16, e8, m1);
  VLOAD_8(v3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0x00, 0x00);
  VSET(8, e8, m1);
  asm volatile("vlse8.v v3, (%0), %1, v0.t" ::"r"(INP1), "r"(stride));
  VSET(16, e8, m1);
  VCMP_U8(4, v3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
}

void TEST_CASE5(void) {
  uint64_t stride = 2;
  VSET(16, e8, m1);
  VCLEAR(v3);
  VLOAD_8(v3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  VSET(8, e8, m1);
  asm volatile("vlse8.v v3, (%0), %1, v0.t" ::"r"(INP1), "r"(stride));
  VSET(16, e8, m1);
  VCMP_U8(5, v3, 1, 0x19, 3, 0x05, 5, 0x71, 7, 0xbb, 9, 10, 11, 12, 13, 14, 15, 16);
}

//******Checking functionality with different combinations of vta and vma*****//
// **** It uses undisturbed policy for tail agnostic and mask agnostic****//
void TEST_CASE6(void) {
  uint64_t stride = 2;
  uint64_t avl;
  VSET(16, e8, m1);
  VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  __asm__ volatile("vsetivli %[A], 8, e8, m1, ta, ma" : [A] "=r"(avl));
  asm volatile("vlse8.v v4, (%0), %1, v0.t" ::"r"(INP1), "r"(stride));
  VSET(16, e8, m1);
  VCMP_U8(6, v4, 1, 0x19, 3, 0x05, 5, 0x71, 7, 0xbb, 9, 10, 11, 12, 13, 14, 15, 16);
}

void TEST_CASE7(void) {
  uint64_t stride = 2;
  uint64_t avl;
  VSET(16, e8, m1);
  VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  __asm__ volatile("vsetivli %[A], 8, e8, m1, ta, mu" : [A] "=r"(avl));
  asm volatile("vlse8.v v4, (%0), %1, v0.t" ::"r"(INP1), "r"(stride));
  VSET(16, e8, m1);
  VCMP_U8(7, v4, 1, 0x19, 3, 0x05, 5, 0x71, 7, 0xbb, 9, 10, 11, 12, 13, 14, 15, 16);
}

void TEST_CASE8(void) {
  uint64_t stride = 2;
  uint64_t avl;
  VSET(16, e8, m1);
  VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  __asm__ volatile("vsetivli %[A], 8, e8, m1, tu, ma" : [A] "=r"(avl));
  asm volatile("vlse8.v v4, (%0), %1, v0.t" ::"r"(INP1), "r"(stride));
  VSET(16, e8, m1);
  VCMP_U8(8, v4, 1, 0x19, 3, 0x05, 5, 0x71, 7, 0xbb, 9, 10, 11, 12, 13, 14, 15, 16);
}

void TEST_CASE9(void) {
  uint64_t stride = 2;
  uint64_t avl;
  VSET(16, e8, m1);
  VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  __asm__ volatile("vsetivli %[A], 8, e8, m1, tu, mu" : [A] "=r"(avl));
  asm volatile("vlse8.v v4, (%0), %1, v0.t" ::"r"(INP1), "r"(stride));
  VSET(16, e8, m1);
  VCMP_U8(9, v4, 1, 0x19, 3, 0x05, 5, 0x71, 7, 0xbb, 9, 10, 11, 12, 13, 14, 15, 16);
}

//*******Checking functionality if encoded EEW is not supported for given SEW
// and LMUL values because EMUL become out of range*****//
// This test case execute lower bound case of EMUL (1/8). If LMUL is changed to
// mf4 or mf8 it will give error because emul become out of range
void TEST_CASE10(void) {
  VSET(8, e32, mf2);
  uint64_t stride = 2;
  asm volatile("vlse8.v v5, (%0), %1" ::"r"(INP1), "r"(stride));
  VCMP_U8(1, v5, 0x9f, 0x19, 0x8f, 0x05, 0xf9, 0x71, 0xc3, 0xbb);
}

//******Checking functionality with different values of vl******//
void TEST_CASE11(void) {
  uint64_t stride = 2;
  VSET(16, e8, m1);
  VLOAD_8(v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VSET(8, e8, m1); // Setting vl=8
  asm volatile("vlse8.v v6, (%0), %1" ::"r"(INP1), "r"(stride));
  VSET(16, e8, m1);
  VCMP_U8(11, v6, 0x9f, 0x19, 0x8f, 0x05, 0xf9, 0x71, 0xc3, 0xbb, 9, 10, 11, 12, 13, 14, 15, 16);
}

void TEST_CASE12(void) {
  uint64_t stride = 2;
  uint64_t avl;
  VSET(16, e8, m1);
  VLOAD_8(v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  __asm__ volatile("vsetivli %[A], 0, e8, m1, ta, ma"
                   : [A] "=r"(avl)); // Setting vl=0
  asm volatile("vlse8.v v6, (%0), %1" ::"r"(INP1), "r"(stride));
  VSET(16, e8, m1);
  VCMP_U8(12, v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
}

void TEST_CASE13(void) {
  uint64_t stride = 2;
  VSET(16, e8, m1);
  VLOAD_8(v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VSET(6, e8, m1); // Setting vl =13
  asm volatile("vlse8.v v6, (%0), %1" ::"r"(INP1), "r"(stride));
  VSET(16, e8, m1);
  VCMP_U8(13, v6, 0x9f, 0x19, 0x8f, 0x05, 0xf9, 0x71, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
}

//******Checking functionality with different vstart value*****//
void TEST_CASE14(void) {
  uint64_t stride = 2;
  uint64_t vstart;
  VSET(16, e8, m1);
  VLOAD_8(v7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  write_csr(vstart, 2);
  VSET(8, e8, m1);
  asm volatile("vlse8.v v7, (%0), %1" ::"r"(INP1), "r"(stride));
  write_csr(vstart, 0);
  VSET(16, e8, m1);
  VCMP_U8(14, v7, 1, 2, 0x8f, 0x05, 0xf9, 0x71, 0xc3, 0xbb, 9, 10, 11, 12, 13, 14, 15, 16);
}

//******Checking functionality with different values of stride****//
void TEST_CASE15(void) {
  VSET(8, e8, m1);
  uint64_t stride = 0;
  asm volatile("vlse8.v v8, (%0), %1" ::"r"(INP1), "r"(stride)); //Stride = 0
  VCMP_U8(15, v8, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f);
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  printf("*****Running tests for vlse8.v*****\n");
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
