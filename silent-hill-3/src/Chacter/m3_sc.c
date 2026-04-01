#include "common.h"
#include "Chacter/m3_sc.h"
#include "Chacter/character.h"
#include "Chacter/sh3_character_manage.h"

static SubCharacter* shCharacterGetFreeList() {
    struct SubCharacter * scp = (SubCharacter*) D_003DAD50;
    if (D_003DAD50 != NULL) {
        D_003DAD50 = scp->next;
    }
    return scp;
}

static void AddFreeList(SubCharacter* scp) {
    scp->next = D_003DAD50;
    D_003DAD50 = (SubCharacterDisp*) scp;
}


void shCharacterSortList(SubCharacter* scp) {
    SubCharacter* pre;
    SubCharacter* next;

    if (!(next = D_003DAD54)) {
        D_003DAD54 = scp;
        scp->next = NULL;
        scp->pre = NULL;
        return;
    }



    if (D_003DAD58 != NULL) {
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
            D_003DAD54 = scp;
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
    if (D_003DAD54 != NULL) {
        ((SubCharacter*)D_003DAD54)->pre = scp;
    }
    scp->next = D_003DAD54;
    scp->pre = NULL;
    D_003DAD54 = scp;
}

static void shCharacterCutList(SubCharacter* scp) {
    SubCharacter* pre = scp->pre;
    SubCharacter* next  = scp->next;

    if (pre != NULL) {
        pre->next = next;
        scp->pre = NULL;
    } else {
        D_003DAD54 = next;
    }
    if (next != NULL) {
        next->pre = pre;
        scp->next = NULL;
    }
}



static void shCharacterSetPlayer(SubCharacter *scp)

{
    if (scp == NULL) {
        D_003DAD58 = scp;
        D_003DAD54 = scp;
        return;
    }

    D_003DAD58 = scp;

    shCharacterCutList(scp);
    shCharacterTopOfList(scp);    
                       
    func_001985B0(scp);
    func_001DC610(scp);
}


INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterInitialize);

void func_0012F090(SubCharacter* scp)
{
    u_short kind = scp->kind;

    switch (kind)
    {

        case HEATHER_CHARA_ID:
            shCharacterSetPlayer(scp);
            return;

        case DOUGLAS_CHARA_ID:
        case DOUGLAS_CC_CHARA_ID:
        case DOUGLAS_DD_CHARA_ID:
            func_0024CA90(scp);
            return;

        case CLAUDIA_CHARA_ID:
            func_00241560(scp);
            return;

        case VINCENT_CHARA_ID:
            func_0025D150(scp);
            return;

        case 0x180: /* unknown */
            func_00198DF0(scp);
            return;

        case VALTIEL_CHARA_ID:
            func_002FE1A0(scp);
            return;

        case DOUBLE_HEAD_CHARA_ID:
        case CLOSER_CHARA_ID:
        case NUMB_BODY_CHARA_ID:
        case NURSE_CHARA_ID:
        case INSANE_CANCER_CHARA_ID:
        case PENDULUM_CHARA_ID:
        case SCRAPER_CHARA_ID:
        case SEWER_MONSTER_CHARA_ID:
        case EN_DED1_CHARA_ID:
        case CAROUSEL_HORSE_CHARA_ID:
        case SLURPER_E_CHARA_ID:
        case SLURPER_X_CHARA_ID:
        case 0x20C: /* unknown */
        case MISSIONARY_CHARA_ID:
        case SPLIT_WORM_CHARA_ID:
        case LEONARD_WOLF_CHARA_ID:
        case GOD_CHARA_ID:
        case MEMORY_OF_ALESSA_CHARA_ID:
            func_0022EB70(scp);
            return;


        default:
            break;
    }

    if (kind >> 8 != 0x10) {
        if (kind >> 8 == 7) {
            return;
        }
        switch (kind >> 8)
        {        
            case 4:
                if (kind & 0x80) {
                    func_001430C0(scp);
                    return;
                }
                func_00142EA0(scp);
                return;
    
            case 8:
                if (kind & 0x80) {
                    func_001A8420(scp);
                    return;
                }
                func_001A8330(scp);
                return;
    
            case 9:
                func_001A94D0(scp);
                return;
    
            
            case 3:
            case 5:
                func_00143360(scp);
                return;
        }
    }

    func_00143360(scp);
}


int shCharacter_Manage_Init() {
    id_counter = 0x1000;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacter_Manage_Create);

int shCharacter_Manage_Delete(u_short kind, u_short id) { 
    SubCharacter * del_scp; // r16
    int delete_on = 0; // r7

    del_scp = D_003DAD54;
    while (del_scp != NULL) {
        if (del_scp->kind == kind && del_scp->id == id) {
            delete_on = 1;
            break;
        }
        del_scp = del_scp->next;
    }

    if (delete_on == 0) {
        return 0;
    }

    if (del_scp->kind >> 8 == 2) {
        func_0022EBD0(del_scp, delete_on);
    }

    shCharacterDelete(del_scp);
    func_0025BE20(kind, id);

    return 1;
}

void func_0012F4E0(void) {
    SubCharacter* del_scp;
    int delete_on = 1;

    do {
        del_scp = D_003DAD54;

        while (del_scp) {
            if (del_scp->kind >> 8 == 2) {
                shCharacter_Manage_Delete(del_scp->kind, del_scp->id);
                delete_on = 2;
                break;
            }
            del_scp = del_scp->next;
        }

        if (delete_on == 1) {
            delete_on = 0;
        } else {
            delete_on = 1;
        }

    } while (delete_on != 0);

    func_0022E9D0();
}

SubCharacter* func_0012F570() {
    return D_003DAD54;
}

SubCharacter* func_0012F580() {
    return D_003DAD58;
}

int shCharacter_Manage_SetDataAdresss(SubCharacter* scp) {
    sh3gfw_ModelDraw_MAN* pMD;
	SubCharacterDisp* scp_d = (SubCharacterDisp*)scp;

    if (scp_d == NULL) {
        return 0;
    }

    pMD = sh3gfw_Get_pMD(scp_d->sc.kind);
    if (pMD == NULL) {
        scp_d->models[2] = NULL;
        return 0;
    }

    if (scp_d->model_adr == NULL) {
        func_00140D60(func_001DCAD0((s16) scp->kind));
        SCSetModel(scp_d, (u_long) pMD->sh_Model, (u_long) pMD->pAnime);
        scp_d->model_adr = (u_long) pMD->sh_Model;
        scp_d->anime_adr = (u_long) pMD->pAnime;
        scp_d->clani_adr = (u_long) pMD->pCluster;
        scp_d->clani_adr = 0;
        (scp_d->anime).anime = (void*)((int)scp_d->anime_adr + 4);
        scp_d->models[2] = pMD;
        scp->function(scp);
        if (scp_d->anime_adr != 0) {
            if (scp_d->sc.unk1C0 & 0x2000) {
                func_001DC700(&scp_d->sc, &scp_d->sc.rot, &scp_d->sc.pos);
                func_001DCF10(&scp_d->sc);
            }
        }
    } else {
        scp_d->model_adr = (u_long) pMD->sh_Model;
        scp_d->anime_adr = (u_long) pMD->pAnime;
        scp_d->clani_adr = 0;
        (scp_d->anime).anime = (void*)((int)scp_d->anime_adr + 4);
        scp_d->models[0] = (void*) scp_d->model_adr;
        scp_d->models[1] = (void*) scp_d->model_adr;
        scp_d->models[2] = pMD;
    }

    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacter_Manage_Create_After_MC_Load);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterCreate);

static void shCharacterDelete(SubCharacter* scp) {
    SubCharacterDisp* scp_d = (SubCharacterDisp*) scp;
    if (scp == NULL) {
        return;
    }

    if (scp == D_003DAD58) {
        shCharacterSetPlayer(NULL);
    }

    if (scp_d->model_adr == 0) {
        func_00140D60(func_001DCAD0((short) scp->kind));
    } else {
        func_00140CD0(scp->unk80);
    }

    scp_d->anime.top = NULL;
    scp_d->model_adr = 0;

    func_001C1B80(scp_d->work);
    scp_d->work = NULL;
    ClusterAnimeDelete(scp_d->cluster_anime, scp->index);
    scp_d->cluster_anime = NULL;
    scp_d->clani_adr = 0;
    shCharacterCutList(scp);

    scp->kind = 0;
    scp->id = 0;
    scp->unk12 = -1;
    scp->unk10 = 0;
    scp->unk80 = 0;
    scp->pre = NULL;
    scp->next = NULL;
    scp->function = NULL;
    scp->sk_top = NULL;
    scp->unkA8[0] = 0;
    scp->unkA8[1] = 0;
    scp->unkA8[2] = 0;
    scp->unkC0[2] = 0;

    AddFreeList(scp);
    D_003DAD5C--;
}


INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", func_0012FB00);
