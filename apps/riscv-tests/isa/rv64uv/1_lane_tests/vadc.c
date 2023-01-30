// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, -7, 7);
  VLOAD_8(v2, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, -8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vvm v3, v1, v2, v0");
  VCMP_U8(1, v3, 9, 10, 9, 10, 9, 10, 9, 10, 2, 5, 6, 9, 10, 13, 0, 0);

  VSET(16, e16, m2);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, -7, 7);
  VLOAD_16(v4, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, -8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vvm v6, v2, v4, v0");
  VCMP_U16(2, v6, 9, 10, 9, 10, 9, 10, 9, 10, 2, 5, 6, 9, 10, 13, 0, 0);

  VSET(16, e32, m4);
  VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, -7, 7);
  VLOAD_32(v8, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, -8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vvm v12, v4, v8, v0");
  VCMP_U32(3, v12, 9, 10, 9, 10, 9, 10, 9, 10, 2, 5, 6, 9, 10, 13, 0, 0);

  VSET(16, e64, m8);
  VLOAD_64(v8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, -7, 7);
  VLOAD_64(v16, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, -8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vvm v24, v8, v16, v0");
  VCMP_U64(4, v24, 9, 10, 9, 10, 9, 10, 9, 10, 2, 5, 6, 9, 10, 13, 0, 0);
};

void TEST_CASE2(void) {
  const uint32_t scalar = 5;

  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  VCMP_U8(5, v3, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);

  VSET(16, e16, m2);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vxm v4, v2, %[A], v0" ::[A] "r"(scalar));
  VCMP_U16(6, v4, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);

  VSET(16, e32, m4);
  VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vxm v8, v4, %[A], v0" ::[A] "r"(scalar));
  VCMP_U32(7, v8, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);

  VSET(16, e64, m8);
  VLOAD_64(v8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vxm v16, v8, %[A], v0" ::[A] "r"(scalar));
  VCMP_U64(8, v16, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);
};

void TEST_CASE3(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vim v3, v1, 5, v0");
  VCMP_U8(9, v3, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);

  VSET(16, e16, m2);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vim v4, v2, 5, v0");
  VCMP_U16(10, v4, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);

  VSET(16, e32, m4);
  VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vim v8, v4, 5, v0");
  VCMP_U32(11, v8, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);

  VSET(16, e64, m8);
  VLOAD_64(v8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vim v16, v8, 5, v0");
  VCMP_U64(12, v16, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);
};

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();

  EXIT_CHECK();
}
