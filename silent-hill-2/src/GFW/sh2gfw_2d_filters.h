#ifndef SH2GFW_2D_FILTERS_H
#define SH2GFW_2D_FILTERS_H

#include "common.h"

void sh2gfw_Reset_FilterCommand(void);
void sh2gfw_Set_FadeIn_Black(float ra /* r20 */);
void sh2gfw_Set_FadeIn_Red(float ra /* r20 */);
void sh2gfw_Set_FadeIn_White(float ra /* r20 */);
void sh2gfw_Set_FadeOutRetain_Black(float ra /* r20 */);
void sh2gfw_Set_FadeOutRetain_Red(double ra /* r20 */);
void sh2gfw_Set_FadeOutRetain_White(float ra /* r20 */);
void sh2gfw_Set_FadeOut_Black(float ra /* r20 */);
void sh2gfw_Set_FadeOut_White(float ra /* r20 */);

#endif // SH2GFW_2D_FILTERS_H
