#ifndef FP_CONSTANTS_H
#define FP_CONSTANTS_H

#if 0

#elif 8*DIGIT_LEN == 16
#define NWORDS_FIELD 32
#define NWORDS_ORDER 32
#define BITS 512
#define LOG2P 9

#elif 8*DIGIT_LEN == 32
#if defined(ARITH_REF) || defined(ARITH_BROADWELL)
#define NWORDS_FIELD 16
#elif defined(ARITH_MIKE)
#define NWORDS_FIELD 18
#endif
#define NWORDS_ORDER 16
#define BITS 512
#define LOG2P 9

#elif 8*DIGIT_LEN == 64
#if defined(ARITH_REF) || defined(ARITH_BROADWELL)
#define NWORDS_FIELD 8
#elif defined(ARITH_MIKE)
#define NWORDS_FIELD 9
#endif
#define NWORDS_ORDER 8
#define BITS 512
#define LOG2P 9

#endif

#endif
