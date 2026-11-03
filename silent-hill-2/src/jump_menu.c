#include "jump_menu.h"

#include "Event/event.h"
#include "Event/item.h"
#include "Event/event_sub.h"

#include "Chacter/player_result.h"
#include "Chacter/sh2_battle_list.h"

#include "SH2_common/playing_info.h"
#include "SH2_common/sh2sys.h"

static int jump_after_data_set; // size: 0x4, address: 0x11B6998
int jump_menu_select; // size: 0x4, address: 0x11B6990

static JumpMenuUserData user_data = { // size: 0x14, address: 0x34C1A0
    0, // x
    0, // z 
    0, // flg
    0, // trg
    0  // glb_crd
}; 

void JumpMenuPosNormal(void) {
    if (user_data.flg != 0) {
        user_data.flg = 0;
    }
}

void CheckModeJumpDataSet(void) {    
    float dummy[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    int i;

    if (jump_after_data_set == 0) {
        jump_after_data_set = 1;
        
        ItemGet(SH2_ITEM_17);
        ItemGet(SH2_ITEM_18);
        
        item.light_switch = 1;
        
        if ((jump_menu_select != 11) &&
            (jump_menu_select != 12) &&
            (jump_menu_select != 48) &&
            (jump_menu_select != 10) &&
            (jump_menu_select != 9) &&
            (jump_menu_select != 8) &&
            (jump_menu_select != 7) &&
            (jump_menu_select != 13) &&
            (jump_menu_select != 0)) {
            
            
            
            
            ItemGet(SH2_ITEM_04);
            for (i = 0; i < 9; i++) ItemGet(SH2_ITEM_05);            
            ItemGet(SH2_ITEM_06);
            for (i = 0; i < 9; i++) ItemGet(SH2_ITEM_07);            
            ItemGet(SH2_ITEM_08);
            for (i = 0; i < 9; i++) ItemGet(SH2_ITEM_09);
            ItemGet(SH2_ITEM_10);
            ItemGet(WOODEN_PLANK);
            ItemGet(SH2_ITEM_12);
            ItemGet(SH2_ITEM_13);
            ItemGet(CHAINSAW);
            for (i = 0; i < 16; i++) ItemGet(HEALTH_DRINK);           
            for (i = 0; i < 16; i++) ItemGet(FIRST_AID_KIT);            
            ItemGet(SH2_ITEM_15);
            ItemGet(SH2_ITEM_RADIO);
            
            SET_GAME_FLAG(GAME_FLAG_32);
            SET_GAME_FLAG(GAME_FLAG_24);
            SET_GAME_FLAG(GAME_FLAG_25);
            SET_GAME_FLAG(GAME_FLAG_26);
            SET_GAME_FLAG(GAME_FLAG_27);
            SET_GAME_FLAG(GAME_FLAG_28);
            SET_GAME_FLAG(GAME_FLAG_29);
            SET_GAME_FLAG(GAME_FLAG_30);
            SET_GAME_FLAG(GAME_FLAG_31);
        }
        
        switch (jump_menu_select) {
            case 16:
                UNSET_GAME_FLAG(GAME_FLAG_32);
                break;
            case 6:
                SET_GAME_FLAG(GAME_FLAG_15);
                SET_GAME_FLAG(GAME_FLAG_150);
                SET_GAME_FLAG(GAME_FLAG_166);
                break;
            case 7:
                ItemGet(WOODEN_PLANK);
                ItemGet(SH2_ITEM_RADIO);
                for (i = 0; i < 16; i++) ItemGet(HEALTH_DRINK);                
                item.equip = 11;
                break;
            case 8:
                SET_GAME_FLAG(GAME_FLAG_15);
                ItemGet(WOODEN_PLANK);
                ItemGet(SH2_ITEM_04);
                for (i = 0; i < 9; i++) ItemGet(SH2_ITEM_05);                
                ItemGet(SH2_ITEM_12);
                ItemGet(SH2_ITEM_RADIO);
                ItemGet(SH2_ITEM_15);
                for (i = 0; i < 16; i++) ItemGet(HEALTH_DRINK);
                item.equip = 4;
                break;
            case 98:
                SET_GAME_FLAG(GAME_FLAG_10);
                break;
            case 9:
                ItemGet(WOODEN_PLANK);
                ItemGet(SH2_ITEM_04);
                for (i = 0; i < 9; i++) ItemGet(SH2_ITEM_05);    
                ItemGet(SH2_ITEM_06);
                for (i = 0; i < 9; i++) ItemGet(SH2_ITEM_07);                
                ItemGet(SH2_ITEM_12);
                ItemGet(SH2_ITEM_RADIO);
                ItemGet(SH2_ITEM_15);
                for (i = 0; i < 16; i++) ItemGet(HEALTH_DRINK);                
                item.equip = 4;
                ItemGet(SH2_ITEM_52);
                break;
            case 10:
                ItemGet(SH2_ITEM_04);
                for (i = 0; i < 9; i++) ItemGet(SH2_ITEM_05);    
                ItemGet(SH2_ITEM_06);
                for (i = 0; i < 9; i++) ItemGet(SH2_ITEM_07);                
                ItemGet(SH2_ITEM_08);
                for(i = 0; i < 9; i++) ItemGet(SH2_ITEM_09);                    
                ItemGet(SH2_ITEM_10);
                ItemGet(WOODEN_PLANK);
                ItemGet(SH2_ITEM_12);
                ItemGet(SH2_ITEM_13);
                for (i = 0; i < 16; i++) ItemGet(HEALTH_DRINK);    
                ItemGet(SH2_ITEM_15);
                ItemGet(SH2_ITEM_RADIO);
                item.equip = 4;
                break;
            case 11:
                ItemGet(SH2_ITEM_04);    
                for (i = 0; i < 3; i++) ItemGet(SH2_ITEM_05);    
                ItemGet(WOODEN_PLANK);    
                for (i = 0; i < 5; i++) ItemGet(HEALTH_DRINK);    
                for (i = 0; i <= 0; i++) ItemGet(FIRST_AID_KIT);                
                ItemGet(SH2_ITEM_RADIO);    
                item.equip = 4;
                SET_GAME_FLAG(GAME_FLAG_25);
                SET_GAME_FLAG(GAME_FLAG_66);
                SET_GAME_FLAG(GAME_FLAG_35);
                SET_GAME_FLAG(GAME_FLAG_40);
                SET_GAME_FLAG(GAME_FLAG_41);
                SET_GAME_FLAG(GAME_FLAG_43);
                SET_GAME_FLAG(GAME_FLAG_49);
                SET_GAME_FLAG(GAME_FLAG_67);
                playing.riddle_level = SH2_RIDDLE_LEVEL_EASY;
                break;
            
            case 12:
                ItemGet(SH2_ITEM_04);
                for (i = 0; i < 3; i++) ItemGet(SH2_ITEM_05);                
                ItemGet(SH2_ITEM_06);
                for(i = 0; i <= 0; i++) ItemGet(SH2_ITEM_07);                
                ItemGet(WOODEN_PLANK);
                ItemGet(SH2_ITEM_12);
                for (i = 0; i < 8; i++) ItemGet(HEALTH_DRINK);                
                for (i = 0; i < 2; i++) ItemGet(FIRST_AID_KIT);                
                ItemGet(SH2_ITEM_15);
                ItemGet(SH2_ITEM_RADIO);
                item.equip = 4;
                SET_GAME_FLAG(GAME_FLAG_28);
                SET_GAME_FLAG(GAME_FLAG_35);
                playing.riddle_level = SH2_RIDDLE_LEVEL_EASY;
                break;
            case 19:
            case 31:
            case 33:
            case 35:
            case 37:
                SET_GAME_FLAG(GAME_FLAG_251);
                SET_GAME_FLAG(GAME_FLAG_43);
                break;
            case 39:
                SET_GAME_FLAG(GAME_FLAG_12);
                break;
            case 43:
                SET_GAME_FLAG(GAME_FLAG_95);
                break;
            case 47:
                ItemGet(SH2_ITEM_25);
                SET_GAME_FLAG(GAME_FLAG_69);
                break;
            case 48:
                SET_GAME_FLAG(GAME_FLAG_68);
                SET_GAME_FLAG(GAME_FLAG_7);
                break;
            case 54:
                ItemGet(SH2_ITEM_46);
                break;
            case 55:
                ItemGet(SH2_ITEM_27);
                break;
            case 52:
                SET_GAME_FLAG(GAME_FLAG_67);
                break;
            case 63:
                SET_GAME_FLAG(GAME_FLAG_150);
                break;
            case 64:
                SET_GAME_FLAG(GAME_FLAG_150);
                SET_GAME_FLAG(GAME_FLAG_152);
                SET_GAME_FLAG(GAME_FLAG_15);
                break;
            case 69:
                SET_GAME_FLAG(GAME_FLAG_150);
                SET_GAME_FLAG(GAME_FLAG_15);
                SET_GAME_FLAG(GAME_FLAG_162);
                SET_GAME_FLAG(GAME_FLAG_164);
                SET_GAME_FLAG(GAME_FLAG_166);
                break;
            case 70:
            case 73:
                SET_GAME_FLAG(GAME_FLAG_15);
                break;
            case 78:
                ItemGet(SH2_ITEM_34);
                break;
            case 82:
                ItemGet(SH2_ITEM_32);
                ItemGet(SH2_ITEM_33);
                break;
            case 88:
                ItemGet(SH2_ITEM_35);
                break;
            case 89:
                SET_GAME_FLAG(GAME_FLAG_15);
                ItemGet(SH2_ITEM_53);
                ItemGet(SH2_ITEM_54);
                break;
            case 95:
                SET_GAME_FLAG(GAME_FLAG_15);
                break;
            case 60:
                ItemGet(SH2_ITEM_28);
                break;
            case 57:
                SET_GAME_FLAG(GAME_FLAG_85);
                break;
            case 58:
                SET_GAME_FLAG(GAME_FLAG_109);
                break;
            case 59:
                ItemGet(COIN_OF_SNAKE);
                ItemGet(SH2_ITEM_48);
                ItemGet(SH2_ITEM_49);
                break;
            case 61:
                ItemGet(SH2_ITEM_29);
                break;
            case 62:
                SET_GAME_FLAG(GAME_FLAG_146);
                break;
            case 66:
                SET_GAME_FLAG(GAME_FLAG_150);
                SET_GAME_FLAG(GAME_FLAG_162);
                SET_GAME_FLAG(GAME_FLAG_154);
                SET_GAME_FLAG(GAME_FLAG_156);
                SET_GAME_FLAG(GAME_FLAG_157);
                break;
            case 67:
                SET_GAME_FLAG(GAME_FLAG_15);
                break;
            case 83:
                ItemGet(SH2_ITEM_50);
                ItemGet(SH2_ITEM_NEEDLE);
                break;
            case 79:
                playing.riddle_level = SH2_RIDDLE_LEVEL_EASY;
                ItemGet(SH2_ITEM_34);
                break;
            case 80:
            case 91:
                SET_GAME_FLAG(GAME_FLAG_15);
                break;
            case 85:
                SET_GAME_FLAG(GAME_FLAG_214);
                break;
            case 93:
                SET_GAME_FLAG(GAME_FLAG_232);
                break;
            case 86:
                SET_GAME_FLAG(GAME_FLAG_222);
                break;
            case 97:
                SET_GAME_FLAG(GAME_FLAG_251);
                SET_GAME_FLAG(GAME_FLAG_150);
                ItemGet(SH2_ITEM_55);
                break;
            case 99:
                SET_GAME_FLAG(GAME_FLAG_10);
                break;
            case 101:
                SET_GAME_FLAG(GAME_FLAG_265);
                break;
            
            case 102:
                ItemGet(SH2_ITEM_52);
                break;
            case 103:
                ItemGet(SH2_ITEM_38);
                break;
            case 104:
                SET_GAME_FLAG(GAME_FLAG_274);
                break;
            case 107:
                ItemGet(SH2_ITEM_56);
                ItemGet(SH2_ITEM_57);
                ItemGet(SH2_ITEM_58);
                break;
            case 108:
                ItemGet(SH2_ITEM_60);
                ItemGet(SH2_ITEM_61);
                ItemGet(SH2_ITEM_59);
                
                break;
            case 114:
                ItemGet(SH2_ITEM_62);
                break;
            case 121:
                ItemGet(SH2_ITEM_39);
                break;
            case 129:
                ItemGet(SH2_ITEM_66);
                ItemGet(SH2_ITEM_64);
                ItemGet(SH2_ITEM_65);
                break;
            case 132:
                ItemGet(SH2_ITEM_17);
                ItemGet(SH2_ITEM_18);
                ItemGet(SH2_ITEM_19);
                ItemGet(SH2_ITEM_21);
                ItemGet(SH2_ITEM_22);
                ItemGet(SH2_ITEM_30);
                ItemGet(SH2_ITEM_40);
                ItemGet(SH2_ITEM_63);
                ItemGet(SH2_ITEM_64);
                ItemGet(SH2_ITEM_65);
                ItemGet(SH2_ITEM_71);
                ItemGet(SH2_ITEM_73);
                ItemGet(SH2_ITEM_74);
                SET_GAME_FLAG(GAME_FLAG_415);
                break;
            case 130:
                ItemGet(SH2_ITEM_44);
                break;
            case 131:
                ItemGet(SH2_ITEM_63);
                break;
            case 136:
                ItemGet(SH2_ITEM_45);
                break;
            case 137:
                ItemGet(SH2_ITEM_20);
                break;
            case 134:
                ItemGet(SH2_ITEM_67);
                ItemGet(SH2_ITEM_43);
                break;
            case 146:
                SET_GAME_FLAG(GAME_FLAG_483);
                SET_GAME_FLAG(GAME_FLAG_484);
                ItemGet(SH2_ITEM_70);
                ItemGet(SH2_ITEM_69);
                break;
            case 147:
                SET_GAME_FLAG(GAME_FLAG_10);
                UNSET_ITEM_FLAG(15);
                break;
            case 139:
                ItemGet(SH2_ITEM_22);
                SET_GAME_FLAG(GAME_FLAG_11);
            case 140:
            case 142:
            case 143:
            case 145:
                UNSET_ITEM_FLAG(15);
                break;
        }
    }
}
