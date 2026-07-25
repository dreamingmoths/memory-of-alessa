#include "Collision/kari_atari_allinit.h"

static int atari_head_index = 0; // size: 0x4, address: 0x4917C8
static int atari_data_num = 0; // size: 0x4, address: 0x4917D0
u_char* CLDadr[CLDADR_NUM]; // size: 0x40, address: 0x4917E0

void kari_init_colidata(void) {
    int i; // r5
    
    atari_head_index = 0;
    
    atari_data_num = 0;
    
    for(i = 0; i < CLDADR_NUM; i++) CLDadr[i] = NULL;

}
