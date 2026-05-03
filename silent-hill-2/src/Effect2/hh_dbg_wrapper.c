#include "common.h"
#include "eeregs.h"

int _t0_count;
int _t0_count_max;
char* tmp;

u_int HH_DBG_Wrapper_Controller_KeyAssign_Check(u_int ControllerID, u_int Mode, u_int Check_Assign) {
    int result = 0;

    switch (Mode) {                                 /* irregular */
        case 0:
            return shPadTrigger(ControllerID, Check_Assign);
        case 1:
            return shPadPress(ControllerID, Check_Assign);
        case 2:
            result = shPadRepeat(ControllerID, Check_Assign);
            /* fallthrough */
        case 3:
            return result;
        default:
            return 0;
    }
}

void HH_DBG_Wrapper_Printf(int, int, void*) {

}

void HH_DBG_Wrapper_T0_COUNT_Get(void) {
    _t0_count = *T0_COUNT;
}

void HH_DBG_Wrapper_T0_COUNT_Delta(void) {
    
    int current_t0_count = *T0_COUNT;
    int delta = current_t0_count - _t0_count;
    
    
    if ((u_int) _t0_count_max < delta) {
        _t0_count_max = delta;
    }
    if (HH_DBG_Wrapper_Controller_KeyAssign_Check(0, 0, 0x8000) != 0) {
        _t0_count_max = 0;
    }
    sprintf(&tmp, "T0_COUNT Delta = %d\n", delta);
    HH_DBG_Wrapper_Printf(0x100, 0xe0, &tmp);
    sprintf(&tmp, "T0_COUNT Max   = %d\n", _t0_count_max);
    HH_DBG_Wrapper_Printf(0x100, 0xd8, &tmp);
}
