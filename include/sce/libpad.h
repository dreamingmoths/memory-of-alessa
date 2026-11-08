// kudos: https://github.com/OpenGOAL-Mods/OG-Mod-Base/blob/main/game/sce/libpad.h
#ifndef LIB_PAD_H
#define LIB_PAD_H

#include "common.h"

// CONTROLLER STATES
#define scePadStateDiscon	(0)
#define scePadStateFindPad	(1)
#define scePadStateFindCTP1	(2)
#define scePadStateExecCmd	(5)
#define scePadStateStable	(6)
#define scePadStateError	(7)
#define scePadStateClosed	( 99 )

// CONTROLLER MODE CHECK
#define InfoModecurID		(1)
#define InfoModeCurExID		(2)
#define InfoModeCurExOffs	(3)
#define InfoModeIdTable		(4)

// CONTROLLER TYPE
#define DIGITAL_CONTROLLER   4
#define DUALSHOCK_CONTROLLER 7
#define DUALSHOCK2_CONTROLLER DUALSHOCK_CONTROLLER
#define NEGCON_CONTROLLER    2
#define JOYSTICK_CONTROLLER  5
#define NAMCOGUN_CONTROLLER  6

// ASYNC FUNCTIONS RESULT
#define scePadReqStateComplete	(0)
#define scePadReqStateFaild	    (1)
#define scePadReqStateFailed	(1)
#define scePadReqStateBusy	    (2)

int scePadPortOpen(int port, int slot, void* data);
int scePadGetState(int port, int slot);
int scePadInfoMode(int port, int slot, int term, int offs);
int scePadRead(int port, int slot, u_char* data);
int scePadSetActDirect(int port, int slot, u_char* data);
int scePadSetActAlign(int port, int slot, u_char* data);
int scePadSetMainMode(int port, int slot, int offs, int lock);
int scePadGetReqState(int port, int slot);
int scePadInfoAct(int port, int slot, int actno, int term);
int scePadInfoPressMode(int port, int slot);
int scePadEnterPressMode(int port, int slot);

#endif LIB_PAD_H
