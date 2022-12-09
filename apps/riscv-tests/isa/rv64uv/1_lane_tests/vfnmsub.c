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
  //              -0.0091, -0.3794, -0.0005, -0.0464,  0.4834,  0.2932, -0.3042,
  //              -0.3096, -0.9844, -0.1815, -0.8760,  0.0853, -0.3723, -0.8877,
  //              0.1584,  0.1943
  VLOAD_16(v4, 0xa0ac, 0xb612, 0x8f83, 0xa9f0, 0x37bc, 0x34b1, 0xb4de, 0xb4f4,
           0xbbe0, 0xb1cf, 0xbb02, 0x2d75, 0xb5f5, 0xbb1a, 0x3112, 0x3238);
  //              -0.3301,  0.7769,  0.6572, -0.8193,  0.4529,  0.2349,  0.5264,
  //              -0.2456,  0.0873,  0.5381,  0.4670,  0.8564, -0.1790,  0.6641,
  //              0.0182,  0.0447
  VLOAD_16(v6, 0xb548, 0x3a37, 0x3942, 0xba8e, 0x373f, 0x3384, 0x3836, 0xb3dc,
           0x2d97, 0x384e, 0x3779, 0x3ada, 0xb1ba, 0x3950, 0x24a7, 0x29b9);
  //               0.5835,  0.4404, -0.3459,  0.0516, -0.4866, -0.2191,  0.0685,
  //               -0.5430, -0.1429, -0.7539, -0.6416, -0.6758, -0.1147, 0.3438,
  //               0.3440,  0.1991
  VLOAD_16(v2, 0x38ab, 0x370c, 0xb589, 0x2a9b, 0xb7c9, 0xb303, 0x2c62, 0xb858,
           0xb093, 0xba08, 0xb922, 0xb968, 0xaf57, 0x3580, 0x3581, 0x325f);
  asm volatile("vfnmsub.vv v2, v4, v6");
  //              -0.3247,  0.9438,  0.6572, -0.8169,  0.6880,  0.2991,  0.5474,
  //              -0.4136, -0.0534,  0.4014, -0.0950,  0.9141, -0.2217,  0.9692,
  //              -0.0363,  0.0060
  VCMP_U16(1, v2, 0xb532, 0x3b8d, 0x3942, 0xba89, 0x3981, 0x34c9, 0x3861,
           0xb69e, 0xaad5, 0x366b, 0xae14, 0x3b50, 0xb318, 0x3bc1, 0xa8a7,
           0x1e29);

  VSET(16, e32, m4);
  //               0.76259303, -0.43966120, -0.19390504, -0.57240725,
  //               -0.57148474, -0.93710214,  0.24273214,  0.44242114,
  //               -0.93160200, -0.56412256, -0.75430351, -0.02741535,
  //               -0.60542876, -0.93627954,  0.02798123,  0.23119579
  VLOAD_32(v8, 0x3f43394c, 0xbee11b46, 0xbe468f0b, 0xbf128948, 0xbf124cd3,
           0xbf6fe5ed, 0x3e788ec6, 0x3ee28506, 0xbf6e7d78, 0xbf106a56,
           0xbf411a09, 0xbce09629, 0xbf1afd61, 0xbf6fb004, 0x3ce538e6,
           0x3e6cbe97);
  //               0.48736989,  0.19715627, -0.47227743,  0.13752034,
  //               -0.16710435,  0.84761631,  0.37147006,  0.25389814,
  //               -0.44707820,  0.38169226, -0.82191414, -0.81056035,
  //               0.29047397, -0.46743703, -0.91869444, -0.08079135
  VLOAD_32(v12, 0x3ef9888c, 0x3e49e355, 0xbef1ce59, 0x3e0cd222, 0xbe2b1d67,
           0x3f58fd62, 0x3ebe3153, 0x3e81fef0, 0xbee4e76f, 0x3ec36d2b,
           0xbf5268f7, 0xbf4f80e2, 0x3e94b901, 0xbeef53e8, 0xbf6b2f8f,
           0xbda575f0);
  //              -0.48655373, -0.87417608,  0.17854533,  0.67417324,
  //              0.46947387,  0.29113689, -0.11920074,  0.63394654,
  //              -0.82611400, -0.84088647, -0.13328743,  0.29885510,
  //              0.91797447, -0.15480036,  0.76857966,  0.16230854
  VLOAD_32(v4, 0xbef91d92, 0xbf5fca01, 0x3e36d496, 0x3f2c969e, 0x3ef05ee1,
           0x3e950fe5, 0xbdf41f84, 0x3f224a52, 0xbf537c35, 0xbf574456,
           0xbe087c80, 0x3e990389, 0x3f6b0060, 0xbe1e83fc, 0x3f44c1a3,
           0x3e263436);
  asm volatile("vfnmsub.vv v4, v8, v12");
  //               0.85841238, -0.18718503, -0.43765658,  0.52342200,
  //               0.10119282,  1.12044132,  0.40040392, -0.02657321,
  //               -1.21668768, -0.09267077, -0.92245328, -0.80236715,
  //               0.84624207, -0.61237341, -0.94020027, -0.11831641
  VCMP_U32(2, v4, 0x3f5bc0ea, 0xbe3fad70, 0xbee01486, 0x3f05fefc, 0x3dcf3e2c,
           0x3f8f6a9f, 0x3ecd01be, 0xbcd9b00d, 0xbf9bbc6c, 0xbdbdca2c,
           0xbf6c25e6, 0xbf4d67ef, 0x3f58a353, 0xbf1cc481, 0xbf70b0f7,
           0xbdf24fdf);

  VSET(16, e64, m8);
  //              -0.1307639483617093,  0.9224167823566942,  0.8635785104096312,
  //              -0.1786758246437388,  0.0810514505300033,  0.4196384170211611,
  //              0.9100790646565715, -0.5457616411379209, -0.5513001815564993,
  //              -0.4320693373833464,  0.2818536966914695,  0.5493933224246561,
  //              0.0505621823765807,  0.7247332126666939, -0.8702311369694951,
  //              -0.0660417836134264
  VLOAD_64(v16, 0xbfc0bcdf80daccc8, 0x3fed847033301d18, 0x3feba26f66779bbe,
           0xbfc6ded973b720d0, 0x3fb4bfc9b151d990, 0x3fdadb5b175011f8,
           0x3fed1f5e216f2d02, 0xbfe176e11e032836, 0xbfe1a44047420c82,
           0xbfdba706266a9d80, 0x3fd209e41662faec, 0x3fe194a14e0e8cc0,
           0x3fa9e3494f719000, 0x3fe73103b4d74f92, 0xbfebd8eef827d60a,
           0xbfb0e81d44ca0760);
  //               0.6650460871127466, -0.8389896062690501,  0.3260860096573337,
  //               0.4421797679090849, -0.1921872051427089, -0.1798768047606598,
  //               -0.5065656464186716,  0.8248933299429206,
  //               -0.3169052211432897, -0.0970247500649024, 0.8584276150948376,
  //               -0.2642287948226270,  0.2403355182026823,
  //               -0.0814065713760876, -0.7437013715700231, -0.6226210619792329
  VLOAD_64(v24, 0x3fe5480ebb4f6ca8, 0xbfead900bb1380ea, 0x3fd4de97daca5430,
           0x3fdc4cac5e87d53c, 0xbfc8999720661708, 0xbfc7063400e0c4f8,
           0xbfe035c92894a640, 0x3fea6586b2596362, 0xbfd4482cd62f7e30,
           0xbfb8d69d306e6ba0, 0x3feb783d309a196c, 0xbfd0e91fe41b2de8,
           0x3fcec350735fb5b8, 0xbfb4d70fa1bd62a0, 0xbfe7cc66d19c4666,
           0xbfe3ec8301600d10);
  //              -0.2122847293404504,  0.9074328134093839, -0.4150374170703475,
  //              -0.4511563805942409, -0.9126942371441604, -0.8237861842027401,
  //              -0.0636244117792013,  0.7124530373845765, -0.4126670585839094,
  //              -0.2810978842877421, -0.3240264495739638,  0.5540367578795606,
  //              0.7398533272929233,  0.4690189457399407, -0.2427822500985419,
  //              0.2399358773396087
  VLOAD_64(v8, 0xbfcb2c2560fa8d98, 0x3fed09b08a1d236c, 0xbfda8ff9193bbdb8,
           0xbfdcdfbf03022cf4, 0xbfed34ca8b7904d0, 0xbfea5c74d801844e,
           0xbfb049b07fd1a3e0, 0x3fe6cc6a4ff0157a, 0xbfda692318304834,
           0xbfd1fd81faff66b8, 0xbfd4bcd96efd6300, 0x3fe1baab4b7bfc96,
           0x3fe7ace0e291ea9e, 0x3fde04680a4a1390, 0xbfcf137d201c7be0,
           0x3fceb6380527c498);
  asm volatile("vfnmsub.vv v8, v16, v24");
  //               0.6372868977272925, -1.6760208622190165,  0.6845034040552052,
  //               0.3615690295631244, -0.1182120133317999,  0.1658155255420807,
  //               -0.4486624012573315,  1.2137228688596235,
  //               -0.5444086454629855, -0.2184785266689677, 0.9497556677330713,
  //               -0.5686128899794636,  0.2029269193361774,
  //               -0.4213201787237407, -0.9549780451092895, -0.6067752686868729
  VCMP_U64(3, v8, 0x3fe464a77dfd0e7c, 0xbffad0fb406a4f74, 0x3fe5e773aecd5e74,
           0x3fd723f26d4e15bc, 0xbfbe43247b412024, 0x3fc5397171afa72c,
           0xbfdcb6e281161599, 0x3ff36b68abc28cd2, 0xbfe16bcbadfd8ab4,
           0xbfcbf71ab775f310, 0x3fee6465ff835579, 0xbfe23213a8d1778a,
           0x3fc9f982610371db, 0xbfdaf6e8e930da95, 0xbfee8f2e1e048ea3,
           0xbfe36ab3f7e103f3);
};

// Simple random test with similar values (masked)
// The numbers are the same of TEST_CASE1
void TEST_CASE2(void) {
  VSET(16, e16, m2);
  //              -0.0091, -0.3794, -0.0005, -0.0464,  0.4834,  0.2932, -0.3042,
  //              -0.3096, -0.9844, -0.1815, -0.8760,  0.0853, -0.3723, -0.8877,
  //              0.1584,  0.1943
  VLOAD_16(v4, 0xa0ac, 0xb612, 0x8f83, 0xa9f0, 0x37bc, 0x34b1, 0xb4de, 0xb4f4,
           0xbbe0, 0xb1cf, 0xbb02, 0x2d75, 0xb5f5, 0xbb1a, 0x3112, 0x3238);
  //              -0.3301,  0.7769,  0.6572, -0.8193,  0.4529,  0.2349,  0.5264,
  //              -0.2456,  0.0873,  0.5381,  0.4670,  0.8564, -0.1790,  0.6641,
  //              0.0182,  0.0447
  VLOAD_16(v6, 0xb548, 0x3a37, 0x3942, 0xba8e, 0x373f, 0x3384, 0x3836, 0xb3dc,
           0x2d97, 0x384e, 0x3779, 0x3ada, 0xb1ba, 0x3950, 0x24a7, 0x29b9);
  VLOAD_8(v0, 0xAA, 0xAA);
  //               0.5835,  0.4404, -0.3459,  0.0516, -0.4866, -0.2191,  0.0685,
  //               -0.5430, -0.1429, -0.7539, -0.6416, -0.6758, -0.1147, 0.3438,
  //               0.3440,  0.1991
  VLOAD_16(v2, 0x38ab, 0x370c, 0xb589, 0x2a9b, 0xb7c9, 0xb303, 0x2c62, 0xb858,
           0xb093, 0xba08, 0xb922, 0xb968, 0xaf57, 0x3580, 0x3581, 0x325f);
  asm volatile("vfnmsub.vv v2, v4, v6, v0.t");
  //               0.5835,  0.9438, -0.3459, -0.8169, -0.4866,  0.2991,  0.0685,
  //               -0.4136, -0.1429,  0.4014, -0.6416,  0.9141, -0.1147, 0.9692,
  //               0.3440,  0.0060
  VCMP_U16(4, v2, 0x38ab, 0x3b8d, 0xb589, 0xba89, 0xb7c9, 0x34c9, 0x2c62,
           0xb69e, 0xb093, 0x366b, 0xb922, 0x3b50, 0xaf57, 0x3bc1, 0x3581,
           0x1e29);

  VSET(16, e32, m4);
  //               0.76259303, -0.43966120, -0.19390504, -0.57240725,
  //               -0.57148474, -0.93710214,  0.24273214,  0.44242114,
  //               -0.93160200, -0.56412256, -0.75430351, -0.02741535,
  //               -0.60542876, -0.93627954,  0.02798123,  0.23119579
  VLOAD_32(v8, 0x3f43394c, 0xbee11b46, 0xbe468f0b, 0xbf128948, 0xbf124cd3,
           0xbf6fe5ed, 0x3e788ec6, 0x3ee28506, 0xbf6e7d78, 0xbf106a56,
           0xbf411a09, 0xbce09629, 0xbf1afd61, 0xbf6fb004, 0x3ce538e6,
           0x3e6cbe97);
  //               0.48736989,  0.19715627, -0.47227743,  0.13752034,
  //               -0.16710435,  0.84761631,  0.37147006,  0.25389814,
  //               -0.44707820,  0.38169226, -0.82191414, -0.81056035,
  //               0.29047397, -0.46743703, -0.91869444, -0.08079135
  VLOAD_32(v12, 0x3ef9888c, 0x3e49e355, 0xbef1ce59, 0x3e0cd222, 0xbe2b1d67,
           0x3f58fd62, 0x3ebe3153, 0x3e81fef0, 0xbee4e76f, 0x3ec36d2b,
           0xbf5268f7, 0xbf4f80e2, 0x3e94b901, 0xbeef53e8, 0xbf6b2f8f,
           0xbda575f0);
  VLOAD_8(v0, 0xAA, 0xAA);
  //              -0.48655373, -0.87417608,  0.17854533,  0.67417324,
  //              0.46947387,  0.29113689, -0.11920074,  0.63394654,
  //              -0.82611400, -0.84088647, -0.13328743,  0.29885510,
  //              0.91797447, -0.15480036,  0.76857966,  0.16230854
  VLOAD_32(v4, 0xbef91d92, 0xbf5fca01, 0x3e36d496, 0x3f2c969e, 0x3ef05ee1,
           0x3e950fe5, 0xbdf41f84, 0x3f224a52, 0xbf537c35, 0xbf574456,
           0xbe087c80, 0x3e990389, 0x3f6b0060, 0xbe1e83fc, 0x3f44c1a3,
           0x3e263436);
  asm volatile("vfnmsub.vv v4, v8, v12, v0.t");
  //              -0.48655373, -0.18718503,  0.17854533,  0.52342200,
  //              0.46947387,  1.12044132, -0.11920074, -0.02657321,
  //              -0.82611400, -0.09267077, -0.13328743, -0.80236715,
  //              0.91797447, -0.61237341,  0.76857966, -0.11831641
  VCMP_U32(5, v4, 0xbef91d92, 0xbe3fad70, 0x3e36d496, 0x3f05fefc, 0x3ef05ee1,
           0x3f8f6a9f, 0xbdf41f84, 0xbcd9b00d, 0xbf537c35, 0xbdbdca2c,
           0xbe087c80, 0xbf4d67ef, 0x3f6b0060, 0xbf1cc481, 0x3f44c1a3,
           0xbdf24fdf);

  VSET(16, e64, m8);
  //              -0.1307639483617093,  0.9224167823566942,  0.8635785104096312,
  //              -0.1786758246437388,  0.0810514505300033,  0.4196384170211611,
  //              0.9100790646565715, -0.5457616411379209, -0.5513001815564993,
  //              -0.4320693373833464,  0.2818536966914695,  0.5493933224246561,
  //              0.0505621823765807,  0.7247332126666939, -0.8702311369694951,
  //              -0.0660417836134264
  VLOAD_64(v16, 0xbfc0bcdf80daccc8, 0x3fed847033301d18, 0x3feba26f66779bbe,
           0xbfc6ded973b720d0, 0x3fb4bfc9b151d990, 0x3fdadb5b175011f8,
           0x3fed1f5e216f2d02, 0xbfe176e11e032836, 0xbfe1a44047420c82,
           0xbfdba706266a9d80, 0x3fd209e41662faec, 0x3fe194a14e0e8cc0,
           0x3fa9e3494f719000, 0x3fe73103b4d74f92, 0xbfebd8eef827d60a,
           0xbfb0e81d44ca0760);
  //               0.6650460871127466, -0.8389896062690501,  0.3260860096573337,
  //               0.4421797679090849, -0.1921872051427089, -0.1798768047606598,
  //               -0.5065656464186716,  0.8248933299429206,
  //               -0.3169052211432897, -0.0970247500649024, 0.8584276150948376,
  //               -0.2642287948226270,  0.2403355182026823,
  //               -0.0814065713760876, -0.7437013715700231, -0.6226210619792329
  VLOAD_64(v24, 0x3fe5480ebb4f6ca8, 0xbfead900bb1380ea, 0x3fd4de97daca5430,
           0x3fdc4cac5e87d53c, 0xbfc8999720661708, 0xbfc7063400e0c4f8,
           0xbfe035c92894a640, 0x3fea6586b2596362, 0xbfd4482cd62f7e30,
           0xbfb8d69d306e6ba0, 0x3feb783d309a196c, 0xbfd0e91fe41b2de8,
           0x3fcec350735fb5b8, 0xbfb4d70fa1bd62a0, 0xbfe7cc66d19c4666,
           0xbfe3ec8301600d10);
  VLOAD_8(v0, 0xAA, 0xAA);
  //              -0.2122847293404504,  0.9074328134093839, -0.4150374170703475,
  //              -0.4511563805942409, -0.9126942371441604, -0.8237861842027401,
  //              -0.0636244117792013,  0.7124530373845765, -0.4126670585839094,
  //              -0.2810978842877421, -0.3240264495739638,  0.5540367578795606,
  //              0.7398533272929233,  0.4690189457399407, -0.2427822500985419,
  //              0.2399358773396087
  VLOAD_64(v8, 0xbfcb2c2560fa8d98, 0x3fed09b08a1d236c, 0xbfda8ff9193bbdb8,
           0xbfdcdfbf03022cf4, 0xbfed34ca8b7904d0, 0xbfea5c74d801844e,
           0xbfb049b07fd1a3e0, 0x3fe6cc6a4ff0157a, 0xbfda692318304834,
           0xbfd1fd81faff66b8, 0xbfd4bcd96efd6300, 0x3fe1baab4b7bfc96,
           0x3fe7ace0e291ea9e, 0x3fde04680a4a1390, 0xbfcf137d201c7be0,
           0x3fceb6380527c498);
  asm volatile("vfnmsub.vv v8, v16, v24, v0.t");
  //              -0.2122847293404504, -1.6760208622190165, -0.4150374170703475,
  //              0.3615690295631244, -0.9126942371441604,  0.1658155255420807,
  //              -0.0636244117792013,  1.2137228688596235, -0.4126670585839094,
  //              -0.2184785266689677, -0.3240264495739638, -0.5686128899794636,
  //              0.7398533272929233, -0.4213201787237407, -0.2427822500985419,
  //              -0.6067752686868729
  VCMP_U64(6, v8, 0xbfcb2c2560fa8d98, 0xbffad0fb406a4f74, 0xbfda8ff9193bbdb8,
           0x3fd723f26d4e15bc, 0xbfed34ca8b7904d0, 0x3fc5397171afa72c,
           0xbfb049b07fd1a3e0, 0x3ff36b68abc28cd2, 0xbfda692318304834,
           0xbfcbf71ab775f310, 0xbfd4bcd96efd6300, 0xbfe23213a8d1778a,
           0x3fe7ace0e291ea9e, 0xbfdaf6e8e930da95, 0xbfcf137d201c7be0,
           0xbfe36ab3f7e103f3);
};

// Simple random test with similar values (vector-scalar)
void TEST_CASE3(void) {
  VSET(16, e16, m2);
  double dscalar_16;
  //                             -0.1346
  BOX_HALF_IN_DOUBLE(dscalar_16, 0xb04f);
  //              -0.1886,  0.9912, -0.0325,  0.5850,  0.2578, -0.2350, -0.8701,
  //              0.9209,  0.5859, -0.4795,  0.8682,  0.9233, -0.8896, -0.5981,
  //              -0.3223,  0.6924
  VLOAD_16(v4, 0xb209, 0x3bee, 0xa82a, 0x38ae, 0x3420, 0xb385, 0xbaf6, 0x3b5e,
           0x38b0, 0xb7ac, 0x3af2, 0x3b63, 0xbb1e, 0xb8c9, 0xb528, 0x398a);
  //              -0.0126,  0.9678,  0.8945, -0.9600, -0.9272,  0.4412,  0.5527,
  //              0.1136,  0.7207, -0.5181, -0.2810, -0.4048,  0.1648,  0.7612,
  //              -0.8853,  0.1761
  VLOAD_16(v2, 0xa27a, 0x3bbe, 0x3b28, 0xbbae, 0xbb6b, 0x370f, 0x386c, 0x2f45,
           0x39c4, 0xb825, 0xb47f, 0xb67a, 0x3146, 0x3a17, 0xbb15, 0x31a3);
  asm volatile("vfnmsub.vf v2, %[A], v4" ::[A] "f"(dscalar_16));
  //              -0.1903,  1.1211,  0.0879,  0.4556,  0.1329, -0.1755, -0.7959,
  //              0.9360,  0.6831, -0.5493,  0.8301,  0.8687, -0.8677, -0.4956,
  //              -0.4414,  0.7163
  VCMP_U16(7, v2, 0xb217, 0x3c7c, 0x2da0, 0x374b, 0x3041, 0xb19e, 0xba5e,
           0x3b7d, 0x3977, 0xb865, 0x3aa5, 0x3af3, 0xbaf1, 0xb7ee, 0xb710,
           0x39bb);

  VSET(16, e32, m4);
  double dscalar_32;
  //                              -0.16110219
  BOX_FLOAT_IN_DOUBLE(dscalar_32, 0xbe24f7f9);
  //              -0.31537205, -0.17563045, -0.79069936,  0.22939304,
  //              -0.89379781,  0.26157290,  0.56702632, -0.11594663,
  //              0.09605245,  0.45930776, -0.76518077, -0.26341528, 0.74385208,
  //              0.89362013, -0.21185355,  0.23924881
  VLOAD_32(v8, 0xbea17872, 0xbe33d878, 0xbf4a6b46, 0x3e6ae602, 0xbf64cfef,
           0x3e85ece2, 0x3f1128a3, 0xbded756d, 0x3dc4b726, 0x3eeb2a63,
           0xbf43e2e3, 0xbe86de5e, 0x3f3e6d17, 0x3f64c44a, 0xbe58f023,
           0x3e74fda4);
  //               0.31856158,  0.48641542,  0.57264513,  0.30210373,
  //               -0.19719712,  0.85649359,  0.36901370, -0.78377151,
  //               0.22567192, -0.75179213, -0.65690833,  0.11298654,
  //               -0.64884853, -0.48376039, -0.11539485, -0.42667609
  VLOAD_32(v4, 0x3ea31a81, 0x3ef90b71, 0x3f1298df, 0x3e9aad57, 0xbe49ee0b,
           0x3f5b432a, 0x3ebcef5d, 0xbf48a540, 0x3e67168a, 0xbf407573,
           0xbf282b25, 0x3de7657d, 0xbf261af0, 0xbef7af71, 0xbdec5422,
           0xbeda754a);
  asm volatile("vfnmsub.vf v4, %[A], v8" ::[A] "f"(dscalar_32));
  //              -0.26405108, -0.09726786, -0.69844496,  0.27806261,
  //              -0.92556667,  0.39955589,  0.62647521, -0.24221393,
  //              0.13240869,  0.33819240, -0.87101012, -0.24521290, 0.63932115,
  //              0.81568527, -0.23044391,  0.17051035
  VCMP_U32(8, v4, 0xbe8731b4, 0xbdc7345f, 0xbf32cd4a, 0x3e8e5e39, 0xbf6cf1f1,
           0x3ecc9297, 0x3f2060ae, 0xbe7806ee, 0x3e079625, 0x3ead278e,
           0xbf5efa85, 0xbe7b1917, 0x3f23aa8d, 0x3f50d0c0, 0xbe6bf97d,
           0x3e2e9a44);

  VSET(16, e64, m8);
  double dscalar_64;
  //                                0.5849101968457469
  BOX_DOUBLE_IN_DOUBLE(dscalar_64, 0x3fe2b79596d194ba);
  //               -0.7607808895269514, -0.0192591699518767, 0.6815284686654297,
  //               -0.5163928614577513, -0.9560613023939111,
  //               -0.8652684824342871,  0.4588682754059621,
  //               -0.5708244737077264, -0.7636024500128011, 0.2236424444447431,
  //               0.8245435877598175,  0.8527344486412596, -0.3097355632002228,
  //               0.0764086736442742,  0.2567358761671383,  0.1904958118727702
  VLOAD_64(v16, 0xbfe8585129fe14da, 0xbf93b8ad045d9c40, 0x3fe5cf14ca86c05c,
           0xbfe0864a527b2a32, 0xbfee980ddf5818b2, 0xbfebb047874a12f4,
           0x3fdd5e190b029804, 0xbfe24431afca9858, 0xbfe86f6e67be6a22,
           0x3fcca050cc719f20, 0x3fea62a93bf1c1ec, 0x3feb4999c122c714,
           0xbfd3d2b51c969928, 0x3fb38f84d26ed230, 0x3fd06e5c4ff641c8,
           0x3fc8622ab1025ec0);
  //                0.1182575129292827, -0.8756460666506833,
  //                -0.3686593299789440,  0.2802900907620893,
  //                -0.5167592439660142,  0.3872686605057347,
  //                -0.0640775227939985, -0.4352087179743556,
  //                -0.1509314378482451, -0.9803534868251271,
  //                0.9211862470421908,  0.7804942879773937, 0.5029472314120484,
  //                0.1158347026033590,  0.7422982722940397,  0.0792254120441500
  VLOAD_64(v8, 0x3fbe461fd6899df0, 0xbfec054ae66457d4, 0xbfd7981d4d67fd54,
           0x3fd1f045d94dd3b0, 0xbfe0894aae97abc2, 0x3fd8c9027de8d2a8,
           0xbfb0676270cf1540, 0xbfdbda75aaa8928c, 0xbfc351b8aabf8c50,
           0xbfef5f0e468ddf22, 0x3fed7a5b94924728, 0x3fe8f9cf28327c9e,
           0x3fe01824cad0e968, 0x3fbda757d36c5e40, 0x3fe7c0e84e6c2aa0,
           0x3fb4481dd9bde340);
  asm volatile("vfnmsub.vf v8, %[A], v16" ::[A] "f"(dscalar_64));
  //              -0.8299509146929066,  0.4929151432599784,  0.8971610699324351,
  //              -0.6803373936193172, -0.6538035512838903, -1.0917858708828851,
  //              0.4963478718767876, -0.3162664568083610, -0.6753211129907725,
  //              0.7970611954020426,  0.2857323586707750,  0.3962153810234212,
  //              -0.6039145273284674,  0.0086557749429749, -0.1774419523986262,
  //              0.1441560605188410
  VCMP_U64(9, v8, 0xbfea8ef5387c85b1, 0x3fdf8bebf5004e06, 0x3fecb58b21d3556c,
           0xbfe5c552ecfae837, 0xbfe4ebf56cd8bc27, 0xbff177f4761ad476,
           0x3fdfc429dd49999d, 0xbfd43db5aa3413c6, 0xbfe59c3b05d2ff7f,
           0x3fe981867ae532b2, 0x3fd249705ff9984b, 0x3fd95b97c1eabccb,
           0xbfe353448f0e8fe6, 0x3f81ba1e7269b44b, 0xbfc6b66afb3ec852,
           0x3fc273b4aeb96c59);
};

// Simple random test with similar values (vector-scalar) (masked)
void TEST_CASE4(void) {
  VSET(16, e16, m2);
  double dscalar_16;
  //                             -0.1346
  BOX_HALF_IN_DOUBLE(dscalar_16, 0xb04f);
  //               -0.1886,  0.9912, -0.0325,  0.5850,  0.2578, -0.2350,
  //               -0.8701,  0.9209,  0.5859, -0.4795,  0.8682,  0.9233,
  //               -0.8896, -0.5981, -0.3223,  0.6924
  VLOAD_16(v4, 0xb209, 0x3bee, 0xa82a, 0x38ae, 0x3420, 0xb385, 0xbaf6, 0x3b5e,
           0x38b0, 0xb7ac, 0x3af2, 0x3b63, 0xbb1e, 0xb8c9, 0xb528, 0x398a);
  VLOAD_8(v0, 0xAA, 0xAA);
  //               -0.0126,  0.9678,  0.8945, -0.9600, -0.9272,  0.4412, 0.5527,
  //               0.1136,  0.7207, -0.5181, -0.2810, -0.4048,  0.1648,  0.7612,
  //               -0.8853,  0.1761
  VLOAD_16(v2, 0xa27a, 0x3bbe, 0x3b28, 0xbbae, 0xbb6b, 0x370f, 0x386c, 0x2f45,
           0x39c4, 0xb825, 0xb47f, 0xb67a, 0x3146, 0x3a17, 0xbb15, 0x31a3);
  asm volatile("vfnmsub.vf v2, %[A], v4, v0.t" ::[A] "f"(dscalar_16));
  //               -0.0126,  1.1211,  0.8945,  0.4556, -0.9272, -0.1755, 0.5527,
  //               0.9360,  0.7207, -0.5493, -0.2810,  0.8687,  0.1648, -0.4956,
  //               -0.8853,  0.7163
  VCMP_U16(10, v2, 0xa27a, 0x3c7c, 0x3b28, 0x374b, 0xbb6b, 0xb19e, 0x386c,
           0x3b7d, 0x39c4, 0xb865, 0xb47f, 0x3af3, 0x3146, 0xb7ee, 0xbb15,
           0x39bb);

  VSET(16, e32, m4);
  double dscalar_32;
  //                              -0.16110219
  BOX_FLOAT_IN_DOUBLE(dscalar_32, 0xbe24f7f9);
  //               -0.31537205, -0.17563045, -0.79069936,  0.22939304,
  //               -0.89379781,  0.26157290,  0.56702632, -0.11594663,
  //               0.09605245,  0.45930776, -0.76518077, -0.26341528,
  //               0.74385208,  0.89362013, -0.21185355,  0.23924881
  VLOAD_32(v8, 0xbea17872, 0xbe33d878, 0xbf4a6b46, 0x3e6ae602, 0xbf64cfef,
           0x3e85ece2, 0x3f1128a3, 0xbded756d, 0x3dc4b726, 0x3eeb2a63,
           0xbf43e2e3, 0xbe86de5e, 0x3f3e6d17, 0x3f64c44a, 0xbe58f023,
           0x3e74fda4);
  VLOAD_8(v0, 0xAA, 0xAA);
  //                0.31856158,  0.48641542,  0.57264513,  0.30210373,
  //                -0.19719712,  0.85649359,  0.36901370, -0.78377151,
  //                0.22567192, -0.75179213, -0.65690833,  0.11298654,
  //                -0.64884853, -0.48376039, -0.11539485, -0.42667609
  VLOAD_32(v4, 0x3ea31a81, 0x3ef90b71, 0x3f1298df, 0x3e9aad57, 0xbe49ee0b,
           0x3f5b432a, 0x3ebcef5d, 0xbf48a540, 0x3e67168a, 0xbf407573,
           0xbf282b25, 0x3de7657d, 0xbf261af0, 0xbef7af71, 0xbdec5422,
           0xbeda754a);
  asm volatile("vfnmsub.vf v4, %[A], v8, v0.t" ::[A] "f"(dscalar_32));
  //                0.31856158, -0.09726786,  0.57264513,  0.27806261,
  //                -0.19719712,  0.39955589,  0.36901370, -0.24221393,
  //                0.22567192,  0.33819240, -0.65690833, -0.24521290,
  //                -0.64884853,  0.81568527, -0.11539485,  0.17051035
  VCMP_U32(11, v4, 0x3ea31a81, 0xbdc7345f, 0x3f1298df, 0x3e8e5e39, 0xbe49ee0b,
           0x3ecc9297, 0x3ebcef5d, 0xbe7806ee, 0x3e67168a, 0x3ead278e,
           0xbf282b25, 0xbe7b1917, 0xbf261af0, 0x3f50d0c0, 0xbdec5422,
           0x3e2e9a44);

  VSET(16, e64, m8);
  double dscalar_64;
  //                                0.5849101968457469
  BOX_DOUBLE_IN_DOUBLE(dscalar_64, 0x3fe2b79596d194ba);
  //                -0.7607808895269514, -0.0192591699518767,
  //                0.6815284686654297, -0.5163928614577513,
  //                -0.9560613023939111, -0.8652684824342871,
  //                0.4588682754059621, -0.5708244737077264,
  //                -0.7636024500128011,  0.2236424444447431,
  //                0.8245435877598175,  0.8527344486412596,
  //                -0.3097355632002228,  0.0764086736442742,
  //                0.2567358761671383,  0.1904958118727702
  VLOAD_64(v16, 0xbfe8585129fe14da, 0xbf93b8ad045d9c40, 0x3fe5cf14ca86c05c,
           0xbfe0864a527b2a32, 0xbfee980ddf5818b2, 0xbfebb047874a12f4,
           0x3fdd5e190b029804, 0xbfe24431afca9858, 0xbfe86f6e67be6a22,
           0x3fcca050cc719f20, 0x3fea62a93bf1c1ec, 0x3feb4999c122c714,
           0xbfd3d2b51c969928, 0x3fb38f84d26ed230, 0x3fd06e5c4ff641c8,
           0x3fc8622ab1025ec0);
  VLOAD_8(v0, 0xAA, 0xAA);
  //                 0.1182575129292827, -0.8756460666506833,
  //                 -0.3686593299789440,  0.2802900907620893,
  //                 -0.5167592439660142,  0.3872686605057347,
  //                 -0.0640775227939985, -0.4352087179743556,
  //                 -0.1509314378482451, -0.9803534868251271,
  //                 0.9211862470421908,  0.7804942879773937,
  //                 0.5029472314120484,  0.1158347026033590,
  //                 0.7422982722940397,  0.0792254120441500
  VLOAD_64(v8, 0x3fbe461fd6899df0, 0xbfec054ae66457d4, 0xbfd7981d4d67fd54,
           0x3fd1f045d94dd3b0, 0xbfe0894aae97abc2, 0x3fd8c9027de8d2a8,
           0xbfb0676270cf1540, 0xbfdbda75aaa8928c, 0xbfc351b8aabf8c50,
           0xbfef5f0e468ddf22, 0x3fed7a5b94924728, 0x3fe8f9cf28327c9e,
           0x3fe01824cad0e968, 0x3fbda757d36c5e40, 0x3fe7c0e84e6c2aa0,
           0x3fb4481dd9bde340);
  asm volatile("vfnmsub.vf v8, %[A], v16, v0.t" ::[A] "f"(dscalar_64));
  //                0.1182575129292827,  0.4929151432599784,
  //                -0.3686593299789440, -0.6803373936193172,
  //                -0.5167592439660142, -1.0917858708828851,
  //                -0.0640775227939985, -0.3162664568083610,
  //                -0.1509314378482451,  0.7970611954020426,
  //                0.9211862470421908,  0.3962153810234212, 0.5029472314120484,
  //                0.0086557749429749,  0.7422982722940397,  0.1441560605188410
  VCMP_U64(12, v8, 0x3fbe461fd6899df0, 0x3fdf8bebf5004e06, 0xbfd7981d4d67fd54,
           0xbfe5c552ecfae837, 0xbfe0894aae97abc2, 0xbff177f4761ad476,
           0xbfb0676270cf1540, 0xbfd43db5aa3413c6, 0xbfc351b8aabf8c50,
           0x3fe981867ae532b2, 0x3fed7a5b94924728, 0x3fd95b97c1eabccb,
           0x3fe01824cad0e968, 0x3f81ba1e7269b44b, 0x3fe7c0e84e6c2aa0,
           0x3fc273b4aeb96c59);
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
