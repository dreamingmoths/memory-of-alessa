#define GIF_REG(reg, n) ((u_long)(reg) << ((n) * 4))

union Q
{
    __int128 u128;         // offset 0x0, size 0x10
    unsigned long u64[2];  // offset 0x0, size 0x8
    unsigned int u32[4];   // offset 0x0, size 0x10
    unsigned short u16[8]; // offset 0x0, size 0x10
    unsigned char u8[16];  // offset 0x0, size 0x10
    signed long s64[2];    // offset 0x0, size 0x8
    signed int s32[4];     // offset 0x0, size 0x10
    signed short s16[8];   // offset 0x0, size 0x10
    signed char s8[16];    // offset 0x0, size 0x10
    signed int q[4];       // offset 0x0, size 0x10
    float fv[4];           // offset 0x0, size 0x10
    signed int iv[4];      // offset 0x0, size 0x10
};

typedef struct TriangleNormal
{
    // total size: 0xD0
    union Q dmatag;   // offset 0x0, size 0x10
    union Q n_giftag; // offset 0x10, size 0x10
    union Q n_tex0;   // offset 0x20, size 0x10
    union Q n_clamp;  // offset 0x30, size 0x10
    union Q n_stq2;   // offset 0x40, size 0x10
    union Q n_rgba2;  // offset 0x50, size 0x10
    union Q n_xyzf2;  // offset 0x60, size 0x10
    union Q n_stq1;   // offset 0x70, size 0x10
    union Q n_rgba1;  // offset 0x80, size 0x10
    union Q n_xyzf1;  // offset 0x90, size 0x10
    union Q n_stq0;   // offset 0xA0, size 0x10
    union Q n_rgba0;  // offset 0xB0, size 0x10
    union Q n_xyzf0;  // offset 0xC0, size 0x10
} TriangleNormal;
