#include "sh2_common.h"
#include "Chacter_Draw/vifot/sh_kt_pkbuf.h"

UNMIGRATED(__int128 vif1_pk_buf_db[2][6144]); // size: 0x30000, address: 0x3E8780
UNMIGRATED(ktPkBuf vif1_pkbuf); // size: 0x14, address: 0x3E8710

#line 44
void ktVif1PkBufInit(void* buf0, void* buf1, int size) {
    ktPkBufInit(&vif1_pkbuf, buf0, buf1, size);
}

#line 48
void sh2_ktVif1kBufInit() {

    ktVif1PkBufInit(vif1_pk_buf_db, vif1_pk_buf_db[1], sizeof(vif1_pk_buf_db[0]));





}

#line 63
void* ktVif1PkBufNext() {
    return ktPkBufNext(&vif1_pkbuf);
}
