#include <ec_params.h>

const digit_t p_plus_minus_bitlength[P_LEN + M_LEN] =
	{2, 3, 4, 6, 8, 9, 10, 3, 4, 7, 7, 8, 8, 8, 8, 9, 10, 11, 12, 12, 13, 13, 13, 13, 14, 15, 16, 16};

const digit_t STRATEGY4[] =
	{20, 12, 7, 4, 2, 1, 1, 2, 1, 1, 3, 2, 1, 1, 1, 1, 5, 3, 2, 1, 1, 1, 1, 2, 1, 1, 1, 8, 5, 3, 2, 1, 1, 1, 1, 2, 1, 1, 1, 4, 2, 1, 1, 2, 1, 1};

const digit_t sizeI[] =
	{0, 1, 2, 3, 6, 14, 14, 1, 3, 5, 5, 7, 8, 8, 10, 11, 14, 19, 26, 30, 35, 40, 44, 44, 52, 88, 114, 114};
const digit_t sizeJ[] =
	{0, 1, 1, 3, 6, 9, 13, 1, 1, 4, 5, 6, 7, 7, 6, 10, 10, 16, 23, 28, 32, 32, 32, 33, 45, 76, 87, 104};
const digit_t sizeK[] =
	{1, 1, 1, 5, 6, 2, 16, 0, 0, 4, 6, 2, 4, 7, 0, 1, 4, 6, 0, 5, 18, 13, 30, 2, 18, 12, 3, 8};

#if 0
#elif 8*DIGIT_LEN == 16
const digit_t TWOpF[NWORDS_ORDER] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const digit_t TWOpFm1[NWORDS_ORDER] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const digit_t THREEpE[NWORDS_ORDER] = {0x3289, 0xf310, 0x3fce, 0x3b, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const digit_t THREEpF[NWORDS_ORDER] = {0xcd51, 0x7119, 0x8372, 0x58de, 0x8c65, 0x794b, 0xdb6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const digit_t THREEpFdiv2[NWORDS_ORDER] = {0xe6a8, 0x388c, 0x41b9, 0xac6f, 0xc632, 0x3ca5, 0x6db, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const digit_t p_cofactor_for_2f[NWORDS_ORDER] = {0xba61, 0x2630, 0x5234, 0x9ab7, 0x7b34, 0xe391, 0x5ba8, 0x4857, 0x1705, 0x32de, 0x856b, 0x22e8, 0x3025, 0x6357, 0x38d1, 0x5584, 0xb777, 0x1ef, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const digit_t p_cofactor_for_3g[NWORDS_ORDER] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3022, 0x97e5, 0xe081, 0x13cf, 0xedda, 0xee54, 0x9f3f, 0xd920, 0xe309, 0xc6bf, 0x484c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const digit_t p_cofactor_for_6fg[NWORDS_ORDER] = {0x9811, 0xcbf2, 0xf040, 0x9e7, 0x76ed, 0xf72a, 0x4f9f, 0xec90, 0xf184, 0x635f, 0x2426, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
#elif 8*DIGIT_LEN == 32
const digit_t TWOpF[NWORDS_ORDER] = {0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const digit_t TWOpFm1[NWORDS_ORDER] = {0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const digit_t THREEpE[NWORDS_ORDER] = {0xf3103289, 0x3b3fce, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const digit_t THREEpF[NWORDS_ORDER] = {0x7119cd51, 0x58de8372, 0x794b8c65, 0xdb6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const digit_t THREEpFdiv2[NWORDS_ORDER] = {0x388ce6a8, 0xac6f41b9, 0x3ca5c632, 0x6db, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const digit_t p_cofactor_for_2f[NWORDS_ORDER] = {0x2630ba61, 0x9ab75234, 0xe3917b34, 0x48575ba8, 0x32de1705, 0x22e8856b, 0x63573025, 0x558438d1, 0x1efb777, 0x0, 0x0, 0x0};
const digit_t p_cofactor_for_3g[NWORDS_ORDER] = {0x0, 0x0, 0x0, 0x97e53022, 0x13cfe081, 0xee54edda, 0xd9209f3f, 0xc6bfe309, 0x484c, 0x0, 0x0, 0x0};
const digit_t p_cofactor_for_6fg[NWORDS_ORDER] = {0xcbf29811, 0x9e7f040, 0xf72a76ed, 0xec904f9f, 0x635ff184, 0x2426, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
#elif 8*DIGIT_LEN == 64
const digit_t TWOpF[NWORDS_ORDER] = {0x0, 0x200000000, 0x0, 0x0, 0x0, 0x0};
const digit_t TWOpFm1[NWORDS_ORDER] = {0x0, 0x100000000, 0x0, 0x0, 0x0, 0x0};
const digit_t THREEpE[NWORDS_ORDER] = {0x3b3fcef3103289, 0x0, 0x0, 0x0, 0x0, 0x0};
const digit_t THREEpF[NWORDS_ORDER] = {0x58de83727119cd51, 0xdb6794b8c65, 0x0, 0x0, 0x0, 0x0};
const digit_t THREEpFdiv2[NWORDS_ORDER] = {0xac6f41b9388ce6a8, 0x6db3ca5c632, 0x0, 0x0, 0x0, 0x0};
const digit_t p_cofactor_for_2f[NWORDS_ORDER] = {0x9ab752342630ba61, 0x48575ba8e3917b34, 0x22e8856b32de1705, 0x558438d163573025, 0x1efb777, 0x0};
const digit_t p_cofactor_for_3g[NWORDS_ORDER] = {0x0, 0x97e5302200000000, 0xee54edda13cfe081, 0xc6bfe309d9209f3f, 0x484c, 0x0};
const digit_t p_cofactor_for_6fg[NWORDS_ORDER] = {0x9e7f040cbf29811, 0xec904f9ff72a76ed, 0x2426635ff184, 0x0, 0x0, 0x0};
#endif

