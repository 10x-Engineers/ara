#include "vector_macros.h"

#define AXI_DWIDTH 128

#define INIT 98

void reset_vec8(volatile uint8_t *vec, int rst_val, uint64_t len) {
  for (uint64_t i = 0; i < len; ++i)
    vec[i] = rst_val;
}
void reset_vec16(volatile uint16_t *vec, int rst_val, uint64_t len) {
  for (uint64_t i = 0; i < len; ++i)
    vec[i] = rst_val;
}
void reset_vec32(volatile uint32_t *vec, int rst_val, uint64_t len) {
  for (uint64_t i = 0; i < len; ++i)
    vec[i] = rst_val;
}
void reset_vec64(volatile uint64_t *vec, int rst_val, uint64_t len) {
  for (uint64_t i = 0; i < len; ++i)
    vec[i] = rst_val;
}
static volatile uint8_t BUFFER_O8[16] __attribute__((aligned(AXI_DWIDTH))) = {
    INIT, INIT, INIT, INIT, INIT, INIT, INIT, INIT,
    INIT, INIT, INIT, INIT, INIT, INIT, INIT, INIT};
static volatile uint16_t BUFFER_O16[16] __attribute__((aligned(AXI_DWIDTH))) = {
    INIT, INIT, INIT, INIT, INIT, INIT, INIT, INIT,
    INIT, INIT, INIT, INIT, INIT, INIT, INIT, INIT};
static volatile uint32_t BUFFER_O32[16] __attribute__((aligned(AXI_DWIDTH))) = {
    INIT, INIT, INIT, INIT, INIT, INIT, INIT, INIT,
    INIT, INIT, INIT, INIT, INIT, INIT, INIT, INIT};
static volatile uint64_t BUFFER_O64[16] __attribute__((aligned(AXI_DWIDTH))) = {
    INIT, INIT, INIT, INIT, INIT, INIT, INIT, INIT,
    INIT, INIT, INIT, INIT, INIT, INIT, INIT, INIT};
    
    
//**********Checking functionality of with different destination
// registers********//
void TEST_CASE1(void) {
  VSET(16, e32, m1);
  VLOAD_32(v0, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  VLOAD_32(v8, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  asm volatile("vsuxei32.v v0, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VVCMP_U32(1, BUFFER_O32, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
}

void TEST_CASE2(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  VSET(16, e32, m1);
  VLOAD_32(v1, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  VLOAD_32(v8, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  asm volatile("vsuxei32.v v1, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VVCMP_U32(2, BUFFER_O32, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
}

//******Checking functionality of with illegal destination register
// specifier for EMUL********//
// If source register is changed to any odd number register it will give
// runtime error
void TEST_CASE3(void) {
  
  VSET(16, e64, m4);
  VLOAD_64(v4, 0x9fe419208f2e05e0, 0xf9aa71f0c394bbd3, 0xa11a9384a7163840,
        0x99991348a9f38cd1, 0x9fa831c7a11a9384, 0x3819759853987548,
        0x1893179501093489, 0x81937598aa819388, 0x1874754791888188,
        0x3eeeeeeee33111ae, 0x9013930148815808, 0xab8b914891484891,
        0x9031850931584902, 0x3189759837598759, 0x8319599991911111,
        0x8913984898951989);
  VLOAD_32(v2, 0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120);
  asm volatile("vsuxei32.v v4, (%0), v2" ::"r"(&BUFFER_O64[0]));
  VVCMP_U64(3, BUFFER_O64, 0x9fe419208f2e05e0, 0xf9aa71f0c394bbd3, 0xa11a9384a7163840,
        0x99991348a9f38cd1, 0x9fa831c7a11a9384, 0x3819759853987548,
        0x1893179501093489, 0x81937598aa819388, 0x1874754791888188,
        0x3eeeeeeee33111ae, 0x9013930148815808, 0xab8b914891484891,
        0x9031850931584902, 0x3189759837598759, 0x8319599991911111,
        0x8913984898951989);
}


//*******Checking functionality of with different values of masking
// register******//
void TEST_CASE4(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  VSET(16, e32, m1);
  VLOAD_32(v3, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  VLOAD_32(v8, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  VLOAD_8(v0, 0xFF, 0xFF);
  asm volatile("vsuxei32.v v3, (%0), v8, v0.t" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v3);
  VVCMP_U32(4, BUFFER_O32, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
}

void TEST_CASE5(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  VSET(16, e32, m1);
  VLOAD_32(v3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_32(v8, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  asm volatile("vsuxei32.v v3, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v3);
  VLOAD_32(v3, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  VLOAD_8(v0, 0x00, 0x00);
  asm volatile("vsuxei32.v v3, (%0), v8, v0.t" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v3);
  VVCMP_U32(5, BUFFER_O32, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
           16);
}

void TEST_CASE6(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  VSET(16, e32, m1);
  VLOAD_32(v3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_32(v8, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  asm volatile("vsuxei32.v v3, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v3);
  VLOAD_32(v3, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vsuxei32.v v3, (%0), v8, v0.t" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v3);
  VVCMP_U32(6, BUFFER_O32, 1, 0xf9aa71f0, 3, 0x99991348, 5, 0x38197598,
        7, 0x81937598, 9, 0x3eeeeeee, 11, 0xab8b9148,
        13, 0x31897598, 15, 0x89139848);
}

//******Checking functionality with different combinations of vta and vma*****//
void TEST_CASE7(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  uint64_t avl;
  VSET(16, e32, m1);
  VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_32(v8, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  asm volatile("vsuxei32.v v4, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v4);
  VLOAD_8(v0, 0xAA, 0xAA);
  VLOAD_32(v4, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  __asm__ volatile("vsetivli %[A], 12, e32, m1, ta, ma" : [A] "=r"(avl));
  asm volatile("vsuxei32.v v4, (%0), v8, v0.t" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v4);
  VVCMP_U32(7, BUFFER_O32,  1, 0xf9aa71f0, 3, 0x99991348, 5, 0x38197598,
        7, 0x81937598, 9, 0x3eeeeeee, 11, 0xab8b9148,
        13, 14, 15, 16);
}

void TEST_CASE8(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  uint64_t avl;
  VSET(16, e32, m1);
  VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_32(v8, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  asm volatile("vsuxei32.v v4, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v4);
  VLOAD_8(v0, 0xAA, 0xAA);
  VLOAD_32(v4, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  __asm__ volatile("vsetivli %[A], 12, e32, m1, ta, mu" : [A] "=r"(avl));
  asm volatile("vsuxei32.v v4, (%0), v8, v0.t" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v4);
  VVCMP_U32(8, BUFFER_O32,  1, 0xf9aa71f0, 3, 0x99991348, 5, 0x38197598,
        7, 0x81937598, 9, 0x3eeeeeee, 11, 0xab8b9148,
        13, 14, 15, 16);
}

void TEST_CASE9(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  uint64_t avl;
  VSET(16, e32, m1);
  VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_32(v8, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  asm volatile("vsuxei32.v v4, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v4);
  VLOAD_8(v0, 0xAA, 0xAA);
  VLOAD_32(v4, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  __asm__ volatile("vsetivli %[A], 12, e32, m1, tu, ma" : [A] "=r"(avl));
  asm volatile("vsuxei32.v v4, (%0), v8, v0.t" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v4);
  VVCMP_U32(9, BUFFER_O32,  1, 0xf9aa71f0, 3, 0x99991348, 5, 0x38197598,
        7, 0x81937598, 9, 0x3eeeeeee, 11, 0xab8b9148,
        13, 14, 15, 16);
}

void TEST_CASE10(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  uint64_t avl;
  VSET(16, e32, m1);
  VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_32(v8, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  asm volatile("vsuxei32.v v4, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v4);
  VLOAD_8(v0, 0xAA, 0xAA);
  VLOAD_32(v4, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  __asm__ volatile("vsetivli %[A], 12, e32, m1, tu, mu" : [A] "=r"(avl));
  asm volatile("vsuxei32.v v4, (%0), v8, v0.t" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v4);
  VVCMP_U32(10, BUFFER_O32,  1, 0xf9aa71f0, 3, 0x99991348, 5, 0x38197598,
        7, 0x81937598, 9, 0x3eeeeeee, 11, 0xab8b9148,
        13, 14, 15, 16);
}

//*******Checking functionality if encoded EEW is not supported for given SEW
// and LMUL values because EMUL become out of range*****// If LMUL is changed to
// mf8 it will give error because emul become less than 1/8 (EMUL = 1/16)
void TEST_CASE11(void) {
  VSET(8, e32, mf2);
  VLOAD_32(v5, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598);
  VLOAD_32(v8, 0, 4, 8, 12, 16, 20, 24, 28);
  asm volatile("vsuxei32.v v5, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VVCMP_U32(11, BUFFER_O32, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598);
}

// If LMUL is changed to m4 it will give error because emul become greater than 8
// (EMUL = 16)

void TEST_CASE12(void) {
  VSET(16, e8, m2);
  VLOAD_8(v4, 0xe0, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88, 0x88, 0xae, 0x08,
          0x91, 0x02, 0x59, 0x11, 0x89);
  VLOAD_32(v8, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
  asm volatile("vsuxei32.v v4, (%0), v8" ::"r"(&BUFFER_O8[0]));
  VVCMP_U8(12, BUFFER_O8, 0xe0, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88, 0x88,
           0xae, 0x08, 0x91, 0x02, 0x59, 0x11, 0x89);
}

//******Checking functionality with different values of vl******//
void TEST_CASE13(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  VSET(16, e32, m1);
  VLOAD_32(v6, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  VLOAD_32(v8, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  asm volatile("vsuxei32.v v6, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v6);
  VVCMP_U32(13, BUFFER_O32, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
}

void TEST_CASE14(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  uint64_t avl;
  VSET(16, e32, m1);
  VLOAD_32(v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_32(v8, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  asm volatile("vsuxei32.v v6, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v6);
  VLOAD_32(v6, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  __asm__ volatile("vsetivli %[A], 0, e32, m1, tu, ma" : [A] "=r"(avl));
  asm volatile("vsuxei32.v v6, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VSET(16, e32, m1);
  VVCMP_U32(14, BUFFER_O32, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
           16);
}

void TEST_CASE15(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  VSET(16, e32, m1);
  VLOAD_32(v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_32(v8, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  asm volatile("vsuxei32.v v6, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v6);
  VLOAD_32(v6, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  VSET(13, e32, m1);
  asm volatile("vsuxei32.v v6, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VVCMP_U32(15, BUFFER_O32, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 14, 15, 16);
}

//******Checking functionality with different vstart value*****//
void TEST_CASE16(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  VSET(16, e32, m1);
  VLOAD_32(v7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  asm volatile("vsuxei32.v v7, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VCLEAR(v7);
  VLOAD_32(v7, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  VSET(13, e32, m1);
  write_csr(vstart, 2);
  asm volatile("vsuxei32.v v7, (%0), v8" ::"r"(&BUFFER_O32[0]));
  write_csr(vstart, 0);
  VVCMP_U32(16, BUFFER_O32, 1, 2, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 14, 15, 16);
}

//****Checking functionality with different values of SEW for data***//

void TEST_CASE17(void) {
  VSET(16, e8, m1);
  VLOAD_8(v12, 0xe0, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88, 0x88, 0xae, 0x08,
          0x91, 0x02, 0x59, 0x11, 0x89);
  VLOAD_32(v8, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
  asm volatile("vsuxei32.v v12, (%0), v8" ::"r"(&BUFFER_O8[0]));
  VVCMP_U8(17, BUFFER_O8, 0xe0, 0xd3, 0x40, 0xd1, 0x84, 0x48, 0x89, 0x88, 0x88,
           0xae, 0x08, 0x91, 0x02, 0x59, 0x11, 0x89);
}
void TEST_CASE18(void) {
  reset_vec16(&BUFFER_O16[0], INIT, 16);
  VSET(16, e16, m1);
  VLOAD_32(v8, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
  VLOAD_16(v12, 0x05e0, 0xbbd3, 0x3840, 0x8cd1, 0x9384, 0x7548, 0x3489, 0x9388,
        0x8188, 0x11ae, 0x5808, 0x4891, 0x4902, 0x8759, 0x1111, 0x1989);
  asm volatile("vsuxei32.v v12, (%0), v8" ::"r"(&BUFFER_O16[0]));
  VVCMP_U16(18, BUFFER_O16, 0x05e0, 0xbbd3, 0x3840, 0x8cd1, 0x9384, 0x7548, 0x3489, 0x9388,
        0x8188, 0x11ae, 0x5808, 0x4891, 0x4902, 0x8759, 0x1111, 0x1989);
}

void TEST_CASE19(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  VSET(16, e32, m1);
  VLOAD_32(v8, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60);
  VLOAD_32(v9, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  asm volatile("vsuxei32.v v9, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VVCMP_U32(19, BUFFER_O32, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
}

void TEST_CASE20(void) {
  reset_vec64(&BUFFER_O64[0], INIT, 16);
  VSET(16, e64, m1);
  VLOAD_32(v8, 0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120);
  VLOAD_64(v9,  0x9fe419208f2e05e0, 0xf9aa71f0c394bbd3, 0xa11a9384a7163840,
        0x99991348a9f38cd1, 0x9fa831c7a11a9384, 0x3819759853987548,
        0x1893179501093489, 0x81937598aa819388, 0x1874754791888188,
        0x3eeeeeeee33111ae, 0x9013930148815808, 0xab8b914891484891,
        0x9031850931584902, 0x3189759837598759, 0x8319599991911111,
        0x8913984898951989);
  asm volatile("vsuxei32.v v9, (%0), v8" ::"r"(&BUFFER_O64[0]));
  VVCMP_U64(20, BUFFER_O64, 0x9fe419208f2e05e0, 0xf9aa71f0c394bbd3, 0xa11a9384a7163840,
        0x99991348a9f38cd1, 0x9fa831c7a11a9384, 0x3819759853987548,
        0x1893179501093489, 0x81937598aa819388, 0x1874754791888188,
        0x3eeeeeeee33111ae, 0x9013930148815808, 0xab8b914891484891,
        0x9031850931584902, 0x3189759837598759, 0x8319599991911111,
        0x8913984898951989);
}

//***Checking functionality with different values of indeces**

void TEST_CASE21(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  VSET(16, e32, m1);
  VLOAD_32(v8, 4, 60);
  VLOAD_32(v10, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848);
  VSET(2, e32, m1);
  asm volatile("vsuxei32.v v10, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VVCMP_U32(21, BUFFER_O32, INIT, 0x9fe41920, INIT, INIT, INIT, INIT, INIT, INIT,
    INIT, INIT, INIT, INIT, INIT, INIT, INIT, 0xf9aa71f0);
}

void TEST_CASE22(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  VSET(16, e32, m1);
  VCLEAR(v8);
  asm volatile("vsuxei32.v v10, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VVCMP_U32(22, BUFFER_O32, 0x89139848, INIT, INIT, INIT, INIT, INIT, INIT, INIT,
    INIT, INIT, INIT, INIT, INIT, INIT, INIT, INIT);
}

void TEST_CASE23(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  VSET(16, e32, m1);
  VLOAD_32(v8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16);
  asm volatile("vsuxei32.v v10, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VVCMP_U32(23, BUFFER_O32, INIT, INIT, INIT, INIT, 0x89139848, INIT, INIT, INIT,
    INIT, INIT, INIT, INIT, INIT, INIT, INIT, INIT);
}    

void TEST_CASE24(void) {
  reset_vec32(&BUFFER_O32[0], INIT, 16);
  VSET(12, e32, m1);
  VLOAD_32(v8, 4, 8, 12, 16, 20, 28, 32, 36, 44, 48, 52, 60);
 asm volatile("vsuxei32.v v10, (%0), v8" ::"r"(&BUFFER_O32[0]));
  VVCMP_U32(24, BUFFER_O32, INIT, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7,INIT, 0x38197598,
        0x18931795, 0x81937598, INIT, 0x18747547, 0x3eeeeeee, 0x90139301, INIT,0xab8b9148,);
}

int main(void) {
  INIT_CHECK();
  enable_vec();
  
  printf("*****Running tests for vsuxei32.v*****\n");
  
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
