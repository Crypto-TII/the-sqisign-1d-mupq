#ifndef TUTIL_H
#define TUTIL_H

#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
#define BSWAP32(i) __builtin_bswap32((i))
#define BSWAP64(i) __builtin_bswap64((i))
#else
#define BSWAP32(i) ((((i) >> 24) & 0xff) | (((i) >> 8) & 0xff00) | (((i) & 0xff00) << 8) | ((i) << 24))
#define BSWAP64(i) ((BSWAP32((i) >> 32) & 0xffffffff) | (BSWAP32(i) << 32)
#endif

#if defined(RADIX_64)
#define digit_t uint64_t
#define sdigit_t int64_t
#define DIGIT_LEN 8
#define RADIX 64
#define LOG2RADIX 6
#define BSWAP_DIGIT(i) BSWAP64(i)
#define HEX_FS "%016" PRIx64
#define PRIx PRIx64
#define PRId PRId64
#elif defined(RADIX_32)
#define digit_t uint32_t
#define sdigit_t int32_t
#define DIGIT_LEN 4
#define RADIX 32
#define LOG2RADIX 5
#define BSWAP_DIGIT(i) BSWAP32(i)
#define HEX_FS "%08" PRIx32
#define PRIx PRIx32
#define PRId PRId32
#else
#error "Radix must be 32bit or 64 bit"
#endif

#endif
