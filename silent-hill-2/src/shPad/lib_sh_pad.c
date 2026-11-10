#include "sce/libpad.h"
#include "shPad/lib_sh_pad.h"

#pragma optimization_level 3

#define LISTEN_FOR_TOGGLE(mode)                                                                   \
    check_mode = *mode;                                                                           \
    while (step != 0x11) {                                                                        \
        if (                                                                                      \
            (check_mode & 0x10) && (check_mode & 2) || (check_mode & 0x20) && (check_mode & 1)) { \
            step = 0x11;                                                                          \
        } else {                                                                                  \
            break;                                                                                \
        }                                                                                         \
    }

enum LIB_SH_PAD_STEPS {
    OPEN_PORT               = 0x0,
    UNKNOWN                 = 0x10,
    SET_CURID               = 0x11,
    RETRY_CURID             = 0x12,
    CHECK_PRESSMODE_SUPPORT = 0x20,
    ENTER_PRESSMODE         = 0x21,
    RETRY_PRESSMODE         = 0x22,
    SET_VIBRATIONMODE       = 0x30,
    RETRY_VIBRATIONMODE     = 0x31,
    FINISH_SUB              = 0x40,
    CHECK_TOGGLE            = 0x41

};

typedef struct shPadData {
    u_char pd[32];        // data from scePadRead
    u_char read_data;     // return value of scePadRead
    u_char should_vibrate;
    u_char actuator[6];   // actuator parameters for vibration motors
    u_char curID;         // upper half holds controller id whilst lower half holds controller id offset
    u_char pressMode;     // upper half holds pressure sensitivity status whilst lower half holds status to be set
    u_char analogMode;    // upper half holds analog lock status whilst lower half holds lock status to be set
    u_char vibrationMode; // used for vibration.
    u_char isAvailable;   // is controller available
    u_char subUnfinished; // used to indicate whether we traversed every step in libShPadSlotTransSub
    u_char reserved[18];
} shPadData;

static int libShPadSlotTrans(int port, int slot);

static u_short libShPadSlotTransSub(int port, int slot, u_short step);

static int libShPadPortTrans(int port);

u_long128* libShPadDmaBuffer[2][4] = {};
u_short    libShPadStep[2][4]      = {};
shPadData* libShPadData[2][4]      = {};

// INCLUDE_ASM("asm/nonmatchings/shPad/lib_sh_pad", libShPadEnable00);
void libShPadEnable00(void) {
    static shPadData data;
    static u_long128 buffer[16] __attribute__(( aligned(64) ));

    libShPadDmaBuffer[0][0] = &buffer;
    libShPadData[0][0]      = &data;
}

// INCLUDE_ASM("asm/nonmatchings/shPad/lib_sh_pad", libShPadEnable10);
void libShPadEnable10(void) {
    static shPadData data;
    static u_long128 buffer[16] __attribute__(( aligned(64) ));

    libShPadDmaBuffer[1][0] = &buffer;
    libShPadData[1][0]      = &data;
}

// INCLUDE_ASM("asm/nonmatchings/shPad/lib_sh_pad", libShPadInit);
void libShPadInit(void) {
    int i, j;

    scePadInit(0);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            libShPadStep[i][j] = 0;
        }
    }
}

// INCLUDE_ASM("asm/nonmatchings/shPad/lib_sh_pad", libShPadStart);
void libShPadStart(int port, int slot) {
    shPadData* paddata;

    paddata = libShPadData[port][slot];
    if (paddata != NULL) {
        paddata->isAvailable = paddata->isAvailable & ~2;
        paddata->isAvailable = paddata->isAvailable | 1;
    }
}

// INCLUDE_ASM("asm/nonmatchings/shPad/lib_sh_pad", libShPadSetMode);
void libShPadSetMode(int port, int slot, u_int controller_id, u_int press_mode, u_int analog_mode, u_int vibration_mode) {
    shPadData* paddata = libShPadData[port][slot];

    if (paddata != NULL) {
        paddata->subUnfinished = 1;
        paddata->curID          |= controller_id &= 3;
        paddata->pressMode      |= press_mode &= 3;
        paddata->analogMode     |= analog_mode &= 3;
        paddata->vibrationMode  |= vibration_mode &= 3;
    }
}

// INCLUDE_ASM("asm/nonmatchings/shPad/lib_sh_pad", libShPadSlotTrans);
int libShPadSlotTrans(int port, int slot) {
    libShPadStep[port][slot] = libShPadSlotTransSub(port, slot, libShPadStep[port][slot]);
    return libShPadStep[port][slot];
}

// INCLUDE_ASM("asm/nonmatchings/shPad/lib_sh_pad", libShPadSlotTransSub);
u_short libShPadSlotTransSub(int port, int slot, u_short step) {
    shPadData* paddata;
    int pad_state;
    u_char check_mode;

    paddata = libShPadData[port][slot];

    if (paddata != NULL && step != OPEN_PORT && step != UNKNOWN) {
        paddata->read_data = scePadRead(port, slot, paddata->pd);
        if ((paddata->should_vibrate != 0) && (paddata->vibrationMode & 0x10)) {
            paddata->should_vibrate = 0;
            scePadSetActDirect(port, slot, &paddata->actuator);
        }
    }

    if (step == OPEN_PORT || step == UNKNOWN)
        pad_state = scePadStateDiscon;
    else
        pad_state = scePadGetState(port, slot);

    switch (pad_state) {
        case scePadStateDiscon:
        case scePadStateError:
            if (paddata != NULL) {
                paddata->curID         &= ~0x30;
                paddata->pressMode     &= ~0x30;
                paddata->analogMode    &= ~0x30;
                paddata->vibrationMode &= ~0x30;
            }
            if (step != 0) {
                return SET_CURID;
            }
            break;
        case scePadStateFindPad:
        case scePadStateExecCmd:
            return step;
    }

    switch (step) {
        case OPEN_PORT:
            if (paddata == NULL)
                return step;
            if (paddata->isAvailable & 1) {
                if (libShPadStep[port][slot] == 0) {
                    if ((libShPadDmaBuffer[port][slot] != NULL) && (scePadPortOpen(port, slot, libShPadDmaBuffer[port][slot]) == 1)) {
                        step = UNKNOWN;
                    }
                }
            }
            return step;
        case UNKNOWN:
            step = SET_CURID;
        /* fallthrough */
        case SET_CURID: {
            u_char* analogMode;
            u_char* curID;
            u_char* pressMode;

            int controller_id;
            int controller_mode_id_offset;
            int analog_switch_lock;

            u_char new_analog_mode;
            u_char new_curid;

            curID      = &paddata->curID;
            analogMode = &paddata->analogMode;
            pressMode  = &paddata->pressMode;

            new_analog_mode = *analogMode;
            // table is empty?
            if (scePadInfoMode(port, slot, InfoModeIdTable, -1) == 0) {
                // current controller mode id
                controller_id = scePadInfoMode(port, slot, InfoModecurID, 0);

                new_analog_mode &= ~0x10;
                *analogMode = new_analog_mode |= 0x20;

                new_curid = *curID;
                new_curid &= ~0x30;

                //
                if (controller_id == DIGITAL_CONTROLLER) {
                    new_curid |= 0x20;
                } else {
                    new_curid |= 0x10;
                }

                *curID = new_curid;

                check_mode = *pressMode;
                check_mode &= ~0x10;
                *pressMode = check_mode |= 0x20;

                return SET_VIBRATIONMODE;
            }

            if (new_analog_mode & 2) {
                analog_switch_lock = 2;
            } else if (new_analog_mode & 1) {
                analog_switch_lock = 3;
            } else {
                analog_switch_lock = 2;
            }

            new_analog_mode &= ~0x30;

            // lock switch is unlocked
            if (analog_switch_lock == 2) {
                new_analog_mode |= 0x20;
            } else {
                new_analog_mode |= 0x10;
            }

            *analogMode = new_analog_mode;

            // check if lower half of curID has the controller id offset
            if (*curID & 2) {
                controller_mode_id_offset = 0;
            } else if (*curID & 1) {
                controller_mode_id_offset = 1;
            } else {
                // curl up and cry, then query scePadInfoMode
                controller_mode_id_offset = scePadInfoMode(port, slot, InfoModeCurExOffs, 0);
            }
            // request to lock/unlock analog lock failed
            if (scePadSetMainMode(port, slot, controller_mode_id_offset, analog_switch_lock) != 0) {
                if (controller_mode_id_offset == 1) {
                    return RETRY_CURID;
                }
                // switching from analog to digital and vice versa
                // may exit pressure sensitive mode; Therefore, pressMode should be updated.
                check_mode = *pressMode;
                check_mode &= ~0x10;
                *pressMode = check_mode |= 0x20;

                return SET_VIBRATIONMODE;
            }
        } break;
        case RETRY_CURID:
            // scePadSetMainMode is considered an async function; Therefore,
            // we use scePadGetReqState to check if execution was successful.
            // If not, we set step to 0x11 which will send us back to the previous case.
            // (essentially, retrying)
            // Otherwise, we will continue to the next case
            switch (scePadGetReqState(port, slot)) {
                case scePadReqStateFailed:
                    return SET_CURID;
                case scePadReqStateComplete:
                    // (we aren't doing anything with this?)
                    scePadInfoMode(port, slot, InfoModecurID, 0);
                    return CHECK_PRESSMODE_SUPPORT;
            }
            break;
        case CHECK_PRESSMODE_SUPPORT: {
            u_char* pressMode;

            check_mode = paddata->pressMode;
            check_mode &= ~0x30;
            pressMode = &paddata->pressMode;

            if (check_mode & 1) {
                // current controller supports pressure sensitivity
                // @bug: docs say this will return "other than 1" if it didn't, which might not be zero
                if (scePadInfoPressMode(port, slot) != 0) {
                    *pressMode = check_mode;
                    return ENTER_PRESSMODE;
                }
            }
            *pressMode = check_mode | 0x20;
            return SET_VIBRATIONMODE;
        }
        case ENTER_PRESSMODE:
            // failed to request pressure-sensitivity
            if (scePadEnterPressMode(port, slot) != 0) {
                return RETRY_PRESSMODE;
            }

            paddata->pressMode |= 0x20;
            return SET_VIBRATIONMODE;
        case RETRY_PRESSMODE:
            switch (scePadGetReqState(port, slot)) {
                case scePadReqStateFailed:
                    return ENTER_PRESSMODE;
                case scePadReqStateComplete:
                    check_mode = paddata->pressMode & (u32) (u_char) ~0x30;
                    check_mode |= 0x10;
                    paddata->pressMode = check_mode;
                    return SET_VIBRATIONMODE;
            }
            break;
        case SET_VIBRATIONMODE: {
            u_char* vibrationMode;

            check_mode = paddata->vibrationMode;
            check_mode &= ~0x30;
            vibrationMode = &paddata->vibrationMode;

            if (check_mode & 1) {
                // couldn't send actuator params to controller
                if (scePadSetActAlign(port, slot, "\00\01\xff\xff\xff\xff\xff") != 0) {
                    *vibrationMode = check_mode;
                    return RETRY_VIBRATIONMODE;
                }
            }

            *vibrationMode = check_mode | 0x20;
            return FINISH_SUB;
        }
        case RETRY_VIBRATIONMODE:
            switch (scePadGetReqState(port, slot)) {
                case scePadReqStateFailed:
                    return SET_VIBRATIONMODE;
                case scePadReqStateComplete:
                    paddata->should_vibrate = 1;
                    check_mode              = paddata->vibrationMode;
                    check_mode &= ~0x30;

                    paddata->vibrationMode = check_mode |= 0x10;
                    return FINISH_SUB;
            }
            break;
        case FINISH_SUB:
            if (!(paddata->analogMode & 0x11)) {
                paddata->curID &= ~0x3;
            }
            paddata->subUnfinished = 0;
            step                   = CHECK_TOGGLE;
            break;
        case CHECK_TOGGLE: {

            u_char* curID         = &paddata->curID;
            u_char* analogMode    = &paddata->analogMode;
            u_char* pressMode     = &paddata->pressMode;
            u_char* vibrationMode = &paddata->vibrationMode;

            if (paddata->subUnfinished != 0) {
                step = SET_CURID;
            }

            LISTEN_FOR_TOGGLE(curID);

            if (scePadInfoMode(port, slot, InfoModeCurExOffs, 0) == 1) {
                LISTEN_FOR_TOGGLE(pressMode);
            }

            LISTEN_FOR_TOGGLE(analogMode);

            LISTEN_FOR_TOGGLE(vibrationMode);
        }
            return step;
    }
    return step;
}

RODATA_PAD_TO(0x0038FDA0);

// INCLUDE_ASM("asm/nonmatchings/shPad/lib_sh_pad", libShPadPortTrans);
int libShPadPortTrans(int port) {
    int ret;
    int slot;

    for (slot = 0; slot < 4; slot++)
        ret = (libShPadSlotTrans(port, slot) != 0) << slot;
    return ret;
}

// INCLUDE_ASM("asm/nonmatchings/shPad/lib_sh_pad", libShPadTrans);
int libShPadTrans(void) {
    int ret;
    int port;
    int temp;

    for (port = 0, temp = 0; port < 2; port++, temp += 4) {
        ret = libShPadPortTrans(port) << temp;
    }
    return ret;
}

// INCLUDE_ASM("asm/nonmatchings/shPad/lib_sh_pad", libShPadRead);
s_char libShPadRead(int port, int slot, char* data) {
    int i;
    int ret;
    shPadData* paddata;
    s_char* pad;

    paddata = libShPadData[port][slot];
    pad     = paddata->pd;
    ret     = paddata ? (s_char) paddata->read_data : 0;

    for (i = 0; i < ret; i++)
        data[i] = pad[i];

    for (; i < 0x20; i++)
        data[i] = 0;

    if (data[0x1] != 0) {
        data[0x2] = ~data[0x2];
        data[0x3] = ~data[0x3];
    }
    return ret;
}

int libShPadSend(int port, int slot, u_short pow0, u_short pow1) {
    int ret;
    shPadData* paddata;
    u_char old_act0;
    u_char old_act1;
    u_char temp_v1;
    int temp;

    ret     = 0;
    paddata = libShPadData[port][slot];
    if (paddata != NULL) {

        old_act0 = paddata->actuator[0];
        old_act1 = paddata->actuator[1];

        temp_v1 = pow0 >> 8;

        pow0 &= (u_char) ~temp_v1;
        pow0 = (pow0 | (old_act0 & temp_v1));
        ret  = old_act0 != pow0;

        if (ret != 0) {
            paddata->actuator[0] = pow0;
        }

        temp_v1 = (pow1 >> 8);

        pow1 &= (u_char) ~temp_v1;
        pow1 |= (u_char) old_act1 & (u_int) temp_v1;

        if (old_act1 != pow1) {
            paddata->actuator[1] = pow1;
            ret |= 1;
        }
        paddata->should_vibrate = ret;
    }
    return ret;
}
