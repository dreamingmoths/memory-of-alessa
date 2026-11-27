#ifndef SH2_GET_DRAWENV_H
#define SH2_GET_DRAWENV_H

void sh2gfw_Set_EyeDir(void);

void sh2gde_Get_EyeDir(sceVu0FVECTOR svt);

float sh2gde_Get_InnerVectorJmsCam(void);

void kari_sh2gde_getspotParams(sceVu0FVECTOR spotpos, sceVu0FVECTOR spotdir, sceVu0FVECTOR decayparms);

void sh2gde_getspotParams_for_Shadow(sceVu0FVECTOR spotpos, sceVu0FVECTOR spotdir, sceVu0FVECTOR decayparms);

void sh2gde_getspotKTParams(sceVu0FVECTOR spotpos, sceVu0FVECTOR spotdir, sceVu0FVECTOR spotcol, sceVu0FVECTOR decayparms, int getmode);

void sh2gde_getCameraDir(sceVu0FVECTOR cameradir);

void sh2gde_get_spotposdir(sceVu0FVECTOR pos, sceVu0FVECTOR dir);

int sh2gde_CheckSpot_JmsOrBG(void);

sceVu0FVECTOR* sh2gde_Get_BGSpotPos(void);

sceVu0FVECTOR* sh2gde_Get_BGSpotDir(void);


extern void sh2gde_getWorldScreenMatrix(sceVu0FMATRIX wsm);

extern void sh2gde_getWorldViewMatrix(sceVu0FMATRIX wsm);


#endif // SH2_GET_DRAWENV_H
