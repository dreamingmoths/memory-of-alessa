#ifndef SH2SHD_CHAR_JMS_H
#define SH2SHD_CHAR_JMS_H

#include "sce/eetypes.h"
#include "Chacter/character.h"
#include "sh2shd/sh2shd_structs.h"

void sh2shd_init_char_man(SHADOW_CHAR_MAN* man, SubCharacter* scp, Q_WORDDATA* raw_data, u_short kind, short id, int light_kind, float* light_pos, float* light_dir, float* light_param);
void sh2shd_make_reftag_pool_char(SHADOW_CHAR_MAN* man, SHADOW_PACKET_BUF* ref_packet, Q_WORDDATA* rawdata);
void sh2shd_make_reftag_pool_char_p_maria(SHADOW_CHAR_MAN* man, SHADOW_PACKET_BUF* ref_packet, Q_WORDDATA* rawdata);
void sh2shd_add_char_to_kick_packet(SHADOW_CHAR_MAN* man, SHADOW_PACKET_BUF* kick_packet);
// void sh2shd_renew_char_man(SHADOW_CHAR_MAN* man, float* spot_pos, float leng, SHADOW_ENV* shadow_env);
// void sh2shd_renew_char_man_for_spot(SHADOW_CHAR_MAN* man, float* spot_pos, SHADOW_ENV* shadow_env);
void sh2shd_renew_char_man_parallel(SHADOW_CHAR_MAN* man, float* virtual_light_position);
void sh2shd_calc_light_position_for_self(float* light_pos, u_short kind, short id, JMS_SHADOW_ENV* env, float height);
void sh2shd_calc_light_position_for_self_spot(float* light_pos, u_short kind, short id, JMS_SHADOW_ENV* env, float* chara_pos, float height);
void sh2shd_make_reftag_pool_char_for_drop_with_order(SHADOW_CHAR_MAN* man, SHADOW_PACKET_BUF* ref_packet, Q_WORDDATA* rawdata);
void sh2shd_make_reftag_pool_char_for_drop_with_order_p_maria(SHADOW_CHAR_MAN* man, SHADOW_PACKET_BUF* ref_packet, Q_WORDDATA* rawdata);
void sh2shd_renew_char_man_for_drop(SHADOW_CHAR_MAN* man, float* spot_pos, float alpha_decay);
void sh2shd_get_height_for_alpha(float* high, float* low, u_short kind, u_short id);
int sh2shd_get_shape_no(u_short kind, int skel_no);
int sh2shd_get_shape_no_jms(int skel_no);
int sh2shd_get_shape_no_mar(int skel_no);
int sh2shd_get_shape_no_p_mar(int skel_no);
int sh2shd_get_shape_no_scu(int skel_no);
int sh2shd_get_shape_no_mkn(int skel_no);
int sh2shd_get_shape_no_nse(int skel_no);
int sh2shd_get_shape_no_red(int skel_no);
int sh2shd_get_shape_no_oni(int skel_no);
int sh2shd_get_shape_no_edb(int skel_no);

#endif // SH2SHD_CHAR_JMS_H
