#ifndef SH_KT_VIF0PKBUF_H
#define SH_KT_VIF0PKBUF_H

#include "sh2_common.h"

extern u_long128 vif0_pk_buf_db[2][256];
extern ktPkBuf vif0_pkbuf;

void ktVif0PkBufInit(void* buf0, void* buf1, int size);

void sh2_ktVif0PkBufInit(void);

void* ktVif0PkBufNext(void);

void* ktVif0PkBufCurrent(void);

#endif // SH_KT_VIF0PKBUF_H
