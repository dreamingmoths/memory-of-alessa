#ifndef SH2GFW_MACROS_H
#define SH2GFW_MACROS_H

#define SET_DMATAG(qwd, id, i0, i1, i2, i3)       \
do {                                              \
    (qwd + (id))->ui32[0] = i0;                   \
    (qwd + (id))->ui32[1] = i1;                   \
    (qwd + (id))->ui32[2] = i2;                   \
    (qwd + (id))->ui32[3] = i3;                   \
    (id)++;                                       \
} while (0)
#define SET_QWORD_U32(qwd, id, i0, i1, i2, i3)    \
do {                                              \
    (qwd + (id))->ui32[0] = i0;                   \
    (qwd + (id))->ui32[1] = i1;                   \
    (qwd + (id))->ui32[2] = i2;                   \
    (qwd + (id))->ui32[3] = i3;                   \
    (id)++;                                       \
} while (0)
#define SET_QWORD_U64(qwd, i0, i1)                \
do {                                              \
    (qwd)->ul64[0] = i0;                          \
    (qwd)->ul64[1] = i1;                          \
} while (0)
#define SET_GIFTAG(qwd, id, ul0, ul1)             \
do {                                              \
    (qwd + (id))->ui32[3] = (u_long) ul1 >> 0x20; \
    (qwd + (id))->ui32[2] = ul1;                  \
    (qwd + (id))->ui32[1] = (u_long) ul0 >> 0x20; \
    (qwd + (id))->ui32[0] = ul0;                  \
    (id)++;                                       \
} while (0)
#define SET_ADDRESS_DATA(qwd, id, address, data)  \
do {                                              \
    (qwd + (id))->ul64[1] = address;              \
    (qwd + (id))->ul64[0] = data;                 \
    (id)++;                                       \
} while (0)
#define SET_DMA_RET(qwd) \
do {                                              \
    (qwd)->ul128 = 0;                             \
    (qwd)->ui32[0] = DMAret;                      \
} while (0)
#define SET_DMA_END(qwd)                          \
do {                                              \
    (qwd)->ul128 = 0;                             \
    (qwd)->ui32[0] = DMAend;                      \
} while (0)

#define SH_GIF_SET_XYZ3 SH_GIF_SET_XYZ
#define SH_GIF_SET_XYZ2 SH_GIF_SET_XYZ
#define SH_GIF_SET_XYZ(qw, idx, x, y, z, e) \
	(qw)[idx].ul64[0] = ((u_long)(x) | ((u_long)(y) << 32)); (qw)[idx++].ul64[1] = (((u_long)(z) << 4) | ((u_long)(e) << 47)) 

#define SH_GIF_PACK_XY(x, y) ((u_long)(x) | ((u_long)(y) << 32))
#define SH_GIF_PACK_UV(u, v) ((u_long)(u) | ((u_long)(v) << 32))

#endif // SH2GFW_MACROS_H
