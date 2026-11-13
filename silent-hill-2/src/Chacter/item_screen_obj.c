#include "Chacter/item_screen_obj.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"
#include "Chacter_Draw/model3_structs.h"
#include "sce/libvu0.h"
#include "SH2_common/sh_vu0.h"
#include "vec.h"

static shItemScreenObjectSettingData item_screen_obj_data[58] = {
    {
        /* .charaId = */ 0x748, // @todo this maps to the BFAW birthday card in greatest hits. what is it in the v0.10 prototype?
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ ITEM_G_DRINK_CHARA_KIND,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ ITEM_G_FIRSTAID_CHARA_KIND,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ ITEM_G_HANDGUN_CHARA_KIND,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ ITEM_G_HANDBUL_CHARA_KIND,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ ITEM_G_KAKUZAI_CHARA_KIND,
        /* .scale = */ 1.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ ITEM_G_JLIGHT_CHARA_KIND,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ ITEM_G_RADIO_CHARA_KIND,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ ITEM_G_KEYPURPLE_CHARA_KIND,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ ITEM_G_HAIR_CHARA_KIND,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ ITEM_G_NEEDLE_CHARA_KIND,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ ITEM_G_KEYELEVATOR_CHARA_KIND,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ ITEM_G_LETTERM_CHARA_KIND,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x60C,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x60D,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x60E,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x60F,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x610,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x611,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x612,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x613,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x614,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x615,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x616,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x617,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x618,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x619,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x61A,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x61B,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x61C,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x61D,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x61E,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x61F,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x620,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x621,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x622,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x623,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x624,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x625,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x626,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x627,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x628,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x629,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x62A,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x62B,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x0,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x0,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x0,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x0,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x0,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x0,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x0,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x0,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x0,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x0,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x0,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x0,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        },
    },
    {
        /* .charaId = */ 0x0,
        /* .scale = */ 10.0f,
        /* .rot = */         {
            /* .x = */ 0.0f,
            /* .y = */ 0.0f,
            /* .z = */ QUARTER_TURN,
            /* .w = */ 0.0f,
        }
    }
};

static int shCharacterItemScreenItemInit(SubCharacter* scp);
static int shCharacterWorldScreenItemInit(SubCharacter* scp);
static void ItemScreenItemFunction(SubCharacter* this);
static void WorldScreenItemFunction(SubCharacter* this);
static void getRmat(float (* mat)[4]);

static int shCharacterItemScreenItemInit(SubCharacter* scp) {
    SCStayModelSwitch(scp, 1);
    return false;
}

static int shCharacterWorldScreenItemInit(SubCharacter* scp) {
    SCStayModelSwitch(scp, 1);
    return false;
}

static void ItemScreenItemFunction(SubCharacter* this) {
    int i1;
    
    
    
    switch (this->step) {
        case 0:
            shCharacterItemScreenItemInit(this);
            
            i1 = 0;
            while (item_screen_obj_data[i1].chara_id != 0) {
                if (this->kind == item_screen_obj_data[i1].chara_id) {
                    shCharacterItemScreenObjectSet(this, &item_screen_obj_data[i1]);
                    shUnitMatrix(this->mat);
                    break;                    
                } 
                i1++;                
            }
            
            
            this->step++;

        
        case 1:
            break;
    }
}

static void WorldScreenItemFunction(SubCharacter* this) {
    float scale;

    
    
    
    
    
    
    switch (this->step) {
        case 0:
            
            
            
            shCharacterWorldScreenItemInit(this);
            
            
            
            
            
            
            switch (shCharacterGetModelID(this)) {
                
                case ITEM_X_RADIO_CHARA_KIND:        scale = 2.0f; break;
                case ITEM_X_KEYPURPLE_CHARA_KIND:    scale = 2.0f; break;
                case ITEM_X_NEEDLE_CHARA_KIND:       scale = 2.0f; break;
                case ITEM_X_KEYELEVATOR_CHARA_KIND:  scale = 2.0f; break;
                
                case ITEM_X_KEYEMERG_CHARA_KIND:     scale = 1.5f; break;
                case ITEM_X_KEY202_CHARA_KIND:       scale = 1.5f; break;
                case ITEM_X_KEYCOURT_CHARA_KIND:     scale = 1.5f; break;
                case ITEM_X_KEYNORTH_CHARA_KIND:     scale = 1.5f; break;
                case ITEM_X_COINPRISONER_CHARA_KIND: scale = 1.5f; break;
                case ITEM_X_KEYFISH_CHARA_KIND:      scale = 1.5f; break;
                case ITEM_X_KEY312_CHARA_KIND:       scale = 1.5f; break;
                case ITEM_X_KEYEMPLOY_CHARA_KIND:    scale = 1.5f; break;
                case ITEM_X_KEY3F_CHARA_KIND:        scale = 1.5f; break;
                case ITEM_X_KEYBAR_CHARA_KIND:       scale = 1.5f; break;
                case ITEM_X_KEYSPIRAL_CHARA_KIND:    scale = 2.0f; break;
                
                default: scale = 1.0f;

            }
            
            
            shCharacterWorldScreenObjectSetNew(this, scale);
            
            this->pos_spd.x = this->pos.x;
            this->pos_spd.z = this->pos.z;
            this->eye_y = this->center_y = this->pos.y - 100.0f;
            
            
            
            
            switch (this->kind) {
                case ITEM_X_KEY202_CHARA_KIND:
                    this->pos_spd.z -= 125.0f;
                    break;
            }
            
            this->step++;
    
        case 1:
            break;
        
    }
}

static inline void _sceVu0RotMatrix2(sceVu0FMATRIX m0, sceVu0FMATRIX m1, float* rot) {
    shRotMatrixZ(m0, m1, rot[2]);
    shRotMatrixY(m0, m0, rot[1]);
    shRotMatrixX(m0, m0, rot[0]);
}

static inline _sceVu0TransposeMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1) {
    asm volatile("\
	lq $8,0x00(%1);\
	lq $9,0x10(%1);\
	lq $10,0x20(%1);\
	lq $11,0x30(%1);\
	\
	pextlw $12,$9,$8;\
	pextuw $13,$9,$8;\
	pextlw $14,$11,$10;\
	pextuw $15,$11,$10;\
	\
	pcpyld $8,$14,$12;\
	pcpyud $9,$12,$14;\
	pcpyld $10,$15,$13;\
	pcpyud $11,$13,$15;\
	\
	sq $8,0x00(%0);\
	sq $9,0x10(%0);\
	sq $10,0x20(%0);\
	sq $11,0x30(%0);\
	" : : "r"(m0), "r"(m1) : "memory");
}

static void getRmat(float (*mat)[4]) {
    sceVu0FMATRIX rot = {
        { 0.0f, PI,   0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
    };
    shUnitMatrix(mat);
    _sceVu0RotMatrix2(mat, mat, rot);
    _sceVu0TransposeMatrix(mat, mat);
}

void shCharacterWorldScreenObjectSetNew(SubCharacter* this, float scale) {
    SubCharacterDisp* scp_d = (SubCharacterDisp*) this;
    shSkelton* sp;
    ModelWork* work;
    int i; // @note: changed order in order to match
    sceVu0FMATRIX rm;
    sp = scp_d->anime.top;
    
    
    
    
    work = scp_d->work;
    
    
    
    
    
    
    
    getRmat(rm);
    
    
    
    SCSetRot(this, &this->rot);
    i = 0;
    for (;sp != NULL; sp = sp->next, i++) {
        sp->src_m = *(Matrix4*) work->matrices[i];
        shMulMatrix((float (*)[4])&sp->src_m, rm, (float (*)[4])&sp->src_m);
        
        sp->des_m = sp->src_m;
        sp->des_t = sp->src_t = *(Vector4*) sp->src_m.d[3];
        
    }
    
    
    shCharacterStayObjectScaleSet(this, scale);
};

void shCharacterSetItemScreenItemLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, ItemScreenItemFunction);
}

void shCharacterSetWorldScreenItemLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, WorldScreenItemFunction);
}
