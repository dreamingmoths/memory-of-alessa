#ifndef SH_CHARACTER_STATUS_H
#define SH_CHARACTER_STATUS_H

#include "common.h"
#include "Chacter/character.h"

// total size: 0x1
struct shInArea {
    // Members
    unsigned char look_on : 2; // offset 0x0, size 0x1
    unsigned char feel_on : 2; // offset 0x0, size 0x1
    unsigned char light_on : 4; // offset 0x0, size 0x1
};

// total size: 0xC
struct shInAreaTgtInfo {
    // Members
    union /* @anon4 */ {
        struct SubCharacter * scp; // offset 0x0, size 0x4
    } adr; // offset 0x0, size 0x4
    float distance; // offset 0x4, size 0x4
    struct shInArea in_area; // offset 0x8, size 0x1
};

void clCheckHitEyes(struct _CL_VHIT_RESULT * res /* r2 */, u_int id /* r2 */, float * st /* r2 */, float * ed /* r2 */, int thru /* r2 */);
struct shInAreaTgtInfo sh2_target_info[20];
static float _shLength(float * v0 /* r2 */, float * v1 /* r2 */);
int sh2gfw_Check_CharaDarkOrBright(void * SubChara /* r2 */);

#endif