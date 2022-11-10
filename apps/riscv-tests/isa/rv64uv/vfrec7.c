// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//y
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "float_macros.h"
#include "vector_macros.h"

void TEST_CASE1(void) {

  VSET(6, e16, m1);
  VLOAD_16(v2, mInfh, pInfh, qNaNh, sNaNh,pZero, mZeroh);
  asm volatile("vfrec7.v v1, v2");
  VCMP_U16(1, v1,mZeroh,pZero,qNaNh,qNaNh,pInfh,mInfh); 

  VSET(10, e32, m1);
  VLOAD_32(v2, mInff, pInff, qNaNf, sNaNf,
               pZero, mZerof,0x008116a3, 0x7e7cfda2,
               0xfe7cfda2,0x808ae379);
  asm volatile("vfrec7.v v1, v2");
  VCMP_U32(2, v1,mZerof,pZero,qNaNf,qNaNf,
                 pInff,mInff,0x7e7d0000,0x00820000,
                 0x80820000,0xfe6d0000);

  VSET(6, e64, m1);
  VLOAD_64(v2, mInfd, pInfd, qNaNd, sNaNd,pZero, mZerod);
  asm volatile("vfrec7.v v1, v2");
  VCMP_U64(3, v1,mZerod,pZero,qNaNd,qNaNd,pInfd,mInfd);

};

int main(void) {
  enable_vec();
  enable_fp();
CHANGE_RM(RM_RTZ);

  TEST_CASE1();
  
  EXIT_CHECK();

  
}
