#ifndef KEYDATA_H
#define KEYDATA_H

#include "sh2_common.h"

typedef union shGameKeyData {
    unsigned long bit; // offset 0x0, size 0x4
    // total size: 0x8
    struct /* @anon0 */ {
        // Members
        unsigned long type : 1; // offset 0x0, size 0x4
        unsigned long DRINK : 1; // offset 0x0, size 0x4
        unsigned long RADIO : 1; // offset 0x0, size 0x4
        unsigned long LIGHT : 1; // offset 0x0, size 0x4
        unsigned long ITEM : 1; // offset 0x0, size 0x4
        unsigned long MAP : 1; // offset 0x0, size 0x4
        unsigned long DECIDE : 1; // offset 0x0, size 0x4
        unsigned long CANCEL : 1; // offset 0x0, size 0x4
        unsigned long SKIP : 1; // offset 0x0, size 0x4
        unsigned long PAUSE : 1; // offset 0x0, size 0x4
        unsigned long ACTION : 2; // offset 0x0, size 0x4
        unsigned long DASH : 2; // offset 0x0, size 0x4
        unsigned long LSLIDE : 2; // offset 0x0, size 0x4
        unsigned long RSLIDE : 2; // offset 0x0, size 0x4
        unsigned long READY : 2; // offset 0x0, size 0x4
        unsigned long VIEW : 2; // offset 0x0, size 0x4
        unsigned long frame_m1 : 2; // offset 0x0, size 0x4
        signed long AX : 4; // offset 0x0, size 0x4
        signed long AY : 4; // offset 0x0, size 0x4
        signed long BX : 2; // offset 0x0, size 0x4
        signed long BY : 2; // offset 0x0, size 0x4
        signed long CX : 4; // offset 0x0, size 0x4
        signed long CY : 4; // offset 0x0, size 0x4
        unsigned long reserve : 2; // offset 0x0, size 0x4
        unsigned long trg : 1; // offset 0x0, size 0x4
        unsigned long rpt : 1; // offset 0x0, size 0x4
        unsigned long len : 16; // offset 0x0, size 0x4
    } f; // offset 0x0, size 0x8
} shGameKeyData;

int shSysKeyNormalize(char* paddata /* r2 */);
int shSysKeyAdjust(char* paddata /* r2 */);
int shGameKeyConvert(shGameKeyData* key /* r10 */, char* paddata /* r2 */);

#endif // KEYDATA_H
