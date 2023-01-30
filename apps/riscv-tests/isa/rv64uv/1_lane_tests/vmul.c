// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0xb3, 0x5d, 0x3d, 0xa4, 0xbf, 0xc7, 0x6b, 0x95, 0xf9, 0x64, 0x52,
          0x57, 0xbc, 0x1f, 0xd5, 0x13);
  VLOAD_8(v3, 0x46, 0x37, 0xf5, 0x2b, 0x55, 0x05, 0xcb, 0x76, 0x31, 0x30, 0x78,
          0xb3, 0x6a, 0xae, 0x5a, 0xe1);
  asm volatile("vmul.vv v1, v2, v3");
  VCMP_I8(1, v1, 0xf2, 0xfb, 0x61, 0x8c, 0x6b, 0xe3, 0xd9, 0xae, 0xa9, 0xc0,
          0x70, 0xd5, 0xd8, 0x12, 0xe2, 0xb3);

  VSET(16, e16, m2);
  VLOAD_16(v4, 0x8132, 0x94b5, 0x245c, 0xd15d, 0xbfca, 0x18b6, 0xd5ba, 0x9299,
           0xccbd, 0x9ad4, 0xce46, 0xfbba, 0x10cc, 0xc463, 0x5298, 0x7b3e);
  VLOAD_16(v6, 0xede6, 0x010b, 0xa570, 0x21c5, 0xfe5a, 0x5386, 0x16c9, 0x45fb,
           0x1439, 0x436f, 0x6f56, 0x90f7, 0x77c0, 0x0751, 0x64c3, 0x36e8);
  asm volatile("vmul.vv v2, v4, v6");
  VCMP_I16(2, v2, 0x5cec, 0x18c7, 0x3440, 0x1991, 0xd904, 0xf144, 0xcb0a,
           0xf903, 0x5a15, 0x9dec, 0xa584, 0x8076, 0x6d00, 0xd853, 0x49c8,
           0xc430);

  VSET(16, e32, m4);
  VLOAD_32(v8, 0x9c2bdc58, 0xe3995899, 0xbbbc0eda, 0x0729ff92, 0xa757a2c5,
           0xd5f3a23e, 0x9a295390, 0xb2367b2e, 0xfee5b6a2, 0x07cb59c1,
           0x6bf5cf9a, 0x7d75506b, 0x013c1e90, 0x600f9ca8, 0x6d4d0522,
           0x0a225ff0);
  VLOAD_32(v12, 0xc51e02f8, 0xae06b334, 0x397b1ec7, 0xc46f34fe, 0x4f9db2ab,
           0x957c2534, 0x70f8e127, 0xa79ebcec, 0x0a542044, 0x20e6ac3e,
           0xd61caed7, 0x6f4e7820, 0x27c56901, 0x0aaf1d61, 0xa95c6f5c,
           0x5b7aedf3);
  asm volatile("vmul.vv v4, v8, v12");
  VCMP_I32(3, v4, 0x2c862540, 0x85aefa14, 0xa5ab1776, 0x3be33adc, 0x5487b397,
           0x57f7ea98, 0xc23d4af0, 0x55135668, 0xad00c308, 0x46f368be,
           0x2f640656, 0x91f63560, 0x1e952e90, 0xd18163a8, 0xf71f9638,
           0x79d240d0);

  VSET(16, e64, m8);
  VLOAD_64(v16, 0x077de9270ce00632, 0x2dadf4e020f3d47a, 0xb54ca84f9fe0573b,
           0x7be639dfdb02db6f, 0x61bb44569da93eff, 0xcd7f973ce822182b,
           0x5434a22e7432397c, 0xcaadfd89d8dd1ad5, 0x5474c56d9089d672,
           0x700e415c07b99bf9, 0xb89d409d4323a9c8, 0x68ccc7411db0ab09,
           0xdf4fe3fa4e113e98, 0xa98a2e2575b04c41, 0x26ddf248ccb4a7aa,
           0xdda1822d4972ee47);
  VLOAD_64(v24, 0xcd2888c8bb07b736, 0xf20013627ac47d4f, 0xc05dbcd989ef329c,
           0xc272db2ebcf7cfad, 0x8869302db041176d, 0xd3d90968a9ee01c2,
           0x9cdb9f91a3381f51, 0x99ad38b70907ee8d, 0xf7d629b266c67cf1,
           0x706f9b996cdd60f2, 0x4caa2335622bd6a0, 0x94171c9dfbbb186f,
           0x7b6e42290f54ecc6, 0xa545b8670143bfbc, 0x9f430bf94b2805c9,
           0xb45030fc2b4cef12);
  asm volatile("vmul.vv v8, v16, v24");
  VCMP_I64(4, v8, 0x90d27e278d0d0c8c, 0x5ea9d3e60b6623a6, 0x6823b3e240d3adf4,
           0xc0dcea378c760b03, 0x17692726a477bb93, 0x784c7f2ee6e87b96,
           0xd1aae9975ffa343c, 0xfdcd46ca398ccd51, 0x405f01791dce1952,
           0x16063fbe99e7d162, 0xc9d244cddacf4d00, 0x22024848323600e7,
           0xb6dfea3bb8ea8990, 0x566db9e82c5f7ebc, 0x5fc0f2db41adf67a,
           0xdaab68ca209d09fe);
};

void TEST_CASE2(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0xb3, 0x5d, 0x3d, 0xa4, 0xbf, 0xc7, 0x6b, 0x95, 0xf9, 0x64, 0x52,
          0x57, 0xbc, 0x1f, 0xd5, 0x13);
  VLOAD_8(v3, 0x46, 0x37, 0xf5, 0x2b, 0x55, 0x05, 0xcb, 0x76, 0x31, 0x30, 0x78,
          0xb3, 0x6a, 0xae, 0x5a, 0xe1);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vmul.vv v1, v2, v3, v0.t");
  VCMP_I8(5, v1, 0, 0xfb, 0, 0x8c, 0, 0xe3, 0, 0xae, 0, 0xc0, 0, 0xd5, 0, 0x12,
          0, 0xb3);

  VSET(16, e16, m2);
  VLOAD_16(v4, 0x8132, 0x94b5, 0x245c, 0xd15d, 0xbfca, 0x18b6, 0xd5ba, 0x9299,
           0xccbd, 0x9ad4, 0xce46, 0xfbba, 0x10cc, 0xc463, 0x5298, 0x7b3e);
  VLOAD_16(v6, 0xede6, 0x010b, 0xa570, 0x21c5, 0xfe5a, 0x5386, 0x16c9, 0x45fb,
           0x1439, 0x436f, 0x6f56, 0x90f7, 0x77c0, 0x0751, 0x64c3, 0x36e8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v2);
  asm volatile("vmul.vv v2, v4, v6, v0.t");
  VCMP_I16(6, v2, 0, 0x18c7, 0, 0x1991, 0, 0xf144, 0, 0xf903, 0, 0x9dec, 0,
           0x8076, 0, 0xd853, 0, 0xc430);

  VSET(16, e32, m4);
  VLOAD_32(v8, 0x9c2bdc58, 0xe3995899, 0xbbbc0eda, 0x0729ff92, 0xa757a2c5,
           0xd5f3a23e, 0x9a295390, 0xb2367b2e, 0xfee5b6a2, 0x07cb59c1,
           0x6bf5cf9a, 0x7d75506b, 0x013c1e90, 0x600f9ca8, 0x6d4d0522,
           0x0a225ff0);
  VLOAD_32(v12, 0xc51e02f8, 0xae06b334, 0x397b1ec7, 0xc46f34fe, 0x4f9db2ab,
           0x957c2534, 0x70f8e127, 0xa79ebcec, 0x0a542044, 0x20e6ac3e,
           0xd61caed7, 0x6f4e7820, 0x27c56901, 0x0aaf1d61, 0xa95c6f5c,
           0x5b7aedf3);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vmul.vv v4, v8, v12, v0.t");
  VCMP_I32(7, v4, 0, 0x85aefa14, 0, 0x3be33adc, 0, 0x57f7ea98, 0, 0x55135668, 0,
           0x46f368be, 0, 0x91f63560, 0, 0xd18163a8, 0, 0x79d240d0);

  VSET(16, e64, m8);
  VLOAD_64(v16, 0x077de9270ce00632, 0x2dadf4e020f3d47a, 0xb54ca84f9fe0573b,
           0x7be639dfdb02db6f, 0x61bb44569da93eff, 0xcd7f973ce822182b,
           0x5434a22e7432397c, 0xcaadfd89d8dd1ad5, 0x5474c56d9089d672,
           0x700e415c07b99bf9, 0xb89d409d4323a9c8, 0x68ccc7411db0ab09,
           0xdf4fe3fa4e113e98, 0xa98a2e2575b04c41, 0x26ddf248ccb4a7aa,
           0xdda1822d4972ee47);
  VLOAD_64(v24, 0xcd2888c8bb07b736, 0xf20013627ac47d4f, 0xc05dbcd989ef329c,
           0xc272db2ebcf7cfad, 0x8869302db041176d, 0xd3d90968a9ee01c2,
           0x9cdb9f91a3381f51, 0x99ad38b70907ee8d, 0xf7d629b266c67cf1,
           0x706f9b996cdd60f2, 0x4caa2335622bd6a0, 0x94171c9dfbbb186f,
           0x7b6e42290f54ecc6, 0xa545b8670143bfbc, 0x9f430bf94b2805c9,
           0xb45030fc2b4cef12);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v8);
  asm volatile("vmul.vv v8, v16, v24, v0.t");
  VCMP_I64(8, v8, 0, 0x5ea9d3e60b6623a6, 0, 0xc0dcea378c760b03, 0,
           0x784c7f2ee6e87b96, 0, 0xfdcd46ca398ccd51, 0, 0x16063fbe99e7d162, 0,
           0x22024848323600e7, 0, 0x566db9e82c5f7ebc, 0, 0xdaab68ca209d09fe);
};

void TEST_CASE3(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x80, 0xb2, 0xb6, 0xd7, 0x4f, 0xbe, 0xee, 0x53, 0xab, 0x57, 0xe4,
          0x28, 0x6a, 0x91, 0x14, 0x4f);
  int64_t scalar = 5;
  asm volatile("vmul.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VCMP_I8(9, v1, 0x80, 0x7a, 0x8e, 0x33, 0x8b, 0xb6, 0xa6, 0x9f, 0x57, 0xb3,
          0x74, 0xc8, 0x12, 0xd5, 0x64, 0x8b);

  VSET(16, e16, m2);
  VLOAD_16(v4, 0xbab0, 0x83a5, 0x06b6, 0x22ba, 0x91b8, 0x7720, 0xc2c7, 0x3494,
           0xd281, 0x6d38, 0x378d, 0xa91d, 0xd731, 0xa4c7, 0x4d8f, 0x2422);
  scalar = -5383;
  asm volatile("vmul.vx v2, v4, %[A]" ::[A] "r"(scalar));
  VCMP_I16(10, v2, 0x7530, 0xdd7d, 0xe306, 0xcaea, 0xebf8, 0x1e20, 0x598f,
           0x6bf4, 0xa979, 0x6b78, 0xea25, 0xff35, 0x18a9, 0x2b8f, 0x2617,
           0x3912);

  VSET(16, e32, m4);
  VLOAD_32(v8, 0x8bb4a8bc, 0x9799b344, 0xcd8c1672, 0xeb2d7c0f, 0x55474d7d,
           0x3dae9eaf, 0xc19a3519, 0x6922f03c, 0x42edfa01, 0x1f60b344,
           0x82f31d5e, 0x0faa2e5c, 0x74e95cfa, 0x9fcdae3b, 0xe6c4e0a0,
           0x45549cbc);
  scalar = 6474219;
  asm volatile("vmul.vx v4, v8, %[A]" ::[A] "r"(scalar));
  VCMP_I32(11, v4, 0xaf4a8094, 0x77dff36c, 0x44dc1ca6, 0x16e6a8c5, 0xee2546bf,
           0x78e111a5, 0x1fd15ef3, 0xe8a9a314, 0xfe2147eb, 0x5a8cf36c,
           0x5536c34a, 0xbed6ca74, 0x23eca37e, 0xe2314329, 0x6857d2e0,
           0x13b37c94);

  VSET(16, e64, m8);
  VLOAD_64(v16, 0xc238e0a3df21299c, 0xb642655c3ab064d5, 0xd19f84bab77e5602,
           0x4e6e3c114a19f160, 0xfd403cbcc59407a1, 0xef3e81a68ae0e48c,
           0xd93a7b1ab54d024e, 0x5f7460aa9f4c4920, 0x4c91150cd4b54f60,
           0x18f2a6528629633f, 0x201b8bdb3c140400, 0x6be03c1074d46ada,
           0xcd0e6874555602d4, 0xb70264bd366ff52f, 0xc0b1fa64cec9368d,
           0x13e86249a0235941);
  scalar = -598189234597999223;
  asm volatile("vmul.vx v8, v16, %[A]" ::[A] "r"(scalar));
  VCMP_I64(12, v8, 0x61ead1213f09307c, 0x7d03f4c84c5e86fd, 0x4aa0acc4e01fa112,
           0x77bc957fdeec0c60, 0x762b14c112e60229, 0xbac65562e2366aec,
           0xcc243dd1e80ab1be, 0xa871135122a1c220, 0x3d0db00992575a60,
           0x8b07763affcd8fb7, 0xc8377fc475ea2400, 0xd8827c839711c0aa,
           0x5a5779ec4f334774, 0x243fd844e74ed927, 0x49204b7602871a75,
           0x33ae5ea6d335d0c9);
};

void TEST_CASE4(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x80, 0xb2, 0xb6, 0xd7, 0x4f, 0xbe, 0xee, 0x53, 0xab, 0x57, 0xe4,
          0x28, 0x6a, 0x91, 0x14, 0x4f);
  int64_t scalar = 5;
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vmul.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_I8(13, v1, 0, 0x7a, 0, 0x33, 0, 0xb6, 0, 0x9f, 0, 0xb3, 0, 0xc8, 0, 0xd5,
          0, 0x8b);

  VSET(16, e16, m2);
  VLOAD_16(v4, 0xbab0, 0x83a5, 0x06b6, 0x22ba, 0x91b8, 0x7720, 0xc2c7, 0x3494,
           0xd281, 0x6d38, 0x378d, 0xa91d, 0xd731, 0xa4c7, 0x4d8f, 0x2422);
  scalar = -5383;
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v2);
  asm volatile("vmul.vx v2, v4, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_I16(14, v2, 0, 0xdd7d, 0, 0xcaea, 0, 0x1e20, 0, 0x6bf4, 0, 0x6b78, 0,
           0xff35, 0, 0x2b8f, 0, 0x3912);

  VSET(16, e32, m4);
  VLOAD_32(v8, 0x8bb4a8bc, 0x9799b344, 0xcd8c1672, 0xeb2d7c0f, 0x55474d7d,
           0x3dae9eaf, 0xc19a3519, 0x6922f03c, 0x42edfa01, 0x1f60b344,
           0x82f31d5e, 0x0faa2e5c, 0x74e95cfa, 0x9fcdae3b, 0xe6c4e0a0,
           0x45549cbc);
  scalar = 6474219;
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vmul.vx v4, v8, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_I32(15, v4, 0, 0x77dff36c, 0, 0x16e6a8c5, 0, 0x78e111a5, 0, 0xe8a9a314,
           0, 0x5a8cf36c, 0, 0xbed6ca74, 0, 0xe2314329, 0, 0x13b37c94);

  VSET(16, e64, m8);
  VLOAD_64(v16, 0xc238e0a3df21299c, 0xb642655c3ab064d5, 0xd19f84bab77e5602,
           0x4e6e3c114a19f160, 0xfd403cbcc59407a1, 0xef3e81a68ae0e48c,
           0xd93a7b1ab54d024e, 0x5f7460aa9f4c4920, 0x4c91150cd4b54f60,
           0x18f2a6528629633f, 0x201b8bdb3c140400, 0x6be03c1074d46ada,
           0xcd0e6874555602d4, 0xb70264bd366ff52f, 0xc0b1fa64cec9368d,
           0x13e86249a0235941);
  scalar = -598189234597999223;
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v8);
  asm volatile("vmul.vx v8, v16, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_I64(16, v8, 0, 0x7d03f4c84c5e86fd, 0, 0x77bc957fdeec0c60, 0,
           0xbac65562e2366aec, 0, 0xa871135122a1c220, 0, 0x8b07763affcd8fb7, 0,
           0xd8827c839711c0aa, 0, 0x243fd844e74ed927, 0, 0x33ae5ea6d335d0c9);
};

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();

  EXIT_CHECK();
}
