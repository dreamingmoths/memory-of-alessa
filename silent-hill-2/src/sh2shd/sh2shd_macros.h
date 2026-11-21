#ifndef SH2SHD_MACROS_H
#define SH2SHD_MACROS_H

// @note file not found in DWARF information

// avoid including this header in other header files as its macros are not too
// distinctively named, for brevity.

#define STCYCL(wl, cl)           SCE_VIF1_SET_STCYCL(wl, cl, 0)
#define UNPACK(vuaddr, num, cmd) SCE_VIF1_SET_UNPACK(vuaddr, num, cmd, 0)

#define REF_ADDR(x) ((u_int) (x) & 0x7fffffff)
#define REFTAG(qwd, count, addr, stcycl, upk) \
    qwd.ui32[0] = DMAref | (count);           \
    qwd.ui32[1] = (u_int) (addr);             \
    qwd.ui32[2] = stcycl;                     \
    qwd.ui32[3] = upk
#define CNT(qwd, vifcode1, vifcode2)          \
    qwd.ui32[0] = DMAcnt | 0;                 \
    qwd.ui32[1] = 0;                          \
    qwd.ui32[2] = vifcode1;                   \
    qwd.ui32[3] = vifcode2

#define RET(qwd)                              \
    (qwd)->ui32[0] = DMAret;                  \
    (qwd)->ui32[1] = 0;                       \
    (qwd)->ui32[2] = 0;                       \
    (qwd)->ui32[3] = 0;                       \
    (qwd)++;

#endif // SH2SHD_MACROS_H
