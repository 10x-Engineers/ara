// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0xff, 0x00, 0xf0, 0x0f, 0xff, 0x00, 0xf0, 0x0f, 0xff, 0x00, 0xf0,
          0x0f, 0xff, 0x00, 0xf0, 0x0f);
  VLOAD_8(v3, 0xf2, 0x01, 0xf0, 0x0f, 0xf2, 0x01, 0xf0, 0x0f, 0xf2, 0x01, 0xf0,
          0x0f, 0xf2, 0x01, 0xf0, 0x0f);
  VCLEAR(v1);
  asm volatile("vmseq.vv v1, v2, v3");
  VSET(2, e8, m1);
  VCMP_U8(1, v1, 0xcc, 0xcc);

  VSET(16, e16, m2);
  VLOAD_16(v4, 0xffff, 0x0000, 0xf0f0, 0x0f0f, 0xffff, 0x0000, 0xf0f0, 0x0f0f,
           0xffff, 0x0000, 0xf0f0, 0x0f0f, 0xffff, 0x0000, 0xf0f0, 0x0f0f);
  VLOAD_16(v6, 0xf2ff, 0x0100, 0xf0f0, 0x0f0f, 0xf2ff, 0x0100, 0xf0f0, 0x0f0f,
           0xf2ff, 0x0100, 0xf0f0, 0x0f0f, 0xf2ff, 0x0100, 0xf0f0, 0x0f0f);
  VCLEAR(v2);
  asm volatile("vmseq.vv v2, v4, v6");
  VSET(2, e8, m1);
  VCMP_U8(2, v2, 0xcc, 0xcc);

  VSET(16, e32, m4);
  VLOAD_32(v8, 0xffffffff, 0x00000000, 0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff,
           0x00000000, 0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff, 0x00000000,
           0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff, 0x00000000, 0xf0f0f0f0,
           0x0f0f0f0f);
  VLOAD_32(v12, 0xfff2ffff, 0x01000000, 0xf0f0f0f0, 0x0f0f0f0f, 0xfff2ffff,
           0x01000000, 0xf0f0f0f0, 0x0f0f0f0f, 0xfff2ffff, 0x01000000,
           0xf0f0f0f0, 0x0f0f0f0f, 0xfff2ffff, 0x01000000, 0xf0f0f0f0,
           0x0f0f0f0f);
  VCLEAR(v4);
  asm volatile("vmseq.vv v4, v8, v12");
  VSET(2, e8, m1);
  VCMP_U8(3, v4, 0xcc, 0xcc);

  VSET(16, e64, m8);
  VLOAD_64(v16, 0xffffffffffffffff, 0x0000000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f, 0xffffffffffffffff, 0x0000000000000000,
           0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f, 0xffffffffffffffff,
           0x0000000000000000, 0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f,
           0xffffffffffffffff, 0x0000000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f);
  VLOAD_64(v24, 0xfff2ffffffffffff, 0x0100000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f, 0xfff2ffffffffffff, 0x0100000000000000,
           0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f, 0xfff2ffffffffffff,
           0x0100000000000000, 0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f,
           0xfff2ffffffffffff, 0x0100000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f);
  VCLEAR(v8);
  asm volatile("vmseq.vv v8, v16, v24");
  VSET(2, e8, m8);
  VCMP_U8(4, v8, 0xcc, 0xcc);
};

void TEST_CASE2(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0xff, 0x00, 0xf0, 0x0f, 0xff, 0x00, 0xf0, 0x0f, 0xff, 0x00, 0xf0,
          0x0f, 0xff, 0x00, 0xf0, 0x0f);
  VLOAD_8(v3, 0xf2, 0x01, 0xf0, 0x0f, 0xf2, 0x01, 0xf0, 0x0f, 0xf2, 0x01, 0xf0,
          0x0f, 0xf2, 0x01, 0xf0, 0x0f);
  VLOAD_8(v0, 0xaa, 0xaa);
  VCLEAR(v1);
  asm volatile("vmseq.vv v1, v2, v3, v0.t");
  VSET(2, e8, m1);
  VCMP_U8(5, v1, 0x88, 0x88);

  VSET(16, e16, m2);
  VLOAD_16(v4, 0xffff, 0x0000, 0xf0f0, 0x0f0f, 0xffff, 0x0000, 0xf0f0, 0x0f0f,
           0xffff, 0x0000, 0xf0f0, 0x0f0f, 0xffff, 0x0000, 0xf0f0, 0x0f0f);
  VLOAD_16(v8, 0xf2ff, 0x0100, 0xf0f0, 0x0f0f, 0xf2ff, 0x0100, 0xf0f0, 0x0f0f,
           0xf2ff, 0x0100, 0xf0f0, 0x0f0f, 0xf2ff, 0x0100, 0xf0f0, 0x0f0f);
  VLOAD_8(v0, 0xaa, 0xaa);
  VCLEAR(v2);
  asm volatile("vmseq.vv v2, v4, v8, v0.t");
  VSET(2, e8, m1);
  VCMP_U8(6, v2, 0x88, 0x88);

  VSET(16, e32, m4);
  VLOAD_32(v8, 0xffffffff, 0x00000000, 0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff,
           0x00000000, 0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff, 0x00000000,
           0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff, 0x00000000, 0xf0f0f0f0,
           0x0f0f0f0f);
  VLOAD_32(v12, 0xfff2ffff, 0x01000000, 0xf0f0f0f0, 0x0f0f0f0f, 0xfff2ffff,
           0x01000000, 0xf0f0f0f0, 0x0f0f0f0f, 0xfff2ffff, 0x01000000,
           0xf0f0f0f0, 0x0f0f0f0f, 0xfff2ffff, 0x01000000, 0xf0f0f0f0,
           0x0f0f0f0f);
  VLOAD_8(v0, 0xaa, 0xaa);
  VCLEAR(v4);
  asm volatile("vmseq.vv v4, v8, v12, v0.t");
  VSET(2, e8, m1);
  VCMP_U8(7, v4, 0x88, 0x88);

  VSET(16, e64, m8);
  VLOAD_64(v16, 0xffffffffffffffff, 0x0000000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f, 0xffffffffffffffff, 0x0000000000000000,
           0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f, 0xffffffffffffffff,
           0x0000000000000000, 0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f,
           0xffffffffffffffff, 0x0000000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f);
  VLOAD_64(v24, 0xfff2ffffffffffff, 0x0100000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f, 0xfff2ffffffffffff, 0x0100000000000000,
           0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f, 0xfff2ffffffffffff,
           0x0100000000000000, 0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f,
           0xfff2ffffffffffff, 0x0100000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f);
  VLOAD_8(v0, 0xaa, 0xaa);
  VCLEAR(v8);
  asm volatile("vmseq.vv v8, v16, v24, v0.t");
  VSET(2, e8, m8);
  VCMP_U8(8, v8, 0x88, 0x88);
};

void TEST_CASE3(void) {
  const uint64_t scalar = 0x00000000ffffffff;

  VSET(16, e8, m1);
  VLOAD_8(v2, 0xff, 0x00, 0xf0, 0x0f, 0xff, 0x00, 0xf0, 0x0f, 0xff, 0x00, 0xf0,
          0x0f, 0xff, 0x00, 0xf0, 0x0f);
  VCLEAR(v1);
  asm volatile("vmseq.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VSET(2, e8, m1);
  VCMP_U8(9, v1, 0x11, 0x11);

  VSET(16, e16, m2);
  VLOAD_16(v4, 0xffff, 0x0000, 0xf0f0, 0x0f0f, 0xffff, 0x0000, 0xf0f0, 0x0f0f,
           0xffff, 0x0000, 0xf0f0, 0x0f0f, 0xffff, 0x0000, 0xf0f0, 0x0f0f);
  VCLEAR(v2);
  asm volatile("vmseq.vx v2, v4, %[A]" ::[A] "r"(scalar));
  VSET(2, e8, m1);
  VCMP_U8(10, v2, 0x11, 0x11);

  VSET(16, e32, m4);
  VLOAD_32(v8, 0xffffffff, 0x00000000, 0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff,
           0x00000000, 0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff, 0x00000000,
           0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff, 0x00000000, 0xf0f0f0f0,
           0x0f0f0f0f);
  VCLEAR(v4);
  asm volatile("vmseq.vx v4, v8, %[A]" ::[A] "r"(scalar));
  VSET(2, e8, m1);
  VCMP_U8(11, v4, 0x11, 0x11);

  VSET(16, e64, m8);
  VLOAD_64(v16, 0xffffffffffffffff, 0x0000000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f, 0xffffffffffffffff, 0x0000000000000000,
           0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f, 0xffffffffffffffff,
           0x0000000000000000, 0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f,
           0xffffffffffffffff, 0x0000000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f);
  VCLEAR(v8);
  asm volatile("vmseq.vx v8, v16, %[A]" ::[A] "r"(scalar));
  VSET(2, e8, m1);
  VCMP_U8(12, v8, 0x00, 0x00);
};

void TEST_CASE4(void) {
  const uint64_t scalar = 0x00000000ffffffff;

  VSET(16, e8, m1);
  VLOAD_8(v2, 0xff, 0x00, 0xf0, 0x0f, 0xff, 0x00, 0xf0, 0x0f, 0xff, 0x00, 0xf0,
          0x0f, 0xff, 0x00, 0xf0, 0x0f);
  VLOAD_8(v0, 0x10, 0x10);
  VCLEAR(v1);
  asm volatile("vmseq.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(2, e8, m1);
  VCMP_U8(13, v1, 0x10, 0x10);

  VSET(16, e16, m2);
  VLOAD_16(v4, 0xffff, 0x0000, 0xf0f0, 0x0f0f, 0xffff, 0x0000, 0xf0f0, 0x0f0f,
           0xffff, 0x0000, 0xf0f0, 0x0f0f, 0xffff, 0x0000, 0xf0f0, 0x0f0f);
  VLOAD_8(v0, 0x10, 0x10);
  VCLEAR(v2);
  asm volatile("vmseq.vx v2, v4, %[A], v0.t" ::[A] "r"(scalar));
  VSET(2, e8, m1);
  VCMP_U8(14, v2, 0x10, 0x10);

  VSET(16, e32, m4);
  VLOAD_32(v8, 0xffffffff, 0x00000000, 0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff,
           0x00000000, 0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff, 0x00000000,
           0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff, 0x00000000, 0xf0f0f0f0,
           0x0f0f0f0f);
  VLOAD_8(v0, 0x10, 0x10);
  VCLEAR(v4);
  asm volatile("vmseq.vx v4, v8, %[A], v0.t" ::[A] "r"(scalar));
  VSET(2, e8, m1);
  VCMP_U8(15, v4, 0x10, 0x10);

  VSET(16, e64, m8);
  VLOAD_64(v16, 0xffffffffffffffff, 0x0000000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f, 0xffffffffffffffff, 0x0000000000000000,
           0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f, 0xffffffffffffffff,
           0x0000000000000000, 0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f,
           0xffffffffffffffff, 0x0000000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f);
  VLOAD_8(v0, 0x10, 0x10);
  VCLEAR(v8);
  asm volatile("vmseq.vx v8, v16, %[A], v0.t" ::[A] "r"(scalar));
  VSET(2, e8, m1);
  VCMP_U8(16, v8, 0x00, 0x00);
};

void TEST_CASE5(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x0f, 0x00, 0xf0, 0x0f, 0x0f, 0x00, 0xf0, 0x0f, 0x0f, 0x00, 0xf0,
          0x0f, 0x0f, 0x00, 0xf0, 0x0f);
  VCLEAR(v1);
  asm volatile("vmseq.vi v1, v2, 15");
  VSET(2, e8, m1);
  VCMP_U8(17, v1, 0x99, 0x99);

  VSET(16, e16, m2);
  VLOAD_16(v4, 0x000f, 0x0000, 0xf0f0, 0x0f0f, 0x000f, 0x0000, 0xf0f0, 0x0f0f,
           0x000f, 0x0000, 0xf0f0, 0x0f0f, 0x000f, 0x0000, 0xf0f0, 0x0f0f);
  VCLEAR(v2);
  asm volatile("vmseq.vi v2, v4, 15");
  VSET(2, e8, m1);
  VCMP_U8(18, v2, 0x11, 0x11);

  VSET(16, e32, m4);
  VLOAD_32(v8, 0x0000000f, 0x00000000, 0xf0f0f0f0, 0x0f0f0f0f, 0x0000000f,
           0x00000000, 0xf0f0f0f0, 0x0f0f0f0f, 0x0000000f, 0x00000000,
           0xf0f0f0f0, 0x0f0f0f0f, 0x0000000f, 0x00000000, 0xf0f0f0f0,
           0x0f0f0f0f);
  VCLEAR(v4);
  asm volatile("vmseq.vi v4, v8, 15");
  VSET(2, e8, m1);
  VCMP_U8(19, v4, 0x11, 0x11);

  VSET(16, e64, m8);
  VLOAD_64(v16, 0x000000000000000f, 0x0000000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f, 0x000000000000000f, 0x0000000000000000,
           0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f, 0x000000000000000f,
           0x0000000000000000, 0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f,
           0x000000000000000f, 0x0000000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f);
  VCLEAR(v8);
  asm volatile("vmseq.vi v8, v16, 15");
  VSET(2, e8, m8);
  VCMP_U8(20, v8, 0x11, 0x11);
};

void TEST_CASE6(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x0f, 0x00, 0xf0, 0x0f, 0x0f, 0x00, 0xf0, 0x0f, 0x0f, 0x00, 0xf0,
          0x0f, 0x0f, 0x00, 0xf0, 0x0f);
  VLOAD_8(v0, 0x10, 0x10);
  VCLEAR(v1);
  asm volatile("vmseq.vi v1, v2, 15, v0.t");
  VSET(2, e8, m1);
  VCMP_U8(21, v1, 0x10, 0x10);

  VSET(16, e16, m2);
  VLOAD_16(v4, 0x000f, 0x0000, 0xf0f0, 0x0f0f, 0x000f, 0x0000, 0xf0f0, 0x0f0f,
           0x000f, 0x0000, 0xf0f0, 0x0f0f, 0x000f, 0x0000, 0xf0f0, 0x0f0f);
  VLOAD_8(v0, 0x10, 0x10);
  VCLEAR(v2);
  asm volatile("vmseq.vi v2, v4, 15, v0.t");
  VSET(2, e8, m1);
  VCMP_U8(22, v2, 0x10, 0x10);

  VSET(16, e32, m4);
  VLOAD_32(v8, 0x0000000f, 0x00000000, 0xf0f0f0f0, 0x0f0f0f0f, 0x0000000f,
           0x00000000, 0xf0f0f0f0, 0x0f0f0f0f, 0x0000000f, 0x00000000,
           0xf0f0f0f0, 0x0f0f0f0f, 0x0000000f, 0x00000000, 0xf0f0f0f0,
           0x0f0f0f0f);
  VLOAD_8(v0, 0x10, 0x10);
  VCLEAR(v4);
  asm volatile("vmseq.vi v4, v8, 15, v0.t");
  VSET(2, e8, m1);
  VCMP_U8(23, v4, 0x10, 0x10);

  VSET(16, e64, m8);
  VLOAD_64(v16, 0x000000000000000f, 0x0000000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f, 0x000000000000000f, 0x0000000000000000,
           0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f, 0x000000000000000f,
           0x0000000000000000, 0xf0f0f0f0f0f0f0f0, 0x0f0f0f0f0f0f0f0f,
           0x000000000000000f, 0x0000000000000000, 0xf0f0f0f0f0f0f0f0,
           0x0f0f0f0f0f0f0f0f);
  VLOAD_8(v0, 0x10, 0x10);
  VCLEAR(v8);
  asm volatile("vmseq.vi v8, v16, 15, v0.t");
  VSET(2, e8, m8);
  VCMP_U8(24, v8, 0x10, 0x10);
};

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();
  TEST_CASE5();
  TEST_CASE6();

  EXIT_CHECK();
}
