#ifndef SH2GFW_2D_FILTERS_H
#define SH2GFW_2D_FILTERS_H

#include "common.h"

// total size: 0x30
typedef struct FilterParams {
    // Members
    short base_Ix; // offset 0x0, size 0x2
    short base_Iy; // offset 0x2, size 0x2
    short FO_timer; // offset 0x4, size 0x2
    short Max_Timer; // offset 0x6, size 0x2
    char TargetSec; // offset 0x8, size 0x1
    char FIO_ratio; // offset 0x9, size 0x1
    char blurMode; // offset 0xA, size 0x1
    char blurRatio; // offset 0xB, size 0x1
    char LesserA; // offset 0xC, size 0x1
    char GreaterA; // offset 0xD, size 0x1
    char sw_flg; // offset 0xE, size 0x1
    char dp_flg; // offset 0xF, size 0x1
    u_char SoftIter; // offset 0x10, size 0x1
    u_char SoftCit; // offset 0x11, size 0x1
    u_char SoftAref; // offset 0x12, size 0x1
    char SoftMode; // offset 0x13, size 0x1
    char SoftShift; // offset 0x14, size 0x1
    char TrimAlpha; // offset 0x15, size 0x1
    short TexTrimEX; // offset 0x16, size 0x2
    short TexTrimEY; // offset 0x18, size 0x2
    short TexTrimSX; // offset 0x1A, size 0x2
    short TexTrimSY; // offset 0x1C, size 0x2
    int DOF_ZDepth; // offset 0x20, size 0x4
    u_char KeyAlpha; // offset 0x24, size 0x1
    u_char testkind; // offset 0x25, size 0x1
    u_char S1_iter; // offset 0x26, size 0x1
    u_char S1_alpha; // offset 0x27, size 0x1
    char S1_shift; // offset 0x28, size 0x1
    char S1_baseIX; // offset 0x29, size 0x1
    u_char S2_iter; // offset 0x2A, size 0x1
    u_char S2_alpha; // offset 0x2B, size 0x1
    char S2_shift; // offset 0x2C, size 0x1
    char S2_baseIX; // offset 0x2D, size 0x1
} FilterParams;

// total size: 0xA0
typedef struct FilterWork {
    // Members
    int GsFilterKind; // offset 0x0, size 0x4
    int Flg; // offset 0x4, size 0x4
    int Kind_History; // offset 0x8, size 0x4
    int mode; // offset 0xC, size 0x4
    union Q_WORDDATA FilterData[8]; // offset 0x10, size 0x80
    union Q_WORDDATA CopyFilterColor; // offset 0x90, size 0x10
} FilterWork;

void* sh2gfw_Get_FilterCommandParams(void);
void sh2gfw_Reset_FilterCommand(void);
void sh2gfw_Set_FadeIn_Black(float ra /* r20 */);
void sh2gfw_Set_FadeIn_Red(float ra /* r20 */);
void sh2gfw_Set_FadeIn_White(float ra /* r20 */);
void sh2gfw_Set_FadeOutRetain_Black(float ra /* r20 */);
void sh2gfw_Set_FadeOutRetain_Red(double ra /* r20 */);
void sh2gfw_Set_FadeOutRetain_White(float ra /* r20 */);
void sh2gfw_Set_FadeOut_Black(float ra /* r20 */);
void sh2gfw_Set_FadeOut_White(float ra /* r20 */);
void sh2gfw_Set_FilterBlur(int rt /* r16 */);
void sh2gfw_Black_Clear(void);

extern FilterWork shGsFilterWork;

#endif // SH2GFW_2D_FILTERS_H
