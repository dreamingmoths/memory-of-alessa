#include "Effect/ef_rain.h"

#include "Effect2/hh_class_wrapper.h"

#include "Chacter/character.h"

#include "Collision/cl_main.h"

#include "Fog/spack.h"

#include "GFW/sh2_DrawEnvData.h"

#include "sce/libvu0.h"
#include "sce/eestruct.h"

#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"

#include "view/vc_main.h"
#include "view/vb_main.h"

#include "vec.h"

static void efRainDropInitSpray(EF_RAINDROP_DATA* dat /* r16 */, float* pos /* r2 */);
static int efRainDropDrawSpray(EF_RAINDROP_DATA* dat /* r16 */);

int EFCTSetRainDrop(int lev /* r17 */) {
    EF_EF_RAINDROP_TASK* ptr; // r2
    int i; // r16
    
    for (i = 0; i < lev; i++) {
        ptr = (EF_EF_RAINDROP_TASK *)shTSKSetTask((void (*)(void *))&EFCTRainDropMain, 4);
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
    shTskTASK* ptr; // r2
    shTskTASK* seekp; // r16
    
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

void EFCTRainDropMain(shTskTASK* ptr) {    
    EF_RAIN_LINE line; // r29+0x50
    int j; // r16
    float campos[4]; // r29+0x80
    EF_RAINDROP_DATA* pt; // r17
    CL_VHIT_RESULT res; // r29+0x90
    float dif; // r20
    float camang[4]; // r29+0xD0
    float pos[4]; // r29+0xE0    
    float m0[4][4]; // r29+0xF0
    pt = &((EF_EF_RAINDROP_TASK*)ptr)->data;
    vcGetNowCamPos(campos);
    line.rgba[0] = 0x80;
    line.rgba[1] = 0x80;
    line.rgba[2] = 0x80;
    line.rgba[3] = 0x80;

    
    HH_ClassWrapper_AmbientColor_Get(efRainDrawData.ambcol);
    efRainDrawData.spoton = HH_ClassWrapper_SpotLight_Enable_Check();
    if (efRainDrawData.spoton) {
        
        HH_ClassWrapper_SpotLight_EnvironmentParameter_Get(efRainDrawData.lightpos, efRainDrawData.lightdir, efRainDrawData.lightcol, efRainDrawData.lightpar);
    }

    
    
    
    
    
    sceVu0CopyMatrix(efRainDrawData.wcm, cam0.view_clip);
    shMulMatrix(efRainDrawData.wcm, efRainDrawData.wcm, VbWvsMatrix.wvm);

    
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1),SCE_GIF_PACKED_AD, 0xFFFF0000, 0);
    *spack.pos++ = SCE_GS_SET_ALPHA(0, 1, 0, 1, 0x80); *spack.pos++ = SCE_GS_ALPHA_1;    
    *spack.pos++ = SCE_GS_SET_TEST(1, 1, 0, 0, 0, 0, 1, 3); *spack.pos++ = SCE_GS_TEST_1;
    

    
    switch (ptr->exe.mode) {
        case 0:
            
            
            
            
            
            
            
            
            vec_zero_xyz(pos);
            pos[2] = 1000.0f;
            vwGetViewAngle(camang);
            vu0_unit_matrix(m0);               
            shRotMatrixY(m0, m0, camang[1]);
            vu0_transform_vector(pos, m0);
            vu0_add_vector(campos, campos, pos);
                    
            
            for (j = 0; j < 15; j++) {
                
                pt->p[j][0] = campos[0] + (shRandF() - 0.5f) * 5.0f * 500.0f;
                pt->p[j][1] = campos[1] + (shRandF() - 0.5f) * 8.0f * 500.0f * -1.0f - 1000.0f;
                pt->p[j][2] = campos[2] + (shRandF() - 0.5f) * 5.0f * 500.0f;
                pt->p[j][3] = 1.0f;
            }
            ptr->exe.mode++;
            break;
    
        case 1:
            dif = 4000.0f / shGetFPS();
    
            for (j = 0; j < 15; j++) {
                
                pt->p[j][1] += dif;
                volatile_vec_copy(line.v[0], pt->p[j]);
                volatile_vec_copy(line.v[1], pt->p[j]);
                line.v[1][1] += 100.0f;
                
                efRainDropDrawLINE(&line);
            }
    
            
            line.v[0][1] -= 250.0f;
            clCheckHitEyesOnlyFloorCeil(&res, line.v[0], line.v[1]);
            if (res.kind == 1) {
                
                efRainDropInitSpray(pt, res.hobj.wall.cp);
                ptr->exe.mode++;
            }  
                
            else if ((line.v[1][1] >= 2500.0f + campos[1])) 
                    
                    ptr->exe.mode = 0;
            break;
            
    
        case 2:
            
            if (efRainDropDrawSpray(pt)) {
                ptr->exe.mode = 0;
            }

    }

    spkCloseGiftag();
}

static void efRainDropInitSpray(EF_RAINDROP_DATA* dat /* r16 */, float* pos /* r2 */) {
    volatile_vec_copy(&dat->v[0], pos);
    dat->v[0][1] -= 25.0f;
    dat->v[0][3] = 1.0f;
    volatile_vec_copy(&dat->v[1], &dat->v[0]);
    volatile_vec_copy(&dat->v[2], &dat->v[0]);
    volatile_vec_copy(&dat->v[3], &dat->v[0]);
    dat->v[1][0] = dat->v[0][0] + (shRandF() - 0.5f) / 10.0f * 500.0f;
    dat->v[2][2] = dat->v[0][2] + (shRandF() - 0.5f) / 10.0f * 500.0f;
    dat->v[3][0] = dat->v[0][0] + (shRandF() - 0.5f) / 10.0f * 500.0f;
    dat->v[3][2] = dat->v[0][2] + (shRandF() - 0.5f) / 10.0f * 500.0f;
    dat->life = shRandI() % 2;

}

static int efRainDropDrawSpray(EF_RAINDROP_DATA* dat /* r16 */)  {
    EF_RAIN_LINE line;
	int i;

    line.rgba[0] = 0xFF;
    line.rgba[1] = 0xFF;
    line.rgba[2] = 0xFF;
    line.rgba[3] = 0xFF;

    for (i = 0; i < 4; i++) {
        volatile_vec_copy(line.v[0], dat->v[i]);
        volatile_vec_copy(line.v[1], dat->v[i]);
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
