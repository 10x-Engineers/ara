// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1(void) {
  uint64_t vxsat = -1;
  VSET(4, e8, m1);
  VLOAD_8(v1, -80, 2, 100, 4);
  VLOAD_8(v2, -90, 2, 50, 4);
  __asm__ volatile("vsadd.vv v3, v1, v2" ::);
  VCMP_U8(1, v3, 0x80, 4, 127, 8);
  read_vxsat(vxsat);
  check_vxsat(1, vxsat, 1);
  check_vxsat(1, vxsat >> 1,
              0); // Bits vxsat[XLEN-1:1] should be written as zeros
}

void TEST_CASE2(void) {
  uint64_t vxsat = -1;
  VSET(4, e8, m1);
  VLOAD_8(v1, -80, 2, 100, 4);
  VLOAD_8(v2, -90, 2, 50, 4);
  VLOAD_8(v0, 0xA, 0x0, 0x0, 0x0);
  VCLEAR(v3);
  __asm__ volatile("vsadd.vv v3, v1, v2, v0.t" ::);
  VCMP_U8(2, v3, 0, 4, 0, 8);
  read_vxsat(vxsat);
  check_vxsat(2, vxsat, 0);
  check_vxsat(2, vxsat >> 1,
              0); // Bits vxsat[XLEN-1:1] should be written as zeros
}

void TEST_CASE3(void) {
  uint64_t vxsat = -1;
  VSET(4, e32, m1);
  VLOAD_32(v1, 1, 0x7FFFFFFB, 3, 4);
  __asm__ volatile("vsadd.vi v3, v1, 5" ::);
  VCMP_U32(3, v3, 6, 0x7FFFFFFF, 8, 9);
  read_vxsat(vxsat);
  check_vxsat(3, vxsat, 1);
  check_vxsat(3, vxsat >> 1,
              0); // Bits vxsat[XLEN-1:1] should be written as zeros
}

// Dont use VCLEAR here, it results in a glitch where are values are off by 1
void TEST_CASE4(void) {
  uint64_t vxsat = -1;
  VSET(4, e32, m1);
  VLOAD_32(v1, 1, 0x7FFFFFFC, 0xFFFFFFFD, 2);
  VLOAD_32(v0, 0xA, 0x0, 0x0, 0x0);
  VCLEAR(v3);
  __asm__ volatile("vsadd.vi v3, v1, 5, v0.t" ::);
  VCMP_U32(4, v3, 0, 0x7FFFFFFF, 0, 7);
  read_vxsat(vxsat);
  check_vxsat(4, vxsat, 1);
  check_vxsat(4, vxsat >> 1,
              0); // Bits vxsat[XLEN-1:1] should be written as zeros
}

void TEST_CASE5(void) {
  uint64_t vxsat = -1;
  VSET(4, e32, m1);
  VLOAD_32(v1, 0x7FFFFFFD, 2, 3, 4);
  const uint32_t scalar = 5;
  __asm__ volatile("vsadd.vx v3, v1, %[A]" ::[A] "r"(scalar));
  VCMP_U32(5, v3, 0x7FFFFFFF, 7, 8, 9);
  read_vxsat(vxsat);
  check_vxsat(5, vxsat, 1);
  check_vxsat(5, vxsat >> 1,
              0); // Bits vxsat[XLEN-1:1] should be written as zeros
}

// Dont use VCLEAR here, it results in a glitch where are values are off by 1
void TEST_CASE6(void) {
  uint64_t vxsat = -1;
  VSET(4, e32, m1);
  VLOAD_32(v1, 1, 0x7ffffffC, 3, 4);
  const uint32_t scalar = 5;
  VLOAD_32(v0, 0xA, 0x0, 0x0, 0x0);
  VCLEAR(v3);
  __asm__ volatile("vsadd.vx v3, v1, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_U32(6, v3, 0, 0x7FFFFFFF, 0, 9);
  read_vxsat(vxsat);
  check_vxsat(6, vxsat, 1);
  check_vxsat(6, vxsat >> 1,
              0); // Bits vxsat[XLEN-1:1] should be written as zeros
}

void TEST_CASE7(void) {
  uint64_t vxsat = -1;
  VSET(4, e8, m1);
  VLOAD_8(v1, 133, 2, 220, 4);
  VLOAD_8(v2, 133, 2, 50, 4);
  __asm__ volatile("vsaddu.vv v3, v1, v2" ::);
  VCMP_U8(7, v3, 255, 4, 255, 8);
  read_vxsat(vxsat);
  check_vxsat(7, vxsat, 1);
  check_vxsat(7, vxsat >> 1,
              0); // Bits vxsat[XLEN-1:1] should be written as zeros
}

void TEST_CASE8(void) {
  uint64_t vxsat = -1;
  VSET(4, e8, m1);
  VLOAD_8(v1, 1, 154, 3, 2);
  VLOAD_8(v2, 1, 124, 3, 2);
  VLOAD_8(v0, 0xA, 0x0, 0x0, 0x0);
  VCLEAR(v3);
  __asm__ volatile("vsaddu.vv v3, v1, v2, v0.t" ::);
  VCMP_U8(8, v3, 0, 255, 0, 4);
  read_vxsat(vxsat);
  check_vxsat(8, vxsat, 1);
  check_vxsat(8, vxsat >> 1,
              0); // Bits vxsat[XLEN-1:1] should be written as zeros
}

void TEST_CASE9(void) {
  uint64_t vxsat = -1;
  VSET(4, e32, m1);
  VLOAD_32(v1, 1, 0xFFFFFFFB, 3, 4);
  __asm__ volatile("vsaddu.vi v3, v1, 5" ::);
  VCMP_U32(9, v3, 6, 0xFFFFFFFF, 8, 9);
  read_vxsat(vxsat);
  check_vxsat(9, vxsat, 1);
  check_vxsat(9, vxsat >> 1,
              0); // Bits vxsat[XLEN-1:1] should be written as zeros
}

// Dont use VCLEAR here, it results in a glitch where are values are off by 1
void TEST_CASE10(void) {
  uint64_t vxsat = -1;
  VSET(4, e32, m1);
  VLOAD_32(v1, 1, 0xFFFFFFFC, 0xFFFFFFFD, 2);
  VLOAD_32(v0, 0xA, 0x0, 0x0, 0x0);
  VCLEAR(v3);
  __asm__ volatile("vsaddu.vi v3, v1, 5, v0.t" ::);
  VCMP_U32(10, v3, 0, 0xFFFFFFFF, 0, 7);
  read_vxsat(vxsat);
  check_vxsat(10, vxsat, 1);
  check_vxsat(10, vxsat >> 1,
              0); // Bits vxsat[XLEN-1:1] should be written as zeros
}

void TEST_CASE11(void) {
  uint64_t vxsat = -1;
  VSET(4, e32, m1);
  VLOAD_32(v1, 0xFFFFFFFD, 2, 3, 4);
  const uint32_t scalar = 5;
  __asm__ volatile("vsaddu.vx v3, v1, %[A]" ::[A] "r"(scalar));
  VCMP_U32(11, v3, 0xFFFFFFFF, 7, 8, 9);
  read_vxsat(vxsat);
  check_vxsat(11, vxsat, 1);
  check_vxsat(11, vxsat >> 1,
              0); // Bits vxsat[XLEN-1:1] should be written as zeros
}

// Dont use VCLEAR here, it results in a glitch where are values are off by 1
void TEST_CASE12(void) {
  uint64_t vxsat = -1;
  VSET(4, e32, m1);
  VLOAD_32(v1, 1, 0xfffffffC, 3, 4);
  const uint32_t scalar = 5;
  VLOAD_32(v0, 0xA, 0x0, 0x0, 0x0);
  VCLEAR(v3);
  __asm__ volatile("vsaddu.vx v3, v1, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_U32(12, v3, 0, 0xFFFFFFFF, 0, 9);
  read_vxsat(vxsat);
  check_vxsat(12, vxsat, 1);
  check_vxsat(12, vxsat >> 1,
              0); // Bits vxsat[XLEN-1:1] should be written as zeros
}

void TEST_CASE13(void) {
  uint64_t vxsat = -1;
  VSET(4, e32, m1);
  VLOAD_32(v1, 1, 0x0000FFFF, 3, 4);
  VLOAD_32(v2, 0xA, 0xFFFF0000, 0x0, 0x0);
  VCLEAR(v3);
  __asm__ volatile("vsaddu.vv v3, v1, v2" ::);
  VCMP_U32(13, v3, 0xB, 0xFFFFFFFF, 3, 4);
  read_vxsat(vxsat);
  check_vxsat(13, vxsat, 0);
  check_vxsat(13, vxsat >> 1,
              0); // Bits vxsat[XLEN-1:1] should be written as zeros
}

int main(void) {
  INIT_CHECK();
  enable_vec();
  enable_fp();
  // vsadd.vv based cases
  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();
  TEST_CASE5();
  TEST_CASE6();
  // vsaddu.vv based cases
  TEST_CASE7();
  TEST_CASE8();
  TEST_CASE9();
  TEST_CASE10();
  TEST_CASE11();
  TEST_CASE12();
  TEST_CASE13();
  EXIT_CHECK();
}
