#ifndef SH2SHD_SHADOW_MODEL_H
#define SH2SHD_SHADOW_MODEL_H

#include "sh2_common.h"
#include "Chacter/character.h"
#include "sh2shd/sh2shd_structs.h"
#include "GFW/sh2_GsAllEnv.h"
#include "Heap/utilheap.h"
#include "view/camera_dat.h"

#define SHADOW_CHAR_MAN_SIZE 16
#define SHADOW_OUTDOOR_MAN_SIZE 4

#define SHADOW_OFF_WORK_CHAR_SIZE 2
#define SHADOW_OFF_WORK_CHAR_OBJ_COUNT 22
#define SHADOW_OFF_WORK_BG_SIZE 4
#define SHADOW_OFF_WORK_BG_OBJ_COUNT 32

#define SHADOW_CALC_HEAP_SIZE 0xA0

void sh2shd_init_shadow(void);

void sh2shd_reset_shadow(void);

int sh2shd_add_char(SubCharacter* scp, Q_WORDDATA* raw_data, short light_kind, float* light_pos, float* light_dir, float* light_param);

int sh2shd_Draw_ShadowChar(SubCharacter* scp, void* kg1, short light_kind, float* light_pos, float* light_dir, float* light_param);

int sh2shd_add_map(u_short id, Q_WORDDATA* raw_data, short light_kind, float* light_pos, float* light_dir, float* light_param);

Q_WORDDATA* sh2shd_exe_shadow(CAMERA_DAT* cam);

float get_distance_from_light_to_chara(SHADOW_CHAR_MAN* man, float* iv);

Q_WORDDATA* sh2shd_exe_drop_shadow(CAMERA_DAT* cam);

// void sh2shd_renew_drop_shadow_man(SPOT_LIGHT* spot, CAMERA_DAT* cam, int glb_coord, int map_id);

void sh2shd_make_stencil_drop_shadow_plane(float* plane, float* pos, float* normal);

void sh2shd_make_drop_shadow_plane(float* plane, float* pos, float* normal);

void sh2shd_reset_shadow_off_work(void);

int sh2shd_add_map_to_shadow_off_work(short map_id);

int sh2shd_off_obj(short map_id, short obj_id);

int sh2shd_add_char_to_shadow_off_work(u_short kind, short id);

int sh2shd_off_char_obj(u_short kind, short id, short obj_id);

int sh2shd_off_char_all_parts(u_short kind, short id);

void sh2shd_bg_shadow_off(void);

int check_self_spot(u_short kind);

int check_self_para(u_short kind);

void sh2shd_del_jms_upper_body(u_short kind, short id);

void sh2shd_del_jms_head(u_short kind, short id);

extern short jms_added_flag;                              // size: 0x2, address: 0x11252F0
extern shGsAllEnv shGs_AllEnv;                            // size: 0x2030, address: 0x2AB750
extern SHADOW_MICRO_FRAME shadow_micro_frame_parallel[3]; // size: 0x660, address: 0x11258A0
extern SHADOW_MICRO_FRAME shadow_micro_frame_point;       // size: 0x220, address: 0x1125680
extern SHADOW_MICRO_FRAME shadow_micro_frame[2];          // size: 0x440, address: 0x1125F00
extern SHADOW_OFF_WORK_BG shadow_off_work_bg[4];          // size: 0x108, address: 0x1125340
extern SHADOW_OFF_WORK_CHAR shadow_off_work_char[2];      // size: 0x60, address: 0x1125450
extern Q_WORDDATA Shadow_REFtag_Packet[6400];             // size: 0x19000, address: 0x10F0AF0
extern SHADOW_MAN shadow_man;                             // size: 0x80, address: 0x11254B0
extern Q_WORDDATA Shadow_Kick_Packet[640];                // size: 0x2800, address: 0x1109AF0
extern utilHeapCtrl* shadow_calcheap;                     // size: 0x4, address: 0x10F0AE0
extern Q_WORDDATA Shadow_Calcwork[6400];                  // size: 0x19000, address: 0x110C2F0

static inline void hword_struct_copy(short* _dst, short* _src) {
    // @todo: specific var order needed for match
    short* src;
    short* dst;
    int i;
    dst = _dst;
    i = sizeof(_src);
    src = _src;
    do {
        short w0 = src[0];
        short w1 = src[1];
        src += 2, i--;
        dst[0] = w0;
        dst[1] = w1;
        dst += 2;
    } while (i > 0);
}

#endif // SH2SHD_SHADOW_MODEL_H
