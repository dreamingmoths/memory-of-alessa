#include "GFW/sh2gfw_LightSet.h"
#include "GFW/sh2_DrawEnvData.h"
#include "Chacter_Draw/sh2_JmsSpot_Man.h"
#include "Event/stg_name.h"
#include "SH2_common/sh_vu0.h"
#include "vec.h"

DemoLight_Work DemoLightWork; // size: 0x1B0, address: 0xE1CA80

void sh2gfw_Init_DemoLight_Work(void) {
    DemoLightWork.Parallel[2] = 0;
    DemoLightWork.Parallel[1] = 0;
    DemoLightWork.Parallel[0] = 0;
    DemoLightWork.Parallel_Cid[2] = 0;
    DemoLightWork.Parallel_Cid[1] = 0;
    DemoLightWork.Parallel_Cid[0] = 0;
    DemoLightWork.Ref = 0;
    DemoLightWork.Amb = 0;
    DemoLightWork.Spot = 0;
    DemoLightWork.Point[2] = 0;
    DemoLightWork.Point[1] = 0;
    DemoLightWork.Point[0] = 0;
    DemoLightWork.Point_Cid[2] = 0;
    DemoLightWork.Point_Cid[1] = 0;
    DemoLightWork.Point_Cid[0] = 0;
}

int sh2gfw_Set_DemoRefrectionHighLight(float* dir, float* col) {
    DemoLightWork.Ref = 1;
    shVectorCopy(DemoLightWork.demo_RefLight_dir, dir);
    shVectorCopy(DemoLightWork.demo_RefLight_col, col);
}

int sh2gfw_Get_DemoRefrectionHightLight(float* dir, float* col) {
    if (DemoLightWork.Ref != 0) {
        shVectorCopy(dir, DemoLightWork.demo_RefLight_dir);
        shVectorCopy(col, DemoLightWork.demo_RefLight_col);
    } else {
        return 0;
    }
}

int sh2gfw_Check_DemoRefrectionHightLight(void) {
    return DemoLightWork.Ref;
}

int sh2gfw_Set_PallarelLight(float* dir, float* color, int n) {
    int k;



    k = n < 0 ? -n : n;
    
    if (k < DEMO_MAX_PARALLEL_LIGHT) {
        switch (k) {
        case 0:
            if (!sh2gfw_Get_NightOrDay()) {
                
                sceVu0CopyVector(DemoLightWork.demo_p_light0, dir);
                sceVu0ScaleVector(DemoLightWork.demo_p_color0, color, 1.0f);
                return n + 1;
            }
            break;    
        case 1:
            sceVu0CopyVector(DemoLightWork.demo_p_light1, dir);
            sceVu0ScaleVector(DemoLightWork.demo_p_color1, color, 1.0f);
            if (n > 0) DemoLightWork.Parallel[1] = 1;
            else DemoLightWork.Parallel[1] = -1;
            
            break;
        case 2:
            sceVu0CopyVector(DemoLightWork.demo_p_light2, dir);
            sceVu0ScaleVector(DemoLightWork.demo_p_color2, color, 1.0f);
            if (n > 0) DemoLightWork.Parallel[2] = 1;
            else DemoLightWork.Parallel[2] = -1;
            
            break;
        }
        return n + 1;
    } 
    
    return 0;
    
}

int sh2gfw_Check_ParallelDemoLight(int n) {
    return DemoLightWork.Parallel[n];
}

int sh2gfw_Get_ParallelDemoLight(int n, float* dir, float* col) {
    sceVu0FVECTOR* svt;

    if (DemoLightWork.Parallel[n] != 0) {
        
        svt = (sceVu0FVECTOR*) DemoLightWork.demo_p_light0 + n * 2;
        
        shVectorCopy(dir, svt[0]);
        shVectorCopy(col, svt[1]);
        
        return 1;
    }
    return 0;
}

void sh2gfw_Revive_ParallelDemoLight(int n) {
    DemoLightWork.Parallel[n] = 1;
}

void sh2gfw_Set_DemoPointLight(int n, float* pos, float* col, float falloff_start, float falloff_end) {
    AAA* pl;

    pl = (AAA*) DemoLightWork.demo_pointcol0;
    pl += n;
    DemoLightWork.Point[n] = 1;
    
    shVectorCopy(pl->pos, pos);
    shVectorCopy(pl->col, col);
    pl->decay[0] = falloff_start;
    pl->decay[1] = falloff_end;
}

int sh2gfw_Check_DemoPointLight(void) {
    return DemoLightWork.Point[0] + DemoLightWork.Point[1] + DemoLightWork.Point[2];
}

int sh2gfw_Get_DemoPointLight(int n, float* pos, float* col, float* decay) {
    AAA* pl;

    if (DemoLightWork.Point[n]) {
        
        pl = (AAA*) DemoLightWork.demo_pointcol0;
        pl += n;
        shVectorCopy(pos, pl->pos);
        shVectorCopy(col, pl->col);
        shVectorCopy(decay, pl->decay);
        return 1;
    }
    return 0;

}

int sh2gfw_Check_DemoSpotLight(void) {
    return DemoLightWork.Spot;
}

void sh2gfw_Get_DemoSpotParm(float* svt) {
    shVectorCopy(svt, &DemoLightWork.demo_spotdecay);

}

void sh2gfw_Get_DemoSpotPosDirCol(float* pos, float* dir, float* col) {
    shVectorCopy(pos, &DemoLightWork.demo_spotpos);
    shVectorCopy(dir, &DemoLightWork.demo_spotdir);
    shVectorCopy(col, &DemoLightWork.demo_spotcol);


}

void sh2gfw_Set_SpotLight(float* dir, float* pos, float* color, int unused, float falloff_start, float falloff_end, float spread_pi) {
    
    DemoLightWork.Spot = 1;
    
    shVectorCopy(DemoLightWork.demo_spotpos, pos);
    shVectorCopy(DemoLightWork.demo_spotdir, dir);
    shVectorCopy(DemoLightWork.demo_spotcol, color);
    
    DemoLightWork.demo_spotdecay[0] = falloff_start;
    DemoLightWork.demo_spotdecay[1] = shCosF(spread_pi);
    DemoLightWork.demo_spotdecay[2] = falloff_end;
    DemoLightWork.demo_spotdecay[3] = spread_pi;

}

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_LightSet", sh2gfw_setparal3LGT_blk);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_LightSet", sh2gfw_LightSet_ForBG);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_LightSet", sh2gfw_Store_SpotLight);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_LightSet", sh2gfw_setsp1para2LGT_blk);

int sh2gfw_Get_NightOrDay(void) {
    return Env_ctl.light_mode - 1;
}

int SetLightMode(int nod) {
    Env_ctl.light_mode = nod ? 2 : 1;
}

void Get_DemoOrPresetLight(float* pl, float* pc, int g) {
    if (DemoLightWork.Parallel[g] <= 0) {
        switch (g) {
            case 0:
                sceVu0CopyVector(pl, Env_ctl.p_light0);
                sceVu0CopyVector(pc, Env_ctl.p_color0);
                break;
            case 1:
                sceVu0CopyVector(pl, Env_ctl.p_light1);
                sceVu0CopyVector(pc, Env_ctl.p_color1);
                break;
            case 2:
                sceVu0CopyVector(pl, Env_ctl.p_light2);
                sceVu0CopyVector(pc, Env_ctl.p_color2);
                break;
        }
    } else {
        switch (g) {
            case 0:
                sceVu0CopyVector(pl, DemoLightWork.demo_p_light0);
                sceVu0CopyVector(pc, DemoLightWork.demo_p_color0);
                break;
            case 1:
                sceVu0CopyVector(pl, DemoLightWork.demo_p_light1);
                sceVu0CopyVector(pc, DemoLightWork.demo_p_color1);
                break;
            case 2:
                sceVu0CopyVector(pl, DemoLightWork.demo_p_light2);
                sceVu0CopyVector(pc, DemoLightWork.demo_p_color2);
                break;
        }
    }



}

void Get_DemoOrPresetAmbient(float* ab) {
   
    if (DemoLightWork.Amb == 0) {
        sceVu0CopyVector(ab, Env_ctl.ambient); 
    } else {
        sceVu0CopyVector(ab, DemoLightWork.demo_ambient);
    }
        
}

void sh2gfw_Set_JmsSpot_OnOrOff(void) {
    int *mp;

    if (!BgIsOut(0)) {
        
        
        mp = Get_NowMapId();
        switch (*mp) {
            case 0x90054:
            case 0xB0055:
            case 0xB00BD:
            case 0xB00C1:
            case 0xC005B:
            case 0xD0015:
            case 0xD0049:
            case 0xE0001:
                sh2gfw_ForceOff_JmsSPOT();
                break;
        }
    }



}
