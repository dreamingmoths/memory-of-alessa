#include "common.h"
#include "Chacter/m3_sc.h"
#include "Chacter/character.h"
#include "Chacter/sh3_character_manage.h"

extern shCharacterAll sh3chara;

/* not from here */
extern int shCharacterGetSkeltonNum(short kind);

static SubCharacter* shCharacterGetFreeList(void) {
    struct SubCharacter * scp = sh3chara.free;
    if (sh3chara.free != NULL) {
        sh3chara.free = scp->next;
    }
    return scp;
}

static void AddFreeList(SubCharacter* scp) {
    scp->next = sh3chara.free;
    sh3chara.free = scp;
}


void shCharacterSortList(SubCharacter* scp) {
    SubCharacter* pre;
    SubCharacter* next;

    if (!(next = sh3chara.head)) {
        sh3chara.head = scp;
        scp->next = NULL;
        scp->pre = NULL;
        return;
    }



    if (sh3chara.player != NULL) {
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
            sh3chara.head = scp;
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
    if (sh3chara.head != NULL) {
        ((SubCharacter*)sh3chara.head)->pre = scp;
    }
    scp->next = sh3chara.head;
    scp->pre = NULL;
    sh3chara.head = scp;
}

static void shCharacterCutList(SubCharacter* scp) {
    SubCharacter* pre = scp->pre;
    SubCharacter* next  = scp->next;

    if (pre != NULL) {
        pre->next = next;
        scp->pre = NULL;
    } else {
        sh3chara.head = next;
    }
    if (next != NULL) {
        next->pre = pre;
        scp->next = NULL;
    }
}



static void shCharacterSetPlayer(SubCharacter *scp)

{
    if (scp == NULL) {
        sh3chara.player = scp;
        sh3chara.head = scp;
        return;
    }

    sh3chara.player = scp;

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

int shCharacter_Manage_Create(CharaOptions* options) {
    SubCharacter* scp = shCharacterCreate(options);
    u_short id;

    if (scp != NULL) { 
        func_00140D40(shCharacterGetSkeltonNum(scp->kind));

        vec_copy(&scp->pos, &options->pos_10);
        vec_copy(&scp->unkF0, &options->pos_10);
        vec_copy(&scp->unkD0, &options->pos_10);
        vec_copy(&scp->rot, &options->rot_20);
        vec_copy(&scp->unkE0, &options->rot_20);
        scp->battle.status |= 0x2000;

        if (options->id != 0xffff) {
            scp->id = options->id;
        } else {
            scp->id = id_counter;
            printf("id %d\n", id_counter);
            id_counter++;
            if (id_counter == 0x7FFF) {
                id_counter = 0x1000;
            }
        }

        func_001DC9E0(scp, 1);
        func_0025BE90(scp->kind, scp->id);

        return scp->id;
    }

    return -1;
}

int shCharacter_Manage_Delete(u_short kind, u_short id) { 
    SubCharacter * del_scp;
    int delete_on = 0;

    del_scp = sh3chara.head;
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

void shCharacter_0x0012f4e0(void) {
    SubCharacter* del_scp;
    int delete_on = 1;

    do {
        del_scp = sh3chara.head;

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

SubCharacter* shCharacter_Manage_GetCharacterList() {
    return sh3chara.head;
}

SubCharacter* shCharacterGetPlayer() {
    return sh3chara.player;
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
        func_00140D60(shCharacterGetSkeltonNum((short) scp->kind));
        SCSetModel(scp_d, (u_long) pMD->sh_Model, (u_long) pMD->pAnime);
        scp_d->model_adr = (u_long) pMD->sh_Model;
        scp_d->anime_adr = (u_long) pMD->pAnime;
        scp_d->clani_adr = (u_long) pMD->pCluster;
        scp_d->clani_adr = 0;
        (scp_d->anime).anime = (void*)((int)scp_d->anime_adr + 4);
        scp_d->models[2] = pMD;
        scp->function(scp);
        if (scp_d->anime_adr != 0) {
            if (scp_d->sc.battle.status & 0x2000) {
                func_001DC700(&scp_d->sc, &scp_d->sc.rot, &scp_d->sc.pos);
                shCharacterExecAnimeOne(&scp_d->sc);
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

    if (scp == sh3chara.player) {
        shCharacterSetPlayer(NULL);
    }

    if (scp_d->model_adr == 0) {
        func_00140D60(shCharacterGetSkeltonNum(scp->kind));
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
    sh3chara.total--;
}


void shCharacterInitSubCharacter(void) {
    int i; // r5
    SubCharacterDisp* scp_d; // r4

    
    memset(&sh3chara, 0, sizeof(shCharacterAll));
    
    scp_d = &sh3chara.work[0];
    sh3chara.free = sh3chara.work;



    
    for (i = 0; i < 31; i++, scp_d++) {
        scp_d->sc.next = (SubCharacter *)(scp_d + 1);
    }
    scp_d->sc.next = NULL;



    
    for (i = 0; i < 32; i++) {
        sh3chara.work[i].sc.index = i;
    }
}


INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", SCSetModel);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", func_0012FC80);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shBattleAroundTargetEnemy);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterGetRemainingFreeSlots);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", shCharacterGetSubCharacter);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", func_0012FE20);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", func_0012FE30);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", func_001300C0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", func_001300F0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc", func_001301B0);

