#include "sh2shd/sh2shd_char_jms.h"

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_init_char_man);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_make_reftag_pool_char);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_make_reftag_pool_char_p_maria);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_add_char_to_kick_packet);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_renew_char_man);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_renew_char_man_for_spot);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_renew_char_man_parallel);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_calc_light_position_for_self);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_calc_light_position_for_self_spot);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_make_reftag_pool_char_for_drop_with_order);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_make_reftag_pool_char_for_drop_with_order_p_maria);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_renew_char_man_for_drop);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_get_height_for_alpha);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_get_shape_no);

int sh2shd_get_shape_no_jms(int skel_no) {
    switch (skel_no) {
        
        case 26:
            return 0;
            
        case 25:
            return 1;
            
        case 14:
            return 2;
            
        case 13:
            return 3;
            
        case 5:
            return 4;
            
        case 4:
            return 5;
            
        case 1:
            return 6;
            
        case 3:
            return 7;
            
        case 28:
            return 8;
            
        case 27:
            return 9;
            
        case 34:
            return 10;
            
        case 33:
            return 11;
            
        case 35:
            return 12;
            
        case 40:
            return 13;
            
        case 8:
            return 14;
            
        case 15:
            return 15;
    }
}

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_get_shape_no_mar);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_get_shape_no_p_mar);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_char_jms", sh2shd_get_shape_no_scu);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_char_jms", @1037_0x0038FDA0);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_char_jms", @1038_0x0038FDD0);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_char_jms", @1091_0x0038FE10);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_char_jms", @1153);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_char_jms", @1154_0x0038FE70);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_char_jms", @1280);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_char_jms", @1319);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_char_jms", @1387);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_char_jms", @1388);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_char_jms", @1541_0x0038FF50);

INCLUDE_RODATA("asm/nonmatchings/sh2shd/sh2shd_char_jms", @1575);

int sh2shd_get_shape_no_mkn(int skel_no) {
    switch (skel_no) {
        
        case 0:
            return 6;
        
        case 1:
            return 7;
        
        case 2:
            return 8;
        
        case 4:
            return 4;
        
        case 3:
            return 5;
        
        case 5:
            return 10;
        
        case 7:
            return 9;
        
        case 9:
            return 12;
        
        case 10:
            return 3;
        
        case 11:
            return 11;
        
        case 12:
            return 2;
        
        case 13:
            return 1;
        
        case 14:
            return 0;
    }
}

int sh2shd_get_shape_no_nse(int skel_no) {
    switch (skel_no) {
        
        case 13:
            return 0;
    
        case 12:
            return 1;
    
        case 8:
            return 2;
    
        case 6:
            return 3;
    
        case 5:
            return 4;
    
        case 4:
            return 5;
    
        case 1:
            return 6;
    
        case 0:
            return 7;
    
        case 2:
            return 8;
    
        case 24:
            return 9;
    
        case 23:
            return 10;
    
        case 20:
            return 11;
    
        case 19:
            return 12;
    
        case 16:
            return 13;
    
        case 15:
            return 14;
    
        case 7:
            return 15;
    
        case 9:
            return 16;
    }
}

int sh2shd_get_shape_no_red(int skel_no) {
    switch (skel_no) {
        
        case 12:
            return 0;

        case 13:
            return 1;

        case 7:
            return 2;

        case 6:
            return 3;

        case 4:
            return 4;

        case 3:
            return 5;

        case 0:
            return 6;

        case 2:
            return 7;

        case 36:
            return 8;

        case 29:
            return 9;

        case 28:
            return 10;

        case 23:
            return 11;

        case 21:
            return 12;

        case 16:
            return 13;

        case 15:
            return 14;

        case 14:
            return 15;
    }
}

int sh2shd_get_shape_no_oni(int skel_no) { 
    switch (skel_no) { 
        
        case 12:
            return 0; 
        
        case 13:
            return 1; 
        
        case 7:            
            return 2; 
        
        case 6:
            return 3; 
        
        case 4:
            return 4; 
        
        case 3:
            return 5; 
        
        case 0:
            return 6; 
        
        case 2:
            return 7; 
        
        case 36:
            return 8; 
        
        case 25:
            return 9; 
        
        case 24:
            return 10; 
        
        case 21:
            return 11; 
        
        case 20:
            return 12; 
        
        case 16:
            return 13; 
        
        case 15:
            return 14;
        
        case 5:
            return 15; 
        
        case 14:
            return 16; 
    } 
}

int sh2shd_get_shape_no_edb(int skel_no) {
    switch (skel_no) {
        
        case 15:
            return 0;
        
        case 14:
            return 1;
        
        case 4:
            return 2;
        
        case 3:
            return 3;
        
        case 0:
            return 4;
        
        case 5:
            return 5;
        
        case 22:
            return 6;
        
        case 17:
            return 7;
        
        case 28:
            return 8;
        
        case 27:
            return 9;
        
        case 31:
            return 10;
        
        case 30:
            return 11;
        
        case 6:
            return 12;
        
        case 13:
            return 13;
    }
}
