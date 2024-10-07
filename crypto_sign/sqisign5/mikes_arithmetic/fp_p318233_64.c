#ifdef RADIX_64

#include <stdint.h>
#include <stdio.h>

#include <stdbool.h>
#include <fp.h>

#define sspint int64_t
#define spint uint64_t
#define udpint __uint128_t
#define dpint __uint128_t

// propagate carries
static spint inline prop(spint *n) {
    int i;
    spint mask = ((spint)1 << 56u) - (spint)1;
    sspint carry = (sspint)n[0];
    carry >>= 56u;
    n[0] &= mask;
    for (i = 1; i < 8; i++) {
        carry += (sspint)n[i];
        n[i] = (spint)carry & mask;
        carry >>= 56u;
    }
    n[8] += (spint)carry;
    return -((n[8] >> 1) >> 62u);
}

// propagate carries and add p if negative, propagate carries again
static void inline flatten(spint *n) {
    spint carry = prop(n);
    n[0] -= (spint)1u & carry;
    n[2] += ((spint)0xada6e200000000u) & carry;
    n[3] += ((spint)0x781974ce994c68u) & carry;
    n[4] += ((spint)0xdea65faf0a29au) & carry;
    n[5] += ((spint)0x7d01fe3ac5904au) & carry;
    n[6] += ((spint)0x9202bdbe632650u) & carry;
    n[7] += ((spint)0x8c15b0036936e7u) & carry;
    n[8] += ((spint)0x255946a8869bc6u) & carry;
    (void)prop(n);
}

// Montgomery final subtract
static void inline modfsb(spint *n) {
    n[0] += (spint)1u;
    n[2] -= (spint)0xada6e200000000u;
    n[3] -= (spint)0x781974ce994c68u;
    n[4] -= (spint)0xdea65faf0a29au;
    n[5] -= (spint)0x7d01fe3ac5904au;
    n[6] -= (spint)0x9202bdbe632650u;
    n[7] -= (spint)0x8c15b0036936e7u;
    n[8] -= (spint)0x255946a8869bc6u;
    flatten(n);
}

// Modular addition - reduce less than 2p
static void inline modadd(const spint *a, const spint *b, spint *n) {
    spint carry;
    n[0] = a[0] + b[0];
    n[1] = a[1] + b[1];
    n[2] = a[2] + b[2];
    n[3] = a[3] + b[3];
    n[4] = a[4] + b[4];
    n[5] = a[5] + b[5];
    n[6] = a[6] + b[6];
    n[7] = a[7] + b[7];
    n[8] = a[8] + b[8];
    n[0] += (spint)2u;
    n[2] -= (spint)0x15b4dc400000000u;
    n[3] -= (spint)0xf032e99d3298d0u;
    n[4] -= (spint)0x1bd4cbf5e14534u;
    n[5] -= (spint)0xfa03fc758b2094u;
    n[6] -= (spint)0x124057b7cc64ca0u;
    n[7] -= (spint)0x1182b6006d26dceu;
    n[8] -= (spint)0x4ab28d510d378cu;
    carry = prop(n);
    n[0] -= (spint)2u & carry;
    n[2] += ((spint)0x15b4dc400000000u) & carry;
    n[3] += ((spint)0xf032e99d3298d0u) & carry;
    n[4] += ((spint)0x1bd4cbf5e14534u) & carry;
    n[5] += ((spint)0xfa03fc758b2094u) & carry;
    n[6] += ((spint)0x124057b7cc64ca0u) & carry;
    n[7] += ((spint)0x1182b6006d26dceu) & carry;
    n[8] += ((spint)0x4ab28d510d378cu) & carry;
    (void)prop(n);
}

// Modular subtraction - reduce less than 2p
static void inline modsub(const spint *a, const spint *b, spint *n) {
    spint carry;
    n[0] = a[0] - b[0];
    n[1] = a[1] - b[1];
    n[2] = a[2] - b[2];
    n[3] = a[3] - b[3];
    n[4] = a[4] - b[4];
    n[5] = a[5] - b[5];
    n[6] = a[6] - b[6];
    n[7] = a[7] - b[7];
    n[8] = a[8] - b[8];
    carry = prop(n);
    n[0] -= (spint)2u & carry;
    n[2] += ((spint)0x15b4dc400000000u) & carry;
    n[3] += ((spint)0xf032e99d3298d0u) & carry;
    n[4] += ((spint)0x1bd4cbf5e14534u) & carry;
    n[5] += ((spint)0xfa03fc758b2094u) & carry;
    n[6] += ((spint)0x124057b7cc64ca0u) & carry;
    n[7] += ((spint)0x1182b6006d26dceu) & carry;
    n[8] += ((spint)0x4ab28d510d378cu) & carry;
    (void)prop(n);
}

// Modular negation
static void inline modneg(const spint *b, spint *n) {
    spint carry;
    n[0] = (spint)0 - b[0];
    n[1] = (spint)0 - b[1];
    n[2] = (spint)0 - b[2];
    n[3] = (spint)0 - b[3];
    n[4] = (spint)0 - b[4];
    n[5] = (spint)0 - b[5];
    n[6] = (spint)0 - b[6];
    n[7] = (spint)0 - b[7];
    n[8] = (spint)0 - b[8];
    carry = prop(n);
    n[0] -= (spint)2u & carry;
    n[2] += ((spint)0x15b4dc400000000u) & carry;
    n[3] += ((spint)0xf032e99d3298d0u) & carry;
    n[4] += ((spint)0x1bd4cbf5e14534u) & carry;
    n[5] += ((spint)0xfa03fc758b2094u) & carry;
    n[6] += ((spint)0x124057b7cc64ca0u) & carry;
    n[7] += ((spint)0x1182b6006d26dceu) & carry;
    n[8] += ((spint)0x4ab28d510d378cu) & carry;
    (void)prop(n);
}

// Overflow limit   = 340282366920938463463374607431768211456
// maximum possible = 62066584718639432850653955984558016
// Modular multiplication, c=a*b mod 2p
static void inline modmul(const spint *a, const spint *b, spint *c) {
    dpint t = 0;
    spint p2 = 0xada6e200000000u;
    spint p3 = 0x781974ce994c68u;
    spint p4 = 0xdea65faf0a29au;
    spint p5 = 0x7d01fe3ac5904au;
    spint p6 = 0x9202bdbe632650u;
    spint p7 = 0x8c15b0036936e7u;
    spint p8 = 0x255946a8869bc6u;
    spint q = ((spint)1 << 56u); // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    t += (dpint)a[0] * b[0];
    spint v0 = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[0] * b[1];
    t += (dpint)a[1] * b[0];
    spint v1 = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[0] * b[2];
    t += (dpint)a[1] * b[1];
    t += (dpint)a[2] * b[0];
    t += (dpint)v0 * (dpint)p2;
    spint v2 = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[0] * b[3];
    t += (dpint)a[1] * b[2];
    t += (dpint)a[2] * b[1];
    t += (dpint)a[3] * b[0];
    t += (dpint)v0 * (dpint)p3;
    t += (dpint)v1 * (dpint)p2;
    spint v3 = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[0] * b[4];
    t += (dpint)a[1] * b[3];
    t += (dpint)a[2] * b[2];
    t += (dpint)a[3] * b[1];
    t += (dpint)a[4] * b[0];
    t += (dpint)v0 * (dpint)p4;
    t += (dpint)v1 * (dpint)p3;
    t += (dpint)v2 * (dpint)p2;
    spint v4 = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[0] * b[5];
    t += (dpint)a[1] * b[4];
    t += (dpint)a[2] * b[3];
    t += (dpint)a[3] * b[2];
    t += (dpint)a[4] * b[1];
    t += (dpint)a[5] * b[0];
    t += (dpint)v0 * (dpint)p5;
    t += (dpint)v1 * (dpint)p4;
    t += (dpint)v2 * (dpint)p3;
    t += (dpint)v3 * (dpint)p2;
    spint v5 = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[0] * b[6];
    t += (dpint)a[1] * b[5];
    t += (dpint)a[2] * b[4];
    t += (dpint)a[3] * b[3];
    t += (dpint)a[4] * b[2];
    t += (dpint)a[5] * b[1];
    t += (dpint)a[6] * b[0];
    t += (dpint)v0 * (dpint)p6;
    t += (dpint)v1 * (dpint)p5;
    t += (dpint)v2 * (dpint)p4;
    t += (dpint)v3 * (dpint)p3;
    t += (dpint)v4 * (dpint)p2;
    spint v6 = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[0] * b[7];
    t += (dpint)a[1] * b[6];
    t += (dpint)a[2] * b[5];
    t += (dpint)a[3] * b[4];
    t += (dpint)a[4] * b[3];
    t += (dpint)a[5] * b[2];
    t += (dpint)a[6] * b[1];
    t += (dpint)a[7] * b[0];
    t += (dpint)v0 * (dpint)p7;
    t += (dpint)v1 * (dpint)p6;
    t += (dpint)v2 * (dpint)p5;
    t += (dpint)v3 * (dpint)p4;
    t += (dpint)v4 * (dpint)p3;
    t += (dpint)v5 * (dpint)p2;
    spint v7 = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[0] * b[8];
    t += (dpint)a[1] * b[7];
    t += (dpint)a[2] * b[6];
    t += (dpint)a[3] * b[5];
    t += (dpint)a[4] * b[4];
    t += (dpint)a[5] * b[3];
    t += (dpint)a[6] * b[2];
    t += (dpint)a[7] * b[1];
    t += (dpint)a[8] * b[0];
    t += (dpint)v0 * (dpint)p8;
    t += (dpint)v1 * (dpint)p7;
    t += (dpint)v2 * (dpint)p6;
    t += (dpint)v3 * (dpint)p5;
    t += (dpint)v4 * (dpint)p4;
    t += (dpint)v5 * (dpint)p3;
    t += (dpint)v6 * (dpint)p2;
    spint v8 = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[1] * b[8];
    t += (dpint)a[2] * b[7];
    t += (dpint)a[3] * b[6];
    t += (dpint)a[4] * b[5];
    t += (dpint)a[5] * b[4];
    t += (dpint)a[6] * b[3];
    t += (dpint)a[7] * b[2];
    t += (dpint)a[8] * b[1];
    t += (dpint)v1 * (dpint)p8;
    t += (dpint)v2 * (dpint)p7;
    t += (dpint)v3 * (dpint)p6;
    t += (dpint)v4 * (dpint)p5;
    t += (dpint)v5 * (dpint)p4;
    t += (dpint)v6 * (dpint)p3;
    t += (dpint)v7 * (dpint)p2;
    c[0] = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[2] * b[8];
    t += (dpint)a[3] * b[7];
    t += (dpint)a[4] * b[6];
    t += (dpint)a[5] * b[5];
    t += (dpint)a[6] * b[4];
    t += (dpint)a[7] * b[3];
    t += (dpint)a[8] * b[2];
    t += (dpint)v2 * (dpint)p8;
    t += (dpint)v3 * (dpint)p7;
    t += (dpint)v4 * (dpint)p6;
    t += (dpint)v5 * (dpint)p5;
    t += (dpint)v6 * (dpint)p4;
    t += (dpint)v7 * (dpint)p3;
    t += (dpint)v8 * (dpint)p2;
    c[1] = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[3] * b[8];
    t += (dpint)a[4] * b[7];
    t += (dpint)a[5] * b[6];
    t += (dpint)a[6] * b[5];
    t += (dpint)a[7] * b[4];
    t += (dpint)a[8] * b[3];
    t += (dpint)v3 * (dpint)p8;
    t += (dpint)v4 * (dpint)p7;
    t += (dpint)v5 * (dpint)p6;
    t += (dpint)v6 * (dpint)p5;
    t += (dpint)v7 * (dpint)p4;
    t += (dpint)v8 * (dpint)p3;
    c[2] = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[4] * b[8];
    t += (dpint)a[5] * b[7];
    t += (dpint)a[6] * b[6];
    t += (dpint)a[7] * b[5];
    t += (dpint)a[8] * b[4];
    t += (dpint)v4 * (dpint)p8;
    t += (dpint)v5 * (dpint)p7;
    t += (dpint)v6 * (dpint)p6;
    t += (dpint)v7 * (dpint)p5;
    t += (dpint)v8 * (dpint)p4;
    c[3] = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[5] * b[8];
    t += (dpint)a[6] * b[7];
    t += (dpint)a[7] * b[6];
    t += (dpint)a[8] * b[5];
    t += (dpint)v5 * (dpint)p8;
    t += (dpint)v6 * (dpint)p7;
    t += (dpint)v7 * (dpint)p6;
    t += (dpint)v8 * (dpint)p5;
    c[4] = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[6] * b[8];
    t += (dpint)a[7] * b[7];
    t += (dpint)a[8] * b[6];
    t += (dpint)v6 * (dpint)p8;
    t += (dpint)v7 * (dpint)p7;
    t += (dpint)v8 * (dpint)p6;
    c[5] = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[7] * b[8];
    t += (dpint)a[8] * b[7];
    t += (dpint)v7 * (dpint)p8;
    t += (dpint)v8 * (dpint)p7;
    c[6] = ((spint)t & mask);
    t >>= 56;
    t += (dpint)a[8] * b[8];
    t += (dpint)v8 * (dpint)p8;
    c[7] = ((spint)t & mask);
    t >>= 56;
    c[8] = (spint)t;
}

// Modular squaring, c=a*a  mod 2p
static void inline modsqr(const spint *a, spint *c) {
    udpint tot;
    udpint t = 0;
    spint p2 = 0xada6e200000000u;
    spint p3 = 0x781974ce994c68u;
    spint p4 = 0xdea65faf0a29au;
    spint p5 = 0x7d01fe3ac5904au;
    spint p6 = 0x9202bdbe632650u;
    spint p7 = 0x8c15b0036936e7u;
    spint p8 = 0x255946a8869bc6u;
    spint q = ((spint)1 << 56u); // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    tot = (udpint)a[0] * a[0];
    t = tot;
    spint v0 = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[0] * a[1];
    tot *= 2;
    t += tot;
    spint v1 = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[0] * a[2];
    tot *= 2;
    tot += (udpint)a[1] * a[1];
    t += tot;
    t += (udpint)v0 * p2;
    spint v2 = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[0] * a[3];
    tot += (udpint)a[1] * a[2];
    tot *= 2;
    t += tot;
    t += (udpint)v0 * p3;
    t += (udpint)v1 * p2;
    spint v3 = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[0] * a[4];
    tot += (udpint)a[1] * a[3];
    tot *= 2;
    tot += (udpint)a[2] * a[2];
    t += tot;
    t += (udpint)v0 * p4;
    t += (udpint)v1 * p3;
    t += (udpint)v2 * p2;
    spint v4 = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[0] * a[5];
    tot += (udpint)a[1] * a[4];
    tot += (udpint)a[2] * a[3];
    tot *= 2;
    t += tot;
    t += (udpint)v0 * p5;
    t += (udpint)v1 * p4;
    t += (udpint)v2 * p3;
    t += (udpint)v3 * p2;
    spint v5 = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[0] * a[6];
    tot += (udpint)a[1] * a[5];
    tot += (udpint)a[2] * a[4];
    tot *= 2;
    tot += (udpint)a[3] * a[3];
    t += tot;
    t += (udpint)v0 * p6;
    t += (udpint)v1 * p5;
    t += (udpint)v2 * p4;
    t += (udpint)v3 * p3;
    t += (udpint)v4 * p2;
    spint v6 = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[0] * a[7];
    tot += (udpint)a[1] * a[6];
    tot += (udpint)a[2] * a[5];
    tot += (udpint)a[3] * a[4];
    tot *= 2;
    t += tot;
    t += (udpint)v0 * p7;
    t += (udpint)v1 * p6;
    t += (udpint)v2 * p5;
    t += (udpint)v3 * p4;
    t += (udpint)v4 * p3;
    t += (udpint)v5 * p2;
    spint v7 = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[0] * a[8];
    tot += (udpint)a[1] * a[7];
    tot += (udpint)a[2] * a[6];
    tot += (udpint)a[3] * a[5];
    tot *= 2;
    tot += (udpint)a[4] * a[4];
    t += tot;
    t += (udpint)v0 * p8;
    t += (udpint)v1 * p7;
    t += (udpint)v2 * p6;
    t += (udpint)v3 * p5;
    t += (udpint)v4 * p4;
    t += (udpint)v5 * p3;
    t += (udpint)v6 * p2;
    spint v8 = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[1] * a[8];
    tot += (udpint)a[2] * a[7];
    tot += (udpint)a[3] * a[6];
    tot += (udpint)a[4] * a[5];
    tot *= 2;
    t += tot;
    t += (udpint)v1 * p8;
    t += (udpint)v2 * p7;
    t += (udpint)v3 * p6;
    t += (udpint)v4 * p5;
    t += (udpint)v5 * p4;
    t += (udpint)v6 * p3;
    t += (udpint)v7 * p2;
    c[0] = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[2] * a[8];
    tot += (udpint)a[3] * a[7];
    tot += (udpint)a[4] * a[6];
    tot *= 2;
    tot += (udpint)a[5] * a[5];
    t += tot;
    t += (udpint)v2 * p8;
    t += (udpint)v3 * p7;
    t += (udpint)v4 * p6;
    t += (udpint)v5 * p5;
    t += (udpint)v6 * p4;
    t += (udpint)v7 * p3;
    t += (udpint)v8 * p2;
    c[1] = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[3] * a[8];
    tot += (udpint)a[4] * a[7];
    tot += (udpint)a[5] * a[6];
    tot *= 2;
    t += tot;
    t += (udpint)v3 * p8;
    t += (udpint)v4 * p7;
    t += (udpint)v5 * p6;
    t += (udpint)v6 * p5;
    t += (udpint)v7 * p4;
    t += (udpint)v8 * p3;
    c[2] = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[4] * a[8];
    tot += (udpint)a[5] * a[7];
    tot *= 2;
    tot += (udpint)a[6] * a[6];
    t += tot;
    t += (udpint)v4 * p8;
    t += (udpint)v5 * p7;
    t += (udpint)v6 * p6;
    t += (udpint)v7 * p5;
    t += (udpint)v8 * p4;
    c[3] = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[5] * a[8];
    tot += (udpint)a[6] * a[7];
    tot *= 2;
    t += tot;
    t += (udpint)v5 * p8;
    t += (udpint)v6 * p7;
    t += (udpint)v7 * p6;
    t += (udpint)v8 * p5;
    c[4] = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[6] * a[8];
    tot *= 2;
    tot += (udpint)a[7] * a[7];
    t += tot;
    t += (udpint)v6 * p8;
    t += (udpint)v7 * p7;
    t += (udpint)v8 * p6;
    c[5] = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[7] * a[8];
    tot *= 2;
    t += tot;
    t += (udpint)v7 * p8;
    t += (udpint)v8 * p7;
    c[6] = ((spint)t & mask);
    t >>= 56;
    tot = (udpint)a[8] * a[8];
    t += tot;
    t += (udpint)v8 * p8;
    c[7] = ((spint)t & mask);
    t >>= 56;
    c[8] = (spint)t;
}

// copy
static void inline modcpy(const spint *a, spint *c) {
    int i;
    for (i = 0; i < 9; i++) {
        c[i] = a[i];
    }
}

// square n times
static void modnsqr(spint *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        modsqr(a, a);
    }
}

// Calculate progenitor
static void modpro(const spint *w, spint *z) {
    spint x[9];
    spint t0[9];
    spint t1[9];
    spint t2[9];
    spint t3[9];
    spint t4[9];
    spint t5[9];
    spint t6[9];
    spint t7[9];
    spint t8[9];
    spint t9[9];
    spint t10[9];
    spint t11[9];
    spint t12[9];
    spint t13[9];
    spint t14[9];
    spint t15[9];
    spint t16[9];
    spint t17[9];
    spint t18[9];
    spint t19[9];
    spint t20[9];
    spint t21[9];
    spint t22[9];
    spint t23[9];
    spint t24[9];
    spint t25[9];
    spint t26[9];
    spint t27[9];
    spint t28[9];
    spint t29[9];
    spint t30[9];
    modcpy(w, x);
    modsqr(x, t16);
    modsqr(t16, t19);
    modmul(t16, t19, z);
    modmul(t16, z, t6);
    modmul(x, t6, t1);
    modmul(x, t1, t20);
    modmul(t16, t20, t8);
    modmul(z, t1, t9);
    modmul(z, t8, t13);
    modmul(t16, t13, t0);
    modmul(t1, t0, t17);
    modmul(z, t17, t26);
    modmul(t16, t26, t5);
    modmul(t20, t5, t12);
    modmul(t6, t12, t1);
    modmul(t8, t1, t27);
    modmul(t16, t27, t3);
    modmul(t19, t3, t22);
    modmul(t19, t22, t10);
    modmul(t19, t10, t11);
    modmul(t16, t11, t7);
    modmul(z, t7, t15);
    modmul(t20, t15, t4);
    modmul(t16, t4, t29);
    modmul(t6, t29, t2);
    modmul(t16, t2, t14);
    modmul(t13, t2, z);
    modmul(t19, z, t18);
    modmul(t13, t18, t21);
    modmul(t19, t21, t19);
    modmul(t16, t19, t24);
    modmul(t13, t24, t25);
    modmul(t16, t25, t21);
    modmul(t13, t25, t13);
    modmul(t8, t13, t8);
    modmul(t20, t8, t28);
    modmul(t20, t28, t20);
    modmul(t6, t20, t23);
    modmul(t16, t23, t6);
    modmul(t16, t6, t16);
    modmul(t0, t16, t0);
    modmul(t27, t23, t30);
    modnsqr(t30, 7);
    modmul(t29, t30, t29);
    modnsqr(t29, 11);
    modmul(t28, t29, t28);
    modnsqr(t28, 10);
    modmul(t27, t28, t27);
    modnsqr(t27, 9);
    modmul(t24, t27, t27);
    modnsqr(t27, 7);
    modmul(t4, t27, t27);
    modnsqr(t27, 7);
    modmul(t26, t27, t26);
    modnsqr(t26, 13);
    modmul(t25, t26, t25);
    modsqr(t25, t25);
    modmul(x, t25, t25);
    modnsqr(t25, 17);
    modmul(t2, t25, t25);
    modnsqr(t25, 10);
    modmul(t24, t25, t24);
    modnsqr(t24, 9);
    modmul(t23, t24, t23);
    modnsqr(t23, 7);
    modmul(t22, t23, t22);
    modnsqr(t22, 15);
    modmul(t21, t22, t21);
    modnsqr(t21, 9);
    modmul(t20, t21, t20);
    modnsqr(t20, 9);
    modmul(t4, t20, t20);
    modnsqr(t20, 10);
    modmul(t19, t20, t19);
    modnsqr(t19, 9);
    modmul(t18, t19, t18);
    modnsqr(t18, 5);
    modmul(t17, t18, t17);
    modnsqr(t17, 15);
    modmul(t0, t17, t17);
    modnsqr(t17, 11);
    modmul(t16, t17, t16);
    modnsqr(t16, 10);
    modmul(t15, t16, t15);
    modnsqr(t15, 11);
    modmul(t5, t15, t15);
    modnsqr(t15, 12);
    modmul(t14, t15, t14);
    modnsqr(t14, 8);
    modmul(t7, t14, t14);
    modnsqr(t14, 10);
    modmul(t13, t14, t13);
    modnsqr(t13, 7);
    modmul(t12, t13, t12);
    modnsqr(t12, 11);
    modmul(t11, t12, t11);
    modnsqr(t11, 8);
    modmul(t10, t11, t10);
    modnsqr(t10, 6);
    modmul(t9, t10, t9);
    modnsqr(t9, 14);
    modmul(t8, t9, t8);
    modnsqr(t8, 7);
    modmul(t7, t8, t7);
    modnsqr(t7, 10);
    modmul(t6, t7, t6);
    modnsqr(t6, 6);
    modmul(t5, t6, t5);
    modnsqr(t5, 9);
    modmul(t4, t5, t4);
    modnsqr(t4, 8);
    modmul(t3, t4, t3);
    modnsqr(t3, 8);
    modmul(t2, t3, t2);
    modnsqr(t2, 8);
    modmul(t1, t2, t1);
    modnsqr(t1, 12);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t1);
    modnsqr(t1, 8);
    modmul(t0, t1, t0);
    modnsqr(t0, 7);
    modmul(z, t0, z);
}

// calculate inverse, provide progenitor h if available
static void modinv(const spint *x, const spint *h, spint *z) {
    spint s[9];
    spint t[9];
    if (h == NULL) {
        modpro(x, t);
    } else {
        modcpy(h, t);
    }
    modcpy(x, s);
    modnsqr(t, 2);
    modmul(s, t, z);
}

// Convert m to n-residue form, n=nres(m)
static void nres(const spint *m, spint *n) {
    const spint c[9] = {0xa546e4e8a0c754u, 0xcb993b5943e89eu, 0x8dda851bf555c8u,
                        0xc717daa328de11u, 0x307cf4eb090199u, 0x8537d92d096114u,
                        0x96f0b3d2dce4eeu, 0x73aacac5bc94fdu, 0x16de108943ddd4u};
    modmul(m, c, n);
}

// Convert n back to normal form, m=redc(n)
static void redc(const spint *n, spint *m) {
    int i;
    spint c[9];
    c[0] = 1;
    for (i = 1; i < 9; i++) {
        c[i] = 0;
    }
    modmul(n, c, m);
    modfsb(m);
}

// is unity?
static int modis1(const spint *a) {
    int i;
    spint c[9];
    spint c0;
    spint d = 0;
    redc(a, c);
    for (i = 1; i < 9; i++) {
        d |= c[i];
    }
    c0 = (spint)c[0];
    return ((spint)1 & ((d - (spint)1) >> 56u) &
            (((c0 ^ (spint)1) - (spint)1) >> 56u));
}

// is zero?
static int modis0(const spint *a) {
    int i;
    spint c[9];
    spint d = 0;
    redc(a, c);
    for (i = 0; i < 9; i++) {
        d |= c[i];
    }
    return ((spint)1 & ((d - (spint)1) >> 56u));
}

// set to zero
static void modzer(spint *a) {
    int i;
    for (i = 0; i < 9; i++) {
        a[i] = 0;
    }
}

// set to one
static void modone(spint *a) {
    int i;
    a[0] = 1;
    for (i = 1; i < 9; i++) {
        a[i] = 0;
    }
    nres(a, a);
}

// Test for quadratic residue
static int modqr(const spint *h, const spint *x) {
    spint r[9];
    if (h == NULL) {
        modpro(x, r);
        modsqr(r, r);
    } else {
        modsqr(h, r);
    }
    modmul(r, x, r);
    return modis1(r);
}

// Modular square root, provide progenitor h if available, NULL if not
static void modsqrt(const spint *x, const spint *h, spint *r) {
    spint s[9];
    spint y[9];
    if (h == NULL) {
        modpro(x, y);
    } else {
        modcpy(h, y);
    }
    modmul(y, x, s);
    modcpy(s, r);
}

// shift left by less than a word
static void modshl(unsigned int n, spint *a) {
    int i;
    a[8] = ((a[8] << n)) | (a[7] >> (56u - n));
    for (i = 7; i > 0; i--) {
        a[i] = ((a[i] << n) & (spint)0xffffffffffffff) | (a[i - 1] >> (56u - n));
    }
    a[0] = (a[0] << n) & (spint)0xffffffffffffff;
}

// shift right by less than a word. Return shifted out part
static int modshr(unsigned int n, spint *a) {
    int i;
    spint r = a[0] & (((spint)1 << n) - (spint)1);
    for (i = 0; i < 8; i++) {
        a[i] = (a[i] >> n) | ((a[i + 1] << (56u - n)) & (spint)0xffffffffffffff);
    }
    a[8] = a[8] >> n;
    return r;
}

/* API functions calling generated code */

const digit_t p[NWORDS_ORDER] =  { 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0x994C68ADA6E1FFFF, 0xFAF0A29A781974CE, 0xFE3AC5904A0DEA65, 0x02BDBE6326507D01, 0x8C15B0036936E792, 0x00255946A8869BC6 };
const digit_t pre[NWORDS_ORDER] = { 0x5eed19df95224d2a, 0x45f7dd5a27b104bc, 0xa9ce1ca2e5c9f709, 0xe38587e8fd4dcfa9, 0xab9087736d3759f7, 0x618d8301d858e7b8, 0x8277b10a26e29dd3, 0xf4578e1094279 };


bool fp_is_zero(const digit_t* a) {
    return (bool) modis0(a);
}

void fp_copy(digit_t* out, const digit_t* a) {
    modcpy(a, out);
}

void fp_add(digit_t* out, const digit_t* a, const digit_t* b) {
    modadd(a, b, out);
    modfsb(out);
}

void fp_sub(digit_t* out, const digit_t* a, const digit_t* b) {
    modsub(a, b, out);
    modfsb(out);
}

void fp_neg(digit_t* out, const digit_t* a) {
    modneg(a, out);
    modfsb(out);
}

void fp_sqr(digit_t* out, const digit_t* a) {
    modsqr(a, out);
    modfsb(out);
}

void fp_mul(digit_t* out, const digit_t* a, const digit_t* b) {
    modmul(a, b, out);
    modfsb(out);
}

void _fp_inv(digit_t* a) {
    modinv(a, NULL, a);
}

bool _fp_is_square(const digit_t* a) {
    return (bool) modqr(NULL, a);
}

void fp_sqrt(digit_t* a) {
    modsqrt(a, NULL, a);
}

void fp_exp3div4(digit_t* out, const digit_t* a) {
    modpro(a, out);
}

void fp_tomont(digit_t* out, const digit_t* a) {
    nres(a, out);
}

void fp_frommont(digit_t* out, const digit_t* a) {
    redc(a, out);
}

void fp_mont_setone(digit_t* out) {
    modone(out);
}

void fp_to_digit_array(digit_t* out, const digit_t* a) {
    digit_t x[NWORDS_FIELD];
    modcpy(a, x);
    for (int i = 0; i < NWORDS_ORDER; i++) {
        out[i] = 0;
    }
    for (int i = 0; i < 63; i++) {
        ((char *) out)[i] = x[0] & 0xff;
        modshr(8, x);
    }
}

void fp_from_digit_array(digit_t* out, const digit_t* a) {
    for (int i = 0; i < NWORDS_FIELD; i++) {
        out[i] = 0;
    }
    for (int i = 62; i >= 0; i--) {
        modshl(8, out);
        out[0] += (digit_t)((unsigned char *) a)[i];
    }
}

#define LIMB 56
#include "../../generic/bn.inc"
#include "../../generic/inversion.inc"
#include "../../generic/symbol.inc"

#endif
