#include "sh2_common.h"

#include "vec.h"

#include "Chacter/character.h"

#include "view/vb_main.h"

#include "GFW/sh2_DrawEnvData.h"
#include "GFW/sh2_get_drawenv.h"

sceVu0FVECTOR shEyeDirVec;      // size: 0x10, address: 0x614EB0
sceVu0FVECTOR shJmsDirVec;      // size: 0x10, address: 0x614EA0
sceVu0FVECTOR shEyeToJmsDirVec; // size: 0x10, address: 0x614E90

#line 49
void sh2gfw_Set_EyeDir(void) {
    sceVu0FMATRIX wvm;                           // r29+0x10
    sceVu0FMATRIX vv = {0.0f, 0.0f, 1.0f, 0.0f}; // @bug typo? seems like it was supposed to be a vector

    sceVu0CopyMatrix(wvm, VbWvsMatrix.wvm);
    sceVu0InversMatrix(wvm, wvm);
    sceVu0ApplyMatrix(shEyeDirVec, wvm, (float*) vv);
    vwGetViewPosition(shEyeToJmsDirVec);

    sceVu0SubVector(shEyeToJmsDirVec, (float*) &sh2jms.player->pos, shEyeToJmsDirVec);

    sceVu0UnitMatrix(wvm);
    sceVu0RotMatrixY(wvm, wvm, sh2jms.player->rot.y);
    sceVu0ApplyMatrix(shJmsDirVec, wvm, (float*) vv);
}

#line 71
void sh2gde_Get_EyeDir(sceVu0FVECTOR svt) {
    sceVu0CopyVector(svt, shEyeDirVec);
}

#line 86
float sh2gde_Get_InnerVectorJmsCam(void) {
    return vec3_dot_product(shJmsDirVec, shEyeDirVec);
}

#line 102
void kari_sh2gde_getspotParams(sceVu0FVECTOR spotpos, sceVu0FVECTOR spotdir, sceVu0FVECTOR decayparms) {
    sceVu0FVECTOR tmp; // r29+0x40

    if (sh2gfw_Check_DemoSpotLight()) {
        sh2gde_get_spotposdir(spotpos, spotdir);

        sh2gfw_Get_DemoSpotParm(tmp);
        decayparms[0] = tmp[1];
        decayparms[1] = tmp[3];
        decayparms[2] = tmp[0];
        decayparms[3] = tmp[2];

    } else {
        shGetJamesLightPosOriginal(spotpos, spotdir);

        tmp[0] = Env_ctl.SpotL0.decayparm.fl32[1];
        tmp[1] = Env_ctl.SpotL0.decayparm.fl32[3];
        tmp[2] = Env_ctl.SpotL0.decayparm.fl32[2];
        tmp[3] = Env_ctl.SpotL0.decayparm.fl32[0];
    }

    sceVu0CopyVector(decayparms, tmp);
}

#line 169
void sh2gde_getspotParams_for_Shadow(sceVu0FVECTOR spotpos, sceVu0FVECTOR spotdir, sceVu0FVECTOR decayparms) {
    sceVu0FVECTOR tmp; // r29+0x40

    if (sh2gfw_Check_DemoSpotLight()) {
        sh2gde_get_spotposdir(spotpos, spotdir);
        sh2gfw_Get_DemoSpotParm(tmp);
        decayparms[0] = tmp[1];
        decayparms[1] = tmp[3];
        decayparms[2] = tmp[0];
        decayparms[3] = tmp[2];
    } else {
        shGetJamesLightPosOriginal(spotpos, spotdir);
        shGetJamesLightPos(tmp, spotdir);

        tmp[0] = Env_ctl.SpotL0.decayparm.fl32[1];
        tmp[1] = Env_ctl.SpotL0.decayparm.fl32[3];
        tmp[2] = Env_ctl.SpotL0.decayparm.fl32[2];
        tmp[3] = Env_ctl.SpotL0.decayparm.fl32[0];
    }

    sceVu0CopyVector(decayparms, tmp);
}

#line 212
void sh2gde_getspotKTParams(sceVu0FVECTOR spotpos, sceVu0FVECTOR spotdir, sceVu0FVECTOR spotcol, sceVu0FVECTOR decayparms, int getmode) {
    sceVu0FVECTOR pos;     // r29+0x50
    sceVu0FVECTOR dir_vec; // r29+0x60
    sceVu0FVECTOR tmp;     // r29+0x70

    if (getmode) {
        if (sh2gfw_Check_DemoSpotLight()) {
            sh2gfw_Get_DemoSpotPosDirCol(pos, dir_vec, spotcol);
        } else {
            shGetJamesLightPosOriginal(pos, dir_vec);
            sceVu0CopyVector(spotcol, (float*) &Env_ctl.SpotL0);
        }
        sceVu0CopyVector(spotpos, pos);
        sceVu0CopyVector(spotdir, dir_vec);
    } else if (sh2gfw_Check_DemoSpotLight()) {
        sh2gfw_Get_DemoSpotPosDirCol(spotpos, spotdir, spotcol);
    } else {
        sh2gde_get_spotposdir(spotpos, spotdir);
        sceVu0CopyVector(spotcol, (float*) &Env_ctl.SpotL0);
    }
    if (sh2gfw_Check_DemoSpotLight()) {
        sh2gfw_Get_DemoSpotParm(tmp);
        decayparms[0] = tmp[1];
        decayparms[1] = tmp[3];
        decayparms[2] = tmp[0];
        decayparms[3] = tmp[2];
        return;
    }
    tmp[0] = Env_ctl.SpotL0.decayparm.fl32[1];
    tmp[1] = Env_ctl.SpotL0.decayparm.fl32[3];
    tmp[2] = Env_ctl.SpotL0.decayparm.fl32[0];
    tmp[3] = Env_ctl.SpotL0.decayparm.fl32[2];
    sceVu0CopyVector(decayparms, tmp);
}

#line 281
void sh2gde_getCameraDir(sceVu0FVECTOR cameradir) {
    sh2gde_Get_EyeDir(cameradir);
}

#line 303
void sh2gde_get_spotposdir(sceVu0FVECTOR pos, sceVu0FVECTOR dir) {
    shVectorCopy(pos, Env_ctl.SpotL0.position.fl32);
    shVectorCopy(dir, Env_ctl.SpotL0.dirvec.fl32);
}

#line 321
int sh2gde_CheckSpot_JmsOrBG(void) {
    DrawEnvData* Now = (DrawEnvData*) Get_NowDrawEnvData(); // r2
    ASSERT_ON_LINE(Now!=NULL, 325);
    return Now->spotLNum;
}

#line 338
sceVu0FVECTOR* sh2gde_Get_BGSpotPos(void) {
    DrawEnvData* Now = (DrawEnvData*) Get_NowDrawEnvData(); // r2
    return &Now->Ld_2;
}

#line 344
sceVu0FVECTOR* sh2gde_Get_BGSpotDir(void) {
    DrawEnvData* Now = (DrawEnvData*) Get_NowDrawEnvData(); // r2
    return &Now->Ld_3;
}
