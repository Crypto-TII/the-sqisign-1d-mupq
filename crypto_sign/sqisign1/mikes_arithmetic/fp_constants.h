#ifndef FP_CONSTANTS_H
#define FP_CONSTANTS_H

#if 0

#elif 8*DIGIT_LEN == 16
#define NWORDS_FIELD 16
#define NWORDS_ORDER 16
#define BITS 256
#define LOG2P 8

#elif 8*DIGIT_LEN == 32
#if defined(ARITH_REF) || defined(ARITH_BROADWELL)
#define NWORDS_FIELD 8
#elif defined(ARITH_MIKE)
#define NWORDS_FIELD 9
#endif
#define NWORDS_ORDER 8
#define BITS 256
#define LOG2P 8

#elif 8*DIGIT_LEN == 64
#if defined(ARITH_REF) || defined(ARITH_BROADWELL)
#define NWORDS_FIELD 4
#elif defined(ARITH_MIKE)
#define NWORDS_FIELD 5
#endif
#define NWORDS_ORDER 4
#define BITS 256
#define LOG2P 8

#endif

#endif
