#include "common.h"
#include "SH2_common/playing_info.h"
#include "DS_Pad/ds_sequencer.h"

UNMIGRATED(/* static */ u_char _Peripheral_Controller_SendData[2][6]);
UNMIGRATED(/* static */ u_int _edit_flag);
UNMIGRATED(/* static */ u_int _sequencer_init);

//#line 89
float DSS_Wrapper_AllVibrationRatio_Get(void) {
    float result = 0.0f;
    
    
    switch (playing.vibration) {
        case 1:
            result = 0.6f;
            break;
        case 2:
            result = 0.8f;
            break;
         case 3: 
            result = 1.0f;
            break;
        case 0: 
            break;
    }





    return result;
}

//#line 153
int DSS_Wrapper_ActuaterData_Send(u_int ControllerID, u_int ActuaterType, u_int ActuaterLV) {
    _Peripheral_Controller_SendData[ControllerID][ActuaterType] = ActuaterLV;


    
    
    
    return 1;
}

//#line 193
int DSS_Wrapper_AllActuaterData_RealSend_to_Peripheral(void) {
    return 1;
}

//#line 297
void DSS_Wrapper_DualShock2_Sequencer(void) {
    if (_edit_flag == 0) {
        
        if (_sequencer_init == 0) {
            DSR_Sequencer_Initialize();
            DSR_Sequence_Different_Time_Set(1.0f/60.0f);
            _sequencer_init = 1;
        }
        DSR_Sequencer();
    }
    DSS_Wrapper_AllActuaterData_RealSend_to_Peripheral();
}

//#line 317
u_int DSS_Wrapper_DualShock2_Send_ActuaterLV_Get(u_int ControllerID, u_int ActuaterType) {
    return _Peripheral_Controller_SendData[ControllerID][ActuaterType];
}

//#line 323
void DSS_Wrapper_DualShock2_Send_ActuaterLV_Claer(u_int ControllerID, u_int ActuaterType) {
    _Peripheral_Controller_SendData[ControllerID][ActuaterType] = 0;
}
