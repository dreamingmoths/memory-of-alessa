#ifndef SH2SHD_CHAR_JMS_H
#define SH2SHD_CHAR_JMS_H

#include "sce/eetypes.h"
#include "Chacter/character.h"
#include "sh2shd/sh2shd_structs.h"

extern void sh2shd_init_char_man(SHADOW_CHAR_MAN* man, SubCharacter* scp, union Q_WORDDATA* raw_data, u_short kind, short id, int light_kind, float* light_pos, float* light_dir, float* light_param);

#endif // SH2SHD_CHAR_JMS_H
