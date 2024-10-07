#if defined(PQM4)

#include <stdint.h>
#include <stddef.h>

#include <stdbool.h>
#include <fp.h>

#define UMULL(rdlo, rdhi, rn, rm) asm volatile("umull %0, %1, %2, %3" : "=r"(rdlo), "=r"(rdhi) : "r"(rn), "r"(rm))
#define UMAAL(rdlo, rdhi, rn, rm) asm volatile("umaal %0, %1, %2, %3" : "+r"(rdlo), "+r"(rdhi) : "r"(rn), "r"(rm))
#define ADDS(rt, r1, r2) asm volatile("adds %0, %1, %2" : "+r"(rt) : "r"(r1), "r" (r2))
#define ADCS(rt, r1, r2) asm volatile("adcs %0, %1, %2" : "+r"(rt) : "r"(r1), "r" (r2))

#define spint uint32_t

static void modfsb_MFP47441_ct(spint *a) {
    const spint p[12] = {4294967295, 4294967295, 4294967295, 1281455297, 896443496, 3340957289, 2427369297, 1706831370, 1171327702, 3333316682, 2869457314, 64974574};
    uint32_t t0, t1, t2, t3;
    uint32_t tmpvec[12];
    asm volatile(
        "ldrd %[t0], %[t1], [%[a]]\n"
        "ldrd %[t2], %[t3], [%[p]]\n"
        "subs %[t0], %[t0], %[t2]\n"
        "sbcs %[t1], %[t1], %[t3]\n"
        "strd %[t0], %[t1], [%[tmpvec]]\n"
        "ldrd %[t0], %[t1], [%[a], #8]\n"
        "ldrd %[t2], %[t3], [%[p], #8]\n"
        "sbcs %[t0], %[t0], %[t2]\n"
        "sbcs %[t1], %[t1], %[t3]\n"
        "strd %[t0], %[t1], [%[tmpvec], #8]\n"
        "ldrd %[t0], %[t1], [%[a], #16]\n"
        "ldrd %[t2], %[t3], [%[p], #16]\n"
        "sbcs %[t0], %[t0], %[t2]\n"
        "sbcs %[t1], %[t1], %[t3]\n"
        "strd %[t0], %[t1], [%[tmpvec], #16]\n"
        "ldrd %[t0], %[t1], [%[a], #24]\n"
        "ldrd %[t2], %[t3], [%[p], #24]\n"
        "sbcs %[t0], %[t0], %[t2]\n"
        "sbcs %[t1], %[t1], %[t3]\n"
        "strd %[t0], %[t1], [%[tmpvec], #24]\n"
        "ldrd %[t0], %[t1], [%[a], #32]\n"
        "ldrd %[t2], %[t3], [%[p], #32]\n"
        "sbcs %[t0], %[t0], %[t2]\n"
        "sbcs %[t1], %[t1], %[t3]\n"
        "strd %[t0], %[t1], [%[tmpvec], #32]\n"
        "ldrd %[t0], %[t1], [%[a], #40]\n"
        "ldrd %[t2], %[t3], [%[p], #40]\n"
        "sbcs %[t0], %[t0], %[t2]\n"
        "sbcs %[t1], %[t1], %[t3]\n"
        "strd %[t0], %[t1], [%[tmpvec], #40]\n"
        "itttt cs\n"
        "ldrdcs %[t0], %[t1], [%[tmpvec], #0]\n"
        "ldrdcs %[t2], %[t3], [%[tmpvec], #8]\n"
        "strdcs %[t0], %[t1], [%[a], #0]\n"
        "strdcs %[t2], %[t3], [%[a], #8]\n"
        "itttt cs\n"
        "ldrdcs %[t0], %[t1], [%[tmpvec], #16]\n"
        "ldrdcs %[t2], %[t3], [%[tmpvec], #24]\n"
        "strdcs %[t0], %[t1], [%[a], #16]\n"
        "strdcs %[t2], %[t3], [%[a], #24]\n"
        "itttt cs\n"
        "ldrdcs %[t0], %[t1], [%[tmpvec], #32]\n"
        "ldrdcs %[t2], %[t3], [%[tmpvec], #40]\n"
        "strdcs %[t0], %[t1], [%[a], #32]\n"
        "strdcs %[t2], %[t3], [%[a], #40]\n"
        : [t0] "=&r" (t0), [t1] "=&r" (t1), [t2] "=&r" (t2), [t3] "=&r" (t3)
        : [a] "r" (a), [p] "r" (p), [tmpvec] "r" (tmpvec)
        : "cc", "memory");
}

static void modadd_MFP47441_ct(const spint *a, const spint *b, spint *res) {
    spint a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4], a5 = a[5], a6 = a[6], a7 = a[7], a8 = a[8], a9 = a[9], a10 = a[10], a11 = a[11];
    spint b0 = b[0], b1 = b[1], b2 = b[2], b3 = b[3], b4 = b[4], b5 = b[5], b6 = b[6], b7 = b[7], b8 = b[8], b9 = b[9], b10 = b[10], b11 = b[11];
    spint of = 0;
    spint nof[12];
    spint t = 0;
    const spint p0 = 4294967295;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 1281455297;
    const spint p4 = 896443496;
    const spint p5 = 3340957289;
    const spint p6 = 2427369297;
    const spint p7 = 1706831370;
    const spint p8 = 1171327702;
    const spint p9 = 3333316682;
    const spint p10 = 2869457314;
    const spint p11 = 64974574;
    UMAAL(a0, t, 1, b0);
    UMAAL(a1, t, 1, b1);
    UMAAL(a2, t, 1, b2);
    UMAAL(a3, t, 1, b3);
    UMAAL(a4, t, 1, b4);
    UMAAL(a5, t, 1, b5);
    UMAAL(a6, t, 1, b6);
    UMAAL(a7, t, 1, b7);
    UMAAL(a8, t, 1, b8);
    UMAAL(a9, t, 1, b9);
    UMAAL(a10, t, 1, b10);
    UMAAL(a11, t, 1, b11);
    of = t;
    res[0] = a0;
    res[1] = a1;
    res[2] = a2;
    res[3] = a3;
    res[4] = a4;
    res[5] = a5;
    res[6] = a6;
    res[7] = a7;
    res[8] = a8;
    res[9] = a9;
    res[10] = a10;
    res[11] = a11;
    spint sub = (of | (res[11] > p11));
    nof[0] = (res[0] - p0 > res[0]) & sub;
    nof[1] = (res[1] - p1 - nof[0] >= res[1]) & sub;
    nof[2] = (res[2] - p2 - nof[1] >= res[2]) & sub;
    nof[3] = (res[3] - p3 - nof[2] >= res[3]) & sub;
    nof[4] = (res[4] - p4 - nof[3] >= res[4]) & sub;
    nof[5] = (res[5] - p5 - nof[4] >= res[5]) & sub;
    nof[6] = (res[6] - p6 - nof[5] >= res[6]) & sub;
    nof[7] = (res[7] - p7 - nof[6] >= res[7]) & sub;
    nof[8] = (res[8] - p8 - nof[7] >= res[8]) & sub;
    nof[9] = (res[9] - p9 - nof[8] >= res[9]) & sub;
    nof[10] = (res[10] - p10 - nof[9] >= res[10]) & sub;
    nof[11] = (res[11] - p11 - nof[10] >= res[11]) & sub;
    res[0] = res[0] - p0*sub;
    res[1] = res[1] - p1*sub - nof[0];
    res[2] = res[2] - p2*sub - nof[1];
    res[3] = res[3] - p3*sub - nof[2];
    res[4] = res[4] - p4*sub - nof[3];
    res[5] = res[5] - p5*sub - nof[4];
    res[6] = res[6] - p6*sub - nof[5];
    res[7] = res[7] - p7*sub - nof[6];
    res[8] = res[8] - p8*sub - nof[7];
    res[9] = res[9] - p9*sub - nof[8];
    res[10] = res[10] - p10*sub - nof[9];
    res[11] = res[11] - p11*sub - nof[10];
}

static void modsub_MFP47441_ct(const spint *a, const spint *b, spint *res) {
    spint a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4], a5 = a[5], a6 = a[6], a7 = a[7], a8 = a[8], a9 = a[9], a10 = a[10], a11 = a[11];
    spint t, t1, t2;
    spint t3, t4;
    const spint p0 = 4294967295;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 1281455297;
    const spint p4 = 896443496;
    const spint p5 = 3340957289;
    const spint p6 = 2427369297;
    const spint p7 = 1706831370;
    const spint p8 = 1171327702;
    const spint p9 = 3333316682;
    const spint p10 = 2869457314;
    const spint p11 = 64974574;
    asm volatile(
        "mov %[t], #0\n"
        "ldrd %[t1], %[t2], [%[b]]\n"
        "ldrd %[t3], %[t4], [%[a]]\n"
        "subs %[t3], %[t3], %[t1]\n"
        "sbcs %[t4], %[t4], %[t2]\n"
        "strd %[t3], %[t4], [%[res]]\n"
        "ldrd %[t1], %[t2], [%[b], #8]\n"
        "ldrd %[t3], %[t4], [%[a], #8]\n"
        "sbcs %[t3], %[t3], %[t1]\n"
        "sbcs %[t4], %[t4], %[t2]\n"
        "strd %[t3], %[t4], [%[res], #8]\n"
        "ldrd %[t1], %[t2], [%[b], #16]\n"
        "ldrd %[t3], %[t4], [%[a], #16]\n"
        "sbcs %[t3], %[t3], %[t1]\n"
        "sbcs %[t4], %[t4], %[t2]\n"
        "strd %[t3], %[t4], [%[res], #16]\n"
        "ldrd %[t1], %[t2], [%[b], #24]\n"
        "ldrd %[t3], %[t4], [%[a], #24]\n"
        "sbcs %[t3], %[t3], %[t1]\n"
        "sbcs %[t4], %[t4], %[t2]\n"
        "strd %[t3], %[t4], [%[res], #24]\n"
        "ldrd %[t1], %[t2], [%[b], #32]\n"
        "ldrd %[t3], %[t4], [%[a], #32]\n"
        "sbcs %[t3], %[t3], %[t1]\n"
        "sbcs %[t4], %[t4], %[t2]\n"
        "strd %[t3], %[t4], [%[res], #32]\n"
        "ldrd %[t1], %[t2], [%[b], #40]\n"
        "ldrd %[t3], %[t4], [%[a], #40]\n"
        "sbcs %[t3], %[t3], %[t1]\n"
        "sbcs %[t4], %[t4], %[t2]\n"
        "strd %[t3], %[t4], [%[res], #40]\n"
        "sbcs %[t], %[t], %[t]\n"
        : [t] "=&r" (t), [t1] "=&r" (t1), [t2] "=&r" (t2), [t3] "=&r" (t3), [t4] "=&r" (t4)
        : [b] "r" (b), [a] "r" (a), [res] "r" (res)
        : "cc", "memory");
    t = -t | (res[11] > p11);
    t2 = 0;
    a0 = res[0];
    a1 = res[1];
    a2 = res[2];
    a3 = res[3];
    a4 = res[4];
    a5 = res[5];
    a6 = res[6];
    a7 = res[7];
    a8 = res[8];
    a9 = res[9];
    a10 = res[10];
    a11 = res[11];
    UMAAL(a0, t2, t, p0);
    UMAAL(a1, t2, t, p1);
    UMAAL(a2, t2, t, p2);
    UMAAL(a3, t2, t, p3);
    UMAAL(a4, t2, t, p4);
    UMAAL(a5, t2, t, p5);
    UMAAL(a6, t2, t, p6);
    UMAAL(a7, t2, t, p7);
    UMAAL(a8, t2, t, p8);
    UMAAL(a9, t2, t, p9);
    UMAAL(a10, t2, t, p10);
    UMAAL(a11, t2, t, p11);
    res[0] = a0;
    res[1] = a1;
    res[2] = a2;
    res[3] = a3;
    res[4] = a4;
    res[5] = a5;
    res[6] = a6;
    res[7] = a7;
    res[8] = a8;
    res[9] = a9;
    res[10] = a10;
    res[11] = a11;
}

static void modneg_MFP47441_ct(const spint *a, spint *r) {
    spint zero[12] = {0};
    modsub_MFP47441_ct(zero,a,r);
}
    
static void mul_MFP47441_ct(const spint *p, const spint *q, spint *r) {
    spint t0, t1, t2, t3, t4, a, b0, b1, b2, b3;
    b0 = q[0];
    b1 = q[1];
    b2 = q[2];
    b3 = q[3];
    asm volatile(
        ".align 4 \n"
        "mov.w  %[t1], #0 \n"
        "mov.w  %[t2], #0 \n"
        "mov.w  %[t3], #0 \n"
        "ldr.w   %[a], [%[p], #0] \n"
        "umull  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#4] \n"
        "str.w  %[t0], [%[r],#0] \n"
        "mov.w  %[t0], #0 \n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#8] \n"
        "str.w  %[t1], [%[r],#4] \n"
        "mov.w  %[t1], #0 \n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#12] \n"
        "str.w  %[t2], [%[r],#8] \n"
        "mov.w  %[t2], #0 \n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#16] \n"
        "str.w  %[t3], [%[r],#12] \n"
        "mov.w  %[t3], #0 \n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#20] \n"
        "str.w  %[t4], [%[r],#16] \n"
        "mov.w  %[t4], #0 \n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#24] \n"
        "str.w  %[t0], [%[r],#20] \n"
        "mov.w  %[t0], #0 \n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#28] \n"
        "str.w  %[t1], [%[r],#24] \n"
        "mov.w  %[t1], #0 \n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#32] \n"
        "str.w  %[t2], [%[r],#28] \n"
        "mov.w  %[t2], #0 \n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#36] \n"
        "str.w  %[t3], [%[r],#32] \n"
        "mov.w  %[t3], #0 \n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#40] \n"
        "str.w  %[t4], [%[r],#36] \n"
        "mov.w  %[t4], #0 \n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#44] \n"
        "str.w  %[t0], [%[r],#40] \n"
        "mov.w  %[t0], #0 \n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "str.w  %[t1], [%[r],#44] \n"
        "str.w  %[t2], [%[r],#48] \n"
        "str.w  %[t3], [%[r],#52] \n"
        "str.w  %[t4], [%[r],#56] \n"
        "str.w  %[t0], [%[r],#60] \n"
        : [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [t0] "=&r"(t0), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = q[4]; b1 = q[5]; b2 = q[6]; b3 = q[7];
    t0 = r[4]; t1 = r[5]; t2 = r[6]; t3 = r[7]; t4 = 0;
    asm volatile(
        ".align 4 \n"
        "ldr.w   %[a], [%[p],#0] \n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#32] \n"
        "str.w  %[t0], [%[r],#16] \n"
        "mov.w  %[t0], #0 \n"
        "adds.w %[t4], %[t4], %[a] \n"
        "ldr.w   %[a], [%[p],#4] \n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#36] \n"
        "str.w  %[t1], [%[r],#20] \n"
        "mov.w  %[t1], #0 \n"
        "adcs.w %[t0], %[t0], %[a] \n"
        "ldr.w   %[a], [%[p],#8] \n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#40] \n"
        "str.w  %[t2], [%[r],#24] \n"
        "mov.w  %[t2], #0 \n"
        "adcs.w %[t1], %[t1], %[a] \n"
        "ldr.w   %[a], [%[p],#12] \n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#44] \n"
        "str.w  %[t3], [%[r],#28] \n"
        "mov.w  %[t3], #0 \n"
        "adcs.w %[t2], %[t2], %[a] \n"
        "ldr.w   %[a], [%[p],#16] \n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#48] \n"
        "str.w  %[t4], [%[r],#32] \n"
        "mov.w  %[t4], #0 \n"
        "adcs.w %[t3], %[t3], %[a] \n"
        "ldr.w   %[a], [%[p],#20] \n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#52] \n"
        "str.w  %[t0], [%[r],#36] \n"
        "mov.w  %[t0], #0 \n"
        "adcs.w %[t4], %[t4], %[a] \n"
        "ldr.w   %[a], [%[p],#24] \n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#56] \n"
        "str.w  %[t1], [%[r],#40] \n"
        "mov.w  %[t1], #0 \n"
        "adcs.w %[t0], %[t0], %[a] \n"
        "ldr.w   %[a], [%[p],#28] \n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#60] \n"
        "str.w  %[t2], [%[r],#44] \n"
        "mov.w  %[t2], #0 \n"
        "adcs.w %[t1], %[t1], %[a] \n"
        "ldr.w   %[a], [%[p],#32] \n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#36] \n"
        "str.w  %[t3], [%[r],#48] \n"
        "mov.w  %[t3], #0 \n"
#ifdef __clang__
        "adcs   %[t2], %[t2], #0\n"
#else
        "adcs.w %[t2], %[t2], #0\n"
#endif
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#40] \n"
        "str.w  %[t4], [%[r],#52] \n"
        "mov.w  %[t4], #0 \n"
#ifdef __clang__
        "adcs   %[t3], %[t3], #0\n"
#else
        "adcs.w %[t3], %[t3], #0\n"
#endif
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#44] \n"
        "str.w  %[t0], [%[r],#56] \n"
        "mov.w  %[t0], #0 \n"
#ifdef __clang__
        "adcs   %[t4], %[t4], #0\n"
#else
        "adcs.w %[t4], %[t4], #0\n"
#endif
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
#ifdef __clang__
        "adcs   %[t0], %[t0], #0 \n"
#else
        "adcs.w %[t0], %[t0], #0 \n"
#endif
        "str.w  %[t1], [%[r],#60] \n"
        "str.w  %[t2], [%[r],#64] \n"
        "str.w  %[t3], [%[r],#68] \n"
        "str.w  %[t4], [%[r],#72] \n"
        "str.w  %[t0], [%[r],#76] \n"
        "mov.w  %[t1], #0 \n"
#ifdef __clang__
        "adcs   %[t1], %[t1], #0 \n"
#else
        "adcs.w %[t1], %[t1], #0 \n"
#endif
        "str.w  %[t1], [%[r],#80] \n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = q[8]; b1 = q[9]; b2 = q[10]; b3 = q[11];
    t0 = r[8]; t1 = r[9]; t2 = r[10]; t3 = r[11]; t4 = 0;
    asm volatile(
        ".align 4 \n"
        "ldr.w   %[a], [%[p],#0] \n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#48] \n"
        "str.w  %[t0], [%[r],#32] \n"
        "mov.w  %[t0], #0 \n"
        "adds.w %[t4], %[t4], %[a] \n"
        "ldr.w   %[a], [%[p],#4] \n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#52] \n"
        "str.w  %[t1], [%[r],#36] \n"
        "mov.w  %[t1], #0 \n"
        "adcs.w %[t0], %[t0], %[a] \n"
        "ldr.w   %[a], [%[p],#8] \n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#56] \n"
        "str.w  %[t2], [%[r],#40] \n"
        "mov.w  %[t2], #0 \n"
        "adcs.w %[t1], %[t1], %[a] \n"
        "ldr.w   %[a], [%[p],#12] \n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#60] \n"
        "str.w  %[t3], [%[r],#44] \n"
        "mov.w  %[t3], #0 \n"
        "adcs.w %[t2], %[t2], %[a] \n"
        "ldr.w   %[a], [%[p],#16] \n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#64] \n"
        "str.w  %[t4], [%[r],#48] \n"
        "mov.w  %[t4], #0 \n"
        "adcs.w %[t3], %[t3], %[a] \n"
        "ldr.w   %[a], [%[p],#20] \n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#68] \n"
        "str.w  %[t0], [%[r],#52] \n"
        "mov.w  %[t0], #0 \n"
        "adcs.w %[t4], %[t4], %[a] \n"
        "ldr.w   %[a], [%[p],#24] \n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#72] \n"
        "str.w  %[t1], [%[r],#56] \n"
        "mov.w  %[t1], #0 \n"
        "adcs.w %[t0], %[t0], %[a] \n"
        "ldr.w   %[a], [%[p],#28] \n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#76] \n"
        "str.w  %[t2], [%[r],#60] \n"
        "mov.w  %[t2], #0 \n"
        "adcs.w %[t1], %[t1], %[a] \n"
        "ldr.w   %[a], [%[p],#32] \n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#80] \n"
        "str.w  %[t3], [%[r],#64] \n"
        "mov.w  %[t3], #0 \n"
        "adcs.w %[t2], %[t2], %[a] \n"
        "ldr.w   %[a], [%[p],#36] \n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#40] \n"
        "str.w  %[t4], [%[r],#68] \n"
        "mov.w  %[t4], #0 \n"
#ifdef __clang__
        "adcs   %[t3], %[t3], #0\n"
#else
        "adcs.w %[t3], %[t3], #0\n"
#endif
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#44] \n"
        "str.w  %[t0], [%[r],#72] \n"
        "mov.w  %[t0], #0 \n"
#ifdef __clang__
        "adcs   %[t4], %[t4], #0\n"
#else
        "adcs.w %[t4], %[t4], #0\n"
#endif
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
#ifdef __clang__
        "adcs   %[t0], %[t0], #0 \n"
#else
        "adcs.w %[t0], %[t0], #0 \n"
#endif
        "str.w  %[t1], [%[r],#76] \n"
        "str.w  %[t2], [%[r],#80] \n"
        "str.w  %[t3], [%[r],#84] \n"
        "str.w  %[t4], [%[r],#88] \n"
        "str.w  %[t0], [%[r],#92] \n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}

static void sqr_MFP47441_ct(const spint *p, spint *r) {
    spint t0, t1, t2, t3, t4, a, b0, b1, b2, b3;
    b0 = p[0];
    b1 = p[1];
    b2 = p[2];
    b3 = p[3];
    asm volatile(
        ".align 4 \n"
        "mov.w  %[t2], #0 \n"
        "mov.w  %[t3], #0 \n"
        "mov.w  %[t4], #0 \n"
        "umull  %[t0], %[t1], %[b0], %[b1]\n"
        "str.w  %[t0], [%[r],#4 ] \n"
        "mov.w  %[t0], #0 \n"
        "umaal  %[t1], %[t3], %[b0], %[b2]\n"
        "umaal  %[t2], %[t3], %[b1], %[b2]\n"
        "str.w  %[t1], [%[r],#8 ] \n"
        "mov.w  %[t1], #0 \n"
        "umaal  %[t2], %[t0], %[b0], %[b3]\n"
        "umaal  %[t3], %[t0], %[b1], %[b3]\n"
        "umaal  %[t4], %[t0], %[b2], %[b3]\n"
        "str.w  %[t2], [%[r],#12 ] \n"
        "mov.w  %[t2], #0 \n"
        "ldr.w   %[a], [%[p], #16] \n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#20] \n"
        "str.w  %[t3], [%[r],#16] \n"
        "mov.w  %[t3], #0 \n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#24] \n"
        "str.w  %[t4], [%[r],#20] \n"
        "mov.w  %[t4], #0 \n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#28] \n"
        "str.w  %[t0], [%[r],#24] \n"
        "mov.w  %[t0], #0 \n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#32] \n"
        "str.w  %[t1], [%[r],#28] \n"
        "mov.w  %[t1], #0 \n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#36] \n"
        "str.w  %[t2], [%[r],#32] \n"
        "mov.w  %[t2], #0 \n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#40] \n"
        "str.w  %[t3], [%[r],#36] \n"
        "mov.w  %[t3], #0 \n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#44] \n"
        "str.w  %[t4], [%[r],#40] \n"
        "mov.w  %[t4], #0 \n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "str.w  %[t0], [%[r],#44] \n"
        "str.w  %[t1], [%[r],#48] \n"
        "str.w  %[t2], [%[r],#52] \n"
        "str.w  %[t3], [%[r],#56] \n"
        "str.w  %[t4], [%[r],#60] \n"
        : [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = p[4]; b1 = p[5]; b2 = p[6]; b3 = p[7];
    t0 = r[9]; t1 = r[10]; t2 = r[11]; t3 = r[12]; t4 = r[13];
    asm volatile(
        ".align 4 \n"
        "mov.w  %[a], #0 \n"
        "umaal  %[t0], %[a], %[b0], %[b1]\n"
        "str.w  %[t0], [%[r],#36 ] \n"
        "mov.w  %[t0], #0 \n"
        "umaal  %[t1], %[a], %[b0], %[b2]\n"
        "umaal  %[t2], %[a], %[b1], %[b2]\n"
        "str.w  %[t1], [%[r],#40 ] \n"
        "mov.w  %[t1], #0 \n"
        "adds.w %[t3], %[t3], %[a] \n"
        "mov.w  %[a], #0 \n"
#ifdef __clang__
        "adcs   %[t4], %[t4], #0 \n"
#else
        "adcs.w %[t4], %[t4], #0 \n"
#endif
        "umaal  %[t2], %[a], %[b0], %[b3]\n"
        "umaal  %[t3], %[a], %[b1], %[b3]\n"
        "umaal  %[t4], %[a], %[b2], %[b3]\n"
        "ldr.w  %[t0], [%[r],#56] \n"
        "ldr.w  %[t1], [%[r],#60] \n"
        "str.w  %[t2], [%[r],#44 ] \n"
        "mov.w  %[t2], #0 \n"
#ifdef __clang__
        "adcs   %[t0], %[t0], %[a] \n"
        "adcs   %[t1], %[t1], #0 \n"
#else
        "adcs.w %[t0], %[t0], %[a] \n"
        "adcs.w %[t1], %[t1], #0 \n"
#endif
        "ldr.w   %[a], [%[p],#32] \n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#36] \n"
        "str.w  %[t3], [%[r],#48] \n"
        "mov.w  %[t3], #0 \n"
#ifdef __clang__
        "adcs   %[t2], %[t2], #0\n"
#else
        "adcs.w %[t2], %[t2], #0\n"
#endif
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#40] \n"
        "str.w  %[t4], [%[r],#52] \n"
        "mov.w  %[t4], #0 \n"
#ifdef __clang__
        "adcs   %[t3], %[t3], #0\n"
#else
        "adcs.w %[t3], %[t3], #0\n"
#endif
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#44] \n"
        "str.w  %[t0], [%[r],#56] \n"
        "mov.w  %[t0], #0 \n"
#ifdef __clang__
        "adcs   %[t4], %[t4], #0\n"
#else
        "adcs.w %[t4], %[t4], #0\n"
#endif
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
#ifdef __clang__
        "adcs   %[t0], %[t0], #0 \n"
#else
        "adcs.w %[t0], %[t0], #0 \n"
#endif
        "str.w  %[t1], [%[r],#60] \n"
        "str.w  %[t2], [%[r],#64] \n"
        "str.w  %[t3], [%[r],#68] \n"
        "str.w  %[t4], [%[r],#72] \n"
        "str.w  %[t0], [%[r],#76] \n"
        "mov.w  %[t1], #0 \n"
#ifdef __clang__
        "adcs   %[t1], %[t1], #0 \n"
#else
        "adcs.w %[t1], %[t1], #0 \n"
#endif
        "str.w  %[t1], [%[r],#80] \n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = p[8]; b1 = p[9]; b2 = p[10]; b3 = p[11];
    t0 = r[17]; t1 = r[18]; t2 = r[19]; t3 = 0; t4 = 0;
    asm volatile(
        ".align 4 \n"
        "mov.w  %[a], #0 \n"
        "umaal  %[t0], %[t4], %[b0], %[b1]\n"
        "str.w  %[t0], [%[r],#68 ] \n"
        "mov.w  %[t0], #0 \n"
        "umaal  %[t1], %[t4], %[b0], %[b2]\n"
        "umaal  %[t2], %[t4], %[b1], %[b2]\n"
        "umaal  %[t2], %[t0], %[b0], %[b3]\n"
        "umaal  %[t3], %[t0], %[b1], %[b3]\n"
        "umaal  %[t3], %[t4], %[a],  %[a] \n"
        "umaal  %[t4], %[t0], %[b2], %[b3]\n"
        "str.w  %[t1], [%[r],#72 ] \n"
        "str.w  %[t2], [%[r],#76 ] \n"
        "str.w  %[t3], [%[r],#80 ] \n"
        "str.w  %[t4], [%[r],#84 ] \n"
        "str.w  %[t0], [%[r],#88 ] \n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [r] "r"(r)
        : "cc", "memory");
    r[0] = 0; r[23]=0;
    asm volatile(
        ".align 4 \n"
        "mov.w  %[a], #2 \n"
        "mov.w  %[t4], #0 \n"
        "ldr.w   %[b0], [%[p],#0] \n"
        "ldr.w   %[b1], [%[p],#4] \n"
        "umull  %[t0], %[t1], %[b0], %[b0]\n"
        "umull  %[t2], %[t3], %[b1], %[b1]\n"
        "ldr.w   %[b0], [%[r],#0] \n"
        "ldr.w   %[b1], [%[r],#4] \n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "ldr.w   %[b0], [%[r],#8] \n"
        "ldr.w   %[b1], [%[r],#12] \n"
        "str.w  %[t0], [%[r],#0 ] \n"
        "str.w  %[t1], [%[r],#4 ] \n"
        "umaal  %[t2], %[t4], %[a], %[b0]\n"
        "umaal  %[t3], %[t4], %[a], %[b1]\n"
        "str.w  %[t2], [%[r],#8 ] \n"
        "str.w  %[t3], [%[r],#12 ] \n"
        "ldr.w   %[b2], [%[p],#8] \n"
        "ldr.w   %[b3], [%[p],#12] \n"
        "umull  %[t0], %[t1], %[b2], %[b2]\n"
        "umull  %[t2], %[t3], %[b3], %[b3]\n"
        "ldr.w   %[b2], [%[r],#16] \n"
        "ldr.w   %[b3], [%[r],#20] \n"
        "umaal  %[t0], %[t4], %[a], %[b2]\n"
        "umaal  %[t1], %[t4], %[a], %[b3]\n"
        "ldr.w   %[b2], [%[r],#24] \n"
        "ldr.w   %[b3], [%[r],#28] \n"
        "str.w  %[t0], [%[r],#16 ] \n"
        "str.w  %[t1], [%[r],#20 ] \n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "str.w  %[t2], [%[r],#24 ] \n"
        "str.w  %[t3], [%[r],#28 ] \n"
        "ldr.w   %[b0], [%[p],#16] \n"
        "ldr.w   %[b1], [%[p],#20] \n"
        "umull  %[t0], %[t1], %[b0], %[b0]\n"
        "umull  %[t2], %[t3], %[b1], %[b1]\n"
        "ldr.w   %[b0], [%[r],#32] \n"
        "ldr.w   %[b1], [%[r],#36] \n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "ldr.w   %[b0], [%[r],#40] \n"
        "ldr.w   %[b1], [%[r],#44] \n"
        "str.w  %[t0], [%[r],#32 ] \n"
        "str.w  %[t1], [%[r],#36 ] \n"
        "umaal  %[t2], %[t4], %[a], %[b0]\n"
        "umaal  %[t3], %[t4], %[a], %[b1]\n"
        "str.w  %[t2], [%[r],#40 ] \n"
        "str.w  %[t3], [%[r],#44 ] \n"
        "ldr.w   %[b2], [%[p],#24] \n"
        "ldr.w   %[b3], [%[p],#28] \n"
        "umull  %[t0], %[t1], %[b2], %[b2]\n"
        "umull  %[t2], %[t3], %[b3], %[b3]\n"
        "ldr.w   %[b2], [%[r],#48] \n"
        "ldr.w   %[b3], [%[r],#52] \n"
        "umaal  %[t0], %[t4], %[a], %[b2]\n"
        "umaal  %[t1], %[t4], %[a], %[b3]\n"
        "ldr.w   %[b2], [%[r],#56] \n"
        "ldr.w   %[b3], [%[r],#60] \n"
        "str.w  %[t0], [%[r],#48 ] \n"
        "str.w  %[t1], [%[r],#52 ] \n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "str.w  %[t2], [%[r],#56 ] \n"
        "str.w  %[t3], [%[r],#60 ] \n"
        "ldr.w   %[b0], [%[p],#32] \n"
        "ldr.w   %[b1], [%[p],#36] \n"
        "umull  %[t0], %[t1], %[b0], %[b0]\n"
        "umull  %[t2], %[t3], %[b1], %[b1]\n"
        "ldr.w   %[b0], [%[r],#64] \n"
        "ldr.w   %[b1], [%[r],#68] \n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "ldr.w   %[b0], [%[r],#72] \n"
        "ldr.w   %[b1], [%[r],#76] \n"
        "str.w  %[t0], [%[r],#64 ] \n"
        "str.w  %[t1], [%[r],#68 ] \n"
        "umaal  %[t2], %[t4], %[a], %[b0]\n"
        "umaal  %[t3], %[t4], %[a], %[b1]\n"
        "str.w  %[t2], [%[r],#72 ] \n"
        "str.w  %[t3], [%[r],#76 ] \n"
        "ldr.w   %[b2], [%[p],#40] \n"
        "ldr.w   %[b3], [%[p],#44] \n"
        "umull  %[t0], %[t1], %[b2], %[b2]\n"
        "umull  %[t2], %[t3], %[b3], %[b3]\n"
        "ldr.w   %[b2], [%[r],#80] \n"
        "ldr.w   %[b3], [%[r],#84] \n"
        "umaal  %[t0], %[t4], %[a], %[b2]\n"
        "umaal  %[t1], %[t4], %[a], %[b3]\n"
        "ldr.w   %[b2], [%[r],#88] \n"
        "ldr.w   %[b3], [%[r],#92] \n"
        "str.w  %[t0], [%[r],#80 ] \n"
        "str.w  %[t1], [%[r],#84 ] \n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "str.w  %[t2], [%[r],#88 ] \n"
        "str.w  %[t3], [%[r],#92 ] \n"
        : [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [a] "=&r"(a),
          [b0] "=&r"(b0), [b1] "=&r"(b1), [b2] "=&r"(b2), [b3] "=&r"(b3)
        : [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}

static void mli_MFP47441_ct(const spint *p, const spint q, spint *r) {
    spint b, t0, t1, t2, t3, t4, t5, t6, t7, t8;
    b = q-1;
    t8 = 0;
    t0 = p[0];
    t1 = p[1];
    t2 = p[2];
    t3 = p[3];
    UMAAL(t0, t8, t0, b);
    UMAAL(t1, t8, t1, b);
    UMAAL(t2, t8, t2, b);
    UMAAL(t3, t8, t3, b);
    r[0] = t0;
    r[1] = t1;
    r[2] = t2;
    r[3] = t3;
    t0 = p[4];
    t1 = p[5];
    t2 = p[6];
    t3 = p[7];
    t4 = p[8];
    t5 = p[9];
    t6 = p[10];
    t7 = p[11];
    UMAAL(t0, t8, t0, b);
    UMAAL(t1, t8, t1, b);
    UMAAL(t2, t8, t2, b);
    UMAAL(t3, t8, t3, b);
    UMAAL(t4, t8, t4, b);
    UMAAL(t5, t8, t5, b);
    UMAAL(t6, t8, t6, b);
    UMAAL(t7, t8, t7, b);
    r[4] = t0;
    r[5] = t1;
    r[6] = t2;
    r[7] = t3;
    r[8] = t4;
    r[9] = t5;
    r[10] = t6;
    r[11] = t7;
    r[12] = t8;
}

static void modmul_MFP47441_ct(const spint *a, const spint *b, spint *res) {
    spint A[24];
    spint A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23;
    const spint p3 = 1281455297;
    const spint p4 = 896443496;
    const spint p5 = 3340957289;
    const spint p6 = 2427369297;
    const spint p7 = 1706831370;
    const spint p8 = 1171327702;
    const spint p9 = 3333316682;
    const spint p10 = 2869457314;
    const spint p11 = 64974574;
    spint q, t, t2 = 0;

    mul_MFP47441_ct(a, b, A);

    A0 = A[0];
    A1 = A[1];
    A2 = A[2];
    A3 = A[3];
    A4 = A[4];
    A5 = A[5];
    A6 = A[6];
    A7 = A[7];
    A8 = A[8];
    A9 = A[9];
    A10 = A[10];
    A11 = A[11];
    A12 = A[12];
    A13 = A[13];
    A14 = A[14];
    A15 = A[15];
    A16 = A[16];
    A17 = A[17];
    A18 = A[18];
    A19 = A[19];
    A20 = A[20];
    A21 = A[21];
    A22 = A[22];
    A23 = A[23];

    q = A0;
    t = 0;
    UMAAL(A3, t, q, p3 + 1);
    UMAAL(A4, t, q, p4);
    UMAAL(A5, t, q, p5);
    UMAAL(A6, t, q, p6);
    UMAAL(A7, t, q, p7);
    UMAAL(A8, t, q, p8);
    UMAAL(A9, t, q, p9);
    UMAAL(A10, t, q, p10);
    UMAAL(A11, t, q, p11);
    UMAAL(A12, t2, 1, t);

    q = A1;
    t = 0;
    UMAAL(A4, t, q, p3 + 1);
    UMAAL(A5, t, q, p4);
    UMAAL(A6, t, q, p5);
    UMAAL(A7, t, q, p6);
    UMAAL(A8, t, q, p7);
    UMAAL(A9, t, q, p8);
    UMAAL(A10, t, q, p9);
    UMAAL(A11, t, q, p10);
    UMAAL(A12, t, q, p11);
    UMAAL(A13, t2, 1, t);

    q = A2;
    t = 0;
    UMAAL(A5, t, q, p3 + 1);
    UMAAL(A6, t, q, p4);
    UMAAL(A7, t, q, p5);
    UMAAL(A8, t, q, p6);
    UMAAL(A9, t, q, p7);
    UMAAL(A10, t, q, p8);
    UMAAL(A11, t, q, p9);
    UMAAL(A12, t, q, p10);
    UMAAL(A13, t, q, p11);
    UMAAL(A14, t2, 1, t);

    q = A3;
    t = 0;
    UMAAL(A6, t, q, p3 + 1);
    UMAAL(A7, t, q, p4);
    UMAAL(A8, t, q, p5);
    UMAAL(A9, t, q, p6);
    UMAAL(A10, t, q, p7);
    UMAAL(A11, t, q, p8);
    UMAAL(A12, t, q, p9);
    UMAAL(A13, t, q, p10);
    UMAAL(A14, t, q, p11);
    UMAAL(A15, t2, 1, t);

    q = A4;
    t = 0;
    UMAAL(A7, t, q, p3 + 1);
    UMAAL(A8, t, q, p4);
    UMAAL(A9, t, q, p5);
    UMAAL(A10, t, q, p6);
    UMAAL(A11, t, q, p7);
    UMAAL(A12, t, q, p8);
    UMAAL(A13, t, q, p9);
    UMAAL(A14, t, q, p10);
    UMAAL(A15, t, q, p11);
    UMAAL(A16, t2, 1, t);

    q = A5;
    t = 0;
    UMAAL(A8, t, q, p3 + 1);
    UMAAL(A9, t, q, p4);
    UMAAL(A10, t, q, p5);
    UMAAL(A11, t, q, p6);
    UMAAL(A12, t, q, p7);
    UMAAL(A13, t, q, p8);
    UMAAL(A14, t, q, p9);
    UMAAL(A15, t, q, p10);
    UMAAL(A16, t, q, p11);
    UMAAL(A17, t2, 1, t);

    q = A6;
    t = 0;
    UMAAL(A9, t, q, p3 + 1);
    UMAAL(A10, t, q, p4);
    UMAAL(A11, t, q, p5);
    UMAAL(A12, t, q, p6);
    UMAAL(A13, t, q, p7);
    UMAAL(A14, t, q, p8);
    UMAAL(A15, t, q, p9);
    UMAAL(A16, t, q, p10);
    UMAAL(A17, t, q, p11);
    UMAAL(A18, t2, 1, t);

    q = A7;
    t = 0;
    UMAAL(A10, t, q, p3 + 1);
    UMAAL(A11, t, q, p4);
    UMAAL(A12, t, q, p5);
    UMAAL(A13, t, q, p6);
    UMAAL(A14, t, q, p7);
    UMAAL(A15, t, q, p8);
    UMAAL(A16, t, q, p9);
    UMAAL(A17, t, q, p10);
    UMAAL(A18, t, q, p11);
    UMAAL(A19, t2, 1, t);

    q = A8;
    t = 0;
    UMAAL(A11, t, q, p3 + 1);
    UMAAL(A12, t, q, p4);
    UMAAL(A13, t, q, p5);
    UMAAL(A14, t, q, p6);
    UMAAL(A15, t, q, p7);
    UMAAL(A16, t, q, p8);
    UMAAL(A17, t, q, p9);
    UMAAL(A18, t, q, p10);
    UMAAL(A19, t, q, p11);
    UMAAL(A20, t2, 1, t);

    q = A9;
    t = 0;
    UMAAL(A12, t, q, p3 + 1);
    UMAAL(A13, t, q, p4);
    UMAAL(A14, t, q, p5);
    UMAAL(A15, t, q, p6);
    UMAAL(A16, t, q, p7);
    UMAAL(A17, t, q, p8);
    UMAAL(A18, t, q, p9);
    UMAAL(A19, t, q, p10);
    UMAAL(A20, t, q, p11);
    UMAAL(A21, t2, 1, t);

    q = A10;
    t = 0;
    UMAAL(A13, t, q, p3 + 1);
    UMAAL(A14, t, q, p4);
    UMAAL(A15, t, q, p5);
    UMAAL(A16, t, q, p6);
    UMAAL(A17, t, q, p7);
    UMAAL(A18, t, q, p8);
    UMAAL(A19, t, q, p9);
    UMAAL(A20, t, q, p10);
    UMAAL(A21, t, q, p11);
    UMAAL(A22, t2, 1, t);

    q = A11;
    t = 0;
    UMAAL(A14, t, q, p3 + 1);
    UMAAL(A15, t, q, p4);
    UMAAL(A16, t, q, p5);
    UMAAL(A17, t, q, p6);
    UMAAL(A18, t, q, p7);
    UMAAL(A19, t, q, p8);
    UMAAL(A20, t, q, p9);
    UMAAL(A21, t, q, p10);
    UMAAL(A22, t, q, p11);
    UMAAL(A23, t2, 1, t);

    res[0] = A12;
    res[1] = A13;
    res[2] = A14;
    res[3] = A15;
    res[4] = A16;
    res[5] = A17;
    res[6] = A18;
    res[7] = A19;
    res[8] = A20;
    res[9] = A21;
    res[10] = A22;
    res[11] = A23;
}

static void modsqr_MFP47441_ct(const spint *a, spint *res) {
    spint A[24];
    spint A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23;
    const spint p3 = 1281455297;
    const spint p4 = 896443496;
    const spint p5 = 3340957289;
    const spint p6 = 2427369297;
    const spint p7 = 1706831370;
    const spint p8 = 1171327702;
    const spint p9 = 3333316682;
    const spint p10 = 2869457314;
    const spint p11 = 64974574;
    spint q, t, t2 = 0;

    sqr_MFP47441_ct(a, A);

    A0 = A[0];
    A1 = A[1];
    A2 = A[2];
    A3 = A[3];
    A4 = A[4];
    A5 = A[5];
    A6 = A[6];
    A7 = A[7];
    A8 = A[8];
    A9 = A[9];
    A10 = A[10];
    A11 = A[11];
    A12 = A[12];
    A13 = A[13];
    A14 = A[14];
    A15 = A[15];
    A16 = A[16];
    A17 = A[17];
    A18 = A[18];
    A19 = A[19];
    A20 = A[20];
    A21 = A[21];
    A22 = A[22];
    A23 = A[23];

    q = A0;
    t = 0;
    UMAAL(A3, t, q, p3 + 1);
    UMAAL(A4, t, q, p4);
    UMAAL(A5, t, q, p5);
    UMAAL(A6, t, q, p6);
    UMAAL(A7, t, q, p7);
    UMAAL(A8, t, q, p8);
    UMAAL(A9, t, q, p9);
    UMAAL(A10, t, q, p10);
    UMAAL(A11, t, q, p11);
    UMAAL(A12, t2, 1, t);

    q = A1;
    t = 0;
    UMAAL(A4, t, q, p3 + 1);
    UMAAL(A5, t, q, p4);
    UMAAL(A6, t, q, p5);
    UMAAL(A7, t, q, p6);
    UMAAL(A8, t, q, p7);
    UMAAL(A9, t, q, p8);
    UMAAL(A10, t, q, p9);
    UMAAL(A11, t, q, p10);
    UMAAL(A12, t, q, p11);
    UMAAL(A13, t2, 1, t);

    q = A2;
    t = 0;
    UMAAL(A5, t, q, p3 + 1);
    UMAAL(A6, t, q, p4);
    UMAAL(A7, t, q, p5);
    UMAAL(A8, t, q, p6);
    UMAAL(A9, t, q, p7);
    UMAAL(A10, t, q, p8);
    UMAAL(A11, t, q, p9);
    UMAAL(A12, t, q, p10);
    UMAAL(A13, t, q, p11);
    UMAAL(A14, t2, 1, t);

    q = A3;
    t = 0;
    UMAAL(A6, t, q, p3 + 1);
    UMAAL(A7, t, q, p4);
    UMAAL(A8, t, q, p5);
    UMAAL(A9, t, q, p6);
    UMAAL(A10, t, q, p7);
    UMAAL(A11, t, q, p8);
    UMAAL(A12, t, q, p9);
    UMAAL(A13, t, q, p10);
    UMAAL(A14, t, q, p11);
    UMAAL(A15, t2, 1, t);

    q = A4;
    t = 0;
    UMAAL(A7, t, q, p3 + 1);
    UMAAL(A8, t, q, p4);
    UMAAL(A9, t, q, p5);
    UMAAL(A10, t, q, p6);
    UMAAL(A11, t, q, p7);
    UMAAL(A12, t, q, p8);
    UMAAL(A13, t, q, p9);
    UMAAL(A14, t, q, p10);
    UMAAL(A15, t, q, p11);
    UMAAL(A16, t2, 1, t);

    q = A5;
    t = 0;
    UMAAL(A8, t, q, p3 + 1);
    UMAAL(A9, t, q, p4);
    UMAAL(A10, t, q, p5);
    UMAAL(A11, t, q, p6);
    UMAAL(A12, t, q, p7);
    UMAAL(A13, t, q, p8);
    UMAAL(A14, t, q, p9);
    UMAAL(A15, t, q, p10);
    UMAAL(A16, t, q, p11);
    UMAAL(A17, t2, 1, t);

    q = A6;
    t = 0;
    UMAAL(A9, t, q, p3 + 1);
    UMAAL(A10, t, q, p4);
    UMAAL(A11, t, q, p5);
    UMAAL(A12, t, q, p6);
    UMAAL(A13, t, q, p7);
    UMAAL(A14, t, q, p8);
    UMAAL(A15, t, q, p9);
    UMAAL(A16, t, q, p10);
    UMAAL(A17, t, q, p11);
    UMAAL(A18, t2, 1, t);

    q = A7;
    t = 0;
    UMAAL(A10, t, q, p3 + 1);
    UMAAL(A11, t, q, p4);
    UMAAL(A12, t, q, p5);
    UMAAL(A13, t, q, p6);
    UMAAL(A14, t, q, p7);
    UMAAL(A15, t, q, p8);
    UMAAL(A16, t, q, p9);
    UMAAL(A17, t, q, p10);
    UMAAL(A18, t, q, p11);
    UMAAL(A19, t2, 1, t);

    q = A8;
    t = 0;
    UMAAL(A11, t, q, p3 + 1);
    UMAAL(A12, t, q, p4);
    UMAAL(A13, t, q, p5);
    UMAAL(A14, t, q, p6);
    UMAAL(A15, t, q, p7);
    UMAAL(A16, t, q, p8);
    UMAAL(A17, t, q, p9);
    UMAAL(A18, t, q, p10);
    UMAAL(A19, t, q, p11);
    UMAAL(A20, t2, 1, t);

    q = A9;
    t = 0;
    UMAAL(A12, t, q, p3 + 1);
    UMAAL(A13, t, q, p4);
    UMAAL(A14, t, q, p5);
    UMAAL(A15, t, q, p6);
    UMAAL(A16, t, q, p7);
    UMAAL(A17, t, q, p8);
    UMAAL(A18, t, q, p9);
    UMAAL(A19, t, q, p10);
    UMAAL(A20, t, q, p11);
    UMAAL(A21, t2, 1, t);

    q = A10;
    t = 0;
    UMAAL(A13, t, q, p3 + 1);
    UMAAL(A14, t, q, p4);
    UMAAL(A15, t, q, p5);
    UMAAL(A16, t, q, p6);
    UMAAL(A17, t, q, p7);
    UMAAL(A18, t, q, p8);
    UMAAL(A19, t, q, p9);
    UMAAL(A20, t, q, p10);
    UMAAL(A21, t, q, p11);
    UMAAL(A22, t2, 1, t);

    q = A11;
    t = 0;
    UMAAL(A14, t, q, p3 + 1);
    UMAAL(A15, t, q, p4);
    UMAAL(A16, t, q, p5);
    UMAAL(A17, t, q, p6);
    UMAAL(A18, t, q, p7);
    UMAAL(A19, t, q, p8);
    UMAAL(A20, t, q, p9);
    UMAAL(A21, t, q, p10);
    UMAAL(A22, t, q, p11);
    UMAAL(A23, t2, 1, t);

    res[0] = A12;
    res[1] = A13;
    res[2] = A14;
    res[3] = A15;
    res[4] = A16;
    res[5] = A17;
    res[6] = A18;
    res[7] = A19;
    res[8] = A20;
    res[9] = A21;
    res[10] = A22;
    res[11] = A23;
}

static void modmli_MFP47441_ct(const spint *a, const spint b, spint *res) {
    spint A[24];
    spint A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23;
    const spint p3 = 1281455297;
    const spint p4 = 896443496;
    const spint p5 = 3340957289;
    const spint p6 = 2427369297;
    const spint p7 = 1706831370;
    const spint p8 = 1171327702;
    const spint p9 = 3333316682;
    const spint p10 = 2869457314;
    const spint p11 = 64974574;
    spint q, t, t2 = 0;

    mli_MFP47441_ct(a, b, A);

    A0 = A[0];
    A1 = A[1];
    A2 = A[2];
    A3 = A[3];
    A4 = A[4];
    A5 = A[5];
    A6 = A[6];
    A7 = A[7];
    A8 = A[8];
    A9 = A[9];
    A10 = A[10];
    A11 = A[11];
    A12 = A[12];
    A13 = 0;
    A14 = 0;
    A15 = 0;
    A16 = 0;
    A17 = 0;
    A18 = 0;
    A19 = 0;
    A20 = 0;
    A21 = 0;
    A22 = 0;
    A23 = 0;

    q = A0;
    t = 0;
    UMAAL(A3, t, q, p3 + 1);
    UMAAL(A4, t, q, p4);
    UMAAL(A5, t, q, p5);
    UMAAL(A6, t, q, p6);
    UMAAL(A7, t, q, p7);
    UMAAL(A8, t, q, p8);
    UMAAL(A9, t, q, p9);
    UMAAL(A10, t, q, p10);
    UMAAL(A11, t, q, p11);
    UMAAL(A12, t2, 1, t);

    q = A1;
    t = 0;
    UMAAL(A4, t, q, p3 + 1);
    UMAAL(A5, t, q, p4);
    UMAAL(A6, t, q, p5);
    UMAAL(A7, t, q, p6);
    UMAAL(A8, t, q, p7);
    UMAAL(A9, t, q, p8);
    UMAAL(A10, t, q, p9);
    UMAAL(A11, t, q, p10);
    UMAAL(A12, t, q, p11);
    UMAAL(A13, t2, 1, t);

    q = A2;
    t = 0;
    UMAAL(A5, t, q, p3 + 1);
    UMAAL(A6, t, q, p4);
    UMAAL(A7, t, q, p5);
    UMAAL(A8, t, q, p6);
    UMAAL(A9, t, q, p7);
    UMAAL(A10, t, q, p8);
    UMAAL(A11, t, q, p9);
    UMAAL(A12, t, q, p10);
    UMAAL(A13, t, q, p11);
    UMAAL(A14, t2, 1, t);

    q = A3;
    t = 0;
    UMAAL(A6, t, q, p3 + 1);
    UMAAL(A7, t, q, p4);
    UMAAL(A8, t, q, p5);
    UMAAL(A9, t, q, p6);
    UMAAL(A10, t, q, p7);
    UMAAL(A11, t, q, p8);
    UMAAL(A12, t, q, p9);
    UMAAL(A13, t, q, p10);
    UMAAL(A14, t, q, p11);
    UMAAL(A15, t2, 1, t);

    q = A4;
    t = 0;
    UMAAL(A7, t, q, p3 + 1);
    UMAAL(A8, t, q, p4);
    UMAAL(A9, t, q, p5);
    UMAAL(A10, t, q, p6);
    UMAAL(A11, t, q, p7);
    UMAAL(A12, t, q, p8);
    UMAAL(A13, t, q, p9);
    UMAAL(A14, t, q, p10);
    UMAAL(A15, t, q, p11);
    UMAAL(A16, t2, 1, t);

    q = A5;
    t = 0;
    UMAAL(A8, t, q, p3 + 1);
    UMAAL(A9, t, q, p4);
    UMAAL(A10, t, q, p5);
    UMAAL(A11, t, q, p6);
    UMAAL(A12, t, q, p7);
    UMAAL(A13, t, q, p8);
    UMAAL(A14, t, q, p9);
    UMAAL(A15, t, q, p10);
    UMAAL(A16, t, q, p11);
    UMAAL(A17, t2, 1, t);

    q = A6;
    t = 0;
    UMAAL(A9, t, q, p3 + 1);
    UMAAL(A10, t, q, p4);
    UMAAL(A11, t, q, p5);
    UMAAL(A12, t, q, p6);
    UMAAL(A13, t, q, p7);
    UMAAL(A14, t, q, p8);
    UMAAL(A15, t, q, p9);
    UMAAL(A16, t, q, p10);
    UMAAL(A17, t, q, p11);
    UMAAL(A18, t2, 1, t);

    q = A7;
    t = 0;
    UMAAL(A10, t, q, p3 + 1);
    UMAAL(A11, t, q, p4);
    UMAAL(A12, t, q, p5);
    UMAAL(A13, t, q, p6);
    UMAAL(A14, t, q, p7);
    UMAAL(A15, t, q, p8);
    UMAAL(A16, t, q, p9);
    UMAAL(A17, t, q, p10);
    UMAAL(A18, t, q, p11);
    UMAAL(A19, t2, 1, t);

    q = A8;
    t = 0;
    UMAAL(A11, t, q, p3 + 1);
    UMAAL(A12, t, q, p4);
    UMAAL(A13, t, q, p5);
    UMAAL(A14, t, q, p6);
    UMAAL(A15, t, q, p7);
    UMAAL(A16, t, q, p8);
    UMAAL(A17, t, q, p9);
    UMAAL(A18, t, q, p10);
    UMAAL(A19, t, q, p11);
    UMAAL(A20, t2, 1, t);

    q = A9;
    t = 0;
    UMAAL(A12, t, q, p3 + 1);
    UMAAL(A13, t, q, p4);
    UMAAL(A14, t, q, p5);
    UMAAL(A15, t, q, p6);
    UMAAL(A16, t, q, p7);
    UMAAL(A17, t, q, p8);
    UMAAL(A18, t, q, p9);
    UMAAL(A19, t, q, p10);
    UMAAL(A20, t, q, p11);
    UMAAL(A21, t2, 1, t);

    q = A10;
    t = 0;
    UMAAL(A13, t, q, p3 + 1);
    UMAAL(A14, t, q, p4);
    UMAAL(A15, t, q, p5);
    UMAAL(A16, t, q, p6);
    UMAAL(A17, t, q, p7);
    UMAAL(A18, t, q, p8);
    UMAAL(A19, t, q, p9);
    UMAAL(A20, t, q, p10);
    UMAAL(A21, t, q, p11);
    UMAAL(A22, t2, 1, t);

    q = A11;
    t = 0;
    UMAAL(A14, t, q, p3 + 1);
    UMAAL(A15, t, q, p4);
    UMAAL(A16, t, q, p5);
    UMAAL(A17, t, q, p6);
    UMAAL(A18, t, q, p7);
    UMAAL(A19, t, q, p8);
    UMAAL(A20, t, q, p9);
    UMAAL(A21, t, q, p10);
    UMAAL(A22, t, q, p11);
    UMAAL(A23, t2, 1, t);

    res[0] = A12;
    res[1] = A13;
    res[2] = A14;
    res[3] = A15;
    res[4] = A16;
    res[5] = A17;
    res[6] = A18;
    res[7] = A19;
    res[8] = A20;
    res[9] = A21;
    res[10] = A22;
    res[11] = A23;
}

static void modcpy_MFP47441_ct(const spint *a, spint *b) {
    b[0] = a[0];
    b[1] = a[1];
    b[2] = a[2];
    b[3] = a[3];
    b[4] = a[4];
    b[5] = a[5];
    b[6] = a[6];
    b[7] = a[7];
    b[8] = a[8];
    b[9] = a[9];
    b[10] = a[10];
    b[11] = a[11];
}

static void modnsqr_MFP47441_ct(spint *a, int n) {
    for (int i = 0; i < n; i++)
        modsqr_MFP47441_ct(a, a);
}

//Calculate progenitor
static void modpro_MFP47441_ct(const spint *w,spint *z) {
	spint x[12];
	spint t0[12];
	spint t1[12];
	spint t2[12];
	spint t3[12];
	spint t4[12];
	spint t5[12];
	spint t6[12];
	spint t7[12];
	spint t8[12];
	spint t9[12];
	spint t10[12];
	spint t11[12];
	spint t12[12];
	spint t13[12];
	spint t14[12];
	spint t15[12];
	spint t16[12];
	spint t17[12];
	spint t18[12];
	spint t19[12];
	spint t20[12];
	spint t21[12];
	spint t22[12];
	spint t23[12];
	spint t24[12];
	modcpy_MFP47441_ct(w,x);
	modsqr_MFP47441_ct(x,t0);
	modmul_MFP47441_ct(x,t0,t1);
	modmul_MFP47441_ct(x,t1,t8);
	modmul_MFP47441_ct(t0,t8,t6);
	modmul_MFP47441_ct(t8,t6,t20);
	modmul_MFP47441_ct(t8,t20,t2);
	modmul_MFP47441_ct(t0,t2,t4);
	modmul_MFP47441_ct(t8,t4,z);
	modmul_MFP47441_ct(t2,z,t5);
	modmul_MFP47441_ct(t1,t5,t19);
	modmul_MFP47441_ct(t8,t19,t7);
	modmul_MFP47441_ct(t20,t7,t16);
	modmul_MFP47441_ct(z,t16,t10);
	modmul_MFP47441_ct(t20,t10,t18);
	modmul_MFP47441_ct(t8,t18,t22);
	modmul_MFP47441_ct(t0,t22,t13);
	modmul_MFP47441_ct(t6,t13,t2);
	modmul_MFP47441_ct(t8,t2,t21);
	modmul_MFP47441_ct(t0,t21,t3);
	modmul_MFP47441_ct(t5,t3,t15);
	modmul_MFP47441_ct(t6,t15,t9);
	modmul_MFP47441_ct(t6,t9,t5);
	modmul_MFP47441_ct(t4,t5,t4);
	modmul_MFP47441_ct(t0,t4,t11);
	modmul_MFP47441_ct(t20,t11,t17);
	modmul_MFP47441_ct(t20,t17,t12);
	modmul_MFP47441_ct(t8,t12,t23);
	modmul_MFP47441_ct(t6,t23,t14);
	modmul_MFP47441_ct(z,t14,t6);
	modmul_MFP47441_ct(t8,t6,t8);
	modmul_MFP47441_ct(t0,t8,t0);
	modmul_MFP47441_ct(t20,t8,t20);
	modmul_MFP47441_ct(z,t20,z);
	modnsqr_MFP47441_ct(z,2);
	modcpy_MFP47441_ct(z,t24);
	modnsqr_MFP47441_ct(t24,5);
	modmul_MFP47441_ct(z,t24,z);
	modmul_MFP47441_ct(t11,z,z);
	modsqr_MFP47441_ct(t24,t24);
	modmul_MFP47441_ct(t0,t24,t24);
	modsqr_MFP47441_ct(z,t0);
	modmul_MFP47441_ct(x,t0,t0);
	modnsqr_MFP47441_ct(t24,8);
	modmul_MFP47441_ct(t23,t24,t23);
	modnsqr_MFP47441_ct(t23,7);
	modmul_MFP47441_ct(t22,t23,t22);
	modnsqr_MFP47441_ct(t22,8);
	modmul_MFP47441_ct(t21,t22,t21);
	modnsqr_MFP47441_ct(t21,12);
	modmul_MFP47441_ct(t20,t21,t20);
	modnsqr_MFP47441_ct(t20,9);
	modmul_MFP47441_ct(t9,t20,t20);
	modnsqr_MFP47441_ct(t20,11);
	modmul_MFP47441_ct(t6,t20,t20);
	modnsqr_MFP47441_ct(t20,6);
	modmul_MFP47441_ct(t16,t20,t20);
	modnsqr_MFP47441_ct(t20,12);
	modmul_MFP47441_ct(t19,t20,t19);
	modnsqr_MFP47441_ct(t19,10);
	modmul_MFP47441_ct(t9,t19,t19);
	modnsqr_MFP47441_ct(t19,7);
	modmul_MFP47441_ct(t18,t19,t18);
	modnsqr_MFP47441_ct(t18,12);
	modmul_MFP47441_ct(t17,t18,t17);
	modnsqr_MFP47441_ct(t17,7);
	modmul_MFP47441_ct(t16,t17,t16);
	modnsqr_MFP47441_ct(t16,10);
	modmul_MFP47441_ct(t12,t16,t16);
	modnsqr_MFP47441_ct(t16,8);
	modmul_MFP47441_ct(t15,t16,t15);
	modnsqr_MFP47441_ct(t15,8);
	modmul_MFP47441_ct(t14,t15,t14);
	modnsqr_MFP47441_ct(t14,7);
	modmul_MFP47441_ct(t7,t14,t14);
	modnsqr_MFP47441_ct(t14,11);
	modmul_MFP47441_ct(t13,t14,t13);
	modnsqr_MFP47441_ct(t13,9);
	modmul_MFP47441_ct(t12,t13,t12);
	modnsqr_MFP47441_ct(t12,9);
	modmul_MFP47441_ct(t11,t12,t11);
	modnsqr_MFP47441_ct(t11,7);
	modmul_MFP47441_ct(t10,t11,t10);
	modnsqr_MFP47441_ct(t10,10);
	modmul_MFP47441_ct(t9,t10,t9);
	modnsqr_MFP47441_ct(t9,8);
	modmul_MFP47441_ct(t8,t9,t8);
	modnsqr_MFP47441_ct(t8,6);
	modmul_MFP47441_ct(t7,t8,t7);
	modnsqr_MFP47441_ct(t7,10);
	modmul_MFP47441_ct(t6,t7,t6);
	modnsqr_MFP47441_ct(t6,7);
	modmul_MFP47441_ct(t2,t6,t6);
	modnsqr_MFP47441_ct(t6,9);
	modmul_MFP47441_ct(t5,t6,t5);
	modnsqr_MFP47441_ct(t5,8);
	modmul_MFP47441_ct(t4,t5,t4);
	modnsqr_MFP47441_ct(t4,9);
	modmul_MFP47441_ct(t3,t4,t3);
	modnsqr_MFP47441_ct(t3,11);
	modmul_MFP47441_ct(t2,t3,t2);
	modnsqr_MFP47441_ct(t2,4);
	modmul_MFP47441_ct(t1,t2,t1);
	modnsqr_MFP47441_ct(t1,21);
	modmul_MFP47441_ct(t0,t1,t1);
	modnsqr_MFP47441_ct(t1,16);
	modmul_MFP47441_ct(t0,t1,t1);
	modnsqr_MFP47441_ct(t1,16);
	modmul_MFP47441_ct(t0,t1,t1);
	modnsqr_MFP47441_ct(t1,16);
	modmul_MFP47441_ct(t0,t1,t1);
	modnsqr_MFP47441_ct(t1,16);
	modmul_MFP47441_ct(t0,t1,t0);
	modnsqr_MFP47441_ct(t0,15);
	modmul_MFP47441_ct(z,t0,z);
}

//calculate inverse, provide progenitor h if available
static void modinv_MFP47441_ct(const spint *x,const spint *h,spint *z) {
	spint s[12];
	spint t[12];
	if (h==NULL) {
		modpro_MFP47441_ct(x,t);
	} else {
		modcpy_MFP47441_ct(h,t);
	}
	modcpy_MFP47441_ct(x,s);
	modnsqr_MFP47441_ct(t,2);
	modmul_MFP47441_ct(s,t,z);
}

static void nres_MFP47441_ct(const spint *a, spint *b) {
    uint32_t nresfactor[] = {2254725502, 1202972710, 3219431852, 3692086853, 4067369453, 875334552, 1707965875, 847840740, 1861278224, 184460779, 760619375, 59316046};
    modmul_MFP47441_ct(a, nresfactor, b);
    modfsb_MFP47441_ct(b);
}

static void redc_MFP47441_ct(const spint *a, spint *b) {
    uint32_t rinv[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    modmul_MFP47441_ct(a, rinv, b);
}

static int modis1_MFP47441_ct(const spint *a) {
    spint c[12] = {0};
    spint d=0;
    redc_MFP47441_ct(a,c);
    c[0] = c[0] - 1;
    for(int i=0; i<12; i++){
        d|=c[i];
    }
    return 1 - ((d | -d) >> 31);
}
    
static int modis0_MFP47441_ct(const spint *a) {
    spint d=0;
    for(int i=0; i<12; i++){
        d|=a[i];
    }
    return 1 - ((d | -d) >> 31);
}
    
static void modzer_MFP47441_ct(spint *a) {
    a[0] = 0;
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
    a[4] = 0;
    a[5] = 0;
    a[6] = 0;
    a[7] = 0;
    a[8] = 0;
    a[9] = 0;
    a[10] = 0;
    a[11] = 0;
}

static void modone_MFP47441_ct(spint *a) {
    a[0] = 66;
    a[1] = 0;
    a[2] = 0;
    a[3] = 1323296252;
    a[4] = 964271388;
    a[5] = 2835118304;
    a[6] = 3002383594;
    a[7] = 3313246534;
    a[8] = 1782969;
    a[9] = 3339398362;
    a[10] = 3889345544;
    a[11] = 6645367;
}

static void modint_MFP47441_ct(int x, spint *a) {
    a[0] = (spint) x;
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
    a[4] = 0;
    a[5] = 0;
    a[6] = 0;
    a[7] = 0;
    a[8] = 0;
    a[9] = 0;
    a[10] = 0;
    a[11] = 0;
    nres_MFP47441_ct(a,a);
}

//Test for quadratic residue, provide progenitor h if available, NULL if not
static int modqr_MFP47441_ct(const spint *h,const spint *x) {
	spint r[12];
	if (h==NULL) {
		modpro_MFP47441_ct(x,r);
		modsqr_MFP47441_ct(r,r);
	} else {
		modsqr_MFP47441_ct(h,r);
	}
	modmul_MFP47441_ct(r,x,r);
	return modis1_MFP47441_ct(r);
}

static void modcmv_MFP47441_ct(int d, const spint *a, spint *b) {
    uint32_t t;
    d = -d;
    for (int i = 0; i < 12; i++) {
        t = d & (a[i] ^ b[i]);
        b[i] ^= t;
    }
}

static void modcsw_MFP47441_ct(int d, spint *a, spint *b) {
    uint32_t t;
    d = -d;
    for (int i = 0; i < 12; i++) {
        t = d & (a[i] ^ b[i]);
        a[i] ^= t;
        b[i] ^= t;
    }
}

//Modular square root, provide progenitor h if available, NULL if not
static void modsqrt_MFP47441_ct(const spint *x, const spint *h, spint *r) {
	spint s[12];
	spint y[12];
	if (h==NULL) {
		modpro_MFP47441_ct(x,y);
	} else {
		modcpy_MFP47441_ct(h,y);
	}
	modmul_MFP47441_ct(y,x,s);
	modcpy_MFP47441_ct(s,r);
}

static void modshl_MFP47441_ct(int n, spint *a) {
    a[11] = (a[11] << n) + (a[10] >> (32-n));
    a[10] = (a[10] << n) + (a[9] >> (32-n));
    a[9] = (a[9] << n) + (a[8] >> (32-n));
    a[8] = (a[8] << n) + (a[7] >> (32-n));
    a[7] = (a[7] << n) + (a[6] >> (32-n));
    a[6] = (a[6] << n) + (a[5] >> (32-n));
    a[5] = (a[5] << n) + (a[4] >> (32-n));
    a[4] = (a[4] << n) + (a[3] >> (32-n));
    a[3] = (a[3] << n) + (a[2] >> (32-n));
    a[2] = (a[2] << n) + (a[1] >> (32-n));
    a[1] = (a[1] << n) + (a[0] >> (32-n));
    a[0] = (a[0] << n);
}

// Only works for n <= 31
static uint32_t modshr_MFP47441_ct(int n, spint *a) {
    uint32_t r = a[0] & ((1 << n) - 1);
    a[0] = (a[0] >> n) | (a[0 + 1] << (32u - n));
    a[1] = (a[1] >> n) | (a[1 + 1] << (32u - n));
    a[2] = (a[2] >> n) | (a[2 + 1] << (32u - n));
    a[3] = (a[3] >> n) | (a[3 + 1] << (32u - n));
    a[4] = (a[4] >> n) | (a[4 + 1] << (32u - n));
    a[5] = (a[5] >> n) | (a[5 + 1] << (32u - n));
    a[6] = (a[6] >> n) | (a[6 + 1] << (32u - n));
    a[7] = (a[7] >> n) | (a[7 + 1] << (32u - n));
    a[8] = (a[8] >> n) | (a[8 + 1] << (32u - n));
    a[9] = (a[9] >> n) | (a[9 + 1] << (32u - n));
    a[10] = (a[10] >> n) | (a[10 + 1] << (32u - n));
    a[11] = a[11] >> n;
    return r;
}

// Code for export, not exponentiation
static void modexp_MFP47441_ct(const spint *a, char *b) {
    uint32_t c[12];
    redc_MFP47441_ct(a, c);
    for (int i = 47; i>= 0; i--) {
        b[i] = c[0] & (uint32_t)0xff;
        (void)modshr_MFP47441_ct(8, c);
    }
}

static void modimp_MFP47441_ct(const char *b, spint *a) {
    a[0] = 0;
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
    a[4] = 0;
    a[5] = 0;
    a[6] = 0;
    a[7] = 0;
    a[8] = 0;
    a[9] = 0;
    a[10] = 0;
    a[11] = 0;
    for (int i=0; i<48; i++){
        modshl_MFP47441_ct(8,a);
        a[0] += (spint)(unsigned char)b[i];
    }
    nres_MFP47441_ct(a,a);
}

#define Nlimbs_MFP47441_ct 12
#define Nbits_MFP47441_ct 378
#define Nbytes_MFP47441_ct 48

/* API functions calling generated code */

const digit_t p[NWORDS_FIELD] =  { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x4C6174C1, 0x356EA468, 0xC722F669, 0x90AEB751, 0x65BC2E0A, 0x45D10AD6, 0xC6AE604A, 0xAB0871A2, 0x03DF6EEE };
const digit_t pre[NWORDS_FIELD] = { 0xF27F82B3, 0x55103253, 0x8CD7E6CD, 0x29FE9068, 0x7604EC49, 0x1056CF25, 0x477E2A37, 0xBC9C6EB8, 0xFCA44A33, 0x78F733D6, 0xBA55933F, 0x32700DE };

bool fp_is_zero(const digit_t* a) {
    return (bool) modis0_MFP47441_ct(a);
}

void fp_copy(digit_t* out, const digit_t* a) {
    modcpy_MFP47441_ct(a, out);
}

void fp_add(digit_t* out, const digit_t* a, const digit_t* b) {
    modadd_MFP47441_ct(a, b, out);
    modfsb_MFP47441_ct(out);
}

void fp_sub(digit_t* out, const digit_t* a, const digit_t* b) {
    modsub_MFP47441_ct(a, b, out);
    modfsb_MFP47441_ct(out);
}

void fp_neg(digit_t* out, const digit_t* a) {
    spint zero[NWORDS_FIELD];
    modzer_MFP47441_ct(zero);
    modsub_MFP47441_ct(zero, a, out);
    modfsb_MFP47441_ct(out);
}

void fp_sqr(digit_t* out, const digit_t* a) {
    modsqr_MFP47441_ct(a, out);
    modfsb_MFP47441_ct(out);
}

void fp_mul(digit_t* out, const digit_t* a, const digit_t* b) {
    modmul_MFP47441_ct(a, b, out);
    modfsb_MFP47441_ct(out);
}

void fp_sqrt(digit_t* a) {
    modsqrt_MFP47441_ct(a, NULL, a);
}

void fp_exp3div4(digit_t* out, const digit_t* a) {
    modpro_MFP47441_ct(a, out);
}

void fp_tomont(digit_t* out, const digit_t* a) {
    nres_MFP47441_ct(a, out);
}

void fp_frommont(digit_t* out, const digit_t* a) {
    redc_MFP47441_ct(a, out);
}

void fp_mont_setone(digit_t* out) {
    modone_MFP47441_ct(out);
}

void fp_to_digit_array(digit_t* out, const digit_t* a) {
    digit_t x[NWORDS_FIELD];
    modcpy_MFP47441_ct(a, x);
    for (int i = 0; i < NWORDS_ORDER; i++) {
        out[i] = 0;
    }
    for (int i = 0; i < 48; i++) {
        ((char *) out)[i] = x[0] & 0xff;
        modshr_MFP47441_ct(8, x);
    }
}

void fp_from_digit_array(digit_t* out, const digit_t* a) {
    for (int i = 0; i < NWORDS_FIELD; i++) {
        out[i] = 0;
    }
    for (int i = 48 - 1; i >= 0; i--) {
        modshl_MFP47441_ct(8, out);
        out[0] += (digit_t)((unsigned char *) a)[i];
    }
}

#ifdef PQM4
#include "bn.inc"
#include "inversion.inc"
#include "symbol.inc"
#else
#include "../../generic/bn.inc"
#include "../../generic/inversion.inc"
#include "../../generic/symbol.inc"
#endif

#endif
