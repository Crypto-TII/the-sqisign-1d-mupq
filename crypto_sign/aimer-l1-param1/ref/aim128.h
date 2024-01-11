// -----------------------------------------------------------------------------
// File Name   : aim128.h
// Description : 
// SPDX-License-Identifier: MIT
// -----------------------------------------------------------------------------

#ifndef AIM128_H
#define AIM128_H

#include "field.h"

#define NUM_INPUT_SBOX      2   // number of input S-box
#define BLOCK_SIZE         16   // block size of AIM
#define TAPE_LEN         2144   // tape length of matrix generation

static const GF e2_power_matrix[128] = {
  {0x0000000000000001, 0x0000000000000000},
  {0x1f726995c3f33829, 0x24f6fc2353c7f232},
  {0xa5b7efc52c5e9c53, 0x150e344316f35f82},
  {0xf99fe339d5effd74, 0x4025648f69742910},
  {0x891738c79d5ad319, 0xcbe66ebbc72d228a},
  {0x400d2b9a8a1eebf3, 0x97a861e70c1e0535},
  {0x1c5cb72768169628, 0x254355a83054ee60},
  {0x3acffd143223de0b, 0xfb297abd4c26f7ef},
  {0xfbb824714f38f6c2, 0xd331a77342cf2867},
  {0x8f32fa46b511d1b5, 0xab75343cbf69e2f3},
  {0x69f4adf85cb0d695, 0x5dc8fd9b68e9e7af},
  {0x722cf12e8a12fc59, 0x61dd5a630843f596},
  {0x8f48fe4fc6b2694e, 0x15af63c3bac1f9d7},
  {0x38de74d4627d4ddd, 0x54e5dc988832b804},
  {0x5cb612427094923f, 0x0d1d6d189dae732f},
  {0xa5fa1f51e56b984f, 0xd64e9026e2bddd62},
  {0x62609e6968de22b0, 0x60dcdee4d2f1fc92},
  {0xa4017bb2d8fe841d, 0xeb853704353bc470},
  {0x35304c6dff367de3, 0xbf04e6f1c636a287},
  {0x652628401720e5eb, 0xd3247818cded1626},
  {0x5cbbc86cf7dcb202, 0xca5fc4fb46473111},
  {0xf8b538808c722c60, 0x64e3b2ebac0cca78},
  {0x618c73b47686591b, 0x79aa1a6f81d76acf},
  {0xeb938fa5e7f27850, 0x6594d77312abb969},
  {0x28e1f5a81e2f2dbf, 0xcf81e7613be6a2ed},
  {0xef7a9f574788d86e, 0xaea95c15d799b34e},
  {0xf5c68c6e6a915d19, 0xfa1bf58a0b8137f1},
  {0x16f90be4371af50e, 0xb20003ae0308bfb0},
  {0x7b14b6b6a89d327e, 0x3867eb294433b6e5},
  {0xe5cc3109ba095ac3, 0xc7d4a02f76e7d3ea},
  {0xfa2e665b5f7d6a16, 0x79750ec946570746},
  {0x98b6d4c7004afaa1, 0x156bb8e91a49f3e8},
  {0x21777af80695052a, 0x782d0a995dd3b018},
  {0xbf23539f9e13f6c2, 0x9beafa2e9d6b910a},
  {0xc2b5ed26f86aff00, 0xcb6ac8f484ae4d76},
  {0x1d115c59b248b207, 0x45ccf6353cd7d022},
  {0xef3b945bcb6c8f87, 0x753a0d5bb6173fff},
  {0x4e8bb91b694b0c44, 0x7d09de90a4d22fce},
  {0x98098137d97f5676, 0x2188106ece80b6e9},
  {0x66a8a28ec0e39c60, 0xc39b34ba0e398a3a},
  {0x2f712bb9de8393dc, 0x82849947e81b1c03},
  {0xdad49622ac5a8a45, 0x011b1a23611445e4},
  {0xb5e03c9d9786dbf6, 0x311beba95c77cf78},
  {0x98277eeb9ab58a7b, 0xda552000beeef0f8},
  {0xd5ba7df55eb49f58, 0xde65bf8cb1d3021a},
  {0x95923bbc67be16c8, 0x8a3aade58c8cb94c},
  {0xd12aaa7c6f0d5971, 0x30930e5c7db4ad8a},
  {0xf3dfa8f5d6bb2bd8, 0xef5c61dfba732caa},
  {0xb924a21ada66d43d, 0x9f4a94adf3f028c5},
  {0x50f47ad700c5e469, 0xf29e3a326e748727},
  {0x2ddf262408d35e91, 0xa3dae80b9fe59ecb},
  {0xa4080718a938e3f1, 0x9e1b036b189ffbc8},
  {0x373e818480913f97, 0x5dcdf4646386f788},
  {0xcccab1bd7fdd6cbf, 0x319e56eb55e64e2a},
  {0x078e20a725194a3d, 0x5808554102fda3bc},
  {0xb0f53ad0e4e0f8e4, 0x875e42390bc73666},
  {0x3c32d8e95443b0ad, 0xaf8f67d0ca4d785b},
  {0x36ded7dacdb89b8d, 0x11f912674db2efdb},
  {0xa403a68324f4cb86, 0xeed36f03d9033760},
  {0xc237d7b777b28305, 0xbf3f2cde7aa1427b},
  {0x6b31e8ba1ea77e4e, 0x9f09e7a33f91800a},
  {0x438eefdae6726e38, 0xbecefad8a1e6361c},
  {0xa4d441287cf4c9c1, 0xcebd0a6c2bfbdd52},
  {0xbdff148c7b6a2a20, 0x926f16bd3f57bcc5},
  {0xde0a74a95b11a7b2, 0xcec3202236b9330f},
  {0x00d98a40c825e856, 0xd3b06ee706861398},
  {0x2f694e7f129363bf, 0x21258bf219db76d8},
  {0xb48190f890233bfe, 0xde25515e1adcbd3d},
  {0x9d13e3e00c68f533, 0xc3550ae4c5ba2745},
  {0x00269afeeb30b3ce, 0x82af1db865a0e8ee},
  {0xf79d2d8272061a31, 0x798f989a303e82b4},
  {0xc6b91817e68eab94, 0x145bfe33d171d26c},
  {0x012999b9f0554508, 0xb7a0bd99682fc53d},
  {0x009313716c4b1e56, 0x0590300aaef4b274},
  {0xc018255b37528e8a, 0xd263612b59cc4666},
  {0xdeea6528058b0a1c, 0x92a279e76f452d90},
  {0xcaccd5764053995d, 0x5de6e181c70b4290},
  {0x059b5e7b2df33559, 0x71198138f4d19dba},
  {0x7baeee63a28eb883, 0xa6ae2019d7573888},
  {0x359dc1e0eda88b52, 0x60f4522bb2d2be17},
  {0xdc94e45eefb543ac, 0xc668dd50620a3f81},
  {0xe6da1b4b19cffb33, 0x1cba9d507074bb68},
  {0x28d79e3c3898b461, 0x51c3f54be5ca1a95},
  {0xa794b803c592f5c6, 0xe3b6763324bc53f9},
  {0x9fafa1d6ca649eda, 0xde96f0708a28bc1e},
  {0x5e1abad522080597, 0xa76b4471e16db4b8},
  {0x31c3c2966b6f0bda, 0x5594fbe009545466},
  {0x7818e8259e88032c, 0x9b1ed375d949dfa2},
  {0x4afa708b4349a1c3, 0x4db72190655bbc82},
  {0xab3557eae63f8b3f, 0xd3fbc4f25f42e104},
  {0xfd84acc77b5b1997, 0xa2cff9fbf059e186},
  {0x9aebf684059ac6c1, 0xeb5d2ece859ff5f2},
  {0xd6415302e457f7d3, 0xca2041df6fe0cbea},
  {0xa9601552868462fe, 0x4da331ae97b5c815},
  {0x29c2acdc31d6bbcd, 0xd2268fef28ee4919},
  {0x446fdedf58793369, 0x01d22770a6e3c38a},
  {0x78f43f166cf9adc1, 0x296257ed0b57f458},
  {0x4e139fe62f801bce, 0x0c890df8029d8a74},
  {0x47a6b3409ef917fb, 0x383d39bead9ac803},
  {0xe7103a6fd8524529, 0xabb04520658b4d5a},
  {0x6c40f5d37dd1c333, 0xdae345a289d4276a},
  {0x79bc9cc438cce65c, 0xda097e7dd1a22b75},
  {0xe2a069405c77d4a6, 0x28bca41b02844e1b},
  {0xa0de81e6f310ed60, 0x74c6e74c33bfa79a},
  {0x2eba8b46249fa4ed, 0xdb0b9c48637b246a},
  {0x8938d06fa3f75dcd, 0x54c39200aa127fff},
  {0xea89f7354ffe7b87, 0xcbf63ce0b846ca02},
  {0x983812db99b23701, 0xea28f51d8ff9d2a3},
  {0x06260355cefc73d9, 0xd6d5619cfbff3492},
  {0xbf0427970b8a80b8, 0x863021daaba75266},
  {0x7762eee9c426221b, 0x8fe389b5775aeb47},
  {0x1f93582fbfe8d702, 0xf7806c48f3ec9ea6},
  {0x82c449388fc88163, 0xf25aee2537826368},
  {0x7c87d7afd46bcd98, 0x0570c7ccda3a7a16},
  {0x09451c77c647540a, 0x82b85b13d40337a7},
  {0xaf15229686758dea, 0x9255a8a335b67f4c},
  {0x12575789c1a43945, 0xc3953594033f42b7},
  {0x8a7a0689d296953a, 0xc2b8d9d9b240178a},
  {0xddea998b3213d923, 0x202db53c648c59b3},
  {0x8f2a7211fd9357a5, 0xfa5924002dc42ec0},
  {0xb15e03b3d55423ef, 0x786e246df2889bdd},
  {0x5a45fe0955930e52, 0xdcaf211cab59a48e},
  {0x88b8b36a8538ba99, 0x6080dbd35ca047a7},
  {0xdb4511c31eade7c0, 0x0d61dc1884842d59},
  {0x2a205d624e7eb142, 0xdf9f232733d741f2},
  {0x2a9b640a7bfe2b2e, 0xda62c9eea4711a4a},
  {0xa566e98c76ddac90, 0x0047127e8c5f3265},
  {0xea4566673052ba63, 0xdc0fb68b0ab97a19},
};

void generate_matrices_L_and_U(const uint8_t* iv, GF temp_matrix[2*AIMER_NUM_INPUT_SBOXES][AIMER_NUM_BITS], GF vector_b);
void generate_matrix_LU(const uint8_t* iv, GF matrix_A[AIMER_NUM_INPUT_SBOXES][AIMER_NUM_BITS*AIMER_FIELD_SIZE], GF vector_b);
void compute_sbox_outputs(const uint8_t* pt, GF* sbox_outputs);

void aim(const uint8_t* pt, const uint8_t* iv, uint8_t* ct);
void aim_mpc(const uint8_t* pt, const GF matrix_A[AIMER_NUM_INPUT_SBOXES][AIMER_NUM_BITS*AIMER_FIELD_SIZE],
             const GF vector_b, const uint8_t* ct,
             const size_t num_parties, GF *z_shares, GF *x_shares);

#endif // AIM128_H
