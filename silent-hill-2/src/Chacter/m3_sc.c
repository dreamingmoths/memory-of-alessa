#include "Chacter/m3_sc.h"
#include "Chacter/m3_play.h"
#include "Chacter/skelton.h"
#include "Heap/sh2_ch_malloc.h"
#include "Lens/lens_flare.h"
#include "Chacter_Draw/clani.h"
#include "Chacter/anime.h"
#include "Chacter_Draw/model3_n.h"

static SubCharacter* shCharacterGetFreeList(void);
static void AddFreeList(SubCharacter* scp);
static void shCharacterSortList(SubCharacter* scp /* r2 */);
static void shCharacterTopOfList(SubCharacter* scp);
static void shCharacterCutList(SubCharacter* scp);
static int shCharacterNeckAngleExec(shAnime3d* ap);
static int shCharacterKneeAngleExec(shAnime3d* ap /* r17 */);
static void shCharacterSetClusterAnimeWork(SubCharacterDisp* scp_d, int index);
static void shCharacterSetHandler(SubCharacter* scp /* r16 */);
static void UpdateMatrix(SubCharacter* scp /* r18 */, Vector4* rot /* r17 */, Vector4 * trans /* r16 */);

inline int clamp_12(int value) {
    int result = value & 0xFFF;
    if (value < 0 && result != 0)
        result -= (1 << 12);
    return result;
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

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterInitialize);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", UpdateMatrix);

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

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", SCSetModel);

void* shCharacterGetAnimeAdrForDrama(SubCharacter* scp) {
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

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterGetSkeltonNum);

int shCharacterAnimeOneFrameSize(u_short id) {
    u_short result; // r2     
    switch (id) {
        case 0x100:
        case 0x101:
            result = 0x210;
            break;
        case 0x105:
            result = 0x1D0;
            break;
        case 0x10B:
            result = 0x46;
            break;
        case 0x106:
            result = 0x3A0;
            break;
        case 0x108:
            result = 0x32C;
            break;
        case 0x107:
            result = 0x3B8;
            break;
        case 0x104:
            result = 0x468;
            break;
        case 0x109:
            result = 0x404;
            break;
        case 0x10A:
            result = 0x3B8;
            break;
        case 0x10D:
            result = 0x190;
            break;
        case 0x200:
            result = 0x184;
            break;
        case 0x201:
            result = 0xE4;
            break;
        case 0x202:
            result = 0x11A;
            break;
        case 0x208:
        case 0x20E:
        case 0x210:
        case 0x20F:
            result = 0x240;
            break;
        case 0x207:
        case 0x20B:
            result = 0x184;
            break;
        case 0x203:
            result = 0xCE;
            break;
        case 0x204:
            result = 0x17E;
            break;
        case 0x205:
            result = 0x1C4;
            break;
        case 0x206:
            result = 0x23A;
            break;
        case 0x209:
            result = 0x210;
            break;
        case 0x20A:
            result = 0xC8;
            break;
        case 0x400:
            result = 0x98;
            break;
        case 0x401:
            result = 0x10E;
            break;
        case 0x801:
            result = 0x22;
            break;
        case 0x802:
            result = 0x22;
            break;
        case 0x803:
            result = 0x22;
            break;
        case 0x805:
            result = 0x22;
            break;
        case 0x806:
            result = 0x22;
            break;
        case 0x804:
            result = 0x22;
            break;
        case 0x807:
            result = 0x22;
            break;
        case 0x808:
            result = 0x22;
            break;
        case 0x40B:
            result = 0x28;
            break;
        case 0x421:
            result = 0x6A;
            break;
        case 0x408:
            result = 0x5E;
            break;
        case 0x42E:
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
        case 0x100:
        case 0x101:
            shCharacterSetPlayer(scp);
            return;
        case 0x120:
        case 0x121:
            shCharacterSetHumanRPJMSLow(scp);
            return;
        case 0x102:
        case 0x103:
            shCharacterSetHumanDJMSLow(scp);
            return;
        case 0x122:
        case 0x123:
            shCharacterSetHumanRDJMSLow(scp);
            return;
        case 0x104:
            shCharacterSetHumanLAULow(scp);
            return;
        case 0x105:
            shCharacterSetHumanMARLow(scp);
            return;
        case 0x106:
            shCharacterSetHumanDMARLow(scp);
            return;
        case 0x107:
            shCharacterSetHumanAGLLow(scp);
            return;
        case 0x127:
            shCharacterSetHumanRAGLLow(scp);
            return;
        case 0x108:
            shCharacterSetHumanEDILow(scp);
            return;
        case 0x109:
            shCharacterSetHumanMRYLow(scp);
            return;
        case 0x10A:
            shCharacterSetHumanMXXLow(scp);
            return;
        case 0x10B:
            shCharacterSetHumanBOTLow(scp);
            return;
        case 0x10D:
            shCharacterSetHumanINULow(scp);
            return;
        case 0x200:
            shCharacterSetEnemySCULow(scp);
            return;
        case 0x201:
            shCharacterSetEnemyMKNLow(scp);
            return;
        case 0x202:
            shCharacterSetEnemyTYULow(scp);
            return;
        case 0x203:
            shCharacterSetEnemyIKELow(scp);
            return;
        case 0x204:
            shCharacterSetEnemyPAPLow(scp);
            return;
        case 0x205:
            shCharacterSetEnemyEDBLow(scp);
            return;
        case 0x206:
            shCharacterSetEnemyBOSLow(scp);
            return;
        case 0x207:
        case 0x20B:
            shCharacterSetEnemyNSELow(scp);
            return;
        case 0x208:
            shCharacterSetEnemyREDLow(scp);
            return;
        case 0x209:
            shCharacterSetEnemyONILow(scp);
            return;
        case 0x20A:
            shCharacterSetEnemyARMLow(scp);
            return;
        case 0x20C:
        case 0x20D:
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
                case 0x443:
                case 0x444:
                    shCharacterSetRObjectLow(scp);
                    return;
                case 0x421:
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

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterCreate);

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
        case LLL_JMS_CHARA_ID:
        case HLL_JMS_CHARA_ID:
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

        case LLL_MAR_CHARA_ID:
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
        case HLL_JMS_CHARA_ID:
        case LLL_JMS_CHARA_ID:
            weapon = PlayerGetJamesWeapon();
            if (!(scp_wp = shCharacterGetSubCharacter(WEAPON_ID_START + weapon, -1))) break;
            shUpdateWeaponMatrixAfterAnime(scp_wp, scp_d->sc.kind);
            break;

        case BOAT_CHARA_ID:
            shUpdateBoatJamesPosAfterAnime();
            break;

        case EN_IKE_CHARA_ID:
            enIKETrans(scp_d->sc.enemy_p);
            break;

        case EN_ARM_CHARA_ID:
            enARMTrans(scp_d->sc.enemy_p);
            break;
    }

    switch (scp_d->sc.kind) {
        case HLL_JMS_CHARA_ID:
        case LLL_JMS_CHARA_ID:
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
        case HHL_JMS_CHARA_ID:
        case HLL_JMS_CHARA_ID:
        case LLL_JMS_CHARA_ID: {
            weapon = PlayerGetJamesWeapon();
            if (!(scp_wp = shCharacterGetSubCharacter(WEAPON_ID_START + weapon, -1))) break;
            shUpdateWeaponMatrixAfterAnime(scp_wp, scp_d->sc.kind);
            break;
        }

        default:
            break;
    }

    switch (scp_d->sc.kind) {
        case HHH_JMS_CHARA_ID:
        case HHL_JMS_CHARA_ID:
        case HLL_JMS_CHARA_ID:
        case LLL_JMS_CHARA_ID:
            shGetJamesLightPos_Calc();
            shLensFlareExec(&scp_d->sc, 3.0f, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeCopyForReverseModel);

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

            ASSERT_ON_LINE(anim->anim_a != NULL, 2374);

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

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterItemScreenObjectSet);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterStayObjectNthPartsGet1st);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterStayObjectNthPartsSet);

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

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterPlayerModelToDrama);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterPlayerModelToPlayable);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterMariaModelToDrama);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterMariaModelToPlayable);

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
