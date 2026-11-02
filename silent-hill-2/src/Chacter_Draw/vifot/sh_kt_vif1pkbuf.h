#ifndef SH_KT_VIF1PKBUF_H
#define SH_KT_VIF1PKBUF_H

extern u_long128 vif1_pk_buf_db[2][6144] __attribute__((aligned(128)));
extern ktPkBuf vif1_pkbuf;

void ktVif1PkBufInit(void* buf0, void* buf1, int size);

void sh2_ktVif1kBufInit(void);

void* ktVif1PkBufNext(void);


#endif // SH_KT_VIF1PKBUF_H
