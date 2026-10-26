#ifndef SH2_JMSSPOT_MAN_H
#define SH2_JMSSPOT_MAN_H

#include "sh2_common.h"

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

#endif // SH2_JMSSPOT_MAN_H
