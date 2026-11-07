#ifndef SH2_SHADOW_FILTERS_H
#define SH2_SHADOW_FILTERS_H

#include "sh2_common.h"

void sh2gfw_Set_FilterData(int NoD, Q_WORDDATA* col);

void* Get_ShadowColor(void);

void sh2gfw_Set_ShadowColorScaleFactor(float fc);

Q_WORDDATA* shdw_Composite_Shadow(Q_WORDDATA* pbuf);

Q_WORDDATA* shdw_fill_Work(Q_WORDDATA* col, u_int prim, Q_WORDDATA* pbuf);

Q_WORDDATA* shdw_clear(Q_WORDDATA* pbuf);

Q_WORDDATA* shdw_StencilBuf2Work(u_int tbp, u_int prim, Q_WORDDATA* pbuf);

Q_WORDDATA* shdw_Work2Work(u_int tbp, Q_WORDDATA* pbuf);

void shdw_shadow_filter_main(void);

#endif // SH2_SHADOW_FILTERS_H
