#include "sh2_common.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/playing_info.h"

#include "vec.h"

#include "Chacter/m3_sc.h"
#include "Chacter/skelton.h"
#include "Chacter/bg_chara.h"
#include "Chacter/chara_list.h"
#include "Chacter/chara_bound.h"
#include "Chacter/m3_play_event.h"
#include "Chacter/sh2_character_manage.h"

#include "Enemy/en_common.h"
#include "GFW/sh2gfw_Init_ModelDrawData.h"
#include "LoadBg/loadbg_event.h"

#include "Event/event.h"
#include "Event/stg_name.h"
#include "Event/chara_data_load.h"
#include "Event/chara_admin.h"

#define GET_ENEMY_FLAG(index) ((game_flag.enemy[(index) >> 5] >> ((index) & 0x1F)) & 1)
#define GET_ITEM_FLAG(index) ((item.flag[(index) >> 5] >> ((index) & 0x1F)) & 1)
#define SET_ENEMY_FLAG(index) ((game_flag.enemy[(index) >> 5] |= (1 << ((index) & 0x1F))))
#define VEC_LENGTH_XZ(_x, _z) ((_x) * (_x) + (_z) * (_z))
#define SQUARE(_x) ((_x) * (_x))

static int RoomDistanceSub(struct CharaAdmin_RoomDistance* dist, short room0, short room1, u_long flag);
static void DeleteEnemyWorkIn(void);
static void DeleteEnemyWorkOut(void);
static int RoomDistance(short room0, short room1);
static void DeleteEnemyWork(void);
static int CharaAdminEnemyEntryCondition(short cond);

#define weapon weapon_959
signed short weapon_959[9][2]; // @ 0x0033DC70

extern float connect_pos[4];                                     // size: 0x10, address: 0x11B6720
extern /* static */ int back_load_admin;                         // size: 0x4, address: 0x116DBC8
extern /* struct */ CharaData_DemoList back_load_admin_list[8];  // size: 0xA0, address: 0x116DBD0
extern /* static */ CharaAdmin_RoomDistance room_dist_hsp_f[31]; // size: 0x7C, address: 0x33DCA0
extern /* static */ CharaAdmin_RoomDistance room_dist_hsp_b[18]; // size: 0x48, address: 0x33DD20
extern /* static */ CharaAdmin_RoomDistance room_dist_apt[30];   // size: 0x78, address: 0x33DD70

void ConnectCharaWorkJamesSet(void) {
    sceVu0FVECTOR pos; // r29+0x10
    sceVu0FVECTOR rot; // r29+0x20

    vu0_unit_vector(pos);
    vu0_unit_vector(rot);
    pos[0] = connect_pos[0];
    pos[1] = connect_pos[1];
    pos[2] = connect_pos[2];
    rot[1] = connect_pos[3];

    if (sh2jms.player == NULL) {
        if (stage->pc_model == 1)
            CharaWorkCreate(HLL_JMS_CHARA_KIND, 0, pos, rot, 0);
        else
            CharaWorkCreate(LLL_JMS_CHARA_KIND, 0, pos, rot, 0);
    } else if (sh2jms.player->kind == LLL_JMS_CHARA_KIND) {
        if (stage->pc_model == 1) {
            shCharacter_Manage_Delete(NULL, LLL_JMS_CHARA_KIND, 0);
            CharaWorkCreate(HLL_JMS_CHARA_KIND, 0, pos, rot, 0);
        }
    } else {
        if (stage->pc_model != 1) {
            shCharacter_Manage_Delete(NULL, HLL_JMS_CHARA_KIND, 0);
            CharaWorkCreate(LLL_JMS_CHARA_KIND, 0, pos, rot, 0);
        }
    }
}

void ConnectCharaWorkWeapon(void) {
    // static short weapon[9][2]; // @ 0x0033DC70
    SubCharacter* scp; // r2
    float dummy[4];    // r29+0x30
    int id;            // r16
    int i;             // r17

    for (i = 0; i < 9; i++)
        if (item.equip == weapon[i][0])
            break;
    ASSERT_ON_LINE(i < 9, 130);

    id = PlayerGetJamesWeapon();
    shCharacter_Manage_Delete(NULL, WEAPON_ID_START + id, 0);
    shCharacter_Manage_Delete(NULL, WEAPON_ID_START + MIRROR_MODE_CHARA_KIND_FLAG + id, 0);

    if ((id != 0) && (id != weapon[i][1]))
        CharaDataDeleteOne(WEAPON_ID_START + MIRROR_MODE_CHARA_KIND_FLAG + id);
    CharaDataLoadWeapon();
    vu0_unit_vector(dummy);
    if (weapon[i][1] != 0) {
        scp = CharaWorkCreate(WEAPON_ID_START + weapon[i][1], 0, dummy, dummy, 0);

        ASSERT_ON_LINE(scp, 144);
        if (GET_BIT(Sh2sys.main_status, 4)) {
            scp = CharaWorkCreate(WEAPON_ID_START + MIRROR_MODE_CHARA_KIND_FLAG + weapon[i][1], 0, dummy, dummy, 0);

            ASSERT_ON_LINE(scp, 149);
        } else {
            scp = shCharacterGetSubCharacter(WEAPON_ID_START + MIRROR_MODE_CHARA_KIND_FLAG + weapon[i][1], 0);

            if (scp != NULL)
                shCharacter_Manage_Delete(scp, 0, 0);
        }
    }
    JamesWeaponSet(weapon[i][1]);
}

void ConnectCharaWorkReset(void) {
    SubCharacter* scp;  // r2
    SubCharacter* next; // r16

    enInitEnemy();

    scp = shCharacter_Manage_GetCharacterList();
    for (; scp != NULL; scp = next) {
        next = scp->next;
        if ((scp->kind == LLL_JMS_CHARA_KIND) || (scp->kind == HLL_JMS_CHARA_KIND) || (scp->kind == LLL_MAR_CHARA_KIND) || (scp->kind >> 8) == WEAPON_CHARA_KIND)
            continue;
        if (((scp->kind >> 8) == ENEMY_CHARA_KIND) && (scp->battle.hp == 0.0f))
            game_flag.enemy[scp->id >> 5] |= 1 << (scp->id & 0x1F);
        shCharacter_Manage_Delete(scp, 0, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", ConnectCharaWorkAdminOut);

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", ConnectCharaWorkAdminIn);

void ConnectCharaWorkAdminClear(void) {
    SubCharacter* scp;  // r2
    SubCharacter* next; // r16

    scp = shCharacter_Manage_GetCharacterList();
    while (scp != NULL) {
        next = scp->next;
        switch (scp->kind) {
            case LAU_CHARA_KIND:
            case HHH_MAR_CHARA_KIND:
            case AGL_CHARA_KIND:
            case HHH_EDI_CHARA_KIND:
            case MRY_CHARA_KIND:
            case HHH_MXX_CHARA_KIND:
            case BOAT_CHARA_KIND:
            case 0x10C:
            case INU_CHARA_KIND:
            case RLLL_JMS_CHARA_KIND:
            case RHLL_JMS_CHARA_KIND:
            case RWEAPON_HANDGUN_CHARA_KIND:
            case RWEAPON_SHOTGUN_CHARA_KIND:
            case RWEAPON_RIFLGUN_CHARA_KIND:
            case RWEAPON_SP_CHARA_KIND:
            case RWEAPON_KAKUZAI_CHARA_KIND:
            case RWEAPON_PIPE_CHARA_KIND:
            case RWEAPON_CSAW_CHARA_KIND:
            case RWEAPON_NATA_CHARA_KIND:
            case RWEAPON_COLT_NOTEX_CHARA_KIND:
                shCharacter_Manage_Delete(scp, 0, 0);
        }

        scp = next;
    }
}

static int RoomDistance(short room0 /* r7 */, short room1 /* r2 */) {
    int len; // r2
    switch (playing.stage) {
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            len = RoomDistanceSub(room_dist_apt, room0, room1, 0U);
            break;
        case 18:
        case 19:
        case 20:
        case 21:
            len = RoomDistanceSub(room_dist_hsp_f, room0, room1, 0U);
            break;
        case 22:
        case 24:
        case 25:
        case 26:
            len = RoomDistanceSub(room_dist_hsp_b, room0, room1, 0U);
            break;
        default:
            return 0xFFFF;
    }
    if (len == -1) {
        return 0xFFFF;
    }
    return len;
}

#ifdef NON_MATCHING
static int RoomDistanceSub(CharaAdmin_RoomDistance* dist /* r21 */, short room0 /* r20 */, short room1 /* r19 */, u_long flag /* r18 */) {
    int len;  // r16
    int work; // r2
    int i;    // r17
    int tmp;  // @note not in dwarf

    if (room1 < room0) {
        tmp   = room1;
        room1 = room0;
        room0 = tmp;
    }

    for (i = 0; dist[i].rm0 != 0; i++)
        if (dist[i].rm0 == room0 && dist[i].rm1 == room1)
            return 1;

    len = -1;
    for (i = 0; dist[i].rm0 != 0; i++) {
        if ((flag & (1 << i)))
            continue;
        if (room0 == dist[i].rm0)
            work = RoomDistanceSub(dist, dist[i].rm1, room1, flag + (1 << i));

        else if (room0 == dist[i].rm1)
            work = RoomDistanceSub(dist, dist[i].rm0, room1, flag + (1 << i));

        else
            work = -1;
        if (work == -1)
            continue;

        if (len == -1 || ((work + 1) < len))
            len = work + 1;
    }
    if ((flag == 0) && (len == -1))
        return 0;
    return len;
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", RoomDistanceSub);
#endif

SubCharacter* CharaWorkCreate(short kind /* r20 */, short id /* r19 */, float* pos /* r18 */, float* rot /* r17 */, u_int status /* r16 */) {
    SubCharacter* scp; // r2
    int sk_last;       // r2

    if (((sh2skelton.last - shCharacterGetSkeltonNum(kind)) <= 0) || (sh2chara.total == 32)) {
        DeleteEnemyWork();
        return CharaWorkCreate(kind, id, pos, rot, status);
    }
    shCharacter_Manage_Create(kind, id, pos, rot, status);
    scp = shCharacterGetSubCharacter(kind, id);
    if (scp != NULL) {
        scp->status |= 0x10;
    }
    return scp;
}

static void DeleteEnemyWork(void) {
    if ((stage->glb_crd != 4) && (stage->glb_crd != 3) && (stage->glb_crd != 2) && (stage->glb_crd != 1)) {
        DeleteEnemyWorkIn();
        return;
    }
    DeleteEnemyWorkOut();
}

static void DeleteEnemyWorkIn(void) {
    SubCharacter* scp; // r17
    SubCharacter* del; // r16
    int j_room;        // r18
    int e_room;        // r2
    int del_point;     // r19
    int work;          // r2

    j_room    = RoomName(0, sh2jms.player->pos.x, sh2jms.player->pos.z);
    del_point = 0;
    del       = NULL;
    scp       = shCharacter_Manage_GetCharacterList();
    for (; scp != NULL; scp = scp->next) {
        if (((s16) scp->kind >> 8) == 2) {
            e_room = RoomName(0, scp->pos.x, scp->pos.z);
            if (j_room != e_room) {
                work = RoomDistance(j_room, e_room);
                if (scp->battle.hp <= 0.0f) {
                    work += 4;
                }
                if (del_point < work) {
                    del       = scp;
                    del_point = work;
                }
            }
        }
    }
    ASSERT_ON_LINE(del, 739);
    if (del->battle.hp <= 0.0f) {
        SET_ENEMY_FLAG(del->id);
    }
    shCharacter_Manage_Delete(del, 0, 0);
}

static void DeleteEnemyWorkOut(void) {
    SubCharacter* scp; // r2
    SubCharacter* del; // r16
    sceVu0FVECTOR vec; // r29+0x30
    float len;         // r29+0x40
    float far;         // r20

    vu0_unit_vector(vec);
    del = NULL;
    far = 16000.0f;
    scp = shCharacter_Manage_GetCharacterList();
    for (; scp != NULL; scp = scp->next) {

        if ((scp->kind >> 8) == ENEMY_CHARA_KIND) {
            vec[0] = scp->pos.x - sh2jms.player->pos.x;
            vec[2] = scp->pos.z - sh2jms.player->pos.z;
            len    = vec_length(vec);
            if (scp->battle.hp <= 0.0f)
                len += 32000.0f;

            if (len >= far) {
                far = len;
                del = scp;
            }
        }
    }
    ASSERT_ON_LINE(del, 775);
    if (del->battle.hp <= 0.0f) {
        SET_ENEMY_FLAG(del->id);
    }
    shCharacter_Manage_Delete(del, 0, 0);
}

#ifdef NON_MATCHING
int CharaAdminEnemyEntryCheck(Enemy_List* ep, int room) {
    if (GET_ENEMY_FLAG(ep->id))
        return 0;
    if (room && room != RoomName(0, ep->pos_x, ep->pos_z))
        return 0;
    if (!CharaAdminEnemyEntryCondition(ep->condition))
        return 0;

    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", CharaAdminEnemyEntryCheck);
#endif

#line 801
static int CharaAdminEnemyEntryCondition(short cond) {
    if (playing.battle_level == 1) {
        if (cond & 1)
            return 0;
    } else if (playing.battle_level == 2) {
        if (cond & 2)
            return 0;
    } else if (playing.battle_level == 3) {
        if (cond & 4)
            return 0;
    }

    // todo line numbers
    switch (cond & 0xFFC0) { /* switch 2; irregular */
        case 0x40:           /* switch 2 */
            if (!GET_GAME_FLAG(43) || GET_GAME_FLAG(251)) {
                return 0;
            }
            break;
        case 0x80: /* switch 2 */
            if (!GET_GAME_FLAG(67)) {
                return 0;
            }
            break;
        case 0x100: /* switch 2 */
            if (!GET_GAME_FLAG(91)) {
                return 0;
            }
            break;
        case 0x440: /* switch 2 */
            if (GET_GAME_FLAG(101) || GET_GAME_FLAG(99)) {
                return 0;
            }
            break;
        case 0x140: /* switch 2 */
            if (!GET_GAME_FLAG(146)) {
                return 0;
            }
            break;
        case 0xC0: /* switch 2 */
            if (!GET_GAME_FLAG(483)) {
                return 0;
            }
            break;
        case 0x180: /* switch 2 */
            if (!GET_GAME_FLAG(68) || GET_GAME_FLAG(70)) {
                return 0;
            }
            break;
        case 0x1C0: /* switch 2 */
            if (GET_GAME_FLAG(68) && !GET_GAME_FLAG(70)) {
                return 0;
            }
            break;
        case 0x2C0: /* switch 2 */
            if (!GET_GAME_FLAG(154) || GET_GAME_FLAG(251)) {
                return 0;
            }
            break;
        case 0x400: /* switch 2 */
            if (!GET_GAME_FLAG(154) || GET_GAME_FLAG(162)) {
                return 0;
            }
            break;
        case 0x3C0: /* switch 2 */
            if (!GET_GAME_FLAG(154) || (GET_GAME_FLAG(156) && !GET_GAME_FLAG(157)) || GET_GAME_FLAG(162)) {
                return 0;
            }
            break;
        case 0x300: /* switch 2 */
            if (GET_ITEM_FLAG(52)) {
                return 0;
            }
            break;
        case 0x200: /* switch 2 */
            if (!GET_GAME_FLAG(335)) {
                return 0;
            }
            break;
        case 0x240: /* switch 2 */
            if (!GET_GAME_FLAG(365)) {
                return 0;
            }
            break;
        case 0x280: /* switch 2 */
            if (GET_GAME_FLAG(329) && !GET_GAME_FLAG(330)) {
                return 0;
            }
            break;
        case 0x340: /* switch 2 */
            if (!GET_GAME_FLAG(251)) {
                return 0;
            }
            break;
        case 0x380: /* switch 2 */
            if (GET_GAME_FLAG(482)) {
                return 0;
            }
            break;
    }
    return 1;
}

void CharaAdminPlayableDisplay(int xxx /* r16 */) {
    SubCharacter* scp; // r4

    scp = shCharacter_Manage_GetCharacterList();
    for (; scp != NULL; scp = scp->next) {
        switch (scp->kind) {
            case LLL_JMS_CHARA_KIND:
            case RLLL_JMS_CHARA_KIND:
            case HLL_JMS_CHARA_KIND:
            case RHLL_JMS_CHARA_KIND:
            case LLL_MAR_CHARA_KIND:
            case RLLL_MAR_CHARA_KIND:
            case WEAPON_HANDGUN_CHARA_KIND:
            case RWEAPON_HANDGUN_CHARA_KIND:
            case WEAPON_SHOTGUN_CHARA_KIND:
            case RWEAPON_SHOTGUN_CHARA_KIND:
            case WEAPON_RIFLGUN_CHARA_KIND:
            case RWEAPON_RIFLGUN_CHARA_KIND:
            case WEAPON_SP_CHARA_KIND:
            case RWEAPON_SP_CHARA_KIND:
            case WEAPON_KAKUZAI_CHARA_KIND:
            case RWEAPON_KAKUZAI_CHARA_KIND:
            case WEAPON_PIPE_CHARA_KIND:
            case RWEAPON_PIPE_CHARA_KIND:
            case WEAPON_CSAW_CHARA_KIND:
            case RWEAPON_CSAW_CHARA_KIND:
            case WEAPON_NATA_CHARA_KIND:
            case (WEAPON_NATA_CHARA_KIND | MIRROR_MODE_CHARA_KIND_FLAG):
                if (xxx != 0) {
                    scp->status |= (1 << 4);
                } else {
                    scp->status &= ~(1 << 4);
                }
            default:
                break;
        }
    }
}

SubCharacter* CharaAdminReCreate(int kind /* r20 */, int new_id /* r19 */, int old_id /* r2 */, float* pos /* r18 */, float* rot /* r17 */, int status /* r16 */) {
    shCharacter_Manage_Delete(NULL, kind, old_id);
    return CharaWorkCreate(kind, new_id, pos, rot, status);
}

void CharaAdminBackLoadEnemy(CharaData_DemoList* list /* r16 */) {
    int i; // r3

    CharaDataBackLoadInit();
    CharaDataLoadDemo(list, 4);
    back_load_admin = 1;
    for (i = 0; list->kind != 0; i++) {
        ASSERT_ON_LINE(i < (8 - 1), 962);
        back_load_admin_list[i].kind      = list->kind;
        back_load_admin_list[i].model     = list->model;
        back_load_admin_list[i].animation = list->animation;
        back_load_admin_list[i].shadow    = list->shadow;
        back_load_admin_list[i].cluster   = list->cluster;
        list++;
    }
    back_load_admin_list[i].kind = 0;
}
