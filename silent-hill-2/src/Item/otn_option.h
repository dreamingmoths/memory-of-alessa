#ifndef OTN_OPTION_H
#define OTN_OPTION_H

#include "sce/eetypes.h"

static inline void dword_struct_copy(u_int* dst, u_int* src, u_int size) {
    int i = size / 8;
    do {
        int w0 = src[0];
        int w1 = src[1];
        src += 2, i--;
        dst[0] = w0;
        dst[1] = w1;
        dst += 2;
    } while (i > 0);
}

int zs(int hoge /* r2 */);

extern void look_board(void);

int option_main(void);

void option_mainmain(void);

void bright_main(void);

void print_config(int con, int* xx, int yy);

int key_check(void);

void key_type1(void);

void key_type2(void);

void key_type3(void);

void key_conf(int* key_a, int* key_b, u_char important);

void key_conf_check(int key_num, int* i);

void key_color(u_char col);

void config_main(void);

void position_main(void);

void look_bgm(void);

void look_se(void);

int option_near(float f0, float f1, float f2, float f3);

int fade_in(void);

int fade_out(int mode);

void look_board(void);

void look_cur(void);

void allow_u(int x, int y);

void allow_d(int x, int y);

void allow_l(int x, int y);

void allow_r(int x, int y);

void KeyConfigPictureLoad(void);

void KeyConfigPitureStart(void);

void key_draw(int key_kind, int xx, int yy);

void option_font(void);

void look_scr(void);

int zs(int hoge);

#endif // OTN_OPTION_H
