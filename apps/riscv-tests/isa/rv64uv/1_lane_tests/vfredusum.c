// Copyright 2022 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Xiaorui Yin <yinx@student.ethz.ch>
// Date: 2022/05/03

#include "float_macros.h"
#include "vector_macros.h"

// Naive test
void TEST_CASE1(void) {
  VSET(16, e16, m2);
  // 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8
  VLOAD_16(v4, 0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800,
           0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800);
  VLOAD_16(v6, 0x3c00);
  asm volatile("vfredsum.vs v2, v4, v6");
  VCMP_U16(1, v2, 0x5490);

  VSET(16, e32, m4);
  VLOAD_32(v8, 0x3F800000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
           0x40C00000, 0x40E00000, 0x41000000, 0x3F800000, 0x40000000,
           0x40400000, 0x40800000, 0x40A00000, 0x40C00000, 0x40E00000,
           0x41000000);
  VLOAD_32(v12, 0x3F800000);
  asm volatile("vfredsum.vs v4, v8, v12");
  VCMP_F32(2, v4, 0x42920000);

  VSET(16, e64, m8);
  VLOAD_64(v16, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  VLOAD_64(v24, 0x3FF0000000000000);
  asm volatile("vfredsum.vs v8, v16, v24");
  VCMP_F64(3, v8, 0x4052400000000000);

  // Super lang vector length
  // VSET(64, e32, m8);
  VSET(32, e32, m8);
  VLOAD_32(
      v16, 0x3F800000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
      0x40C00000, 0x40E00000, 0x41000000, 0x3F800000, 0x40000000, 0x40400000,
      0x40800000, 0x40A00000, 0x40C00000, 0x40E00000, 0x41000000,

      0x3F800000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000, 0x40C00000,
      0x40E00000, 0x41000000, 0x3F800000, 0x40000000, 0x40400000, 0x40800000,
      0x40A00000, 0x40C00000, 0x40E00000, 0x41000000);

  //      0x3F800000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
  //      0x40C00000, 0x40E00000, 0x41000000, 0x3F800000, 0x40000000,
  //      0x40400000, 0x40800000, 0x40A00000, 0x40C00000, 0x40E00000,
  //      0x41000000,
  //
  //      0x3F800000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
  //      0x40C00000, 0x40E00000, 0x41000000, 0x3F800000, 0x40000000,
  //      0x40400000, 0x40800000, 0x40A00000, 0x40C00000, 0x40E00000,
  //      0x41000000);
  VLOAD_32(v24, 0x3F800000);
  asm volatile("vfredsum.vs v8, v16, v24");
  // VCMP_F32(4, v8, 0x43908000);
  VCMP_F32(4, v8, 0x43110000);
}

// Masked naive test
void TEST_CASE2(void) {
  VSET(16, e16, m2);
  VLOAD_8(v0, 0xaa, 0x55);
  // 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8
  VLOAD_16(v4, 0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800,
           0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800);
  VLOAD_16(v6, 0x3c00);
  asm volatile("vfredsum.vs v2, v4, v6, v0.t");
  VCMP_U16(5, v2, 0x50A0);

  VSET(16, e32, m4);
  VLOAD_8(v0, 0xaa, 0x55);
  VLOAD_32(v8, 0x3F800000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
           0x40C00000, 0x40E00000, 0x41000000, 0x3F800000, 0x40000000,
           0x40400000, 0x40800000, 0x40A00000, 0x40C00000, 0x40E00000,
           0x41000000);
  VLOAD_32(v12, 0x3F800000);
  asm volatile("vfredsum.vs v4, v8, v12, v0.t");
  VCMP_F32(6, v4, 0x42140000);

  VSET(16, e64, m8);
  VLOAD_8(v0, 0xaa, 0x55);
  VLOAD_64(v16, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  VLOAD_64(v24, 0x3FF0000000000000);
  asm volatile("vfredsum.vs v8, v16, v24, v0.t");
  VCMP_F64(7, v8, 0x4042800000000000);
}

// Are we respecting the undisturbed tail policy?
void TEST_CASE3(void) {
  VSET(16, e16, m2);
  // 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8
  VLOAD_16(v4, 0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800,
           0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800);
  VLOAD_16(v6, 0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800,
           0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800);
  VLOAD_16(v2, 0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800,
           0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800);
  asm volatile("vfredsum.vs v2, v4, v6");
  VCMP_U16(8, v2, 0x5490, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700,
           0x4800, 0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700,
           0x4800);

  VSET(16, e32, m4);
  VLOAD_32(v8, 0x3F800000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
           0x40C00000, 0x40E00000, 0x41000000, 0x3F800000, 0x40000000,
           0x40400000, 0x40800000, 0x40A00000, 0x40C00000, 0x40E00000,
           0x41000000);
  VLOAD_32(v12, 0x3F800000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
           0x40C00000, 0x40E00000, 0x41000000, 0x3F800000, 0x40000000,
           0x40400000, 0x40800000, 0x40A00000, 0x40C00000, 0x40E00000,
           0x41000000);
  VLOAD_32(v4, 0x3F800000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
           0x40C00000, 0x40E00000, 0x41000000, 0x3F800000, 0x40000000,
           0x40400000, 0x40800000, 0x40A00000, 0x40C00000, 0x40E00000,
           0x41000000);
  asm volatile("vfredsum.vs v4, v8, v12");
  VCMP_F32(9, v4, 0x42920000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
           0x40C00000, 0x40E00000, 0x41000000, 0x3F800000, 0x40000000,
           0x40400000, 0x40800000, 0x40A00000, 0x40C00000, 0x40E00000,
           0x41000000);

  VSET(16, e64, m8);
  VLOAD_64(v16, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  VLOAD_64(v24, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  VLOAD_64(v8, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  asm volatile("vfredsum.vs v8, v16, v24");
  VCMP_F64(10, v8, 0x4052400000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
}

// Odd number of elements, undisturbed policy
void TEST_CASE4(void) {
  VSET(1, e64, m8);
  VLOAD_64(v16, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  VLOAD_64(v24, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  VLOAD_64(v8, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  asm volatile("vfredsum.vs v8, v16, v24");
  VCMP_F64(11, v8, 0x4000000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);

  VSET(3, e64, m8);
  VLOAD_64(v16, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  VLOAD_64(v24, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  VLOAD_64(v8, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  asm volatile("vfredsum.vs v8, v16, v24");
  VCMP_F64(12, v8, 0x401C000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3ff0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);

  VSET(7, e64, m8);
  VLOAD_64(v16, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  VLOAD_64(v24, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  VLOAD_64(v8, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  asm volatile("vfredsum.vs v8, v16, v24");
  VCMP_F64(13, v8, 0x403d000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3ff0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);

  VSET(15, e64, m8);
  VLOAD_64(v16, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  VLOAD_64(v24, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  VLOAD_64(v8, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  asm volatile("vfredsum.vs v8, v16, v24");
  VCMP_F64(14, v8, 0x4050400000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
}

// Odd number of elements, undisturbed policy, and mask
void TEST_CASE5(void) {
  VSET(7, e16, m2);
  VLOAD_8(v0, 0x00, 0xff);
  // 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8
  VLOAD_16(v4, 0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800,
           0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800);
  VLOAD_16(v6, 0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800,
           0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800);
  VLOAD_16(v2, 0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800,
           0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700, 0x4800);
  asm volatile("vfredsum.vs v2, v4, v6, v0.t");
  VCMP_U16(15, v2, 0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700,
           0x4800, 0x3c00, 0x4000, 0x4200, 0x4400, 0x4500, 0x4600, 0x4700,
           0x4800);

  VSET(1, e32, m4);
  VLOAD_8(v0, 0xff, 0x00);
  VLOAD_32(v8, 0x3F800000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
           0x40C00000, 0x40E00000, 0x41000000, 0x3F800000, 0x40000000,
           0x40400000, 0x40800000, 0x40A00000, 0x40C00000, 0x40E00000,
           0x41000000);
  VLOAD_32(v12, 0x3F800000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
           0x40C00000, 0x40E00000, 0x41000000, 0x3F800000, 0x40000000,
           0x40400000, 0x40800000, 0x40A00000, 0x40C00000, 0x40E00000,
           0x41000000);
  VLOAD_32(v4, 0x3F800000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
           0x40C00000, 0x40E00000, 0x41000000, 0x3F800000, 0x40000000,
           0x40400000, 0x40800000, 0x40A00000, 0x40C00000, 0x40E00000,
           0x41000000);
  asm volatile("vfredsum.vs v4, v8, v12, v0.t");
  VCMP_F32(16, v4, 0x40000000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
           0x40C00000, 0x40E00000, 0x41000000, 0x3F800000, 0x40000000,
           0x40400000, 0x40800000, 0x40A00000, 0x40C00000, 0x40E00000,
           0x41000000);

  VSET(3, e64, m8);
  VLOAD_8(v0, 0xaa, 0x55);
  VLOAD_64(v16, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  VLOAD_64(v24, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  VLOAD_64(v8, 0x3FF0000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
  asm volatile("vfredsum.vs v8, v16, v24, v0.t");
  VCMP_F64(17, v8, 0x4008000000000000, 0x4000000000000000, 0x4008000000000000,
           0x4010000000000000, 0x4014000000000000, 0x4018000000000000,
           0x401C000000000000, 0x4020000000000000, 0x3FF0000000000000,
           0x4000000000000000, 0x4008000000000000, 0x4010000000000000,
           0x4014000000000000, 0x4018000000000000, 0x401C000000000000,
           0x4020000000000000);
}

int main(void) {
  INIT_CHECK();
  enable_vec();
  enable_fp();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();
  TEST_CASE5();

  EXIT_CHECK();
}
