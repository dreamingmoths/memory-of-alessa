#ifndef SH2_JMSSPOT_MAN_H
#define SH2_JMSSPOT_MAN_H

#include "sh2_common.h"

// total size: 0x44
typedef struct James_SpotLight_Man {
    // Members
    short GunFlg; // offset 0x0, size 0x2
    short Spot_Light_OnOff; // offset 0x2, size 0x2
    short MicroCodeMode; // offset 0x4, size 0x2
    short MicroChange; // offset 0x6, size 0x2
    short SpotTime; // offset 0x8, size 0x2
    short MaxTime; // offset 0xA, size 0x2
    short MinTime; // offset 0xC, size 0x2
    short SDt; // offset 0xE, size 0x2
    short DarkTrimMax; // offset 0x10, size 0x2
    short DarkDt; // offset 0x12, size 0x2
    short NowDarkParm; // offset 0x14, size 0x2
    short Pads; // offset 0x16, size 0x2
    short FlickerRatio; // offset 0x18, size 0x2
    short FlickerTime; // offset 0x1A, size 0x2
    short FlickerMaxTime; // offset 0x1C, size 0x2
    short FlickerFlg; // offset 0x1E, size 0x2
    float Gun_Refrection; // offset 0x20, size 0x4
    float MaxIntensity; // offset 0x24, size 0x4
    float MinIntensity; // offset 0x28, size 0x4
    float NowIntensity; // offset 0x2C, size 0x4
    float MaxAlpha; // offset 0x30, size 0x4
    float MinAlpha; // offset 0x34, size 0x4
    float NowAlpha; // offset 0x38, size 0x4
    float IntensityFactor; // offset 0x3C, size 0x4
    float DarkFactor; // offset 0x40, size 0x4
} James_SpotLight_Man;

// total size: 0x40
typedef struct DynamicLight {
    // Members
    sceVu0FVECTOR NowCamDir; // offset 0x0, size 0x10
    sceVu0FVECTOR BeforeCamDir; // offset 0x10, size 0x10
    sceVu0FVECTOR NowDir; // offset 0x20, size 0x10
    sceVu0FVECTOR BeforeDir; // offset 0x30, size 0x10
} DynamicLight;

void sh2gfw_ALLInit_SpotMan(void);
void sh2gfw_Propagate_JmsGunLight(void);
void sh2gfw_Set_JmsGunLight(void);
float sh2gfw_Get_JmsGunLight(void);
float sh2gfw_Get_GunLight(void);
void sh2gfw_Clear_MicroChange(void);
void sh2gfw_Set_MicroChange(void);
void sh2gfw_Change_MicroFLGS(void);
int sh2gfw_Check_MicroCode(void);
void sh2gfw_Set_MicroCode(int xx);
float sh2gfw_Get_DarkTrimFactor(void);
int sh2gfw_Check_JmsSpotOnOff(void);
void sh2gfw_On_JmsSPOT(void);
void sh2gfw_Off_JmsSPOT(void);
void sh2gfw_ForceOff_JmsSPOT(void);
void sh2gfw_ForceOn_JmsSPOT(void);
void Programed_Light_Set(void);

extern James_SpotLight_Man JmsSpotMan;

#endif // SH2_JMSSPOT_MAN_H
