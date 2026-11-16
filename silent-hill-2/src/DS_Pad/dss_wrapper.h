#ifndef DSS_WRAPPER_H
#define DSS_WRAPPER_H

float DSS_Wrapper_AllVibrationRatio_Get(void);
int DSS_Wrapper_ActuaterData_Send(u_int ControllerID, u_int ActuaterType, u_int ActuaterLV);
int DSS_Wrapper_AllActuaterData_RealSend_to_Peripheral(void);
void DSS_Wrapper_DualShock2_Sequencer(void);
u_int DSS_Wrapper_DualShock2_Send_ActuaterLV_Get(u_int ControllerID, u_int ActuaterType);
void DSS_Wrapper_DualShock2_Send_ActuaterLV_Claer(u_int ControllerID, u_int ActuaterType);

#endif // DSS_WRAPPER_H
