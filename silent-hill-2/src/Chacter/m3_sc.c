#include "Chacter/character.h"
#include "m3_sc.h"

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

static void AddFreeList(SubCharacter* scp) {
    scp->next = &sh2chara.free->sc;
    sh2chara.free = (SubCharacterDisp*) scp;
}


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

void shCharacterSortList(SubCharacter* scp) {
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

void shCharacterSetHandler(SubCharacter* scp) {
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
