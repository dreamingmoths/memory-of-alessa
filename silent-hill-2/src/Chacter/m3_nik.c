#include "sh2_common.h"
#include "vec.h"
#include "Chacter/character.h"
#include "Chacter/m3_nik.h"
#include "Enemy/en_common.h"
#include "Chacter/m3_sc.h"
#include "DBG/shDBG_fontHandle.h"

static int ObjectNIKInit(SubCharacter* scp);

static const AnimeInfo nik_anim[] = {
    {
        /* .name = */ 0,
        /* .frame = */ 0,
        /* .speed = */ 0,
        /* .start = */ 0,
        /* .end = */ 0,
        /* .loop = */ 0,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 8301,
        /* .frame = */ 146,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 145,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 8302,
        /* .frame = */ 200,
        /* .speed = */ 2048,
        /* .start = */ 146,
        /* .end = */ 345,
        /* .loop = */ 1,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 8303,
        /* .frame = */ 150,
        /* .speed = */ 2048,
        /* .start = */ 346,
        /* .end = */ 495,
        /* .loop = */ 1,
        /* .pad = */ 0,
    }
}; 


#line 49
static int ObjectNIKInit(SubCharacter* scp) {
    return 0;
}

#line 63
void ObjectNIKFunction(SubCharacter* this) {
    AnimeInfo * aip;
    
    
    
    signed short init_frame[11] = {
        52,
        19,
        0,
        99,
        23,
        7,
        71,
        10,
        55,
        0,
        27
    };
    signed short init_anime[11] = {
        2,
        1,
        2,
        0,
        0,
        0,
        2,
        0,
        0,
        2,
        1
    };
    float pos[4];
    float rot[4];
    EnLOCAL_DATA* dp;
    SubCharacterDisp* scp_d;
    char buf[128];

    switch (this->step) {
        case 0:
        
        
        
        
            shVectorCopy(pos, &this->pos);
            shVectorCopy(rot, &this->rot);
        
            ObjectNIKInit(this);
            SCAnimeTypeSwitch(this, 1);
            
            
            aip = (AnimeInfo*)&nik_anim[init_anime[this->id] + 1];
            shCharacterAnimeSet(this, 0, 2, aip, (int)shCharacterGetAnimeAdrForPlay(this));
            
            
            
            
            
            
            
            
            shCharacterAnimeFrameSet(this, aip->start + init_frame[this->id]);
            
            if (this->status & (1 << SCP_STATUS_BIT_ANIME_TYPE)) {
        
            
                if ((dp = enEntryEnemy(12)) != NULL) {
                    this->enemy_p = dp;
                    enInitData(dp, this);
                } 
                else this->enemy_p = NULL;
            }
            
            
            this->step++;
            
            return;
        case 1:
            if (shPadGetPort() == 7) {
            
                
                scp_d = (SubCharacterDisp*)this;
                sprintf(buf, "Frame %d", scp_d->anime.cur_frame.x);
                shDBG_print_string(buf, 8, (this->id * 8) + 200);
            }

            
            return;
    }
}

#line 167
void shCharacterSetObjectNIKLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, ObjectNIKFunction);
}
