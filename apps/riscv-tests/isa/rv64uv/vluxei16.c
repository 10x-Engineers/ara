#include "vector_macros.h"

#define AXI_DWIDTH 128

static volatile uint8_t ALIGNED_I8[16] __attribute__((aligned(AXI_DWIDTH))) = {
    0xe0, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88,
    0x88, 0xae, 0x08, 0x91, 0x02, 0x59, 0x11, 0x89};

static volatile uint16_t ALIGNED_I16[16]
    __attribute__((aligned(AXI_DWIDTH))) = {
        0x05e0, 0xbbd3, 0x3840, 0x8cd1, 0x9384, 0x7548, 0x3489, 0x9388,
        0x8188, 0x11ae, 0x5808, 0x4891, 0x4902, 0x8759, 0x1111, 0x1989};

static volatile uint32_t ALIGNED_I32[16]
    __attribute__((aligned(AXI_DWIDTH))) = {
        0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848};

static volatile uint64_t ALIGNED_I64[16]
    __attribute__((aligned(AXI_DWIDTH))) = {
        0x9fe419208f2e05e0, 0xf9aa71f0c394bbd3, 0xa11a9384a7163840,
        0x99991348a9f38cd1, 0x9fa831c7a11a9384, 0x3819759853987548,
        0x1893179501093489, 0x81937598aa819388, 0x1874754791888188,
        0x3eeeeeeee33111ae, 0x9013930148815808, 0xab8b914891484891,
        0x9031850931584902, 0x3189759837598759, 0x8319599991911111,
        0x8913984898951989};


//****Checking functionality with different destination registers***//        
void TEST_CASE1(void) {
  VSET(16, e16, m1);
  VLOAD_16(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  asm volatile("vluxei16.v v0, (%0), v8" ::"r"(&ALIGNED_I16[0]));
  VCMP_U16(1, v0, 0x05e0, 0xbbd3, 0x3840, 0x8cd1, 0x9384, 0x7548, 0x3489, 0x9388,
        0x8188, 0x11ae, 0x5808, 0x4891, 0x4902, 0x8759, 0x1111, 0x1989);
}

void TEST_CASE2(void) {
  VSET(16, e16, m1);
  VLOAD_16(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  asm volatile("vluxei16.v v1, (%0), v8" ::"r"(&ALIGNED_I16[0]));
  VCMP_U16(2, v1, 0x05e0, 0xbbd3, 0x3840, 0x8cd1, 0x9384, 0x7548, 0x3489, 0x9388,
        0x8188, 0x11ae, 0x5808, 0x4891, 0x4902, 0x8759, 0x1111, 0x1989);
}

//Checking functionality with illegal destination register specifier for EMUL
//If sorce register is changed to any odd number register it will give 
//runtime error

void TEST_CASE3(void) {
  VSET(16, e32, m4);
  VLOAD_16(v2, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  asm volatile("vluxei16.v v4, (%0), v2" ::"r"(&ALIGNED_I32[0]));
  VCMP_U32(3, v4, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
}

//**Checking functionality with different values of masking register**

void TEST_CASE4(void) {
  VSET(16, e16, m1);
  VLOAD_16(v3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xFF, 0xFF);
  VLOAD_16(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  asm volatile("vluxei16.v v3, (%0), v8, v0.t" ::"r"(&ALIGNED_I16[0]));
  VCMP_U16(4, v3, 0x05e0, 0xbbd3, 0x3840, 0x8cd1, 0x9384, 0x7548, 0x3489, 0x9388,
        0x8188, 0x11ae, 0x5808, 0x4891, 0x4902, 0x8759, 0x1111, 0x1989);
}

void TEST_CASE5(void) {
  VSET(16, e16, m1);
  VLOAD_16(v3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0x00, 0x00);
  VLOAD_16(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  asm volatile("vluxei16.v v3, (%0), v8, v0.t" ::"r"(&ALIGNED_I16[0]));
  VCMP_U16(5, v3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
}

void TEST_CASE6(void) {
  VSET(16, e16, m1);
  VLOAD_16(v3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  VLOAD_16(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  asm volatile("vluxei16.v v3, (%0), v8, v0.t" ::"r"(&ALIGNED_I16[0]));
  VCMP_U16(6, v3, 1, 0xbbd3, 3, 0x8cd1, 5, 0x7548, 7, 0x9388,
        9, 0x11ae, 11, 0x4891, 13, 0x8759, 15, 0x1989);
}

//******Checking functionality with different combinations of vta and vma*****//

void TEST_CASE7(void) {
  uint64_t avl;
  VSET(16, e16, m1);
  VLOAD_16(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  VLOAD_16(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  asm volatile("vsetivli %[A], 12, e16, m1, ta, ma" : [A] "=r"(avl));
  asm volatile("vluxei16.v v4, (%0), v8, v0.t" ::"r"(&ALIGNED_I16[0]));
  VSET(16, e16, m1);
  VCMP_U16(7, v4, 1, 0xbbd3, 3, 0x8cd1, 5, 0x7548, 7, 0x9388,
        9, 0x11ae, 11, 0x4891, 13, 14, 15, 16);
}

void TEST_CASE8(void) {
  uint64_t avl;
  VSET(16, e16, m1);
  VLOAD_16(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  VLOAD_16(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  asm volatile("vsetivli %[A], 12, e16, m1, ta, mu" : [A] "=r"(avl));
  asm volatile("vluxei16.v v4, (%0), v8, v0.t" ::"r"(&ALIGNED_I16[0]));
  VSET(16, e16, m1);
  VCMP_U16(8, v4, 1, 0xbbd3, 3, 0x8cd1, 5, 0x7548, 7, 0x9388,
        9, 0x11ae, 11, 0x4891, 13, 14, 15, 16);
}

void TEST_CASE9(void) {
  uint64_t avl;
  VSET(16, e16, m1);
  VLOAD_16(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  VLOAD_16(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  asm volatile("vsetivli %[A], 12, e16, m1, tu, ma" : [A] "=r"(avl));
  asm volatile("vluxei16.v v4, (%0), v8, v0.t" ::"r"(&ALIGNED_I16[0]));
  VSET(16, e16, m1);
  VCMP_U16(9, v4, 1, 0xbbd3, 3, 0x8cd1, 5, 0x7548, 7, 0x9388,
        9, 0x11ae, 11, 0x4891, 13, 14, 15, 16);
}

void TEST_CASE10(void) {
  uint64_t avl;
  VSET(16, e16, m1);
  VLOAD_16(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  VLOAD_16(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  asm volatile("vsetivli %[A], 12, e16, m1, tu, mu" : [A] "=r"(avl));
  asm volatile("vluxei16.v v4, (%0), v8, v0.t" ::"r"(&ALIGNED_I16[0]));
  VSET(16, e16, m1);
  VCMP_U16(10, v4, 1, 0xbbd3, 3, 0x8cd1, 5, 0x7548, 7, 0x9388,
        9, 0x11ae, 11, 0x4891, 13, 14, 15, 16);
}

//*******Checking functionality if encoded EEW is not supported for given SEW
// and LMUL values because EMUL become out of range*****// If LMUL is changed to
// mf8 it will give error because emul become less than 1/8 (EMUL = 1/16)

void TEST_CASE11(void) {
  VSET(8, e32, mf2);
  VLOAD_16(v8, 0, 4, 8, 12, 16, 20, 24, 28);
  asm volatile("vluxei16.v v5, (%0), v8" ::"r"(&ALIGNED_I32[0]));
  VCMP_U32(11, v5,0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598);
}

// If LMUL is changed to m8 it will give error because emul become greater than 8
// (EMUL = 16)
void TEST_CASE12(void) {
  VSET(8, e8, m4);
  VLOAD_16(v8, 0, 1, 2, 3, 4, 5, 6, 7);
  asm volatile("vluxei16.v v4, (%0), v8" ::"r"(&ALIGNED_I8[0]));
  VCMP_U8(12, v4,0xe0, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88);
}


//******Checking functionality with different values of vl******//
void TEST_CASE13(void) {
  VSET(16, e16, m1);
  VLOAD_16(v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_16(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  asm volatile("vluxei16.v v6, (%0), v8" ::"r"(&ALIGNED_I16[0]));
  VCMP_U16(13, v6, 0x05e0, 0xbbd3, 0x3840, 0x8cd1, 0x9384, 0x7548, 0x3489, 0x9388,
        0x8188, 0x11ae, 0x5808, 0x4891, 0x4902, 0x8759, 0x1111, 0x1989);
}
void TEST_CASE14(void) {
  uint64_t avl;
  VSET(16, e16, m1);
  VLOAD_16(v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_16(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  asm volatile("vsetivli %[A], 0, e16, m1, ta, ma" : [A] "=r"(avl));
  asm volatile("vluxei16.v v6, (%0), v8" ::"r"(&ALIGNED_I16[0]));
  VSET(16, e16, m1);
  VCMP_U16(14, v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
}

void TEST_CASE15(void) {
  VSET(16, e16, m1);
  VLOAD_16(v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_16(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  VSET(13, e16, m1);
  asm volatile("vluxei16.v v6, (%0), v8" ::"r"(&ALIGNED_I16[0]));
  VSET(16, e16, m1);
  VCMP_U16(15, v6, 0x05e0, 0xbbd3, 0x3840, 0x8cd1, 0x9384, 0x7548, 0x3489, 0x9388,
        0x8188, 0x11ae, 0x5808, 0x4891, 0x4902, 14, 15, 16);
}

//******Checking functionality with different vstart value*****//
void TEST_CASE16(void) {
  VSET(16, e16, m1);
  VLOAD_16(v7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_16(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  write_csr(vstart, 2);
  asm volatile("vluxei16.v v7, (%0), v8" ::"r"(&ALIGNED_I16[0]));
  write_csr(vstart, 0);
  VCMP_U16(16, v7, 1, 2, 0x3840, 0x8cd1, 0x9384, 0x7548, 0x3489, 0x9388,
        0x8188, 0x11ae, 0x5808, 0x4891, 0x4902, 0x8759, 0x1111, 0x1989);
}

//****Checking functionality with different values of SEW for data***//

void TEST_CASE17(void) {
  VSET(16, e8, m1);
  VLOAD_16(v8, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
  asm volatile("vluxei16.v v10, (%0), v8" ::"r"(&ALIGNED_I8[0]));
  VCMP_U8(17, v10, 0xe0, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88,
    0x88, 0xae, 0x08, 0x91, 0x02, 0x59, 0x11, 0x89);
}

void TEST_CASE18(void) {
  VSET(16, e16, m1);
  VLOAD_16(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  asm volatile("vluxei16.v v9, (%0), v8" ::"r"(&ALIGNED_I16[0]));
  VCMP_U16(18, v9, 0x05e0, 0xbbd3, 0x3840, 0x8cd1, 0x9384, 0x7548, 0x3489, 0x9388,
        0x8188, 0x11ae, 0x5808, 0x4891, 0x4902, 0x8759, 0x1111, 0x1989);
}

void TEST_CASE19(void) {
  VSET(16, e32, m1);
  VLOAD_16(v8, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  asm volatile("vluxei16.v v9, (%0), v8" ::"r"(&ALIGNED_I32[0]));
  VCMP_U32(19, v9, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
}

void TEST_CASE20(void) {
  VSET(16, e64, m1);
  VLOAD_16(v8, 0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120);
  asm volatile("vluxei16.v v9, (%0), v8" ::"r"(&ALIGNED_I64[0]));
  VCMP_U64(20, v9, 0x9fe419208f2e05e0, 0xf9aa71f0c394bbd3, 0xa11a9384a7163840,
        0x99991348a9f38cd1, 0x9fa831c7a11a9384, 0x3819759853987548,
        0x1893179501093489, 0x81937598aa819388, 0x1874754791888188,
        0x3eeeeeeee33111ae, 0x9013930148815808, 0xab8b914891484891,
        0x9031850931584902, 0x3189759837598759, 0x8319599991911111,
        0x8913984898951989);
}

//***Checking functionality with different values of indeces**

void TEST_CASE21(void) {
  VSET(2, e16, m1);
  VLOAD_16(v8, 2, 30);
  asm volatile("vluxei16.v v10, (%0), v8" ::"r"(&ALIGNED_I16[0]));
  VCMP_U16(21, v10, 0xbbd3, 0x1989);
}

void TEST_CASE22(void) {
  VSET(16, e16, m1);
  VCLEAR(v8);
  asm volatile("vluxei16.v v10, (%0), v8" ::"r"(&ALIGNED_I16[0]));
  VCMP_U16(22, v10, 0x05e0, 0x05e0, 0x05e0, 0x05e0, 0x05e0, 0x05e0, 0x05e0, 0x05e0,
    0x05e0, 0x05e0, 0x05e0, 0x05e0, 0x05e0, 0x05e0, 0x05e0, 0x05e0);
}

void TEST_CASE23(void) {
  VSET(16, e16, m1);
  VLOAD_16(v8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8);
  asm volatile("vluxei16.v v10, (%0), v8" ::"r"(&ALIGNED_I16[0]));
  VCMP_U16(23, v10, 0x9384, 0x9384, 0x9384, 0x9384, 0x9384, 0x9384, 0x9384, 0x9384,
    0x9384, 0x9384, 0x9384, 0x9384, 0x9384, 0x9384, 0x9384, 0x9384);
}    

void TEST_CASE24(void) {
  VSET(12, e16, m1);
  VLOAD_16(v8, 2, 4, 6, 8, 10, 14, 16, 18, 22, 24, 26, 30);
  asm volatile("vluxei16.v v0, (%0), v8" ::"r"(&ALIGNED_I16[0]));
  VCMP_U16(24, v0, 0xbbd3, 0x3840, 0x8cd1, 0x9384, 0x7548, 0x9388,
        0x8188, 0x11ae, 0x4891, 0x4902, 0x8759, 0x1989);
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  printf("*****Running tests for vluxei16.v*****\n");
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
  TEST_CASE16();
  TEST_CASE17();
  TEST_CASE18();
  TEST_CASE19();
  TEST_CASE20();
  TEST_CASE21();
  TEST_CASE22();
  TEST_CASE23();
  TEST_CASE24();
  
  EXIT_CHECK();
}
