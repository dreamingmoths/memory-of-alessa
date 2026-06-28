#ifndef SH2_GET_DRAWENV_H
#define SH2_GET_DRAWENV_H

void sh2gde_getWorldScreenMatrix(float (* wsm)[4]);

void sh2gde_getWorldViewMatrix(float (* wsm)[4]);

float (* sh2gde_Get_BGSpotPos())[4];

float (* sh2gde_Get_BGSpotDir())[4];

#endif // SH2_GET_DRAWENV_H
