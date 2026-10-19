#ifndef KEYDATA_H
#define KEYDATA_H

#include "sh2_common.h"

typedef union shGameKeyData {
    u_long bit; // offset 0x0, size 0x4
    // total size: 0x8
    struct /* @anon0 */ {
        // Members
        u_long type : 1; // offset 0x0, size 0x4
        u_long DRINK : 1; // offset 0x0, size 0x4
        u_long RADIO : 1; // offset 0x0, size 0x4
        u_long LIGHT : 1; // offset 0x0, size 0x4
        u_long ITEM : 1; // offset 0x0, size 0x4
        u_long MAP : 1; // offset 0x0, size 0x4
        u_long DECIDE : 1; // offset 0x0, size 0x4
        u_long CANCEL : 1; // offset 0x0, size 0x4
        u_long SKIP : 1; // offset 0x0, size 0x4
        u_long PAUSE : 1; // offset 0x0, size 0x4
        u_long ACTION : 2; // offset 0x0, size 0x4
        u_long DASH : 2; // offset 0x0, size 0x4
        u_long LSLIDE : 2; // offset 0x0, size 0x4
        u_long RSLIDE : 2; // offset 0x0, size 0x4
        u_long READY : 2; // offset 0x0, size 0x4
        u_long VIEW : 2; // offset 0x0, size 0x4
        u_long frame_m1 : 2; // offset 0x0, size 0x4
        long AX : 4; // offset 0x0, size 0x4
        long AY : 4; // offset 0x0, size 0x4
        long BX : 2; // offset 0x0, size 0x4
        long BY : 2; // offset 0x0, size 0x4
        long CX : 4; // offset 0x0, size 0x4
        long CY : 4; // offset 0x0, size 0x4
        u_long reserve : 2; // offset 0x0, size 0x4
        u_long trg : 1; // offset 0x0, size 0x4
        u_long rpt : 1; // offset 0x0, size 0x4
        u_long len : 16; // offset 0x0, size 0x4
    } f; // offset 0x0, size 0x8
} shGameKeyData;

int shSysKeyNormalize(char* paddata /* r2 */);
int shSysKeyAdjust(char* paddata /* r2 */);
int shGameKeyConvert(shGameKeyData* key /* r10 */, char* paddata /* r2 */);

#endif // KEYDATA_H
