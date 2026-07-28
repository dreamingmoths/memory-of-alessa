#ifndef SH2_GET_DRAWENV_H
#define SH2_GET_DRAWENV_H

void kari_sh2gde_getspotParams(float* spotpos /* r18 */, float* spotdir /* r17 */, float* decayparms /* r16 */);

void sh2gde_getWorldScreenMatrix(float (* wsm)[4]);

void sh2gde_getWorldViewMatrix(float (* wsm)[4]);

float (* sh2gde_Get_BGSpotPos())[4];

float (* sh2gde_Get_BGSpotDir())[4];

#endif // SH2_GET_DRAWENV_H
