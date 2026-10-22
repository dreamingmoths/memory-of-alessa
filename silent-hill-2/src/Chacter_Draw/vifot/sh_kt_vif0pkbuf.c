#include "sh2_common.h"
#include "Chacter_Draw/vifot/sh_kt_pkbuf.h"

UNMIGRATED(u_long128 vif0_pk_buf_db[2][256]); // size: 0x2000, address: 0x3E6700
UNMIGRATED(ktPkBuf vif0_pkbuf); // size: 0x14, address: 0x3E66E0


#line 32
void ktVif0PkBufInit(void* buf0, void* buf1, int size) {
    ktPkBufInit(&vif0_pkbuf, buf0, buf1, size);
}

#line 37
void sh2_ktVif0PkBufInit() {

    ktVif0PkBufInit(vif0_pk_buf_db, vif0_pk_buf_db[1], sizeof(vif0_pk_buf_db[0]));





}

#line 50
void* ktVif0PkBufNext() {
    return ktPkBufNext(&vif0_pkbuf);
}

#line 70
void* ktVif0PkBufCurrent() {
    return ktPkBufCurrent(&vif0_pkbuf);
}
