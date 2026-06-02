#include "Chacter/m3_sc.h"
#include "Chacter/m3_play.h"

static void AddFreeList(SubCharacter* scp);
static void shCharacterSortList(SubCharacter* scp /* r2 */);

static void shCharacterCutList(SubCharacter* scp);

static void shCharacterSetHandler(SubCharacter* scp /* r16 */);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterGetFreeList);

static void AddFreeList(SubCharacter* scp) {
    scp->next = &sh2chara.free->sc;
    sh2chara.free = (SubCharacterDisp*) scp;
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

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterTopOfList);

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

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterNeckAngleExec);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterKneeAngleExec);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", SCAddPos);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", SCSetRot);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", SCAddRot);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterSetClusterAnimeWork);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterClusterAnimeSet);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", SCSetModel);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterGetAnimeAdrForDrama);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterGetAnimeAdrForPlay);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterGetClusterAnimeAdr);

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

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterGetModelID);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterGetSubCharacter);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterGetSkeltonNum);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeOneFrameSize);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterInitSubCharacter);

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

void shCharacterDelete(SubCharacter* scp) {
    SubCharacterDisp* scp_d = (SubCharacterDisp*) scp;
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

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterPlayingExecAnimeOne);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterDramaExecAnimeOne);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeCopyForReverseModel);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", SCNowDemoEventSwitch);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", SCNowPlayableEventSwitch);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", SCStayModelSwitch);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", SCAnimeTypeSwitch);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", SCRotZYXSwitch);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", SCFreefallSwitch);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", SCLightOnNowSwitch);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterExecAnimeAll);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterUpdateAll);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterSetFunction);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterExecFunctionAll);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeSet);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterStayObjectScaleSet);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterItemScreenObjectSet);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterStayObjectNthPartsGet1st);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterStayObjectNthPartsSet);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeSpeedGet_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeSpeedAdd);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeSpeedAdd_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeSpeedAddY);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeSpeedAddY_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimePause);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimePause_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeRestart);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeRestart_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeIsEnd);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeIsEnd_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeFrameGet);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeFrameGet_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeFrameSet);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeFrameSet_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeCounterGet);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeCounterGet_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeCounterSet_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeGetInfo);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterAnimeGetInfo_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterPlayerModelToDrama);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterPlayerModelToPlayable);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterMariaModelToDrama);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterMariaModelToPlayable);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterSetPosAfterDemo);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterGetPartsMatrixForShadow);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterGetGroundInfoForShadow);
