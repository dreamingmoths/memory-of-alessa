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

static void func_0012EE90(SubCharacter* scp) {
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

#define HEATHER_CHARA_ID 0x100
#define DOUGLAS_CHARA_ID 0x101
#define CLAUDIA_CHARA_ID 0x102
#define VINCENT_CHARA_ID 0x103
#define DOUGLAS_CC_CHARA_ID 0x104
#define DOUGLAS_DD_CHARA_ID 0x105
#define DOUBLE_HEAD_CHARA_ID 0x200
#define NUMB_BODY_CHARA_ID 0x201
#define CLOSER_CHARA_ID 0x202
#define NURSE_CHARA_ID 0x203
#define INSANE_CANCER_CHARA_ID 0x204
#define PENDULUM_CHARA_ID 0x205
#define SCRAPER_CHARA_ID 0x206
#define SEWER_MONSTER_CHARA_ID 0x207
#define EN_DED1_CHARA_ID 0x208
#define CAROUSEL_HORSE_CHARA_ID 0x209
#define SLURPER_E_CHARA_ID 0x20a
#define SLURPER_X_CHARA_ID 0x20b
#define SPLIT_WORM_CHARA_ID 0x210
#define MISSIONARY_CHARA_ID 0x211
#define VALTIEL_CHARA_ID 0x212
#define LEONARD_WOLF_CHARA_ID 0x213
#define GOD_CHARA_ID 0x214
#define MEMORY_OF_ALESSA_CHARA_ID 0x215
#ifdef NON_MATCHING
void func_0012F090(SubCharacter* scp)
{
    u16 kind = scp->kind;
    int value;

    switch (kind)
    {
        case GOD_CHARA_ID:
        case SLURPER_E_CHARA_ID:
        case MEMORY_OF_ALESSA_CHARA_ID:
        case LEONARD_WOLF_CHARA_ID:
        case DOUBLE_HEAD_CHARA_ID:
        case CLOSER_CHARA_ID:
        case SLURPER_X_CHARA_ID:
        case MISSIONARY_CHARA_ID:
        case 0x20C: /* unknown */
        case CAROUSEL_HORSE_CHARA_ID:
        case EN_DED1_CHARA_ID:
        case SEWER_MONSTER_CHARA_ID:
        case SCRAPER_CHARA_ID:
        case PENDULUM_CHARA_ID:
        case INSANE_CANCER_CHARA_ID:
        case NURSE_CHARA_ID:
        case NUMB_BODY_CHARA_ID:
        case SPLIT_WORM_CHARA_ID:
            return;


        case CLAUDIA_CHARA_ID:
            func_00241560(CLAUDIA_CHARA_ID);
            return;

        case VINCENT_CHARA_ID:
            func_0025D150(CLAUDIA_CHARA_ID);
            return;

        case 0x180: /* unknown */
            func_00198DF0(0x180);
            return;

        case VALTIEL_CHARA_ID:
            func_002FE1A0(0x180);
            return;

        default:
            func_0022EB70(scp);
            break;
    }

    if (kind == HEATHER_CHARA_ID) {
        shCharacterSetPlayer(scp);
        return;
    }

    if (kind == DOUGLAS_CC_CHARA_ID ||
        kind == DOUGLAS_DD_CHARA_ID ||
        kind == DOUGLAS_CHARA_ID
    )
    {
        func_0024CA90();
        return;
    }


    value = (int)kind >> 8;

    switch (value)
    {
        case 4:
            if (kind & 0x80)
                func_001430C0(7, value);
            else
                func_00142EA0(7, value);
            return;

        case 8:
            if (kind & 0x80)
                func_001A8420(7, value);
            else
                func_001A8330(7, value);
            return;

        case 9:
            func_001A94D0(7, value);
            return;

        case 5:
        case 3:
        default:
            func_00143360(7, value);
            return;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", func_0012F090);
#endif


int shCharacter_Manage_Init() {
    id_counter = 0x1000;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacter_Manage_Create);

int shCharacter_Manage_Delete(u16 kind, u16 id) { 
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
        SCSetModel(scp_d, (u64) pMD->sh_Model, (u64) pMD->pAnime);
        scp_d->model_adr = (u64) pMD->sh_Model;
        scp_d->anime_adr = (u64) pMD->pAnime;
        scp_d->clani_adr = (u64) pMD->pCluster;
        scp_d->clani_adr = 0;
        (scp_d->anime).anime = (void*)((int)scp_d->anime_adr + 4);
        scp_d->models[2] = pMD;
        scp->function(scp);
        if (scp_d->anime_adr != 0) {
            if ((int) scp_d->sc.unk_1c4 & 0x2000) {
                func_001DC700(&scp_d->sc, &scp_d->sc.rot, &scp_d->sc.pos);
                func_001DCF10(&scp_d->sc);
            }
        }
    } else {
        scp_d->model_adr = (u64) pMD->sh_Model;
        scp_d->anime_adr = (u64) pMD->pAnime;
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
        shCharacterSetPlayer(0);
    }
    if (scp_d->model_adr == 0) {
        func_00140D60(func_001DCAD0((s16) scp->kind));
    } else {
        func_00140CD0(scp->unk);
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
    scp->unk = 0;
    scp->pre = NULL;
    scp->next = NULL;
    scp->function = NULL;
    scp->sk_top = NULL;
    scp->eye_y = 0.0f;
    scp->center_y = 0.0f;
    scp->spd = 0.0f;
    scp->grnd_normal[2] = 0.0f;
    func_0012EE90(scp);
    D_003DAD5C -= 1;
}


INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", func_0012FB00);
