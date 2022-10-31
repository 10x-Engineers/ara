// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE(void) {
  VSET(10, e8, m2);
  VLOAD_8(v0, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v2, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vadd.vv v4, v0, v2");
  VCMP_U8(0, v4, 2, 4, 6, 8, 10, 12, 14, 16);
}


int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE();
  
  EXIT_CHECK();
}
