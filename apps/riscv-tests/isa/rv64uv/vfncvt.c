// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "float_macros.h"
#include "vector_macros.h"

/////////////////
// vfncvt.xu.f //
/////////////////

// Simple random test with similar values
void TEST_CASE1(void) {
  VSET(16, e16, m1);
  //                9165.669,   5488.131,  -1648.302,  80154.047,   7163.093,
  //                -6826.076,  -6976.746,   2675.899,   9587.624, -3671.810,
  //                3611.960, -9086.531, -5333.617, -3284.205,   5676.141,
  //                -8293.472
  VLOAD_32(v2, 0x460f36ad, 0x45ab810c, 0x479c8d06, 0xc59cf316, 0x45dfd8be,
           0xc5d5509c, 0xc5da05f8, 0x45273e62, 0x4615ce7f, 0xc5657cf5,
           0x4561bf5b, 0xc60dfa20, 0xc5a6acf0, 0xc54d4347, 0x45b16120,
           0xc60195e3);
  asm volatile("vfncvt.xu.f.w v4, v2");
  //                    9166,       5488,      65535,          0,       7163, 0,
  //                    0,       2676,       9588,          0,       3612, 0, 0,
  //                    0,       5676,          0
  VCMP_U16(1, v4, 0x23ce, 0x1570, 0xffff, 0x0000, 0x1bfb, 0x0000, 0x0000,
           0x0a74, 0x2574, 0x0000, 0x0e1c, 0x0000, 0x0000, 0x0000, 0x162c,
           0x0000);

  VSET(16, e32, m1);
  //              -3508862.563,   1678202.418, -799491.756,   1707676.429,
  //              -5056868.769,   4282070.604,   458667.918,   8393053.957,
  //              -4485003.775, -5016427.098, -9086965.507, -6796529.257,
  //              -7756776.890, -1173384.460,   4850684.145,   8658279.578
  VLOAD_64(v2, 0xc14ac53f4813ac38, 0x41399b7a6ae9e42f, 0xc128660783332e44,
           0x413a0e9c6ddfa609, 0xc1534a59313a407b, 0x415055b5a6a655de,
           0x411bfeafabb28b3f, 0x4160022bbe9fc5e9, 0xc1511be2f1a1ac8b,
           0xc15322dac64b7c31, 0xc16154feb0372db3, 0xc159ed3c506ab6eb,
           0xc15d96fa38fb0400, 0xc131e78875bc4ace, 0x415280ff09493a97,
           0x416083acf280b61e);
  asm volatile("vfncvt.xu.f.w v4, v2");
  //                           0,        1678202,              0, 1707676, 0,
  //                           4282071,         458668,        8393054, 0, 0, 0,
  //                           0,              0,              0, 4850684,
  //                           8658280
  VCMP_U32(2, v4, 0x00000000, 0x00199b7a, 0x00000000, 0x001a0e9c, 0x00000000,
           0x004156d7, 0x0006ffac, 0x0080115e, 0x00000000, 0x00000000,
           0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x004a03fc,
           0x00841d68);
};

// Simple random test with similar values (masked)
// The numbers are the same of TEST_CASE1
void TEST_CASE2(void) {
  VSET(16, e16, m1);
  //                    9165.669,       5488.131,      -1648.302, -5022.386,
  //                    7163.093, -6826.076, -6976.746,   2675.899,   9587.624,
  //                    -3671.810,   3611.960, -9086.531, -5333.617, -3284.205,
  //                    5676.141, -8293.472
  VLOAD_32(v2, 0x460f36ad, 0x45ab810c, 0xc4ce09ad, 0xc59cf316, 0x45dfd8be,
           0xc5d5509c, 0xc5da05f8, 0x45273e62, 0x4615ce7f, 0xc5657cf5,
           0x4561bf5b, 0xc60dfa20, 0xc5a6acf0, 0xc54d4347, 0x45b16120,
           0xc60195e3);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.xu.f.w v4, v2, v0.t");
  //                       0,       5488,          0,          0,          0, 0,
  //                       0,       2676,          0,          0,          0, 0,
  //                       0,          0,          0,          0
  VCMP_U16(3, v4, 0x0000, 0x1570, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
           0x0a74, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
           0x0000);

  VSET(16, e32, m1);
  //                        -3508862.563,            1678202.418, -799491.756,
  //                        1707676.429, -5056868.769,   4282070.604,
  //                        458667.918,   8393053.957, -4485003.775,
  //                        -5016427.098, -9086965.507, -6796529.257,
  //                        -7756776.890, -1173384.460,   4850684.145,
  //                        8658279.578
  VLOAD_64(v2, 0xc14ac53f4813ac38, 0x41399b7a6ae9e42f, 0xc128660783332e44,
           0x413a0e9c6ddfa609, 0xc1534a59313a407b, 0x415055b5a6a655de,
           0x411bfeafabb28b3f, 0x4160022bbe9fc5e9, 0xc1511be2f1a1ac8b,
           0xc15322dac64b7c31, 0xc16154feb0372db3, 0xc159ed3c506ab6eb,
           0xc15d96fa38fb0400, 0xc131e78875bc4ace, 0x415280ff09493a97,
           0x416083acf280b61e);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.xu.f.w v4, v2, v0.t");
  //                           0,        1678202,              0, 1707676, 0,
  //                           4282071,              0,        8393054, 0, 0, 0,
  //                           0,              0,              0, 0, 8658280
  VCMP_U32(4, v4, 0x00000000, 0x00199b7a, 0x00000000, 0x001a0e9c, 0x00000000,
           0x004156d7, 0x00000000, 0x0080115e, 0x00000000, 0x00000000,
           0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
           0x00841d68);
};

////////////////
// vfncvt.x.f //
////////////////

// Simple random test with similar values
void TEST_CASE3(void) {
  VSET(16, e16, m1);
  //              -7808.056,   9317.408,   1685.891,   3975.596, -5978.108,
  //              9676.333,   6963.966,   3589.870, -4334.772, -3261.309,
  //              -2340.480,   6085.075,   4043.322,   2827.902,   4389.497,
  //              -5196.684
  VLOAD_32(v2, 0xc5f40072, 0x461195a2, 0x44d2bc86, 0x4578798a, 0xc5bad0dd,
           0x46173155, 0x45d99fbb, 0x45605ded, 0xc587762e, 0xc54bd4f0,
           0xc51247af, 0x45be2899, 0x457cb528, 0x4530be6f, 0x45892bfa,
           0xc5a26578);
  asm volatile("vfncvt.x.f.w v4, v2");
  //                   -7808,       9317,       1686,       3976,      -5978,
  //                   9676,       6964,       3590,      -4335,      -3261,
  //                   -2340,       6085,       4043,       2828,       4389,
  //                   -5197
  VCMP_U16(5, v4, 0xe180, 0x2465, 0x0696, 0x0f88, 0xe8a6, 0x25cc, 0x1b34,
           0x0e06, 0xef11, 0xf343, 0xf6dc, 0x17c5, 0x0fcb, 0x0b0c, 0x1125,
           0xebb3);

  VSET(16, e32, m1);
  //                5365665.770, -7563846.858,   8056193.411, -2468299.255,
  //                -9624608.750, -6974543.165,   5868078.422, -5387798.170,
  //                3847378.080,   1368753.124,   4380497.931, -8044304.268,
  //                1687738.849,   3753399.509, -3684410.483, -7416477.444
  VLOAD_64(v2, 0x415477e8714aea69, 0xc15cda91b6eefd56, 0x415ebb605a479cd5,
           0xc142d4e5a0a1f367, 0xc1625b841802ee1d, 0xc15a9b13ca8c7bb6,
           0x4156628b9afacdc9, 0xc1548d858ae6df86, 0x414d5a690a2dbb5e,
           0x4134e2b11fa8e994, 0x4150b5d47b9c3df2, 0xc15eafc4112995f5,
           0x4139c0bad971859a, 0x414ca2dbc1288a12, 0xc14c1c1d3dcd1b39,
           0xc15c4aa75c6c5635);
  asm volatile("vfncvt.x.f.w v4, v2");
  //                     5365666,       -7563847,        8056193, -2468299,
  //                     -9624609,       -6974543,        5868078, -5387798,
  //                     3847378,        1368753,        4380498, -8044304,
  //                     1687739,        3753400,       -3684410,       -7416477
  VCMP_U32(6, v4, 0x0051dfa2, 0xff8c95b9, 0x007aed81, 0xffda5635, 0xff6d23df,
           0xff9593b1, 0x00598a2e, 0xffadc9ea, 0x003ab4d2, 0x0014e2b1,
           0x0042d752, 0xff8540f0, 0x0019c0bb, 0x003945b8, 0xffc7c7c6,
           0xff8ed563);
};

// Simple random test with similar values (masked)
// The numbers are the same of TEST_CASE1
void TEST_CASE4(void) {
  VSET(16, e16, m1);
  //              -7808.056,   9317.408,   1685.891,   3975.596, -5978.108,
  //              9676.333,   6963.966,   3589.870, -4334.772, -3261.309,
  //              -2340.480,   6085.075,   4043.322,   2827.902,   4389.497,
  //              -5196.684
  VLOAD_32(v2, 0xc5f40072, 0x461195a2, 0x44d2bc86, 0x4578798a, 0xc5bad0dd,
           0x46173155, 0x45d99fbb, 0x45605ded, 0xc587762e, 0xc54bd4f0,
           0xc51247af, 0x45be2899, 0x457cb528, 0x4530be6f, 0x45892bfa,
           0xc5a26578);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.x.f.w v4, v2, v0.t");
  //                       0,       9317,          0,       3976,          0,
  //                       9676,          0,       3590,          0,      -3261,
  //                       0,       6085,          0,       2828,          0,
  //                       -5197
  VCMP_U16(7, v4, 0x0000, 0x2465, 0x0000, 0x0f88, 0x0000, 0x25cc, 0x0000,
           0x0e06, 0x0000, 0xf343, 0x0000, 0x17c5, 0x0000, 0x0b0c, 0x0000,
           0xebb3);

  VSET(16, e32, m1);
  //                5365665.770, -7563846.858,   8056193.411, -2468299.255,
  //                -9624608.750, -6974543.165,   5868078.422, -5387798.170,
  //                3847378.080,   1368753.124,   4380497.931, -8044304.268,
  //                1687738.849,   3753399.509, -3684410.483, -7416477.444
  VLOAD_64(v2, 0x415477e8714aea69, 0xc15cda91b6eefd56, 0x415ebb605a479cd5,
           0xc142d4e5a0a1f367, 0xc1625b841802ee1d, 0xc15a9b13ca8c7bb6,
           0x4156628b9afacdc9, 0xc1548d858ae6df86, 0x414d5a690a2dbb5e,
           0x4134e2b11fa8e994, 0x4150b5d47b9c3df2, 0xc15eafc4112995f5,
           0x4139c0bad971859a, 0x414ca2dbc1288a12, 0xc14c1c1d3dcd1b39,
           0xc15c4aa75c6c5635);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.x.f.w v4, v2, v0.t");
  //                           0,       -7563847,              0, -2468299, 0,
  //                           -6974543,              0,       -5387798, 0,
  //                           1368753,              0,       -8044304, 0,
  //                           3753400,              0,       -7416477
  VCMP_U32(8, v4, 0x00000000, 0xff8c95b9, 0x00000000, 0xffda5635, 0x00000000,
           0xff9593b1, 0x00000000, 0xffadc9ea, 0x00000000, 0x0014e2b1,
           0x00000000, 0xff8540f0, 0x00000000, 0x003945b8, 0x00000000,
           0xff8ed563);
};

/////////////////////
// vfncvt.rtz.xu.f //
/////////////////////

// Simple random test with similar values
void TEST_CASE5(void) {
  VSET(16, e16, m1);
  //              -9750.252, -4363.736, -2345.615,   6996.062, -7115.004,
  //              6670.171, -4079.234, -1773.082,   254.350,   53.058,
  //              -9041.926, -8137.022,   1522.146,   198.516, -920.430,
  //              2857.583
  VLOAD_32(v2, 0xc6185902, 0xc5885de3, 0xc51299d6, 0x45daa07e, 0xc5de5808,
           0x45d0715e, 0xc57ef3bf, 0xc4dda29c, 0x437e5998, 0x42543afb,
           0xc60d47b4, 0xc5fe482e, 0x44be44af, 0x43468433, 0xc4661b8b,
           0x45329953);
  asm volatile("vfncvt.rtz.xu.f.w v4, v2");
  //                       0,          0,          0,       6996,          0,
  //                       6670,          0,          0,        254,         53,
  //                       0,          0,       1522,        198,          0,
  //                       2857
  VCMP_U16(9, v4, 0x0000, 0x0000, 0x0000, 0x1b54, 0x0000, 0x1a0e, 0x0000,
           0x0000, 0x00fe, 0x0035, 0x0000, 0x0000, 0x05f2, 0x00c6, 0x0000,
           0x0b29);

  VSET(16, e32, m1);
  //              -8404683.758,   3627605.540, -4368861.865, -2883871.623,
  //              5750957.328, -7243911.338, -8202847.045,   5348152.868,
  //              9957770.965,   8018962.598, -8478197.842, -9780786.953,
  //              184470.081,   250336.923, -6517203.475, -7691903.192
  VLOAD_64(v2, 0xc16007d978438b7f, 0x414bad2ac51eade4, 0xc150aa777763eeda,
           0xc146008fcfc2093b, 0x4155f02b54fbd105, 0xc15ba221d5a4f5c3,
           0xc15f4a97c2e2daa6, 0x415466ce378e9269, 0x4162fe315edeecec,
           0x415e9704a64d845e, 0xc1602bbebaf40bb8, 0xc162a7c65e8002a9,
           0x410684b0a4ee482d, 0x410e8f07623ffd06, 0xc158dc74de617fbc,
           0xc15d579fcc41ba16);
  asm volatile("vfncvt.rtz.xu.f.w v4, v2");
  //                           0,        3627605,              0, 0, 5750957, 0,
  //                           0,        5348152,        9957770, 8018962, 0, 0,
  //                           184470,         250336,              0, 0
  VCMP_U32(10, v4, 0x00000000, 0x00375a55, 0x00000000, 0x00000000, 0x0057c0ad,
           0x00000000, 0x00000000, 0x00519b38, 0x0097f18a, 0x007a5c12,
           0x00000000, 0x00000000, 0x0002d096, 0x0003d1e0, 0x00000000,
           0x00000000);
};

// Simple random test with similar values (masked)
// The numbers are the same of TEST_CASE1
void TEST_CASE6(void) {
  VSET(16, e16, m1);
  //              -9750.252, -4363.736, -2345.615,   6996.062, -7115.004,
  //              6670.171, -4079.234, -1773.082,   254.350,   53.058,
  //              -9041.926, -8137.022,   1522.146,   198.516, -920.430,
  //              2857.583
  VLOAD_32(v2, 0xc6185902, 0xc5885de3, 0xc51299d6, 0x45daa07e, 0xc5de5808,
           0x45d0715e, 0xc57ef3bf, 0xc4dda29c, 0x437e5998, 0x42543afb,
           0xc60d47b4, 0xc5fe482e, 0x44be44af, 0x43468433, 0xc4661b8b,
           0x45329953);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.rtz.xu.f.w v4, v2, v0.t");
  //                       0,          0,          0,       6996,          0,
  //                       6670,          0,          0,          0,         53,
  //                       0,          0,          0,        198,          0,
  //                       2857
  VCMP_U16(11, v4, 0x0000, 0x0000, 0x0000, 0x1b54, 0x0000, 0x1a0e, 0x0000,
           0x0000, 0x0000, 0x0035, 0x0000, 0x0000, 0x0000, 0x00c6, 0x0000,
           0x0b29);

  VSET(16, e32, m1);
  //              -8404683.758,   3627605.540, -4368861.865, -2883871.623,
  //              5750957.328, -7243911.338, -8202847.045,   5348152.868,
  //              9957770.965,   8018962.598, -8478197.842, -9780786.953,
  //              184470.081,   250336.923, -6517203.475, -7691903.192
  VLOAD_64(v2, 0xc16007d978438b7f, 0x414bad2ac51eade4, 0xc150aa777763eeda,
           0xc146008fcfc2093b, 0x4155f02b54fbd105, 0xc15ba221d5a4f5c3,
           0xc15f4a97c2e2daa6, 0x415466ce378e9269, 0x4162fe315edeecec,
           0x415e9704a64d845e, 0xc1602bbebaf40bb8, 0xc162a7c65e8002a9,
           0x410684b0a4ee482d, 0x410e8f07623ffd06, 0xc158dc74de617fbc,
           0xc15d579fcc41ba16);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.rtz.xu.f.w v4, v2, v0.t");
  //                           0,        3627605,              0, 0, 0, 0, 0,
  //                           5348152,              0,        8018962, 0, 0, 0,
  //                           250336,              0,              0
  VCMP_U32(12, v4, 0x00000000, 0x00375a55, 0x00000000, 0x00000000, 0x00000000,
           0x00000000, 0x00000000, 0x00519b38, 0x00000000, 0x007a5c12,
           0x00000000, 0x00000000, 0x00000000, 0x0003d1e0, 0x00000000,
           0x00000000);
};

////////////////////
// vfncvt.rtz.x.f //
////////////////////

// Simple random test with similar values
void TEST_CASE7(void) {
  VSET(16, e16, m1);
  //                9352.418, -5719.459,   4617.815, -3012.009, -3597.063,
  //                -5717.140, -3327.545,   1286.004,   1797.767,   3842.966,
  //                -2148.369, -7283.256,   8783.331, -7958.880, -6728.271,
  //                4727.792
  VLOAD_32(v2, 0x461221ac, 0xc5b2bbac, 0x45904e86, 0xc53c4026, 0xc560d104,
           0xc5b2a91e, 0xc54ff8b9, 0x44a0c01e, 0x44e0b88c, 0x45702f76,
           0xc50645e9, 0xc5e39a0c, 0x46093d53, 0xc5f8b70a, 0xc5d2422c,
           0x4593be56);
  asm volatile("vfncvt.rtz.x.f.w v4, v2");
  //                    9352,      -5719,       4617,      -3012,      -3597,
  //                    -5717,      -3327,       1286,       1797,       3842,
  //                    -2148,      -7283,       8783,      -7958,      -6728,
  //                    4727
  VCMP_U16(13, v4, 0x2488, 0xe9a9, 0x1209, 0xf43c, 0xf1f3, 0xe9ab, 0xf301,
           0x0506, 0x0705, 0x0f02, 0xf79c, 0xe38d, 0x224f, 0xe0ea, 0xe5b8,
           0x1277);

  VSET(16, e32, m1);
  //                1563546.261, -1988965.594,   6496092.888,   5054778.769,
  //                9551708.952, -336377.787, -2352111.643,   4412162.570,
  //                7087155.475,   338850.875,   2765611.498,   2723631.912,
  //                -3252079.308,   1096915.326,   5492109.280, -7265880.245
  VLOAD_64(v2, 0x4137db9a42b839bd, 0xc13e596598118127, 0x4158c7d738d1eec8,
           0x4153484eb13573ed, 0x416237eb9e79d2a8, 0xc11487e725f1ce50,
           0xc141f1f7d2451c3d, 0x4150d4c0a47be906, 0x415b090cde6b0575,
           0x4114ae8b8081532d, 0x41451995bfc3bc74, 0x4144c797f4b307dd,
           0xc148cfb7a76dea0f, 0x4130bcd353667e5d, 0x4154f36351f3a3c5,
           0xc15bb7960fb007a5);
  asm volatile("vfncvt.rtz.x.f.w v4, v2");
  //                     1563546,       -1988965,        6496092, 5054778,
  //                     9551708,        -336377,       -2352111, 4412162,
  //                     7087155,         338850,        2765611, 2723631,
  //                     -3252079,        1096915,        5492109, -7265880
  VCMP_U32(14, v4, 0x0017db9a, 0xffe1a69b, 0x00631f5c, 0x004d213a, 0x0091bf5c,
           0xfffade07, 0xffdc1c11, 0x00435302, 0x006c2433, 0x00052ba2,
           0x002a332b, 0x00298f2f, 0xffce6091, 0x0010bcd3, 0x0053cd8d,
           0xff9121a8);
};

// Simple random test with similar values (masked)
// The numbers are the same of TEST_CASE1
void TEST_CASE8(void) {
  VSET(16, e16, m1);
  //                9352.418, -5719.459,   4617.815, -3012.009, -3597.063,
  //                -5717.140, -3327.545,   1286.004,   1797.767,   3842.966,
  //                -2148.369, -7283.256,   8783.331, -7958.880, -6728.271,
  //                4727.792
  VLOAD_32(v2, 0x461221ac, 0xc5b2bbac, 0x45904e86, 0xc53c4026, 0xc560d104,
           0xc5b2a91e, 0xc54ff8b9, 0x44a0c01e, 0x44e0b88c, 0x45702f76,
           0xc50645e9, 0xc5e39a0c, 0x46093d53, 0xc5f8b70a, 0xc5d2422c,
           0x4593be56);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.rtz.x.f.w v4, v2, v0.t");
  //                       0,      -5719,          0,      -3012,          0,
  //                       -5717,          0,       1286,          0, 3842, 0,
  //                       -7283,          0,      -7958,          0,       4727
  VCMP_U16(15, v4, 0x0000, 0xe9a9, 0x0000, 0xf43c, 0x0000, 0xe9ab, 0x0000,
           0x0506, 0x0000, 0x0f02, 0x0000, 0xe38d, 0x0000, 0xe0ea, 0x0000,
           0x1277);

  VSET(16, e32, m1);
  //                1563546.261, -1988965.594,   6496092.888,   5054778.769,
  //                9551708.952, -336377.787, -2352111.643,   4412162.570,
  //                7087155.475,   338850.875,   2765611.498,   2723631.912,
  //                -3252079.308,   1096915.326,   5492109.280, -7265880.245
  VLOAD_64(v2, 0x4137db9a42b839bd, 0xc13e596598118127, 0x4158c7d738d1eec8,
           0x4153484eb13573ed, 0x416237eb9e79d2a8, 0xc11487e725f1ce50,
           0xc141f1f7d2451c3d, 0x4150d4c0a47be906, 0x415b090cde6b0575,
           0x4114ae8b8081532d, 0x41451995bfc3bc74, 0x4144c797f4b307dd,
           0xc148cfb7a76dea0f, 0x4130bcd353667e5d, 0x4154f36351f3a3c5,
           0xc15bb7960fb007a5);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.rtz.x.f.w v4, v2, v0.t");
  //                           0,       -1988965,              0, 5054778, 0,
  //                           -336377,              0,        4412162, 0,
  //                           338850,              0,        2723631, 0,
  //                           1096915,              0,       -7265880
  VCMP_U32(16, v4, 0x00000000, 0xffe1a69b, 0x00000000, 0x004d213a, 0x00000000,
           0xfffade07, 0x00000000, 0x00435302, 0x00000000, 0x00052ba2,
           0x00000000, 0x00298f2f, 0x00000000, 0x0010bcd3, 0x00000000,
           0xff9121a8);
};

/////////////////
// vfncvt.f.xu //
/////////////////

// Simple random test with similar values
void TEST_CASE9(void) {
  VSET(16, e16, m1);
  //                 4294964178,       5853,    4294962638,    4294962082, 4585,
  //                 1637,       3984,    4294964217,       9553,    4294962615,
  //                 4294962166,       9867,    4294958580,    4294966752, 5172,
  //                 7478
  VLOAD_32(v2, 0xfffff3d2, 0x000016dd, 0xffffedce, 0xffffeba2, 0x000011e9,
           0x00000665, 0x00000f90, 0xfffff3f9, 0x00002551, 0xffffedb7,
           0xffffebf6, 0x0000268b, 0xffffddf4, 0xfffffde0, 0x00001434,
           0x00001d36);
  asm volatile("vfncvt.f.xu.w v4, v2");
  //                     inf,   5852.000,   inf,   inf,   4584.000,   1637.000,
  //                     3984.000,   inf,   9552.000,   inf,   inf,   9864.000,
  //                     inf,   inf,   5172.000,   7480.000
  VCMP_U16(17, v4, 0x7c00, 0x6db7, 0x7c00, 0x7c00, 0x6c7a, 0x6665, 0x6bc8,
           0x7c00, 0x70aa, 0x7c00, 0x7c00, 0x70d1, 0x7c00, 0x7c00, 0x6d0d,
           0x6f4e);

  VSET(16, e32, m1);
  //                 18446744073704835106,    18446744073709117625,
  //                 18446744073705901616,        2086515, 18446744073699655996,
  //                 932771,         255753,        3148047,
  //                 18446744073705977615,    18446744073704792883,
  //                 18446744073704699584,        8685460, 18446744073709143843,
  //                 18446744073703142874,        3905530, 18446744073704152149
  VLOAD_64(v2, 0xffffffffffb80822, 0xfffffffffff960b9, 0xffffffffffc84e30,
           0x00000000001fd673, 0xffffffffff69013c, 0x00000000000e3ba3,
           0x000000000003e709, 0x000000000030090f, 0xffffffffffc9770f,
           0xffffffffffb76333, 0xffffffffffb5f6c0, 0x0000000000848794,
           0xfffffffffff9c723, 0xffffffffff9e35da, 0x00000000003b97fa,
           0xffffffffffad9c55);
  asm volatile("vfncvt.f.xu.w v4, v2");
  //                18446744073709551616.000,   18446744073709551616.000,
  //                18446744073709551616.000,   2086515.000,
  //                18446744073709551616.000,   932771.000,   255753.000,
  //                3148047.000,   18446744073709551616.000,
  //                18446744073709551616.000,   18446744073709551616.000,
  //                8685460.000,   18446744073709551616.000,
  //                18446744073709551616.000,   3905530.000,
  //                18446744073709551616.000
  VCMP_U32(18, v4, 0x5f800000, 0x5f800000, 0x5f800000, 0x49feb398, 0x5f800000,
           0x4963ba30, 0x4879c240, 0x4a40243c, 0x5f800000, 0x5f800000,
           0x5f800000, 0x4b048794, 0x5f800000, 0x5f800000, 0x4a6e5fe8,
           0x5f800000);
};

// Simple random test with similar values (masked)
// The numbers are the same of TEST_CASE1
void TEST_CASE10(void) {
  VSET(16, e16, m1);
  //                 4294964178,       5853,    4294962638,    4294962082, 4585,
  //                 1637,       3984,    4294964217,       9553,    4294962615,
  //                 4294962166,       9867,    4294958580,    4294966752, 5172,
  //                 7478
  VLOAD_32(v2, 0xfffff3d2, 0x000016dd, 0xffffedce, 0xffffeba2, 0x000011e9,
           0x00000665, 0x00000f90, 0xfffff3f9, 0x00002551, 0xffffedb7,
           0xffffebf6, 0x0000268b, 0xffffddf4, 0xfffffde0, 0x00001434,
           0x00001d36);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.f.xu.w v4, v2, v0.t");
  //                0.000,   5852.000,   0.000,   inf,   0.000,   1637.000,
  //                0.000,   inf,   0.000,   inf,   0.000,   9864.000,   0.000,
  //                inf,   0.000,   7480.000
  VCMP_U16(19, v4, 0x0, 0x6db7, 0x0, 0x7c00, 0x0, 0x6665, 0x0, 0x7c00, 0x0,
           0x7c00, 0x0, 0x70d1, 0x0, 0x7c00, 0x0, 0x6f4e);

  VSET(16, e32, m1);
  //                 18446744073704835106,    18446744073709117625,
  //                 18446744073705901616,        2086515, 18446744073699655996,
  //                 932771,         255753,        3148047,
  //                 18446744073705977615,    18446744073704792883,
  //                 18446744073704699584,        8685460, 18446744073709143843,
  //                 18446744073703142874,        3905530, 18446744073704152149
  VLOAD_64(v2, 0xffffffffffb80822, 0xfffffffffff960b9, 0xffffffffffc84e30,
           0x00000000001fd673, 0xffffffffff69013c, 0x00000000000e3ba3,
           0x000000000003e709, 0x000000000030090f, 0xffffffffffc9770f,
           0xffffffffffb76333, 0xffffffffffb5f6c0, 0x0000000000848794,
           0xfffffffffff9c723, 0xffffffffff9e35da, 0x00000000003b97fa,
           0xffffffffffad9c55);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.f.xu.w v4, v2, v0.t");
  //                0.000,   18446744073709551616.000,   0.000,   2086515.000,
  //                0.000,   932771.000,   0.000,   3148047.000,   0.000,
  //                18446744073709551616.000,   0.000,   8685460.000,   0.000,
  //                18446744073709551616.000,   0.000, 18446744073709551616.000
  VCMP_U32(20, v4, 0x0, 0x5f800000, 0x0, 0x49feb398, 0x0, 0x4963ba30, 0x0,
           0x4a40243c, 0x0, 0x5f800000, 0x0, 0x4b048794, 0x0, 0x5f800000, 0x0,
           0x5f800000);
};

////////////////
// vfncvt.f.x //
////////////////

// Simple random test with similar values
void TEST_CASE11(void) {
  VSET(16, e16, m1);
  //                       -6279,           3717,           9022, -8925, -5530,
  //                       3851,       5592,      -3692,      -2747,       -748,
  //                       -2621,      -9352,       4018,       3174, -6975,
  //                       -4466
  VLOAD_32(v2, 0xffffe779, 0x00000e85, 0x0000233e, 0xffffdd23, 0xffffea66,
           0x00000f0b, 0x000015d8, 0xfffff194, 0xfffff545, 0xfffffd14,
           0xfffff5c3, 0xffffdb78, 0x00000fb2, 0x00000c66, 0xffffe4c1,
           0xffffee8e);
  asm volatile("vfncvt.f.x.w v4, v2");
  //                -6280.000,   3716.000,   9024.000,  -8928.000,  -5528.000,
  //                3852.000,   5592.000, -3692.000, -2748.000, -748.000,
  //                -2620.000, -9352.000,   4018.000,   3174.000, -6976.000,
  //                -4464.000
  VCMP_U16(21, v4, 0xee22, 0x6b42, 0x7068, 0xf05c, 0xed66, 0x6b86, 0x6d76,
           0xeb36, 0xe95e, 0xe1d8, 0xe91e, 0xf091, 0x6bd9, 0x6a33, 0xeed0,
           0xec5c);

  VSET(16, e32, m1);
  //                              757099,       -9365555,        3016973,
  //                              -9277105,       -8350486,        -650348,
  //                              -1775160,        4659116,         148573,
  //                              4475248,       -2937762,        3310433,
  //                              9151745,       -2201488,       -1506850,
  //                              1593161
  VLOAD_64(v2, 0x00000000000b8d6b, 0xffffffffff7117cd, 0x00000000002e090d,
           0xffffffffff72714f, 0xffffffffff8094ea, 0xfffffffffff61394,
           0xffffffffffe4e9c8, 0x00000000004717ac, 0x000000000002445d,
           0x0000000000444970, 0xffffffffffd32c5e, 0x0000000000328361,
           0x00000000008ba501, 0xffffffffffde6870, 0xffffffffffe901de,
           0x0000000000184f49);
  asm volatile("vfncvt.f.x.w v4, v2");
  //                   757099.000, -9365555.000,   3016973.000, -9277105.000,
  //                   -8350486.000, -650348.000, -1775160.000,   4659116.000,
  //                   148573.000,   4475248.000, -2937762.000,   3310433.000,
  //                   9151745.000, -2201488.000, -1506850.000,   1593161.000
  VCMP_U32(22, v4, 0x4938d6b0, 0xcb0ee833, 0x4a382434, 0xcb0d8eb1, 0xcafed62c,
           0xc91ec6c0, 0xc9d8b1c0, 0x4a8e2f58, 0x48111740, 0x4a8892e0,
           0xca334e88, 0x4a4a0d84, 0x4b0ba501, 0xca065e40, 0xc9b7f110,
           0x49c27a48);
};

// Simple random test with similar values (masked)
// The numbers are the same of TEST_CASE1
void TEST_CASE12(void) {
  VSET(16, e16, m1);
  //                   -6279,       3717,       9022,      -8925,      -5530,
  //                   3851,       5592,      -3692,      -2747,       -748,
  //                   -2621,      -9352,       4018,       3174,      -6975,
  //                   -4466
  VLOAD_32(v2, 0xffffe779, 0x00000e85, 0x0000233e, 0xffffdd23, 0xffffea66,
           0x00000f0b, 0x000015d8, 0xfffff194, 0xfffff545, 0xfffffd14,
           0xfffff5c3, 0xffffdb78, 0x00000fb2, 0x00000c66, 0xffffe4c1,
           0xffffee8e);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.f.x.w v4, v2, v0.t");
  //                0.000,   3716.000,   0.000, -8928.000,   0.000,   3852.000,
  //                0.000, -3692.000,   0.000, -748.000,   0.000, -9352.000,
  //                0.000,   3174.000,   0.000, -4464.000
  VCMP_U16(23, v4, 0x0, 0x6b42, 0x0, 0xf05c, 0x0, 0x6b86, 0x0, 0xeb36, 0x0,
           0xe1d8, 0x0, 0xf091, 0x0, 0x6a33, 0x0, 0xec5c);

  VSET(16, e32, m1);
  //                      757099,       -9365555,        3016973, -9277105,
  //                      -8350486,        -650348,       -1775160, 4659116,
  //                      148573,        4475248,       -2937762, 3310433,
  //                      9151745,       -2201488,       -1506850, 1593161
  VLOAD_64(v2, 0x00000000000b8d6b, 0xffffffffff7117cd, 0x00000000002e090d,
           0xffffffffff72714f, 0xffffffffff8094ea, 0xfffffffffff61394,
           0xffffffffffe4e9c8, 0x00000000004717ac, 0x000000000002445d,
           0x0000000000444970, 0xffffffffffd32c5e, 0x0000000000328361,
           0x00000000008ba501, 0xffffffffffde6870, 0xffffffffffe901de,
           0x0000000000184f49);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.f.x.w v4, v2, v0.t");
  //                0.000, -9365555.000,   0.000, -9277105.000,   0.000,
  //                -650348.000,   0.000,   4659116.000,   0.000,   4475248.000,
  //                0.000,   3310433.000,   0.000, -2201488.000,   0.000,
  //                1593161.000
  VCMP_U32(24, v4, 0x0, 0xcb0ee833, 0x0, 0xcb0d8eb1, 0x0, 0xc91ec6c0, 0x0,
           0x4a8e2f58, 0x0, 0x4a8892e0, 0x0, 0x4a4a0d84, 0x0, 0xca065e40, 0x0,
           0x49c27a48);
};

////////////////
// vfncvt.f.f //
////////////////

// Simple random test with similar values
void TEST_CASE13(void) {
  VSET(16, e16, m1);
  //              908.994, -6788.630, -5789.335, 8054.104, 3947.551, 9596.856,
  //              2474.506, 3094.286, 7684.992, -6850.149, -54.922, 7737.443,
  //              4171.873, 5266.611, 9163.839, 5679.187
  VLOAD_32(v2, 0x44633fa3, 0xc5d4250b, 0xc5b4eaaf, 0x45fbb0d4, 0x4576b8d0,
           0x4615f36d, 0x451aa818, 0x45416494, 0x45f027ef, 0xc5d61131,
           0xc25bb026, 0x45f1cb8c, 0x45825efb, 0x45a494e4, 0x460f2f5b,
           0x45b1797f);
  asm volatile("vfncvt.f.f.w v4, v2");
  //              909.000, -6788.000, -5788.000, 8056.000, 3948.000, 9600.000,
  //              2474.000, 3094.000, 7684.000, -6852.000, -54.938, 7736.000,
  //              4172.000, 5268.000, 9160.000, 5680.000
  VCMP_U16(25, v4, 0x631a, 0xeea1, 0xeda7, 0x6fde, 0x6bb6, 0x70b0, 0x68d5,
           0x6a0b, 0x6f81, 0xeeb1, 0xd2de, 0x6f8e, 0x6c13, 0x6d25, 0x7079,
           0x6d8c);

  VSET(16, e32, m1);
  //              153431.766, -7796010.957, -6652812.196, 1049714.758,
  //              7538298.328, -8731739.480, 537176.622, -3884944.157,
  //              7612336.042, -2270131.404, -4976406.726, -5260237.163,
  //              -4947737.810, 3583352.355, 7648790.331, -9360989.228
  VLOAD_64(v2, 0x4102babe20435c2f, 0xc15dbd4abd4015a9, 0xc15960e30c871450,
           0x41300472c1efbd9f, 0x415cc19e94ffb79b, 0xc160a78b6f5bcd25,
           0x412064b13e931aa9, 0xc14da3c81425b914, 0x415d09ec02a8cc93,
           0xc14151d9b3c1ecaf, 0xc152fbc5ae718384, 0xc15410f34a6ddb48,
           0xc152dfc673d9ba53, 0x414b56bc2d765fad, 0x415d2d85952e8398,
           0xc161dacba74d791e);
  asm volatile("vfncvt.f.f.w v4, v2");
  //              153431.766, -7796011.000, -6652812.000, 1049714.750,
  //              7538298.500, -8731739.000, 537176.625, -3884944.250,
  //              7612336.000, -2270131.500, -4976406.500, -5260237.000,
  //              -4947738.000, 3583352.250, 7648790.500, -9360989.000
  VCMP_U32(26, v4, 0x4815d5f1, 0xcaedea56, 0xcacb0718, 0x49802396, 0x4ae60cf5,
           0xcb053c5b, 0x4903258a, 0xca6d1e41, 0x4ae84f60, 0xca0a8ece,
           0xca97de2d, 0xcaa0879a, 0xca96fe34, 0x4a5ab5e1, 0x4ae96c2d,
           0xcb0ed65d);
};

// Simple random test with similar values (masked)
// The numbers are the same of TEST_CASE1
void TEST_CASE14(void) {
  VSET(16, e16, m1);
  //              908.994, -6788.630, -5789.335, 8054.104, 3947.551, 9596.856,
  //              2474.506, 3094.286, 7684.992, -6850.149, -54.922, 7737.443,
  //              4171.873, 5266.611, 9163.839, 5679.187
  VLOAD_32(v2, 0x44633fa3, 0xc5d4250b, 0xc5b4eaaf, 0x45fbb0d4, 0x4576b8d0,
           0x4615f36d, 0x451aa818, 0x45416494, 0x45f027ef, 0xc5d61131,
           0xc25bb026, 0x45f1cb8c, 0x45825efb, 0x45a494e4, 0x460f2f5b,
           0x45b1797f);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.f.f.w v4, v2, v0.t");
  //              0.000, -6788.000, 0.000, 8056.000, 0.000, 9600.000, 0.000,
  //              3094.000, 0.000, -6852.000, 0.000, 7736.000, 0.000, 5268.000,
  //              0.000, 5680.000
  VCMP_U16(27, v4, 0x0, 0xeea1, 0x0, 0x6fde, 0x0, 0x70b0, 0x0, 0x6a0b, 0x0,
           0xeeb1, 0x0, 0x6f8e, 0x0, 0x6d25, 0x0, 0x6d8c);

  VSET(16, e32, m1);
  //              153431.766, -7796010.957, -6652812.196, 1049714.758,
  //              7538298.328, -8731739.480, 537176.622, -3884944.157,
  //              7612336.042, -2270131.404, -4976406.726, -5260237.163,
  //              -4947737.810, 3583352.355, 7648790.331, -9360989.228
  VLOAD_64(v2, 0x4102babe20435c2f, 0xc15dbd4abd4015a9, 0xc15960e30c871450,
           0x41300472c1efbd9f, 0x415cc19e94ffb79b, 0xc160a78b6f5bcd25,
           0x412064b13e931aa9, 0xc14da3c81425b914, 0x415d09ec02a8cc93,
           0xc14151d9b3c1ecaf, 0xc152fbc5ae718384, 0xc15410f34a6ddb48,
           0xc152dfc673d9ba53, 0x414b56bc2d765fad, 0x415d2d85952e8398,
           0xc161dacba74d791e);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.f.f.w v4, v2, v0.t");
  //              0.000, -7796011.000, 0.000, 1049714.750, 0.000, -8731739.000,
  //              0.000, -3884944.250, 0.000, -2270131.500, 0.000, -5260237.000,
  //              0.000, 3583352.250, 0.000, -9360989.000
  VCMP_U32(28, v4, 0x0, 0xcaedea56, 0x0, 0x49802396, 0x0, 0xcb053c5b, 0x0,
           0xca6d1e41, 0x0, 0xca0a8ece, 0x0, 0xcaa0879a, 0x0, 0x4a5ab5e1, 0x0,
           0xcb0ed65d);
};

////////////////////
// vfncvt.rod.f.f //
////////////////////

// Simple random test with similar values
void TEST_CASE15(void) {
  VSET(16, e16, m1);
  //                     908.994, -6788.630, -5789.335, 8054.104, 3947.551,
  //                     9596.856, 2474.506, 3094.286, 7684.992, -6850.149,
  //                     -54.922, 7737.443, 4171.873, 5266.611, 9163.839,
  //                     5679.187
  VLOAD_32(v2, 0x44633fa3, 0xc5d4250b, 0xc5b4eaaf, 0x45fbb0d4, 0x4576b8d0,
           0x4615f36d, 0x451aa818, 0x45416494, 0x45f027ef, 0xc5d61131,
           0xc25bb026, 0x45f1cb8c, 0x45825efb, 0x45a494e4, 0x460f2f5b,
           0x45b1797f);
  asm volatile("vfncvt.rod.f.f.w v4, v2");
  //                  909.000, -6788.000, -5788.000, 8056.000, 3948.000,
  //                  9600.000, 2474.000, 3094.000, 7684.000, -6852.000,
  //                  -54.938, 7736.000, 4172.000, 5268.000, 9160.000, 5680.000
  VCMP_U16(29, v4, 0x6319, 0xeea1, 0xeda7, 0x6fdd, 0x6bb5, 0x70af, 0x68d5,
           0x6a0b, 0x6f81, 0xeeb1, 0xd2dd, 0x6f8f, 0x6c13, 0x6d25, 0x7079,
           0x6d8b);

  VSET(16, e32, m1);
  //                       153431.9687, 153431.984375, -6652812.196,
  //                       1049714.758, 7538298.328, -8731739.480, 537176.622,
  //                       -3884944.157, 7612336.042, -2270131.404,
  //                       -4976406.726, -5260237.163, -4947737.810,
  //                       3583352.355, 7648790.331, -9360989.228
  VLOAD_64(v2, 0x4102babfc0000000, 0x4102babfe0000000, 0xc15960e30c871450,
           0x41300472c1efbd9f, 0x415cc19e94ffb79b, 0xc160a78b6f5bcd25,
           0x412064b13e931aa9, 0xc14da3c81425b914, 0x415d09ec02a8cc93,
           0xc14151d9b3c1ecaf, 0xc152fbc5ae718384, 0xc15410f34a6ddb48,
           0xc152dfc673d9ba53, 0x414b56bc2d765fad, 0x415d2d85952e8398,
           0xc161dacba74d791e);
  asm volatile("vfncvt.rod.f.f.w v4, v2");
  //                       153431.9687, 153431.984375,    -6652812.500,
  //                       1049714.875,    7538298.500,   -8731739.000,
  //                       537176.5625,   -3884944.250,    7612336.500,
  //                       -2270131.250, -4976406.500,     -5260237.500,
  //                       -4947737.500,    3583352.250,    7648790.500,
  //                       -9360989.000
  VCMP_U32(30, v4, 0x4815d5fe, 0x4815d5ff, 0xcacb0719, 0x49802397, 0x4ae60cf5,
           0xcb053c5b, 0x49032589, 0xca6d1e41, 0x4ae84f61, 0xca0a8ecd,
           0xca97de2d, 0xcaa0879b, 0xca96fe33, 0x4a5ab5e1, 0x4ae96c2d,
           0xcb0ed65d);
};

// Simple random test with similar values (masked)
// The numbers are the same of TEST_CASE1
void TEST_CASE16(void) {
  VSET(16, e16, m1);
  //              908.994, -6788.630, -5789.335, 8054.104, 3947.551, 9596.856,
  //              2474.506, 3094.286, 7684.992, -6850.149, -54.922, 7737.443,
  //              4171.873, 5266.611, 9163.839, 5679.187
  VLOAD_32(v2, 0x44633fa3, 0xc5d4250b, 0xc5b4eaaf, 0x45fbb0d4, 0x4576b8d0,
           0x4615f36d, 0x451aa818, 0x45416494, 0x45f027ef, 0xc5d61131,
           0xc25bb026, 0x45f1cb8c, 0x45825efb, 0x45a494e4, 0x460f2f5b,
           0x45b1797f);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.rod.f.f.w v4, v2, v0.t");
  //              0.000, -6788.000, 0.000, 8056.000, 0.000, 9600.000, 0.000,
  //              3094.000, 0.000, -6852.000, 0.000, 7736.000, 0.000, 5268.000,
  //              0.000, 5680.000
  VCMP_U16(31, v4, 0x0, 0xeea1, 0x0, 0x6fdd, 0x0, 0x70af, 0x0, 0x6a0b, 0x0,
           0xeeb1, 0x0, 0x6f8f, 0x0, 0x6d25, 0x0, 0x6d8b);

  VSET(16, e32, m1);
  //              153431.766, -7796010.957, -6652812.196, 1049714.758,
  //              7538298.328, -8731739.480, 537176.622, -3884944.157,
  //              7612336.042, -2270131.404, -4976406.726, -5260237.163,
  //              -4947737.810, 3583352.355, 7648790.331, -9360989.228
  VLOAD_64(v2, 0x4102babe20435c2f, 0xc15dbd4abd4015a9, 0xc15960e30c871450,
           0x41300472c1efbd9f, 0x415cc19e94ffb79b, 0xc160a78b6f5bcd25,
           0x412064b13e931aa9, 0xc14da3c81425b914, 0x415d09ec02a8cc93,
           0xc14151d9b3c1ecaf, 0xc152fbc5ae718384, 0xc15410f34a6ddb48,
           0xc152dfc673d9ba53, 0x414b56bc2d765fad, 0x415d2d85952e8398,
           0xc161dacba74d791e);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v4);
  asm volatile("vfncvt.rod.f.f.w v4, v2, v0.t");
  //              0.000, -7796011.000, 0.000, 1049714.750, 0.000, -8731739.000,
  //              0.000, -3884944.250, 0.000, -2270131.500, 0.000, -5260237.000,
  //              0.000, 3583352.250, 0.000, -9360989.000
  VCMP_U32(32, v4, 0x0, 0xcaedea55, 0x0, 0x49802397, 0x0, 0xcb053c5b, 0x0,
           0xca6d1e41, 0x0, 0xca0a8ecd, 0x0, 0xcaa0879b, 0x0, 0x4a5ab5e1, 0x0,
           0xcb0ed65d);
};

int main(void) {
  enable_vec();
  enable_fp();

  TEST_CASE1();
  TEST_CASE2();

  TEST_CASE3();
  TEST_CASE4();

  TEST_CASE5();
  TEST_CASE6();

  TEST_CASE7();
  TEST_CASE8();

  TEST_CASE9();
  TEST_CASE10();

  TEST_CASE11();
  TEST_CASE12();

  TEST_CASE13();
  TEST_CASE14();

  TEST_CASE15();
  TEST_CASE16();

  EXIT_CHECK();
}
