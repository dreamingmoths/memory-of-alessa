#include "Effect/ef_rain.h"
#include "SH2_common/sh_vu0.h"

static void efRainDropInitSpray(_EF_RAINDROP_DATA * dat /* r16 */, float * pos /* r2 */);
static int efRainDropDrawSpray(_EF_RAINDROP_DATA * dat /* r16 */);

int EFCTSetRainDrop(int lev /* r17 */) {
    _EF_EF_RAINDROP_TASK * ptr; // r2
    int i; // r16
    
    for (i = 0; i < lev; i++) {
        ptr = (_EF_EF_RAINDROP_TASK *)shTSKSetTask((void (*)(void *))&EFCTRainDropMain, 4);
        if (ptr != NULL) {
            ptr->exe.atr = 10;
            ptr->exe.mode = 0;
        } else {
            return 0;
        }
    }
    return 1;
}

void EFCTDelRainDrop(void) {
    _shTskTASK * ptr; // r2
    _shTskTASK * seekp; // r16
    
    seekp = shTskTaskListTop[4]->exe.next;
    while (1) {
        ptr = shTSKSearchTaskWithAtr(10, seekp, 4);
        if (ptr == NULL) {
            return;
        }
        seekp = ptr->exe.next;
        shTSKDelTask(ptr);
    }
}

INCLUDE_ASM("asm/nonmatchings/Effect/ef_rain", EFCTRainDropMain);

static void efRainDropInitSpray(_EF_RAINDROP_DATA * dat /* r16 */, float * pos /* r2 */) {
    vec_copy(&dat->v[0], pos);
    dat->v[0][1] -= 25.0f;
    dat->v[0][3] = 1.0f;
    vec_copy(&dat->v[1], &dat->v[0]);
    vec_copy(&dat->v[2], &dat->v[0]);
    vec_copy(&dat->v[3], &dat->v[0]);
    dat->v[1][0] = dat->v[0][0] + (shRandF() - 0.5f) / 10.0f * 500.0f;
    dat->v[2][2] = dat->v[0][2] + (shRandF() - 0.5f) / 10.0f * 500.0f;
    dat->v[3][0] = dat->v[0][0] + (shRandF() - 0.5f) / 10.0f * 500.0f;
    dat->v[3][2] = dat->v[0][2] + (shRandF() - 0.5f) / 10.0f * 500.0f;
    dat->life = shRandI() % 2;

}

static int efRainDropDrawSpray(_EF_RAINDROP_DATA * dat /* r16 */)  {
    _EF_RAIN_LINE line;
	int i;

    line.rgba[0] = 0xFF;
    line.rgba[1] = 0xFF;
    line.rgba[2] = 0xFF;
    line.rgba[3] = 0xFF;

    for (i = 0; i < 4; i++) {
        vec_copy(line.v[0], dat->v[i]);
        vec_copy(line.v[1], dat->v[i]);
        line.v[1][1] -= 10.0f;
        efRainDropDrawLINE(&line);
    }

    if (dat->life != 0) {
        dat->life--;
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Effect/ef_rain", efRainDropDrawLINE);
