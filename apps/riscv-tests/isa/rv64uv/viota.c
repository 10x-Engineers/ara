// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1() {
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 0, 0, 1, 0, 0, 0, 1);
  __asm__ volatile("viota.m v2, v1");
  VCMP_U8(1, v2, 0, 1, 1, 1, 1, 1, 1, 1);
}

void TEST_CASE2() {
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 0, 0, 1, 0, 0, 0, 1);
  VLOAD_8(v0, 199, 0, 0, 0, 0, 0, 0, 0);
  VCLEAR(v2);
  __asm__ volatile("viota.m v2, v1, v0.t");
  VCMP_U8(2, v0, 199, 0, 0, 0, 0, 0, 0, 0);
  VCMP_U8(3, v2, 0, 1, 1, 0, 0, 0, 1, 1);
}

int main(void) {
  INIT_CHECK();
  enable_vec();
  enable_fp();
  TEST_CASE1();
  TEST_CASE2();
  EXIT_CHECK();
}
