#include "sh2_common.h"
#include "Chacter_Draw/vifot/sh_kt_pkbuf.h"
#include "Chacter_Draw/vifot/sh_kt_vif1pkbuf.h"


u_long128 vif1_pk_buf_db[2][6144] __attribute__((aligned(128)));
ktPkBuf vif1_pkbuf;

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
