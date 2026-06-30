#include "Chacter/m3_sc.h"
#include "Chacter/m3_play.h"
#include "Chacter/skelton.h"
#include "Heap/sh2_ch_malloc.h"
#include "Lens/lens_flare.h"
#include "Chacter_Draw/clani.h"
#include "Chacter/anime.h"
#include "Chacter_Draw/model3_n.h"
#include "Chacter/m3_wep.h"
#include "Chacter/m3_play_event.h"
#include "Chacter/chara_list.h"

static SubCharacter* shCharacterGetFreeList(void);
static void AddFreeList(SubCharacter* scp);
static void shCharacterSortList(SubCharacter* scp /* r2 */);
static void shCharacterTopOfList(SubCharacter* scp);
static void shCharacterCutList(SubCharacter* scp);
static int shCharacterNeckAngleExec(shAnime3d* ap);
static int shCharacterKneeAngleExec(shAnime3d* ap /* r17 */);
static void shCharacterSetClusterAnimeWork(SubCharacterDisp* scp_d, int index);
static void shCharacterInitialize(SubCharacter* scp, int id, int model);
static void shCharacterSetHandler(SubCharacter* scp /* r16 */);
static void UpdateMatrix(SubCharacter* scp /* r18 */, Vector4* rot /* r17 */, Vector4* trans /* r16 */);

// @todo: migrate data
extern /* static */ u_char human_skelton[14]; // size: 0xE, address: 0x38C6D8
extern /* static */ u_char enemy_skelton[14]; // size: 0xE, address: 0x38C6E8
extern /* static */ u_char obj_outdoor_skelton[20]; // size: 0x14, address: 0x38C700
extern /* static */ u_char obj_anime_skelton[69]; // size: 0x45, address: 0x38C720
extern /* static */ u_char obj_stay_skelton[97]; // size: 0x61, address: 0x38C770

static inline int clamp_12(int value) {
    int result = value & 0xFFF;
    if (value < 0 && result != 0)
        result -= (1 << 12);
    return result;
}

static inline subchar_rot(SubCharacter* scp, Vector4* rot)
{
    sceVu0FVECTOR stack_rot;
    stack_rot[0] = rot->x;
    stack_rot[1] = 0.0f;
    stack_rot[2] = rot->z;
    stack_rot[3] = 1.0f; 

    sceVu0RotMatrix(scp->mat, kt_unit_matrix, stack_rot);
    sceVu0RotMatrixY(scp->mat, scp->mat, rot->y);
}

static inline subchar_trans(SubCharacter* scp, Vector4* trans)
{
    scp->mat[3][0] = trans->x;
    scp->mat[3][1] = trans->y;
    scp->mat[3][2] = trans->z;
    scp->mat[3][3] = 1.0f;
}

static SubCharacter* shCharacterGetFreeList(void) {
    SubCharacter* scp = sh2chara.free; // r2
    if (scp != NULL) {
        sh2chara.free = scp->next;
    }
    return scp;
}

static void AddFreeList(SubCharacter* scp) {
    scp->next = &sh2chara.free->sc;
    sh2chara.free = scp;
}

static void shCharacterSortList(SubCharacter* scp /* r2 */) {
    SubCharacter* pre;
    SubCharacter* next;

    if (!(next = sh2chara.head)) {
        sh2chara.head = scp;
        scp->next = NULL;
        scp->pre = NULL;
        return;
    }



    if (sh2chara.player != NULL) {
        pre = next;
        next = next->next;
    } else {
        pre = NULL;
    }

    for (; next != NULL; pre = next,  next = next->next) {
        if (scp->kind > next->kind)
            continue;

        if (pre != NULL) {
            pre->next = scp;
        } else {
            sh2chara.head = scp;
        }
        next->pre = scp;

        scp->pre = pre;
        scp->next = next;

        return;
    }

    pre->next = scp;
    scp->pre = pre;
    scp->next = NULL;
}

static void shCharacterTopOfList(SubCharacter* scp) {
    if (sh2chara.head != NULL) {
        sh2chara.head->pre = scp;
    }
    scp->next = sh2chara.head;
    scp->pre = NULL;
    sh2chara.head = scp;
}


static void shCharacterCutList(SubCharacter* scp) {
    SubCharacter* pre = scp->pre;
    SubCharacter* next  = scp->next;

    if (pre != NULL) {
        pre->next = next;
        scp->pre = NULL;
    } else {
        sh2chara.head = next;
    }
    if (next != NULL) {
        next->pre = pre;
        scp->next = NULL;
    }
}

static void shCharacterInitialize(SubCharacter* scp, int id, int _model) {
    
    shCharacterSortList(scp);

    scp->status = 1 | (1 << 4);
    scp->sub_status = 0;
    scp->sub_st = 0;


    scp->id = id;

    scp->step = 0;
    scp->model_type = 0;


    scp->pos = (Vector4){0};
    scp->b_pos = (Vector4){0};
    scp->rot = (Vector4){0};


    scp->mat = kt_unit_matrix;

    scp->spd_roty = 0.0f;
    scp->spd_y = 0.0f;
    scp->spd_org = 0.0f;
    scp->spd = 0.0f;
    scp->center_y = 0.0f;
    scp->eye_y = 0.0f;

    
    shQzero(&scp->battle, sizeof(shBattleInfo));

    *(u_int*) &scp->work = 0;
    scp->function = NULL;

}

static void UpdateMatrix(SubCharacter* scp, Vector4* rot, Vector4* trans) {
    if (scp->status & 0x80) {


        
        subchar_rot(scp, rot);
    } else {
        sceVu0RotMatrix(scp->mat, kt_unit_matrix, rot);
    }
    subchar_trans(scp, trans);
}

static int shCharacterNeckAngleExec(shAnime3d* ap) {
    shSkelton* stp; // r16

    for (stp = ap->top; stp != NULL; stp = stp->next) {
        if (stp->untouchable == NULL) {
            shCharacterAnimePartsControl(ap, stp, &ap->rot_neck);
        }     
    }
    return 0;
}

static int shCharacterKneeAngleExec(shAnime3d* ap /* r17 */) {
    shSkelton* stp; // r16

    for (stp = ap->top; stp != NULL; stp = stp->next) {
        if (stp->untouchable == NULL) {
            shCharacterAnimePartsControl(ap, stp, &ap->rot_body_neck);
        }
    }
    return 0;
}

void SCAddPos(SubCharacter* scp, Vector4* pos) {
    scp->pos.x += pos->x;
    scp->pos.y += pos->y;
    scp->pos.z += pos->z;
    scp->pos.w = 1.0f;
}

void SCSetRot(SubCharacter* scp, Vector4* rot) {
    scp->rot = *rot;
}

void SCAddRot(SubCharacter* scp, Vector4* rot) {
    scp->rot.x += rot->x;
    scp->rot.y += rot->y;
    scp->rot.z += rot->z;
}

static void shCharacterSetClusterAnimeWork(SubCharacterDisp* scp_d, int index) {
    if (scp_d->cluster_anime != NULL) {
        ClusterAnimeDelete(scp_d->cluster_anime, index);
        scp_d->cluster_anime = NULL;
    }
    if (scp_d->models[0] != NULL) { 

        
        scp_d->cluster_anime = ClusterAnimeNew(Model3NClusters(scp_d->models[0]), index);
    }
}

void shCharacterClusterAnimeSet(SubCharacter* scp, int anime) {
    SubCharacterDisp* scp_d = scp;

    ClusterAnimeSet(scp_d->cluster_anime, (void *)anime);
}

void SCSetModel(SubCharacter* scp, int model) { // not line matched
    void* model_adr; // r17
    SubCharacterDisp* scp_d = scp; // r2

    model_adr = (void*) model;
    
    if (scp_d == NULL)
        ASSERT_ON_LINE(0, 581);
    
    if (model_adr) {
        if (!scp_d->anime.top) {
            shCharacterAnimeSetSkelton(&scp_d->anime, shCharacterGetSkeletons(Model3NSkeletons(model_adr), (u_char*)Model3SkeletonStructure(model_adr)));
            scp_d->sc.sk_top = scp_d->anime.top;
        }
        scp_d->work = shCh_ASC_Malloc(Model3WorkSize(model_adr));
        Model3InitWork(model_adr, scp_d->work);
    }

    scp_d->models[0] = model_adr;
    scp_d->models[1] = model_adr;
    scp_d->models[2] = model_adr;

    shCharacterSetClusterAnimeWork(scp_d, scp->index);

    sh2chara.total++;
}

void* shCharacterGetAnimeAdrForDrama(SubCharacter* scp, int arg1) {
    SubCharacterDisp* scp_d = scp; // r2
    return (void*) scp_d->anime_adr;
}

void* shCharacterGetAnimeAdrForPlay(SubCharacter* scp) {
    SubCharacterDisp* scp_d = scp; // r2
    return (void*) scp_d->anime_adr;
}

void* shCharacterGetClusterAnimeAdr(SubCharacter* scp) {
    SubCharacterDisp* scp_d = scp; // r2
    return (void*) scp_d->clani_adr;
}

void shCharacterSetPlayer(SubCharacter* scp) {
    if (scp == NULL) {





        sh2chara.player = scp;
        sh2chara.head = scp;
        return;
    }



    sh2chara.player = scp;

    shCharacterCutList(scp);
    shCharacterTopOfList(scp);

    shCharacterSetPlayerLow(scp);

}

short shCharacterGetModelID(SubCharacter* scp) {
    return scp->kind;
}

SubCharacter* shCharacterGetSubCharacter(u_short kind, short id) {
    SubCharacter* pre = sh2chara.head; // r2
    SubCharacter* next = pre->next; // r6
    
    if (pre->kind == kind) {
        if (id == -1 || id == pre->id) 
            return pre;        
    }
    while (next != NULL) {
        if (next->kind == kind) {
            if (id == -1 || id == next->id)
                return next;
        }
        next = next->next;
    }
    return NULL;
}

u_char shCharacterGetSkeltonNum(short kind) {
    #define NONE_SKELETON_NUM   0
    #define ITEM_SKELETON_NUM   1
    #define WEAPON_SKELETON_NUM 2

    int type = kind >> 8;

    switch (type) {
        case HUMAN_CHARA_KIND:
            return (human_skelton - HUMAN_CHARA_KIND_START)[kind];

        case ENEMY_CHARA_KIND:
            return (enemy_skelton - ENEMY_CHARA_KIND_START)[kind];

        case OBJECT_SKELETAL_OUTDOOR_CHARA_KIND:
            return (obj_outdoor_skelton - OBJECT_SKELETAL_OUTDOOR_CHARA_KIND_START)[kind];

        case WEAPON_CHARA_KIND:
            return WEAPON_SKELETON_NUM;

        case OBJECT_ANIMATED_CHARA_KIND:
            return (obj_anime_skelton - OBJECT_ANIMATED_CHARA_KIND_START)[kind];

        case OBJECT_STAY_CHARA_KIND:
            return (obj_stay_skelton - OBJECT_STAY_CHARA_KIND_START)[kind];

        case OBJECT_G_CHARA_KIND:
        case OBJECT_X_CHARA_KIND:
            return ITEM_SKELETON_NUM;

        default:
            return NONE_SKELETON_NUM;
    }
}

int shCharacterAnimeOneFrameSize(u_short id) {
    u_short result; // r2     
    switch (id) {
        case LLL_JMS_CHARA_KIND:
        case HLL_JMS_CHARA_KIND:
            result = 0x210;
            break;
        case LLL_MAR_CHARA_KIND:
            result = 0x1D0;
            break;
        case BOAT_CHARA_KIND:
            result = 0x46;
            break;
        case HHH_MAR_CHARA_KIND:
            result = 0x3A0;
            break;
        case HHH_EDI_CHARA_KIND:
            result = 0x32C;
            break;
        case AGL_CHARA_KIND:
            result = 0x3B8;
            break;
        case LAU_CHARA_KIND:
            result = 0x468;
            break;
        case MRY_CHARA_KIND:
            result = ITEM_I_KAKUZAI_CHARA_KIND;
            break;
        case HHH_MXX_CHARA_KIND:
            result = 0x3B8;
            break;
        case INU_CHARA_KIND:
            result = 0x190;
            break;
        case EN_SCU_CHARA_KIND:
            result = 0x184;
            break;
        case EN_MKN_CHARA_KIND:
            result = 0xE4;
            break;
        case EN_TYU_CHARA_KIND:
            result = 0x11A;
            break;
        case EN_RED_CHARA_KIND:
        case 0x20E:
        case 0x210:
        case 0x20F:
            result = 0x240;
            break;
        case EN_NSE_CHARA_KIND:
        case EN_XOO_CHARA_KIND:
            result = 0x184;
            break;
        case EN_IKE_CHARA_KIND:
            result = 0xCE;
            break;
        case EN_PAP_CHARA_KIND:
            result = 0x17E;
            break;
        case EN_LLL_EDI_CHARA_KIND:
            result = 0x1C4;
            break;
        case EN_BOS_CHARA_KIND:
            result = 0x23A;
            break;
        case EN_ONI_CHARA_KIND:
            result = 0x210;
            break;
        case EN_ARM_CHARA_KIND:
            result = 0xC8;
            break;
        case 0x400:
            result = 0x98;
            break;
        case 0x401:
            result = 0x10E;
            break;
        case WEAPON_HANDGUN_CHARA_KIND:
            result = 0x22;
            break;
        case WEAPON_SHOTGUN_CHARA_KIND:
            result = 0x22;
            break;
        case WEAPON_RIFLGUN_CHARA_KIND:
            result = 0x22;
            break;
        case WEAPON_KAKUZAI_CHARA_KIND:
            result = 0x22;
            break;
        case WEAPON_PIPE_CHARA_KIND:
            result = 0x22;
            break;
        case WEAPON_SP_CHARA_KIND:
            result = 0x22;
            break;
        case WEAPON_CSAW_CHARA_KIND:
            result = 0x22;
            break;
        case WEAPON_NATA_CHARA_KIND:
            result = 0x22;
            break;
        case ITEM_B_REI_CHARA_KIND:
            result = 0x28;
            break;
        case ITEM_B_NIK_CHARA_KIND:
            result = 0x6A;
            break;
        case ITEM_I_LETTER_CHARA_KIND:
            result = 0x5E;
            break;
        case ITEM_B_PIZ_CHARA_KIND:
            result = 0x16;
            break;
        default:
            result = 0;
            break;
    }
    return result;
}

void shCharacterInitSubCharacter(void) {
    int i; // r5
    SubCharacterDisp* scp_d; // r4

    
    memset(&sh2chara, 0, sizeof(shCharacterAll));
    
    scp_d = &sh2chara.work[0];
    sh2chara.free = sh2chara.work;



    
    for (i = 0; i < 31; i++, scp_d++) {
        scp_d->sc.next = (scp_d + 1);
    }
    scp_d->sc.next = NULL;



    
    for (i = 0; i < 32; i++) {
        sh2chara.work[i].sc.index = i;
    }
}

static void shCharacterSetHandler(SubCharacter* scp /* r16 */) {
    switch (scp->kind) {
        case LLL_JMS_CHARA_KIND:
        case HLL_JMS_CHARA_KIND:
            shCharacterSetPlayer(scp);
            return;
        case RLLL_JMS_CHARA_KIND:
        case RHLL_JMS_CHARA_KIND:
            shCharacterSetHumanRPJMSLow(scp);
            return;
        case HHL_JMS_CHARA_KIND:
        case HHH_JMS_CHARA_KIND:
            shCharacterSetHumanDJMSLow(scp);
            return;
        case RHHL_JMS_CHARA_KIND:
        case RHHH_JMS_CHARA_KIND:
            shCharacterSetHumanRDJMSLow(scp);
            return;
        case LAU_CHARA_KIND:
            shCharacterSetHumanLAULow(scp);
            return;
        case LLL_MAR_CHARA_KIND:
            shCharacterSetHumanMARLow(scp);
            return;
        case HHH_MAR_CHARA_KIND:
            shCharacterSetHumanDMARLow(scp);
            return;
        case AGL_CHARA_KIND:
            shCharacterSetHumanAGLLow(scp);
            return;
        case RAGL_CHARA_KIND:
            shCharacterSetHumanRAGLLow(scp);
            return;
        case HHH_EDI_CHARA_KIND:
            shCharacterSetHumanEDILow(scp);
            return;
        case MRY_CHARA_KIND:
            shCharacterSetHumanMRYLow(scp);
            return;
        case HHH_MXX_CHARA_KIND:
            shCharacterSetHumanMXXLow(scp);
            return;
        case BOAT_CHARA_KIND:
            shCharacterSetHumanBOTLow(scp);
            return;
        case INU_CHARA_KIND:
            shCharacterSetHumanINULow(scp);
            return;
        case EN_SCU_CHARA_KIND:
            shCharacterSetEnemySCULow(scp);
            return;
        case EN_MKN_CHARA_KIND:
            shCharacterSetEnemyMKNLow(scp);
            return;
        case EN_TYU_CHARA_KIND:
            shCharacterSetEnemyTYULow(scp);
            return;
        case EN_IKE_CHARA_KIND:
            shCharacterSetEnemyIKELow(scp);
            return;
        case EN_PAP_CHARA_KIND:
            shCharacterSetEnemyPAPLow(scp);
            return;
        case EN_LLL_EDI_CHARA_KIND:
            shCharacterSetEnemyEDBLow(scp);
            return;
        case EN_BOS_CHARA_KIND:
            shCharacterSetEnemyBOSLow(scp);
            return;
        case EN_NSE_CHARA_KIND:
        case EN_XOO_CHARA_KIND:
            shCharacterSetEnemyNSELow(scp);
            return;
        case EN_RED_CHARA_KIND:
            shCharacterSetEnemyREDLow(scp);
            return;
        case EN_ONI_CHARA_KIND:
            shCharacterSetEnemyONILow(scp);
            return;
        case EN_ARM_CHARA_KIND:
            shCharacterSetEnemyARMLow(scp);
            return;
        case EN_TY2_CHARA_KIND:
        case EN_TY3_CHARA_KIND:
            shCharacterSetEnemyTY23Low(scp);
            return;
        default:
            switch (scp->kind >> 0x8) {
            case 8:
                if (scp->kind  & 0x20) {
                    shCharacterSetWeaponRLow(scp);
                    return;
                }
                shCharacterSetWeaponLow(scp);
                JamesWeaponSet(scp->kind & 0xF);
                return;
            case 4:
                switch (scp->kind) {
                case ITEM_RI_KNIFE_CHARA_KIND:
                case ITEM_RI_PHOTO_CHARA_KIND:
                    shCharacterSetRObjectLow(scp);
                    return;
                case ITEM_B_NIK_CHARA_KIND:
                    shCharacterSetObjectNIKLow(scp);
                    return;
                default:
                    shCharacterSetObjectLow(scp);
                    return;
                }
                break;
            case 3:
            case 5:
                shCharacterSetStayObjectLow(scp);
                return;
            case 7:
                shCharacterSetWorldScreenItemLow(scp);
                return;
            case 6:
                shCharacterSetItemScreenItemLow(scp);
            default:
                return;
            }
            break;
    }
}

SubCharacter* shCharacterCreate(u_int id, int model, int anime, int clani, int chr_id) {
    SubCharacter* scp = shCharacterGetFreeList(); // r2
    SubCharacterDisp* scp_d = (SubCharacterDisp*) scp; // r16

    if (scp_d == NULL)
        ASSERT_ON_LINE(0, 1229);


    
    scp->kind = chr_id;
    
    shCharacterInitialize(scp, id, model);
    
    scp_d->model_adr = model;
    scp_d->anime_adr = anime;
    scp_d->clani_adr = clani;
    
    
    
    shCharacterSetHandler(scp);
    return scp;
}

void shCharacterDelete(SubCharacter* scp) { // but this is not matched lol
    SubCharacterDisp* scp_d = scp;
    if (scp_d == NULL) {
        return;
    }
    if (scp == sh2chara.player) {
        shCharacterSetPlayer(NULL);
    }





    shCharacterFreeSkeltons(scp->sk_top);
    scp_d->anime.top = NULL;



    shCh_ASC_Free(scp_d->work);


    
    scp_d->work = NULL;
    
    
    ClusterAnimeDelete(scp_d->cluster_anime, scp->index);
    

    shCharacterCutList(scp);
    
    
    scp->kind = 0;
    scp->id = 0;
    scp->sk_top = NULL;
    scp->pre = NULL;
    scp->next = NULL;
    scp->function = NULL;
    scp->enemy_p = NULL;
    
    AddFreeList(scp);
    sh2chara.total--;

}

void shCharacterPlayingExecAnimeOne(SubCharacter* scp) {
    SubCharacterDisp* scp_d = scp;
    shSkelton * stp; // r2
    SubCharacter * scp_wp; // r2
    u_char weapon; // r2

    switch (scp_d->sc.kind) {
        case LLL_JMS_CHARA_KIND:
        case HLL_JMS_CHARA_KIND:
            sh_PJMS_SetUntouchUpper(scp_d->anime.top);
            shCharacterPlayingAnimeExecMain(&scp_d->anime, 0);
            sh_PJMS_ResetUntouchUpper(scp_d->anime.top);
            sh_PJMS_SetUntouchUnder(scp_d->anime2.top);
            shCharacterPlayingAnimeExecMain(&scp_d->anime2, 1);
            sh_PJMS_ResetUntouchUnder(scp_d->anime2.top);
            mizSetUntouchWithoutKnee(scp_d->anime2.top);
            shCharacterKneeAngleExec(&scp_d->anime2);
            mizResetUntouchWithoutKnee(scp_d->anime2.top);
            if (scp_d->sc.status & 0x20000) {
                sh_PJMS_SetUntouchUnder(scp_d->anime2.top);
                shCharacterNeckAngleExec(&scp_d->anime2);
                sh_PJMS_ResetUntouchUnder(scp_d->anime2.top);
            }
            break;

        case LLL_MAR_CHARA_KIND:
            shCharacterPlayingAnimeExecMain(&scp_d->anime, 0);
            MariaSetUntouchWithoutNeck(scp_d->anime.top);
            shCharacterNeckAngleExec(&scp_d->anime);
            MariaResetUntouchWithoutNeck(scp_d->anime.top);
            break;
        default:
            shCharacterPlayingAnimeExecMain(&scp_d->anime, 0);
            break;
    }

    switch (scp_d->sc.kind) {
        case HLL_JMS_CHARA_KIND:
        case LLL_JMS_CHARA_KIND:
            weapon = PlayerGetJamesWeapon();
            if (!(scp_wp = shCharacterGetSubCharacter(WEAPON_ID_START + weapon, -1))) break;
            shUpdateWeaponMatrixAfterAnime(scp_wp, scp_d->sc.kind);
            break;

        case BOAT_CHARA_KIND:
            shUpdateBoatJamesPosAfterAnime();
            break;

        case EN_IKE_CHARA_KIND:
            enIKETrans(scp_d->sc.enemy_p);
            break;

        case EN_ARM_CHARA_KIND:
            enARMTrans(scp_d->sc.enemy_p);
            break;
    }

    switch (scp_d->sc.kind) {
        case HLL_JMS_CHARA_KIND:
        case LLL_JMS_CHARA_KIND:
            shGetJamesLightPos_Calc();
            shLensFlareExec(&scp_d->sc, 3.0f, 0);
            if (PlayerReverseLightCalcIsOn()) {
                shGetJamesLightPos_Calc_Reverse();
                shLensFlareExec(&scp_d->sc, 3.0f, 1);
            }   
    }
}

void shCharacterDramaExecAnimeOne(SubCharacter* scp) {
    SubCharacterDisp* scp_d = scp;
    SubCharacter* scp_wp;
    u_char weapon;

    shCharacterDramaAnimeExecMain(&scp_d->anime);
    ClusterAnimeExec(scp_d->cluster_anime, &scp_d->anime, scp_d);

    switch (scp_d->sc.kind) {
        case HHL_JMS_CHARA_KIND:
        case HLL_JMS_CHARA_KIND:
        case LLL_JMS_CHARA_KIND: {
            weapon = PlayerGetJamesWeapon();
            if (!(scp_wp = shCharacterGetSubCharacter(WEAPON_ID_START + weapon, -1))) break;
            shUpdateWeaponMatrixAfterAnime(scp_wp, scp_d->sc.kind);
            break;
        }

        default:
            break;
    }

    switch (scp_d->sc.kind) {
        case HHH_JMS_CHARA_KIND:
        case HHL_JMS_CHARA_KIND:
        case HLL_JMS_CHARA_KIND:
        case LLL_JMS_CHARA_KIND:
            shGetJamesLightPos_Calc();
            shLensFlareExec(&scp_d->sc, 3.0f, 0);
    }
}

void shCharacterAnimeCopyForReverseModel(SubCharacter* scp) { // not line matched 
    SubCharacter* org; // r2
    SubCharacterDisp* org_d; // r2
    SubCharacterDisp* scp_d; // r2    
    SubCharacter* scp_wp; // r2
    u_char weapon; // r2
    
    org = shCharacterGetSubCharacter(scp->kind - 0x20, -1);
    
    if (org == NULL)
        ASSERT_ON_LINE(0, 1657);

    scp_d = scp;
    org_d = org;

    scp_d->anime.top = org_d->anime.top;

    scp_d->cluster_anime = org_d->cluster_anime;

    switch (scp->kind) {
            case RHLL_JMS_CHARA_KIND:
            case RLLL_JMS_CHARA_KIND:
                weapon = PlayerGetJamesWeapon();
                    
                if ((scp_wp = shCharacterGetSubCharacter((weapon + 0x820), -1)) != NULL) {
                    shUpdateWeaponMatrixAfterAnime(scp_wp, scp->kind);
                }
                break;
        }

    switch (scp->kind) {
        case RHLL_JMS_CHARA_KIND:
        case RLLL_JMS_CHARA_KIND:
        case RHHH_JMS_CHARA_KIND:
        case RHHL_JMS_CHARA_KIND:
            break;
    }
}

void SCNowDemoEventSwitch(SubCharacter* scp, int flag) {
    if (flag) {
        scp->status |= (1 << SCP_STATUS_BIT_NOW_DEMO_EVENT);     
    } else {
        scp->status &= ~(1 << SCP_STATUS_BIT_NOW_DEMO_EVENT);
    }    
}

void SCNowPlayableEventSwitch(SubCharacter* scp, int flag) {
    if (flag) {
        scp->status |= (1 << SCP_STATUS_BIT_NOW_PLAYABLE_EVENT);
    } else {
        scp->status &= ~(1 << SCP_STATUS_BIT_NOW_PLAYABLE_EVENT);
    }
}

void SCStayModelSwitch(SubCharacter* scp, int flag) {
    if (flag) {
        scp->status |= (1 << SCP_STATUS_BIT_STAY_MODEL);
    } else {
        scp->status &= ~(1 << SCP_STATUS_BIT_STAY_MODEL);        
    }
}

void SCAnimeTypeSwitch(SubCharacter* scp, int flag) {
    if (flag) {
        scp->status |= (1 << SCP_STATUS_BIT_ANIME_TYPE);
    } else {
        scp->status &= ~(1 << SCP_STATUS_BIT_ANIME_TYPE);
    }
}

void SCRotZYXSwitch(SubCharacter* scp, int flag) {
    if (flag) {
        scp->status |= (1 << SCP_STATUS_BIT_ROT_ZYX);
    } else {
        scp->status &= ~(1 << SCP_STATUS_BIT_ROT_ZYX);        
    }
}

void SCFreefallSwitch(SubCharacter* scp, int sw) {
    if (sw) {
        scp->status |= (1 << SCP_STATUS_BIT_FREEFALL);
    } else {
        scp->status &= ~(1 << SCP_STATUS_BIT_FREEFALL);
    }
}

void SCLightOnNowSwitch(SubCharacter* scp, int sw) {
    if (sw) {
        scp->status |= (1 << SCP_STATUS_BIT_LIGHT_ON_NOW);
    } else {
        scp->status &= ~(1 << SCP_STATUS_BIT_LIGHT_ON_NOW);
    }
}

void shCharacterExecAnimeAll(void) { // not line matched
    SubCharacter* scp; // r16

    for (scp = sh2chara.head; scp != NULL; scp = scp->next) {
        if (!(scp->status & 0x100) && (scp->status & 0x10)) {
            if (scp->model_type != 0) {
                shCharacterAnimeCopyForReverseModel(scp);
            } else if (scp->status & 4) {
                shCharacterPlayingExecAnimeOne(scp);
            } else {
                shCharacterDramaExecAnimeOne(scp);
            }
        }
    }
    demo_status &= ~0x40;
}

void shCharacterUpdateAll(void) {
    SubCharacter* scp; // r16
    
    for (scp = sh2chara.head; scp != NULL; scp = scp->next) {
        if (scp->status & 1) {
            scp->status &= ~1;
        }
        UpdateMatrix(scp, &scp->rot, &scp->pos);        
    }
    
}

void shCharacterSetFunction(SubCharacter* scp, void (*func)(SubCharacter*)) {
    scp->function = func;
}

void shCharacterExecFunctionAll(void) {
    SubCharacter* scp; // r2
    SubCharacter* next; // r16

    
    scp = sh2chara.head;



    
    while (scp != NULL) {
        next = scp->next;
        
        if (scp->function != NULL)
            scp->function(scp);        
        scp = next;
    }

    
    shCharacterUpdateAll();
}

void shCharacterAnimeSet(SubCharacter* scp /* r19 */, int ctrl_type /* r2 */, int inter_type /* r18 */, AnimeInfo* anim_info /* r17 */, int anime /* r2 */) { //line matched up to a certain point then I gave up
    SubCharacterDisp* scp_d; // r2
    shAnime3d* anim; // r16
    void* anime_adr; // r2
























    
    scp_d = scp;

    switch (ctrl_type) {
        case 0:
        case 2:
            anim = &scp_d->anime;
            break;
        case 1:
            anim = &scp_d->anime2;
            break;
    }    

    
    scp_d->anime.scale  = 1.0f;
    scp_d->anime2.scale = 1.0f;



    
    anim->p_anime = anim->anime;
    anim->p_frame_top = anim->frame_top;
    
    anim->anime = (void*)anime;




    
    anim->frame_size = shCharacterAnimeOneFrameSize(scp->kind);






















    
    if ((scp->kind >> 8) == 8) {
        anim->first_bone_type = 1;
    } else {
        anim->first_bone_type = 0;
    }



    

    switch (anim->comp_type = inter_type) {



        
        case 0:
        case 2:
            anim->total_count = 0;
            if (anim_info->speed < 0) 
                anim->cur_frame.x = anim->cur_frame.y = anim_info->end;
            else 
                anim->cur_frame.x = anim->cur_frame.y = anim_info->start;

            
            anim->frame_top = (void*)((u_char*)anim->anime + (anim->frame_size * anim->cur_frame.y));
            
            anim->c_count.x = anim->c_count.y = 0;           
            anim->c_speed.x = anim->c_speed.y = 0;            
            anim->anim_a = anim_info;
            anim->anim_b = anim_info;
            
            break;
















        


        
        case 4:
        case 6:
        case 8:
    

            switch (inter_type) {
                    case 4:
                    if (anim_info->speed < 0) {
                        anim->cur_frame.y = anim_info->end;
                    } else {
                        anim->cur_frame.y = anim_info->start;
                    }
                    break;
                case 8:
                    anim->cur_frame.y = scp_d->anime.cur_frame.y;
                    break;        
            }
            

            anim->frame_top = (void*)((u_char*)anim->anime + (anim->frame_size * anim->cur_frame.y));
            
            anim->c_count.y = 0;
            anim->c_speed.y = 0;
            anim->total_speed.y = 0;


            if (anim->anim_a == NULL) {

                
                anim->anim_a = anim_info;
                
            } else {                
                anim->anim_a = anim->anim_b;
            }
            anim->anim_b = anim_info;
            break;        
        case 10:





            
            

            
            anim->cur_frame.y = anim->cur_frame.x;


            anim->c_count.y = 0;
            
            anim->c_speed.y = 128;
            
            anim->total_speed.y = 0;

            if (anim->anim_a == NULL)
                ASSERT_ON_LINE(0, 2374);

            anim->anim_a = anim->anim_b;
            anim->anim_b = anim_info;
            break;
    }
}

void shCharacterStayObjectScaleSet(SubCharacter* scp, float scale) {
    SubCharacterDisp* scp_d = scp; // r2
    
    scp_d->anime.scale = scale;
    shCharacterStayModelScale(&scp_d->anime);
}

void shCharacterItemScreenObjectSet(SubCharacter* scp, shItemScreenObjectSettingData* data) {    
    SubCharacterDisp* scp_d = scp; // r2
    
    Vector4 rot_tmp = { 0.0f, 0.0f, 0.0f, 1.0f }; // r29+0x30 took these from ghidra
    shSkelton* sp; // r2
    
    sp = scp_d->anime.top;

    
    shCharacterStayModelExecItem(sp, &data->rot);


    
    scp_d->anime.scale = data->scale;
    shCharacterStayModelScale(&scp_d->anime);
    
    SCSetRot(scp, &rot_tmp);
}

void shCharacterStayObjectNthPartsGet1st(SubCharacter* scp, int n, float* pos, float* rot) {
    int i; // r4
    SubCharacterDisp* scp_d = scp; // r2
    shSkelton* sp = scp_d->anime.top; // r8

    for (i = 0; i < n; i++) 
        sp = sp->next; 
    
    pos[0] = sp->des_t.x;
    pos[1] = sp->des_t.y;
    pos[2] = sp->des_t.z;
    rot[0] = rot[1] = rot[2] = 0.0f;


    
}


void shCharacterStayObjectNthPartsSet(SubCharacter* scp, s32 n, f32* pos, f32* rot) {
    int i; // r3
    SubCharacterDisp* scp_d = scp; // r2
    shSkelton* sp; // r16



    sp = scp_d->anime.top;
    scp_d->anime.scale = 1.0f;

    for (i = 0; i < n; i++) 
        sp = sp->next; 


    
    shCharacterStayModelExecNthParts(sp, pos, rot);

    sp->xx = rot[0];
    sp->yy = rot[1];
    sp->zz = rot[2];
}

short shCharacterAnimeSpeedGet_(SubCharacter* scp, u_int type) {
    SubCharacterDisp* scp_d;
    shAnime3d* anime;   
    scp_d = scp;
    switch (type) {
        case 0:
        case 2:
            anime = &scp_d->anime;
            break;
        case 1:
            anime = &scp_d->anime2;
            break;

    }
    return anime->total_speed.x;
}

void shCharacterAnimeSpeedAdd(SubCharacter* scp, short add) {
    shCharacterAnimeSpeedAdd_(scp, 0, add);
}

void shCharacterAnimeSpeedAdd_(SubCharacter* scp, u_int type, short add) {
    SubCharacterDisp* scp_d; // r2
    shAnime3d* anime; // r7
    shAnime3d* anime2; // r4    
    scp_d = scp;
    anime = &scp_d->anime;
    anime2 = &scp_d->anime2;

    switch (type) {
        case 0:
            anime->c_speed.x = add;
            anime2->c_speed.x = add;
            break;
        case 2:
            anime->c_speed.x = add;
            break;
        case 1:
            anime2->c_speed.x = add;
            break;
    }
}

void shCharacterAnimeSpeedAddY(SubCharacter* scp, short add) {
    shCharacterAnimeSpeedAddY_(scp, 0, add);
}

void shCharacterAnimeSpeedAddY_(SubCharacter* scp /* r2 */, u_int type /* r2 */, short add /* r2 */) {
    SubCharacterDisp* scp_d; // r2
    shAnime3d* anime; // r7
    shAnime3d* anime2; // r4    
    scp_d = scp;
    anime = &scp_d->anime;
    anime2 = &scp_d->anime2;        
    switch (type) {
        case 0:
            anime->c_speed.y = add;
            anime2->c_speed.y = add;
            break;
        case 2:
            anime->c_speed.y = add;
            break;
        case 1:
            anime2->c_speed.y = add;
            break;
    }
}

void shCharacterAnimePause(SubCharacter* scp) {
    shCharacterAnimePause_(scp, 0);
}

void shCharacterAnimePause_(SubCharacter* scp, u_int type) {
    SubCharacterDisp* scp_d; // r2
    shAnime3d* anime; // r6
    shAnime3d* anime2; // r4

    scp_d = scp;
    anime = &scp_d->anime;
    anime2 = &scp_d->anime2;        
    switch (type) {
        case 0:
            anime->comp_type = -1;
            anime2->comp_type = -1;
            break;
        case 2:
            anime->comp_type = -1;
            break;
        case 1:
            anime2->comp_type = -1;
            break;



        
    }
}

void shCharacterAnimeRestart(SubCharacter* scp) {
    shCharacterAnimeRestart_(scp, 0);
}

void shCharacterAnimeRestart_(SubCharacter* scp, u_int type) {
    SubCharacterDisp* scp_d; // r2
    shAnime3d* anime; // r6
    shAnime3d* anime2; // r8

    scp_d = scp;
    anime = &scp_d->anime;
    anime2 = &scp_d->anime2;  
    
    switch (type) {
        case 0:
            if (anime->comp_type == -1) {
                anime->comp_type = 2; 
            }        
            if (anime2->comp_type == -1) {
                anime2->comp_type = 2;    
            }
            break;
        case 2:
            if (anime->comp_type == -1) {
                anime->comp_type = 2;
            }
            break;
        case 1:
            if (anime2->comp_type == -1) {
                anime2->comp_type = 2;
            }
            break;
    }
}

int shCharacterAnimeIsEnd(SubCharacter* scp) {
    return shCharacterAnimeIsEnd_(scp, 0);
}

int shCharacterAnimeIsEnd_(SubCharacter* scp, u_int type) {
    SubCharacterDisp* scp_d; // r2
    shAnime3d* anime; // r4
    scp_d = scp;
    
    switch (type) {
            case 0: case 2:            
                anime = &scp_d->anime;
                break;
            case 1:
                anime = &scp_d->anime2;
                break;
        }


    
    if (anime->anim_b->loop != 0) return 0;
    







    
    if (anime->total_speed.x < 0) 
        return anime->total_count == 0;
    
    return anime->total_count == ((anime->anim_b->end - anime->anim_b->start) << 12);

    
}

short shCharacterAnimeFrameGet(SubCharacter* scp) {
    return shCharacterAnimeFrameGet_(scp, 0);
}

short shCharacterAnimeFrameGet_(SubCharacter* scp /* r2 */, u_int type /* r2 */) { // not line matched
    SubCharacterDisp* scp_d; // r2
    shAnime3d* anime; // r6
    
    scp_d = scp;
    
    switch (type) {
        case 0: case 2:        
            anime = &scp_d->anime;
            break;
        case 1:
            anime = &scp_d->anime2;
            break;
    }

    switch (anime->comp_type) {
        case 10:
            if ((anime->cur_frame.y - anime->cur_frame.x) == 1) {
                return (anime->cur_frame.x - anime->anim_a->start);
            }
            return (anime->cur_frame.y - anime->anim_a->start);

        default:
            if ((anime->cur_frame.y - anime->cur_frame.x) == 1) {
                return (anime->cur_frame.x - anime->anim_b->start);
            }
            return (anime->cur_frame.y - anime->anim_b->start);
    }    
}

void shCharacterAnimeFrameSet(SubCharacter* scp, u_short frame) {
    shCharacterAnimeFrameSet_(scp, 0, frame);
}

void shCharacterAnimeFrameSet_(SubCharacter* scp, u_int type, u_short frame) { // not line matched
    SubCharacterDisp* scp_d; // r2
    shAnime3d* anime; // r5
        
    scp_d = scp;
    
    switch (type) {
            case 0:
            case 2:
                anime = &scp_d->anime;
                break;
            case 1:
                anime = &scp_d->anime2;
                break;

        }    
        anime->cur_frame.x = frame;
        anime->cur_frame.y = frame;
    
        anime->total_count = frame << 12;
    
        anime->c_count.x = 0;
    
        anime->frame_top = (void*)((u_char*)anime->anime + (anime->frame_size * anime->cur_frame.x));
}

int shCharacterAnimeCounterGet(SubCharacter* scp) {
    return shCharacterAnimeCounterGet_(scp, 0);
}

int shCharacterAnimeCounterGet_(SubCharacter* scp, u_int type) { // didnt check lines
    SubCharacterDisp* scp_d; // r2
    shAnime3d* anime; // r5
        
    scp_d = scp;
    
    switch (type) { 
        case 0:
        case 2:
            anime = &scp_d->anime;
            break;
        case 1:
            anime = &scp_d->anime2;
            break;
    }
    return anime->total_count;
}

void shCharacterAnimeCounterSet_(SubCharacter* scp, u_int type, int counter) {
    SubCharacterDisp* scp_d = scp; // r2
    shAnime3d* anime; // r5
    
    switch (type) {
        case 0: case 2:
            anime = &scp_d->anime;
            break;
        case 1:
            anime = &scp_d->anime2;
    }
    
    anime->total_count = counter;
    anime->cur_frame.x = anime->cur_frame.y = (counter >> 12);
    anime->c_count.x = clamp_12(counter);
    anime->frame_top = (void*)((u_char*)anime->anime + (anime->frame_size * anime->cur_frame.x));
}

AnimeInfo* shCharacterAnimeGetInfo(SubCharacter* scp) {
    return shCharacterAnimeGetInfo_(scp, 0);
}

AnimeInfo* shCharacterAnimeGetInfo_(SubCharacter* scp, int ctrl_type) {
    shAnime3d* ap; // r2
    SubCharacterDisp* scp_d = scp; // r2

    switch (ctrl_type) {
        case 0:
        case 2:
            ap = &scp_d->anime;
            break;
        case 1:
            ap = &scp_d->anime2;
            break;
        
        default:
            printf("error\n");
            return NULL;
    }
    
    return ap->anim_b;
}

void shCharacterPlayerModelToDrama(void) {
    SubCharacter* p; // r2

    p = shCharacterGetSubCharacter(LLL_JMS_CHARA_KIND, -1);
    if (p == NULL) 
        p = shCharacterGetSubCharacter(HLL_JMS_CHARA_KIND, -1);    
    if (p != NULL)


        
        SCAnimeTypeSwitch(p, 0);    
}

void shCharacterPlayerModelToPlayable(void) { // not line matched 
    SubCharacter* p; // r2

    p = shCharacterGetSubCharacter(LLL_JMS_CHARA_KIND, -1);
    if (p == NULL)
        p = shCharacterGetSubCharacter(HLL_JMS_CHARA_KIND, -1);
    if (p != NULL) {


        
        p->step = 0;

        
        SCAnimeTypeSwitch(p, 1);
    }
}

void shCharacterMariaModelToDrama(void) {
    SubCharacter* p; // r2

    p = shCharacterGetSubCharacter(LLL_MAR_CHARA_KIND, -1);
    if (p != NULL)


        
        SCAnimeTypeSwitch(p, 0);       
}

void shCharacterMariaModelToPlayable(void) { // not line matched
    SubCharacter* p; // r2

    p = shCharacterGetSubCharacter(LLL_MAR_CHARA_KIND, -1);
    if (p != NULL) {


        
        p->step = 0;
        
        SCAnimeTypeSwitch(p, 1);
    }
}

void shCharacterSetPosAfterDemo(SubCharacter* scp, float* pos, float roty) {
    scp->pos.x = scp->b_pos.x = pos[0];
    scp->pos.y =  scp->b_pos.y = pos[1];
    scp->pos.z = scp->b_pos.z = pos[2];
    scp->rot.y = scp->b_rot.y = roty;
    scp->rot.x = scp->b_rot.x = 0.0f;
    scp->rot.z = scp->b_rot.z = 0.0f;

    
    scp->spd = scp->spd_org = 0.0f;
}

void shCharacterGetPartsMatrixForShadow(float (*mat)[4], u_short kind, u_short id, u_int parts_name) {
    int i1; // r4
    SubCharacter* p; // r2
    shSkelton* sk; // r6

    
    p = shCharacterGetSubCharacter(kind, id);
    if (p != NULL) {
        
        sk = p->sk_top;        
        for (i1 = 0; i1 < parts_name; i1++) {
            sk = sk->next;


            
        }
        
        sceVu0MulMatrix(mat, p->mat[0], sk->src_m[0]);
    }
}

void shCharacterGetGroundInfoForShadow(float* pos, float* normal, float* height, u_short kind, u_short id) {
    SubCharacter* p; // r2

    
    p = shCharacterGetSubCharacter(kind, id);
    if (p != NULL) {
        
        volatile_vec_copy(pos, &p->pos);
        volatile_vec_copy(normal, &p->grnd_normal);
        *height = p->grnd_height;
    }
}

