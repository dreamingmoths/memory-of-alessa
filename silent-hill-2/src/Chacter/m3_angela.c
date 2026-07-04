#include "Chacter/character.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"

#define ANGELA_DRAMA_ANIME_ID_START 3500
#define ANGELA_PLAY_ANIME_ID_START  3900

#define ANGELA_PLAY_ANIM_3901       3901
#define ANGELA_PLAY_ANIM_3902       3902
#define ANGELA_PLAY_ANIM_3903       3903
#define ANGELA_PLAY_ANIM_3904       3904
#define ANGELA_PLAY_ANIM_3905       3905

// @todo: migrate data
extern float wall_pos_0x003C7EA8;
extern int mirror_mode_0x003C7EA0;
extern /* static */ AnimeInfo dangela_anim[32]; // size: 0x180, address: 0x0
extern /* static */ AnimeInfo pangela_anim[6]; // size: 0x48, address: 0x0
extern /* static */ int dangela_anime_adr_list[32]; // size: 0x80, address: 0x2A7BD0
extern /* static */ int dangela_clani_adr_list[32]; // size: 0x80, address: 0x2A7C50

#line 151
void HumanAGLFunction(SubCharacter* this) {
    AnimeInfo* aip; // r2
    short id;       // r4

    switch (this->step) {
        case 0:
            id = shCharacterGetModelID(this);

            if (id == AGL_CHARA_KIND) {
                shCharacterAnimeSet(this, 0, 0, (aip = &dangela_anim[1]), (int)shCharacterGetAnimeAdrForDrama(this, 1));
            }

            this->step++;

        /* fallthrough */

        case 1:
            return;
    }
}

#line 202
void shCharacterSetHumanAGLLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, HumanAGLFunction);
}

#line 218
int shCharacterHumanAGLAnimeSet(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip; // r2

    SCAnimeTypeSwitch(scp, 0);

    if (shCharacterGetModelID(scp) == AGL_CHARA_KIND) {
        aip = &dangela_anim[anime_id - ANGELA_DRAMA_ANIME_ID_START];
        shCharacterAnimeSet(
            scp,
            0,
            2,
            aip,
            dangela_anime_adr_list[anime_id - ANGELA_DRAMA_ANIME_ID_START] + (int)shCharacterGetAnimeAdrForDrama(scp, anime_id - ANGELA_DRAMA_ANIME_ID_START));

        shCharacterClusterAnimeSet(scp, dangela_clani_adr_list[anime_id - ANGELA_DRAMA_ANIME_ID_START] + (int)shCharacterGetClusterAnimeAdr(scp));
        return 0;
    }
    return -1;
}

#line 263
int shCharacterHumanAGLAnimeSetP(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip;

    SCAnimeTypeSwitch(scp, 1);

    if (shCharacterGetModelID(scp) == AGL_CHARA_KIND) {
        // @note: possible macro here?
        switch (anime_id) {
            case ANGELA_PLAY_ANIM_3901:
                scp->eye_y = 1986.6311f, scp->center_y = 1986.6311f;
                break;

            case ANGELA_PLAY_ANIM_3902:
                scp->eye_y = 1755.6741f, scp->center_y = 1755.6741f;
                break;

            case ANGELA_PLAY_ANIM_3903:
                scp->eye_y = -500.0f, scp->center_y = -500.0f;
                break;

            case ANGELA_PLAY_ANIM_3904:
            case ANGELA_PLAY_ANIM_3905:
                break;
        }

        aip = &pangela_anim[anime_id - ANGELA_PLAY_ANIME_ID_START];
        shCharacterAnimeSet(
            scp,
            0,
            0,
            aip,
            (int)shCharacterGetAnimeAdrForPlay(scp));

        return 0;
    }
    return -1;
}

#line 329
int HumanRAGLInit(SubCharacter* scp) {
    SCAnimeTypeSwitch(scp, 0);

    scp->model_type = 1;

    switch (RoomNameJms()) {
        case 1:
            mirror_mode_0x003C7EA0 = 0;
            wall_pos_0x003C7EA8 = -20000.0f;
            break;
        case 36:
            mirror_mode_0x003C7EA0 = 2;
            wall_pos_0x003C7EA8 = -99995.0f;
            break;
    }

    return 0;
}

#line 355
void HumanRAGLFunction(SubCharacter* this) {
    SubCharacter* scp;

    switch (this->step) {
        case 0:
            HumanRAGLInit(this);
            this->step++;
            return;

        case 1:
            scp = shCharacterGetSubCharacter(this->kind - MIRROR_MODE_CHARA_KIND_FLAG /* remove mirror mode from kind */, -1);
            if (!scp)
                break;

            switch (mirror_mode_0x003C7EA0) {
                case 0:

                    this->pos.x = wall_pos_0x003C7EA8 + (wall_pos_0x003C7EA8 - scp->pos.x);
                    this->pos.y = scp->pos.y;
                    this->pos.z = scp->pos.z;
                    this->rot.y = -scp->rot.y;
                    return;

                case 1:
                    this->pos.x = scp->pos.x;

                    this->pos.y = wall_pos_0x003C7EA8 + (wall_pos_0x003C7EA8 - scp->pos.y);

                    this->pos.z = scp->pos.z;
                    this->rot.y = scp->rot.y;
                    this->rot.z = PI;
                    return;

                case 2:
                    this->pos.x = scp->pos.x;
                    this->pos.y = scp->pos.y;
                    this->pos.z = wall_pos_0x003C7EA8 + (wall_pos_0x003C7EA8 - scp->pos.z);
                    if (scp->rot.y >= 0.0f)
                        this->rot.y = PI - scp->rot.y;
                    else
                        this->rot.y = -PI - scp->rot.y;
            }
    }
}

#line 405
void shCharacterSetHumanRAGLLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, HumanRAGLFunction);
}
