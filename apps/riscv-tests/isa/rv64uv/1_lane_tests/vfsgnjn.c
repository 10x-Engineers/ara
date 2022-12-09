// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "float_macros.h"
#include "vector_macros.h"

// Simple random test with similar values
void TEST_CASE1(void) {
  VSET(16, e16, m2);
  //               0.5278, -0.6548,  0.2776,  0.8730,  0.2180,  0.6172, -0.8408,
  //               0.9922,  0.4250,  0.7393,  0.2549,  0.4998,  0.4609, -0.6348,
  //               0.1127, -0.1804
  VLOAD_16(v4, 0x3839, 0xb93d, 0x3471, 0x3afc, 0x32fa, 0x38f0, 0xbaba, 0x3bf0,
           0x36cd, 0x39ea, 0x3414, 0x37ff, 0x3760, 0xb914, 0x2f36, 0xb1c6);
  //              -0.6348, -0.4368, -0.1896,  0.9419, -0.6108, -0.3594, -0.5166,
  //              -0.1266, -0.9233,  0.2368,  0.1243,  0.3745,  0.0945, -0.3088,
  //              0.0190, -0.6289
  VLOAD_16(v6, 0xb914, 0xb6fd, 0xb211, 0x3b89, 0xb8e3, 0xb5c0, 0xb822, 0xb00d,
           0xbb63, 0x3394, 0x2ff5, 0x35fe, 0x2e0c, 0xb4f1, 0x24da, 0xb908);
  asm volatile("vfsgnjn.vv v2, v4, v6");
  //               0.5278,  0.6548,  0.2776, -0.8730,  0.2180,  0.6172,  0.8408,
  //               0.9922,  0.4250, -0.7393, -0.2549, -0.4998, -0.4609,  0.6348,
  //               -0.1127,  0.1804
  VCMP_U16(1, v2, 0x3839, 0x393d, 0x3471, 0xbafc, 0x32fa, 0x38f0, 0x3aba,
           0x3bf0, 0x36cd, 0xb9ea, 0xb414, 0xb7ff, 0xb760, 0x3914, 0xaf36,
           0x31c6);

  VSET(16, e32, m4);
  //              -0.64186704,  0.87601262, -0.93132722,  0.53574133,
  //              0.17954259, -0.80486834, -0.95272040, -0.45182621, 0.20335940,
  //              0.96179944,  0.80393785,  0.06180594,  0.86447370,
  //              -0.24008171, -0.42264909, -0.01868468
  VLOAD_32(v8, 0xbf245166, 0x3f60425d, 0xbf6e6b76, 0x3f092658, 0x3e37da03,
           0xbf4e0bda, 0xbf73e57c, 0xbee755c4, 0x3e503d72, 0x3f76387d,
           0x3f4dcedf, 0x3d7d283b, 0x3f5d4e26, 0xbe75d7fb, 0xbed86576,
           0xbc99109c);
  //               0.32984266, -0.78281105,  0.73037797,  0.99060333,
  //               0.44768164,  0.66998041,  0.39474848, -0.39895460,
  //               -0.06065369,  0.53388232, -0.60164928, -0.09839682,
  //               -0.38704434,  0.47123700,  0.40912241, -0.54495376
  VLOAD_32(v12, 0x3ea8e123, 0xbf48664e, 0x3f3afa0d, 0x3f7d982e, 0x3ee53687,
           0x3f2b83d6, 0x3eca1c79, 0xbecc43c7, 0xbd787002, 0x3f08ac83,
           0xbf1a05b0, 0xbdc98446, 0xbec62aad, 0x3ef145fa, 0x3ed1787e,
           0xbf0b8217);
  asm volatile("vfsgnjn.vv v4, v8, v12");
  //              -0.64186704,  0.87601262, -0.93132722, -0.53574133,
  //              -0.17954259, -0.80486834, -0.95272040,  0.45182621,
  //              0.20335940, -0.96179944,  0.80393785,  0.06180594, 0.86447370,
  //              -0.24008171, -0.42264909,  0.01868468
  VCMP_U32(2, v4, 0xbf245166, 0x3f60425d, 0xbf6e6b76, 0xbf092658, 0xbe37da03,
           0xbf4e0bda, 0xbf73e57c, 0x3ee755c4, 0x3e503d72, 0xbf76387d,
           0x3f4dcedf, 0x3d7d283b, 0x3f5d4e26, 0xbe75d7fb, 0xbed86576,
           0x3c99109c);

  VSET(16, e64, m8);
  //               0.3054868811191440, -0.2848737407493320,  0.8796894022735833,
  //               -0.2053728688878902, -0.3336030943630310, 0.2807217618714037,
  //               0.4723331455917303, -0.8582398814993568,  0.8015611350975347,
  //               0.0545934239457773,  0.8461592442963186,  0.5731810427237676,
  //               0.9004228762726765, -0.5815114412549589, -0.4481603571708770,
  //               -0.3109452697316515
  VLOAD_64(v16, 0x3fd38d18d8f0e180, 0xbfd23b5f12007bec, 0x3fec266a63ace3f8,
           0xbfca49a87dadf9c0, 0xbfd559c0cb088d3c, 0x3fd1f75868a0d7ec,
           0x3fde3ab4cd4887cc, 0xbfeb76b37be53474, 0x3fe9a663899fa232,
           0x3fabf3ab54d8f940, 0x3feb13bc8d2ebe92, 0x3fe2577fc525f1c0,
           0x3fecd043a2c52a30, 0xbfe29bbde1ce1372, 0xbfdcaea8c75a67f8,
           0xbfd3e686fd15f950);
  //              -0.8601583185162320, -0.2023208019417544,  0.7046992650654684,
  //              0.0669209072111863, -0.9495814052980500,  0.4501419112888980,
  //              0.1528430256162707, -0.2750771515266404, -0.5539880061109905,
  //              -0.7302340801247744,  0.1579280396497211, -0.6128023516491234,
  //              0.2706272563647967, -0.7982929669593624, -0.2521632643799878,
  //              0.9025785865542095
  VLOAD_64(v24, 0xbfeb866abced1b2e, 0xbfc9e5a5e5d1f648, 0x3fe68ce5791f15e4,
           0x3fb121ba83e404a0, 0xbfee62f88b14a294, 0x3fdccf2004e2dd30,
           0x3fc3905c3a38c700, 0xbfd19add326bc2ac, 0xbfe1ba450e13ef3a,
           0xbfe75e13dc91f006, 0x3fc436fc6ab55e68, 0xbfe39c13ad67d608,
           0x3fd151f4fbdf8d78, 0xbfe98b9db136f3e0, 0xbfd023716370f004,
           0x3fece1ec7cea3f5e);
  asm volatile("vfsgnjn.vv v8, v16, v24");
  //               0.3054868811191440,  0.2848737407493320, -0.8796894022735833,
  //               -0.2053728688878902,  0.3336030943630310,
  //               -0.2807217618714037, -0.4723331455917303, 0.8582398814993568,
  //               0.8015611350975347,  0.0545934239457773, -0.8461592442963186,
  //               0.5731810427237676, -0.9004228762726765,  0.5815114412549589,
  //               0.4481603571708770, -0.3109452697316515
  VCMP_U64(3, v8, 0x3fd38d18d8f0e180, 0x3fd23b5f12007bec, 0xbfec266a63ace3f8,
           0xbfca49a87dadf9c0, 0x3fd559c0cb088d3c, 0xbfd1f75868a0d7ec,
           0xbfde3ab4cd4887cc, 0x3feb76b37be53474, 0x3fe9a663899fa232,
           0x3fabf3ab54d8f940, 0xbfeb13bc8d2ebe92, 0x3fe2577fc525f1c0,
           0xbfecd043a2c52a30, 0x3fe29bbde1ce1372, 0x3fdcaea8c75a67f8,
           0xbfd3e686fd15f950);
};

// Simple random test with similar values (masked)
// The numbers are the same of TEST_CASE1
void TEST_CASE2(void) {
  VSET(16, e16, m2);
  //               0.5278, -0.6548,  0.2776,  0.8730,  0.2180,  0.6172, -0.8408,
  //               0.9922,  0.4250,  0.7393,  0.2549,  0.4998,  0.4609, -0.6348,
  //               0.1127, -0.1804
  VLOAD_16(v4, 0x3839, 0xb93d, 0x3471, 0x3afc, 0x32fa, 0x38f0, 0xbaba, 0x3bf0,
           0x36cd, 0x39ea, 0x3414, 0x37ff, 0x3760, 0xb914, 0x2f36, 0xb1c6);
  //              -0.6348, -0.4368, -0.1896,  0.9419, -0.6108, -0.3594, -0.5166,
  //              -0.1266, -0.9233,  0.2368,  0.1243,  0.3745,  0.0945, -0.3088,
  //              0.0190, -0.6289
  VLOAD_16(v6, 0xb914, 0xb6fd, 0xb211, 0x3b89, 0xb8e3, 0xb5c0, 0xb822, 0xb00d,
           0xbb63, 0x3394, 0x2ff5, 0x35fe, 0x2e0c, 0xb4f1, 0x24da, 0xb908);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v2);
  asm volatile("vfsgnjn.vv v2, v4, v6, v0.t");
  //               0.0000,  0.6548,  0.0000, -0.8730,  0.0000,  0.6172,  0.0000,
  //               0.9922,  0.0000, -0.7393,  0.0000, -0.4998,  0.0000,  0.6348,
  //               0.0000,  0.1804
  VCMP_U16(4, v2, 0x0, 0x393d, 0x0, 0xbafc, 0x0, 0x38f0, 0x0, 0x3bf0, 0x0,
           0xb9ea, 0x0, 0xb7ff, 0x0, 0x3914, 0x0, 0x31c6);

  VSET(16, e32, m4);
  //              -0.64186704,  0.87601262, -0.93132722,  0.53574133,
  //              0.17954259, -0.80486834, -0.95272040, -0.45182621, 0.20335940,
  //              0.96179944,  0.80393785,  0.06180594,  0.86447370,
  //              -0.24008171, -0.42264909, -0.01868468
  VLOAD_32(v8, 0xbf245166, 0x3f60425d, 0xbf6e6b76, 0x3f092658, 0x3e37da03,
           0xbf4e0bda, 0xbf73e57c, 0xbee755c4, 0x3e503d72, 0x3f76387d,
           0x3f4dcedf, 0x3d7d283b, 0x3f5d4e26, 0xbe75d7fb, 0xbed86576,
           0xbc99109c);
  //               0.32984266, -0.78281105,  0.73037797,  0.99060333,
  //               0.44768164,  0.66998041,  0.39474848, -0.39895460,
  //               -0.06065369,  0.53388232, -0.60164928, -0.09839682,
  //               -0.38704434,  0.47123700,  0.40912241, -0.54495376
  VLOAD_32(v12, 0x3ea8e123, 0xbf48664e, 0x3f3afa0d, 0x3f7d982e, 0x3ee53687,
           0x3f2b83d6, 0x3eca1c79, 0xbecc43c7, 0xbd787002, 0x3f08ac83,
           0xbf1a05b0, 0xbdc98446, 0xbec62aad, 0x3ef145fa, 0x3ed1787e,
           0xbf0b8217);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfsgnjn.vv v4, v8, v12, v0.t");
  //               0.00000000,  0.87601262,  0.00000000, -0.53574133,
  //               0.00000000, -0.80486834,  0.00000000,  0.45182621,
  //               0.00000000, -0.96179944,  0.00000000,  0.06180594,
  //               0.00000000, -0.24008171,  0.00000000,  0.01868468
  VCMP_U32(5, v4, 0x0, 0x3f60425d, 0x0, 0xbf092658, 0x0, 0xbf4e0bda, 0x0,
           0x3ee755c4, 0x0, 0xbf76387d, 0x0, 0x3d7d283b, 0x0, 0xbe75d7fb, 0x0,
           0x3c99109c);

  VSET(16, e64, m8);
  //               0.3054868811191440, -0.2848737407493320,  0.8796894022735833,
  //               -0.2053728688878902, -0.3336030943630310, 0.2807217618714037,
  //               0.4723331455917303, -0.8582398814993568,  0.8015611350975347,
  //               0.0545934239457773,  0.8461592442963186,  0.5731810427237676,
  //               0.9004228762726765, -0.5815114412549589, -0.4481603571708770,
  //               -0.3109452697316515
  VLOAD_64(v16, 0x3fd38d18d8f0e180, 0xbfd23b5f12007bec, 0x3fec266a63ace3f8,
           0xbfca49a87dadf9c0, 0xbfd559c0cb088d3c, 0x3fd1f75868a0d7ec,
           0x3fde3ab4cd4887cc, 0xbfeb76b37be53474, 0x3fe9a663899fa232,
           0x3fabf3ab54d8f940, 0x3feb13bc8d2ebe92, 0x3fe2577fc525f1c0,
           0x3fecd043a2c52a30, 0xbfe29bbde1ce1372, 0xbfdcaea8c75a67f8,
           0xbfd3e686fd15f950);
  //              -0.8601583185162320, -0.2023208019417544,  0.7046992650654684,
  //              0.0669209072111863, -0.9495814052980500,  0.4501419112888980,
  //              0.1528430256162707, -0.2750771515266404, -0.5539880061109905,
  //              -0.7302340801247744,  0.1579280396497211, -0.6128023516491234,
  //              0.2706272563647967, -0.7982929669593624, -0.2521632643799878,
  //              0.9025785865542095
  VLOAD_64(v24, 0xbfeb866abced1b2e, 0xbfc9e5a5e5d1f648, 0x3fe68ce5791f15e4,
           0x3fb121ba83e404a0, 0xbfee62f88b14a294, 0x3fdccf2004e2dd30,
           0x3fc3905c3a38c700, 0xbfd19add326bc2ac, 0xbfe1ba450e13ef3a,
           0xbfe75e13dc91f006, 0x3fc436fc6ab55e68, 0xbfe39c13ad67d608,
           0x3fd151f4fbdf8d78, 0xbfe98b9db136f3e0, 0xbfd023716370f004,
           0x3fece1ec7cea3f5e);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v8);
  asm volatile("vfsgnjn.vv v8, v16, v24, v0.t");
  //               0.0000000000000000,  0.2848737407493320,  0.0000000000000000,
  //               -0.2053728688878902,  0.0000000000000000,
  //               -0.2807217618714037,  0.0000000000000000, 0.8582398814993568,
  //               0.0000000000000000,  0.0545934239457773,  0.0000000000000000,
  //               0.5731810427237676,  0.0000000000000000,  0.5815114412549589,
  //               0.0000000000000000, -0.3109452697316515
  VCMP_U64(6, v8, 0x0, 0x3fd23b5f12007bec, 0x0, 0xbfca49a87dadf9c0, 0x0,
           0xbfd1f75868a0d7ec, 0x0, 0x3feb76b37be53474, 0x0, 0x3fabf3ab54d8f940,
           0x0, 0x3fe2577fc525f1c0, 0x0, 0x3fe29bbde1ce1372, 0x0,
           0xbfd3e686fd15f950);
};

// Simple random test with similar values (vector-scalar)
void TEST_CASE3(void) {
  VSET(16, e16, m2);
  double dscalar_16;
  //                             -0.6143
  BOX_HALF_IN_DOUBLE(dscalar_16, 0xb8ea);
  //              -0.9351,  0.6538, -0.6743, -0.4695, -0.1439,  0.6250, -0.1511,
  //              -0.7476,  0.8496,  0.6279,  0.5234,  0.2610,  0.6299, -0.0123,
  //              -0.9995, -0.3872
  VLOAD_16(v4, 0xbb7b, 0x393b, 0xb965, 0xb783, 0xb09b, 0x3900, 0xb0d6, 0xb9fb,
           0x3acc, 0x3906, 0x3830, 0x342d, 0x390a, 0xa24d, 0xbbff, 0xb632);
  asm volatile("vfsgnjn.vf v2, v4, %[A]" ::[A] "f"(dscalar_16));
  //               0.9351,  0.6538,  0.6743,  0.4695,  0.1439,  0.6250,  0.1511,
  //               0.7476,  0.8496,  0.6279,  0.5234,  0.2610,  0.6299,  0.0123,
  //               0.9995,  0.3872
  VCMP_U16(7, v2, 0x3b7b, 0x393b, 0x3965, 0x3783, 0x309b, 0x3900, 0x30d6,
           0x39fb, 0x3acc, 0x3906, 0x3830, 0x342d, 0x390a, 0x224d, 0x3bff,
           0x3632);

  VSET(16, e32, m4);
  double dscalar_32;
  //                               0.56259364
  BOX_FLOAT_IN_DOUBLE(dscalar_32, 0x3f100623);
  //              -0.00813205, -0.38676089,  0.94379848,  0.39548567,
  //              0.90217608,  0.57424510,  0.05995686, -0.00974263,
  //              -0.45620662, -0.36967716, -0.56535333, -0.93745488,
  //              -0.55570704,  0.04399948, -0.57520008, -0.05702910
  VLOAD_32(v8, 0xbc053c4a, 0xbec60586, 0x3f719cc7, 0x3eca7d19, 0x3f66f503,
           0x3f1301ba, 0x3d759554, 0xbc1f9f8d, 0xbee993ea, 0xbebd4653,
           0xbf10baff, 0xbf6ffd0b, 0xbf0e42d1, 0x3d3438cd, 0xbf134050,
           0xbd699758);
  asm volatile("vfsgnjn.vf v4, v8, %[A]" ::[A] "f"(dscalar_32));
  //              -0.00813205, -0.38676089, -0.94379848, -0.39548567,
  //              -0.90217608, -0.57424510, -0.05995686, -0.00974263,
  //              -0.45620662, -0.36967716, -0.56535333, -0.93745488,
  //              -0.55570704, -0.04399948, -0.57520008, -0.05702910
  VCMP_U32(8, v4, 0xbc053c4a, 0xbec60586, 0xbf719cc7, 0xbeca7d19, 0xbf66f503,
           0xbf1301ba, 0xbd759554, 0xbc1f9f8d, 0xbee993ea, 0xbebd4653,
           0xbf10baff, 0xbf6ffd0b, 0xbf0e42d1, 0xbd3438cd, 0xbf134050,
           0xbd699758);

  VSET(16, e64, m8);
  double dscalar_64;
  //                                0.1909501680714165
  BOX_DOUBLE_IN_DOUBLE(dscalar_64, 0x3fc8710e1b8426e8);
  //               -0.2692390874696449, -0.3268380231167121, 0.8386824891028197,
  //               -0.5650452268361481, -0.6389787807266418, 0.5318945600667211,
  //               -0.7817543128402196, -0.5679136293897145,
  //               -0.0001555883762874,  0.5283267089670276, 0.5439688283816015,
  //               -0.2866314604291811, -0.0576946087921848, 0.7960283598249005,
  //               -0.8999056473475127,  0.2142070697411482
  VLOAD_64(v16, 0xbfd13b3694df2b24, 0xbfd4eaea07180958, 0x3fead67ca8cd9566,
           0xbfe214d9ba40b584, 0xbfe47283a0c1e25c, 0x3fe10547bd8d051e,
           0xbfe904219ee4fb76, 0xbfe22c593425cec0, 0xbf2464adf9bfe000,
           0x3fe0e80d6a13bbf4, 0x3fe1683150fe2844, 0xbfd2582b7b231344,
           0xbfad8a25d3d5fd40, 0x3fe9791077845df2, 0xbfeccc06ed9afc1e,
           0x3fcb6b23238e1bc8);
  asm volatile("vfsgnjn.vf v8, v16, %[A]" ::[A] "f"(dscalar_64));
  //              -0.2692390874696449, -0.3268380231167121, -0.8386824891028197,
  //              -0.5650452268361481, -0.6389787807266418, -0.5318945600667211,
  //              -0.7817543128402196, -0.5679136293897145, -0.0001555883762874,
  //              -0.5283267089670276, -0.5439688283816015, -0.2866314604291811,
  //              -0.0576946087921848, -0.7960283598249005, -0.8999056473475127,
  //              -0.2142070697411482
  VCMP_U64(9, v8, 0xbfd13b3694df2b24, 0xbfd4eaea07180958, 0xbfead67ca8cd9566,
           0xbfe214d9ba40b584, 0xbfe47283a0c1e25c, 0xbfe10547bd8d051e,
           0xbfe904219ee4fb76, 0xbfe22c593425cec0, 0xbf2464adf9bfe000,
           0xbfe0e80d6a13bbf4, 0xbfe1683150fe2844, 0xbfd2582b7b231344,
           0xbfad8a25d3d5fd40, 0xbfe9791077845df2, 0xbfeccc06ed9afc1e,
           0xbfcb6b23238e1bc8);
};

// Simple random test with similar values (vector-scalar) (masked)
void TEST_CASE4(void) {
  VSET(16, e16, m2);
  double dscalar_16;
  //                             -0.6143
  BOX_HALF_IN_DOUBLE(dscalar_16, 0xb8ea);
  //               -0.9351,  0.6538, -0.6743, -0.4695, -0.1439,  0.6250,
  //               -0.1511, -0.7476,  0.8496,  0.6279,  0.5234,  0.2610, 0.6299,
  //               -0.0123, -0.9995, -0.3872
  VLOAD_16(v4, 0xbb7b, 0x393b, 0xb965, 0xb783, 0xb09b, 0x3900, 0xb0d6, 0xb9fb,
           0x3acc, 0x3906, 0x3830, 0x342d, 0x390a, 0xa24d, 0xbbff, 0xb632);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v2);
  asm volatile("vfsgnjn.vf v2, v4, %[A], v0.t" ::[A] "f"(dscalar_16));
  //                0.0000,  0.6538,  0.0000,  0.4695,  0.0000,  0.6250, 0.0000,
  //                0.7476,  0.0000,  0.6279,  0.0000,  0.2610,  0.0000, 0.0123,
  //                0.0000,  0.3872
  VCMP_U16(10, v2, 0x0, 0x393b, 0x0, 0x3783, 0x0, 0x3900, 0x0, 0x39fb, 0x0,
           0x3906, 0x0, 0x342d, 0x0, 0x224d, 0x0, 0x3632);

  VSET(16, e32, m4);
  double dscalar_32;
  //                               0.56259364
  BOX_FLOAT_IN_DOUBLE(dscalar_32, 0x3f100623);
  //               -0.00813205, -0.38676089,  0.94379848,  0.39548567,
  //               0.90217608,  0.57424510,  0.05995686, -0.00974263,
  //               -0.45620662, -0.36967716, -0.56535333, -0.93745488,
  //               -0.55570704,  0.04399948, -0.57520008, -0.05702910
  VLOAD_32(v8, 0xbc053c4a, 0xbec60586, 0x3f719cc7, 0x3eca7d19, 0x3f66f503,
           0x3f1301ba, 0x3d759554, 0xbc1f9f8d, 0xbee993ea, 0xbebd4653,
           0xbf10baff, 0xbf6ffd0b, 0xbf0e42d1, 0x3d3438cd, 0xbf134050,
           0xbd699758);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfsgnjn.vf v4, v8, %[A], v0.t" ::[A] "f"(dscalar_32));
  //                0.00000000, -0.38676089,  0.00000000, -0.39548567,
  //                0.00000000, -0.57424510,  0.00000000, -0.00974263,
  //                0.00000000, -0.36967716,  0.00000000, -0.93745488,
  //                0.00000000, -0.04399948,  0.00000000, -0.05702910
  VCMP_U32(11, v4, 0x0, 0xbec60586, 0x0, 0xbeca7d19, 0x0, 0xbf1301ba, 0x0,
           0xbc1f9f8d, 0x0, 0xbebd4653, 0x0, 0xbf6ffd0b, 0x0, 0xbd3438cd, 0x0,
           0xbd699758);

  VSET(16, e64, m8);
  double dscalar_64;
  //                                0.1909501680714165
  BOX_DOUBLE_IN_DOUBLE(dscalar_64, 0x3fc8710e1b8426e8);
  //                -0.2692390874696449, -0.3268380231167121,
  //                0.8386824891028197, -0.5650452268361481,
  //                -0.6389787807266418,  0.5318945600667211,
  //                -0.7817543128402196, -0.5679136293897145,
  //                -0.0001555883762874,  0.5283267089670276,
  //                0.5439688283816015, -0.2866314604291811,
  //                -0.0576946087921848,  0.7960283598249005,
  //                -0.8999056473475127,  0.2142070697411482
  VLOAD_64(v16, 0xbfd13b3694df2b24, 0xbfd4eaea07180958, 0x3fead67ca8cd9566,
           0xbfe214d9ba40b584, 0xbfe47283a0c1e25c, 0x3fe10547bd8d051e,
           0xbfe904219ee4fb76, 0xbfe22c593425cec0, 0xbf2464adf9bfe000,
           0x3fe0e80d6a13bbf4, 0x3fe1683150fe2844, 0xbfd2582b7b231344,
           0xbfad8a25d3d5fd40, 0x3fe9791077845df2, 0xbfeccc06ed9afc1e,
           0x3fcb6b23238e1bc8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v8);
  asm volatile("vfsgnjn.vf v8, v16, %[A], v0.t" ::[A] "f"(dscalar_64));
  //                0.0000000000000000, -0.3268380231167121, 0.0000000000000000,
  //                -0.5650452268361481,  0.0000000000000000,
  //                -0.5318945600667211,  0.0000000000000000,
  //                -0.5679136293897145,  0.0000000000000000,
  //                -0.5283267089670276,  0.0000000000000000,
  //                -0.2866314604291811,  0.0000000000000000,
  //                -0.7960283598249005,  0.0000000000000000,
  //                -0.2142070697411482
  VCMP_U64(12, v8, 0x0, 0xbfd4eaea07180958, 0x0, 0xbfe214d9ba40b584, 0x0,
           0xbfe10547bd8d051e, 0x0, 0xbfe22c593425cec0, 0x0, 0xbfe0e80d6a13bbf4,
           0x0, 0xbfd2582b7b231344, 0x0, 0xbfe9791077845df2, 0x0,
           0xbfcb6b23238e1bc8);
};

int main(void) {
  enable_vec();
  enable_fp();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();

  EXIT_CHECK();
}
