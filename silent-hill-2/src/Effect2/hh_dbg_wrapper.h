#ifndef HH_DBG_WRAPPER_H
#define HH_DBG_WRAPPER_H

#include "sh2_common.h"

u_int HH_DBG_Wrapper_Controller_KeyAssign_Check(u_int ControllerID, u_int Mode, u_int Check_Assign);

void HH_DBG_Wrapper_Printf(void);

void HH_DBG_Wrapper_T0_COUNT_Get(void);

void HH_DBG_Wrapper_T0_COUNT_Delta(void);


#endif // HH_DBG_WRAPPER_H
