// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

// unmasked
void TEST_CASE1(void) {
  VSET(4, e32, m1);
  VLOAD_32(v2, 7, 15, 15, 15);
  VSET(128, e32, m1);
  volatile uint32_t scalar = 1337;
  volatile uint32_t OUP[] = {0, 0, 0, 0};
  __asm__ volatile("vpopc.m x12, v2 \n"
                   "sw x12, (%1) \n"
                   :
                   : [A] "r"(scalar), "r"(OUP));
  XCMP(1, OUP[0], 15);
}

int main(void) {
  INIT_CHECK();
  enable_vec();
  enable_fp();
  TEST_CASE1();
  EXIT_CHECK();
}
