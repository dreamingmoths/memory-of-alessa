#include "sh2_common.h"

#include "Chacter/character.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"
#include "Chacter_Draw/model3_n.h"

#include "Event/chara_data_load.h"

#include "GFW/sh2gfw_structs.h"
#include "GFW/sh2gfw_alltexman.h"
#include "GFW/sh2gfw_Texpacket.h"
#include "GFW/sh2gfw_Init_ModelDrawData.h"

#include "data/fs_structs.h"
#include "data/daily.thu/data_chr_jms.h"

#define SH2_MODEL_DRAWWORK_COUNT 48
#define MODEL_ID 0xFFFF0003
#define MWORK_ID 0xFFFE0003

static int Delete_Model(void* modeldw);
static int Check_RevChara(int id);
static void init_CharaTex(sh2gfw_ALLTEXSYNC_MAN* pATSM, sh2gfw_ModelDraw_MAN* pMD);
static void init_ReverseCharaTex(sh2gfw_ALLTEXSYNC_MAN* pATSM, sh2gfw_ModelDraw_MAN* pMD);
static int Init_WithoutCharaTex(sh2gfw_ALLTEXSYNC_MAN* pATSM, sh2gfw_ModelDraw_MAN* pMD);

extern chr_mge_files Character_Mge_files[21]; // size: 0x1A4, address: 0x0
extern chr_mge_files hhh_jms_TGS_turi; // size: 0x14, address: 0x0
extern sh2gfw_AllModelData_Man All_MDW; // size: 0x308, address: 0x616AD0

extern sh2gfw_ModelDraw_MAN ModelDW_Man[SH2_MODEL_DRAWWORK_COUNT]; // size: 0x1BC0, address: 0x616EA0

extern /* static */ int MDL_iniflg; // size: 0x4, address: 0x616AC0

extern sh2gfw_LoadModel_MEMMAN LoadModel_MemMan; // size: 0x18, address: 0x616DE0

extern fsFileIndex data_chr_scu_scu_anm[1]; // size: 0x8, address: 0x3A1060
extern fsFileIndex data_chr_scu_scu_mdl[1]; // size: 0x8, address: 0x3A1070
extern fsFileIndex data_chr_mkn_mkn_anm[1]; // size: 0x8, address: 0x3A0FD8
extern fsFileIndex data_chr_mkn_mkn_mdl[1]; // size: 0x8, address: 0x3A0FE8

extern Q_WORDDATA ANIME_DATA[1024]; // size: 0x4000, address: 0x618A80
extern sh2gfw_ModelDraw_MAN UniModelDW_Man; // size: 0x94, address: 0x616E00

void sh2gfw_srInit_ModelDrawWork(void) {
    int i; // r16

    for (i = 0; i < 32; i++) {
        memset(&ModelDW_Man[i], 0, sizeof(ModelDW_Man[i]));
    }
    
    memset(&All_MDW, 0, sizeof(All_MDW));
}

sh2gfw_ModelDraw_MAN* sh2gfw_Get_pMD(int chara_id /* r2 */) {
    int i; // r5
    int kind; // r2
    int id; // r2
    int cid; // r2

    for (i = 0; i < SH2_MODEL_DRAWWORK_COUNT; i++)
        if (chara_id == ModelDW_Man[i].chara_id)
            return &ModelDW_Man[i];

    return NULL;
}


int sh2gfw_Check_ModelIsOnMemory(int cid /* r16 */) {
    sh2gfw_ModelDraw_MAN* pMD; // r2
    sh2gfw_Model_Header* sMH; // r2
    sh_Model* pModel; // r2

    pMD = sh2gfw_Get_pMD(cid);
    if (pMD == NULL) {
        return 0;
    }
    sMH = (sh2gfw_Model_Header*) pMD->Model_Head;
    if (sMH == NULL) {
        return 0;
    }
    if (sMH->chara_id != cid) {
        return 0;
    }
    pModel = (u_char*) sMH + sMH->toModel_offset;
    if ((pModel->id != 0xFFFF0003) && (pModel->id != 0xFFFE0003)) {
        return 0;
    }
    return 1;
}

int sh2gfw_LoadInit_CharaModelData() {

}

int sh2gfw_LoadMemorySet_CharaModelData(chr_mge_files* cdl /* r2 */, u_long128** ModelMemBuffer /* r2 */, u_long128** AnimeMemBuffer /* r2 */, u_long128** ClusterMemBuffer /* r2 */, u_long128** Kg1MemBuffer /* r2 */) {
    int i; // r3
    int k; // r9
    u_long128* modelbuf; // r5
    u_long128* animebuf; // r6
    u_long128* clusterbuf; // r7
    u_long128* kg1buf; // r8
    sh2gfw_ModelDraw_MAN* pMD2; // r10
    chr_mge_files* cdlist2; // r2

    k = -1;
    modelbuf = *ModelMemBuffer;
    animebuf = *AnimeMemBuffer;
    clusterbuf = *ClusterMemBuffer;
    kg1buf = *Kg1MemBuffer;
    for (i = 0; i < SH2_MODEL_DRAWWORK_COUNT; i++) {
        if ((ModelDW_Man[i].chara_id == 0) && (k == -1)) {
            k = i;
        }
        if ((cdl->mid >= WEAPON_ID_START) && (cdl->mid < MIRROR_KIND(WEAPON_ID_START))) {
            if (ModelDW_Man[i].chara_id < WEAPON_ID_START || ModelDW_Man[i].chara_id >= MIRROR_KIND(WEAPON_ID_START))
                continue;
        } else if ((cdl->mid >= MIRROR_KIND(WEAPON_ID_START)) && (cdl->mid <= MIRROR_KIND(WEAPON_ID_END))) {
            if (ModelDW_Man[i].chara_id < MIRROR_KIND(WEAPON_ID_START) || MIRROR_KIND(WEAPON_ID_END + 1) <= ModelDW_Man[i].chara_id)
                continue;
        } else if (cdl->mid != ModelDW_Man[i].chara_id) {
            continue;
        }
        break;
    }
    if (i == SH2_MODEL_DRAWWORK_COUNT) {
        if (k == -1) {
            return -1;
        }
        i = k;
    }
    pMD2 = &ModelDW_Man[i];
    All_MDW.file_struct[All_MDW.n_load_character] = cdl;
    All_MDW.pMDM[All_MDW.n_load_character] = pMD2;
    pMD2->chara_id = (u32) cdl->mid;
    if (cdl->model_fid != NULL) {
        ASSERT_ON_LINE(modelbuf!=NULL, 716);
        pMD2->Model_Head = modelbuf;
        pMD2->pModel_Header = pMD2->Model_Head;
    } else {
        pMD2->Model_Head = modelbuf;
        pMD2->pModel_Header = pMD2->Model_Head;
    }
    if (cdl->anime_fid != NULL) {
        ASSERT_ON_LINE(animebuf!=NULL, 729);
        pMD2->pAnime = animebuf;
    } else
        pMD2->pAnime = animebuf;

    if (cdl->cluster_fid != NULL) {
        ASSERT_ON_LINE(clusterbuf!=NULL, 745);
        pMD2->pCluster = clusterbuf;

    } else
        pMD2->pCluster = clusterbuf;

    if (cdl->shadow_fid != NULL) {
        ASSERT_ON_LINE(kg1buf!=NULL, 756);
        pMD2->pKg1Work = kg1buf;
    } else
        pMD2->pKg1Work = kg1buf;

    All_MDW.n_load_character++;
    // @bug forgor to return anything?
}

int sh2gfw_LOAD_CharaModelData(void) {
    int i; // r16
    chr_mge_files* cdlist3; // r17
    sh2gfw_ModelDraw_MAN* pMD3; // r18

    for (i = 0; i < All_MDW.n_load_character; i++) {
        cdlist3 = All_MDW.file_struct[i];
        pMD3 = All_MDW.pMDM[i];
        if (cdlist3->model_fid != NULL) {
            All_MDW.fid_model[i] = FcRead(cdlist3->model_fid, pMD3->Model_Head);
        } else {
            All_MDW.fid_model[i] = -1;
        }
        if (cdlist3->anime_fid != NULL) {
            All_MDW.fid_anim[i] = FcRead(cdlist3->anime_fid, pMD3->pAnime);
        } else {
            All_MDW.fid_anim[i] = -1;
        }
        if (cdlist3->cluster_fid != NULL) {
            All_MDW.fid_clus[i] = FcRead(cdlist3->cluster_fid , pMD3->pCluster);
        } else {
            All_MDW.fid_clus[i] = -1;
        }
        if (cdlist3->shadow_fid != NULL) {
            All_MDW.fid_kg1[i] = FcRead(cdlist3->shadow_fid, pMD3->pKg1Work);
        } else {
            All_MDW.fid_kg1[i] = -1;
        }
    }
}

void sh2gfw_SyncInit_ChacterModelData(void) {
    int i; // r16
    int dac; // r17
    int imdl2; // r2
    int ianm2; // r2
    int iclus2; // r2
    int ikg12; // r2
    chr_mge_files* cdlist; // r2
    sh2gfw_ModelDraw_MAN* pMD4; // r18

    dac = 0;
    for (i = 0; i < All_MDW.n_load_character; i++) {
        pMD4 = All_MDW.pMDM[i];
        imdl2 = All_MDW.fid_model[i];
        if (imdl2 != -1) {
            fsSync(0, imdl2);
            pMD4->sh_Model = (u_char*) pMD4->pModel_Header + ((sh2gfw_Model_Header*) pMD4->pModel_Header)->toModel_offset;
            pMD4->chara_id = ((sh2gfw_Model_Header*) pMD4->pModel_Header)->chara_id;
            sh2gfw_init_CharaModel_TextureData(pMD4);
            dac++;
        } else if (pMD4->Model_Head != NULL) {
            pMD4->pModel_Header = pMD4->pModel_Header;
            pMD4->sh_Model = (u_char*) pMD4->pModel_Header + ((sh2gfw_Model_Header*) pMD4->pModel_Header)->toModel_offset;
            pMD4->chara_id = ((sh2gfw_Model_Header*) pMD4->pModel_Header)->chara_id;
            sh2gfw_init_CharaModel_TextureData(pMD4);
        }
        ianm2 = All_MDW.fid_anim[i];
        if (ianm2 != -1) {
            if (pMD4->chara_id == WEAPON_ID_START) {
                dac++;
            }
            fsSync(0, ianm2);
        }
        iclus2 = All_MDW.fid_clus[i];
        if (iclus2 != -1) {
            fsSync(0, iclus2);
        }
        ikg12 = All_MDW.fid_kg1[i];
        if (ikg12 != -1) {
            fsSync(0, ikg12);
        }
    }
    All_MDW.n_load_character = 0;
    All_MDW.n_active_character += dac;
    if (All_MDW.n_active_character > SH2_MODEL_DRAWWORK_COUNT) {
        All_MDW.n_active_character = SH2_MODEL_DRAWWORK_COUNT;
    }
    if (MDL_iniflg == 0) {
        ModelInit();
        MDL_iniflg ^= 1;
    }
}

int sh2gfw_Cancel_LOADCharaModelData(void) {
    int i; // r2

    for (i = 0; i < All_MDW.n_load_character; i++) {
        ASSERT_ON_LINE(All_MDW.pMDM[i]->chara_id!=0, 935);
        All_MDW.pMDM[i]->chara_id = 0;
    }

    All_MDW.n_load_character = 0;
    return i;
}

void sh2gfw_ModelDrawInit_for_BackgroundLoad(int chara_id /* r21 */, void* memhead_model /* r20 */, void* memhead_anime /* r19 */, void* memhead_cluster /* r18 */, void* memhead_kg1 /* r17 */) {
    int i; // r16
    int ze; // r5
    sh2gfw_ModelDraw_MAN* pMD; // r2

    ze = -1;
    for (i = 0; i < SH2_MODEL_DRAWWORK_COUNT; i++) {
        pMD = &ModelDW_Man[i];
        if (chara_id == pMD->chara_id) {
            Delete_Model(pMD);
            ze = i;
        } else {
            if ((ze == -1) && (pMD->chara_id == 0)) {
                ze = i;
            }
            continue;
        }
        break;
    }
    ASSERT_ON_LINE(ze!=-1, 1044);
    pMD = &ModelDW_Man[ze];
    pMD->chara_id = chara_id;
    pMD->Model_Head = memhead_model;
    pMD->pModel_Header = memhead_model;
    pMD->sh_Model = (u_char*) pMD->pModel_Header + ((sh2gfw_Model_Header*) pMD->pModel_Header)->toModel_offset;
    pMD->pAnime = memhead_anime;
    pMD->pCluster = memhead_cluster;
    pMD->pKg1Work = memhead_kg1;
    sh2gfw_init_CharaModel_TextureData(pMD);
}

void* sh2gfw_CreateSubCharacter(int chara_id /* r17 */) {
    sh2gfw_ModelDraw_MAN* pMD; // r16
    SubCharacter* pSubc; // r17

    pMD = sh2gfw_Get_pMD(chara_id);
    if (pMD == NULL) {
        return NULL;
    }
    pSubc = shCharacterCreate(0, (int) pMD->sh_Model, (int) pMD->pAnime, (int) pMD->pCluster, chara_id);
    SCSetModel(pSubc, (int) pMD->sh_Model, (int) pMD->pAnime);
    return pSubc;
}


// @hack for string deduplication until Init_WithoutCharaTex is matched
const char rodata_zero_0x0038F340[];
#define ASSERT_ZERO_ON_LINE(line) \
do { \
    if (!(0)) { \
        printf(__FILE__ ":" #line "> assert:(%s)\n", rodata_zero_0x0038F340); \
        do {} while (1); \
    } \
} while (0)

static int Delete_Model(void* modeldw /* r2 */) {
    sh2gfw_ModelDraw_MAN* pMD; // r16
    int i; // r17
    int ret; // r2

    pMD = modeldw;
    ASSERT_ON_LINE(pMD->chara_id!=0, 1123);
    ret = pMD->chara_id;
    pMD->chara_id = 0;
    for (i = 0; i < pMD->TB_change_VU1num + pMD->TB_change_VU0num; i++) {
        if (sh2gfw_del_TexMAN(&AllTexSync_Man, pMD->pTexMAN[i]) == NULL) {
            ASSERT_ZERO_ON_LINE(1142);
        }
    }
    return ret;
}

// see @hack above
const char rodata_zero_0x0038F340[] = "0";

int sh2gfw_Delete_Model_from_CharaID(int chara_id /* r2 */) {
    sh2gfw_ModelDraw_MAN* pMD; // r2
    pMD = sh2gfw_Get_pMD(chara_id);
    if ((pMD == NULL) || (pMD->sh_Model == NULL)) {
        return -1;
    }
    return Delete_Model(pMD);
}

void sh2gfw_kari_clear_LM(void) {
    LoadModel_MemMan.index_model = 0;
    LoadModel_MemMan.pLM_head = CHRDATA;
    LoadModel_MemMan.index_anime = 0;
    LoadModel_MemMan.pLA_head = &ANIME_DATA->ul128;
}

static int Check_RevChara(int id /* r2 */) {
    if (id <= MIRROR_KIND(HUMAN_CHARA_KIND_END)) {
        return 1;
    }
    if ((id - ITEM_RI_KNIFE_CHARA_KIND) < 2u) {
        return 1;
    }
    if ((id >= WEAPON_ID_START) && (id <= MIRROR_KIND(WEAPON_ID_END))) {
        return 1;
    }
    return 0;

}

void sh2gfw_init_CharaModel_TextureData(sh2gfw_ModelDraw_MAN* pMD /* r16 */) {
    sh2gfw_Model_Header* smh; // r3

    smh = pMD->Model_Head;
    if (smh->NoTextureID != 0) {
        printf("NoTex Character\n");
        Init_WithoutCharaTex(&AllTexSync_Man, pMD);
        return;
    }

    if (Check_RevChara(smh->chara_id) == 0) {
        init_CharaTex(&AllTexSync_Man, pMD);
        return;
    }
    if (smh->chara_id & MIRROR_MODE_CHARA_KIND_FLAG) {
        printf("Mirror Character!\n");
        init_ReverseCharaTex(&AllTexSync_Man, pMD);
        return;
    }
    init_CharaTex(&AllTexSync_Man, pMD);
}

static void init_CharaTex(sh2gfw_ALLTEXSYNC_MAN* pATSM /* r21 */, sh2gfw_ModelDraw_MAN* pMD /* r20 */) {
    sh_Model* pModel; // r16
    sh2gfw_TEX_HEAD* pTH; // r2
    sh2gfw_CLUTS_HEAD* pCH; // r2
    sh2gfw_Model_Header* sMH; // r17
    int i, j; // r2, r3

    sMH = pMD->Model_Head;
    
    pModel = (u_char*) sMH + sMH->toModel_offset;
    
    ASSERT_ON_LINE((pModel->id==MODEL_ID)||(pModel->id==MWORK_ID), 1463);
    
    for (i = 0; i < sMH->texnum; i++) {
        pTH = (u_char*) sMH + ((u_int*) (sMH + 1))[i]; // unclear if there's a struct for this?
        pCH = (u_char*) sMH + ((u_int*) (sMH + 1))[i + sMH->texnum]; // but these ints are between the model header and the pModel

        for (j = pCH->clutamount; j != 0; j--) {
            if (pCH->fmt[j + 15] != 0) break;
        }
        
        
        
        
        
        sMH->pTexMAN[i] = sh2gfw_set_TexToTrasMan(pATSM, pTH, pCH, sMH, sMH->chara_id);




        
        pModel->pTexMAN[i] = sMH->pTexMAN[i];
        
        pMD->pTexMAN[i] = sMH->pTexMAN[i];
    
    
    }






    
    pMD->TB_change_VU1num = 0;
    pMD->TB_change_VU1now = 0;
    pMD->TB_change_VU0num = 0;
    pMD->TB_change_VU0now = 0;
    
    if (sMH->texnum > 1) {
        int mode; // r2
        TextPos* pTP; // r7
        short* pitex; // r8
        int texblk_index; // r7
        int n_parts = pModel->n_vu1_parts; // r3
        Part* part = (u_char*) pModel + pModel->vu1_parts_offset; // r2
        Part* parts_top = part; // r4
        int buff = 0xFFFF; // r5





        

        for (i = 0; i < n_parts; i++, part = (u_char*) part + part->size) {
            
            pitex = (u_char*) part + part->text_pos_indices_offset;
            pTP = (u_char*) pModel + pModel->text_poses_offset;
            texblk_index = pTP[pitex[0]].block_index;
            
            if (texblk_index == buff) continue;
            
            pMD->TB_change_VU1[pMD->TB_change_VU1num] = i;
            pMD->TB_index_VU1[pMD->TB_change_VU1num++] = texblk_index;
            buff = texblk_index;
        
        
        }
        
        
        pMD->TB_change_VU1[pMD->TB_change_VU1num] = n_parts;
        pMD->TB_index_VU1[pMD->TB_change_VU1num] = 0xFFFF;
        
        
        if (sMH->texnum > pMD->TB_change_VU1num) {
            
            n_parts = pModel->n_vu0_parts;
            parts_top = part = (u_char*) pModel + pModel->vu0_parts_offset;
            
            for (i = 0; i < n_parts; i++, part = (u_char*) part + part->size) {
                
                pitex = (u_char*) part + part->text_pos_indices_offset;
                pTP = (u_char*) pModel + pModel->text_poses_offset;
                texblk_index = pTP[pitex[0]].block_index;
                if (texblk_index == buff) continue;
                
                pMD->TB_change_VU0[pMD->TB_change_VU0num] = i;
                pMD->TB_index_VU0[pMD->TB_change_VU0num++] = texblk_index;
                buff = texblk_index;
            
            }
        
        }
        
        
        pMD->TB_change_VU0[pMD->TB_change_VU0num] = n_parts;
        pMD->TB_index_VU0[pMD->TB_change_VU0num] = 0xFFFF;
        
        return;
    }
    pMD->TB_change_VU1[pMD->TB_change_VU1num++] = 0;
    pMD->TB_change_VU1[pMD->TB_change_VU1num] = pModel->n_vu1_parts;








}

static void init_ReverseCharaTex(sh2gfw_ALLTEXSYNC_MAN* pATSM /* r22 */, sh2gfw_ModelDraw_MAN* pMD /* r16 */) {
    sh_Model* pModel; // r17
    sh2gfw_TEX_HEAD* pTH; // r2
    sh2gfw_CLUTS_HEAD* pCH; // r2
    sh2gfw_Model_Header* sMH, *Real_sMH; // r18, r19
    sh2gfw_ModelDraw_MAN* Real_pMD; // r2
    int i, real; // r2

    sMH = pMD->Model_Head;
    pModel = (u_char*) sMH + sMH->toModel_offset;
    
    ASSERT_ON_LINE((pModel->id==MODEL_ID)||(pModel->id==MWORK_ID), 1930);

    
    real = sMH->chara_id & ~MIRROR_MODE_CHARA_KIND_FLAG;
    Real_pMD = sh2gfw_Get_pMD(real);
    ASSERT_ON_LINE(Real_pMD!=NULL, 1935);
    Real_sMH = Real_pMD->Model_Head;
    
    for (i = 0; i < sMH->texnum; i++) {
        
        pTH = (u_char*) Real_sMH + ((u_int*) (Real_sMH + 1))[i]; // unclear if there's a struct for this?
        pCH = (u_char*) Real_sMH + ((u_int*) (Real_sMH + 1))[i + Real_sMH->texnum]; // but these ints are between the model header and the pModel

        
        sMH->pTexMAN[i] = sh2gfw_set_TexToTrasMan(pATSM, pTH, pCH, sMH, sMH->chara_id);




        pModel->pTexMAN[i] = sMH->pTexMAN[i];
        
        pMD->pTexMAN[i] = sMH->pTexMAN[i];
    }






    
    pMD->TB_change_VU1num = 0;
    pMD->TB_change_VU1now = 0;
    pMD->TB_change_VU0num = 0;
    pMD->TB_change_VU0now = 0;
    
    if (sMH->texnum > 1) {
        TextPos* pTP; // r7
        short* pitex; // r8
        int texblk_index; // r7
        int n_parts = pModel->n_vu1_parts; // r3
        Part* part = (u_char*) pModel + pModel->vu1_parts_offset; // r2
        Part* parts_top = part; // r4
        int buff = 0xFFFF; // r5





        

        for (i = 0; i < n_parts; i++, part = (u_char*) part + part->size) {
            
            pitex = (u_char*) part + part->text_pos_indices_offset;
            pTP = (u_char*) pModel + pModel->text_poses_offset;
            texblk_index = pTP[pitex[0]].block_index;
            
            if (texblk_index == buff) continue;
            
            pMD->TB_change_VU1[pMD->TB_change_VU1num] = i;
            pMD->TB_index_VU1[pMD->TB_change_VU1num++] = texblk_index;
            buff = texblk_index;
        
        
        }
        
        
        pMD->TB_change_VU1[pMD->TB_change_VU1num] = n_parts;
        pMD->TB_index_VU1[pMD->TB_change_VU1num] = 0xFFFF;
        
        
        if (sMH->texnum > pMD->TB_change_VU1num) {
            
            n_parts = pModel->n_vu0_parts;
            parts_top = part = (u_char*) pModel + pModel->vu0_parts_offset;
            
            for (i = 0; i < n_parts; i++, part = (u_char*) part + part->size) {
                
                pitex = (u_char*) part + part->text_pos_indices_offset;
                pTP = (u_char*) pModel + pModel->text_poses_offset;
                texblk_index = pTP[pitex[0]].block_index;
                if (texblk_index == buff) continue;
                
                pMD->TB_change_VU0[pMD->TB_change_VU0num] = i;
                pMD->TB_index_VU0[pMD->TB_change_VU0num++] = texblk_index;
                buff = texblk_index;
            
            }
        
        }
        
        
        pMD->TB_change_VU0[pMD->TB_change_VU0num] = n_parts;
        pMD->TB_index_VU0[pMD->TB_change_VU0num] = 0xFFFF;

        return;
    }
    pMD->TB_change_VU1[pMD->TB_change_VU1num++] = 0;
    pMD->TB_change_VU1[pMD->TB_change_VU1num] = pModel->n_vu1_parts;
}

#ifdef NON_MATCHING
static int Init_WithoutCharaTex(sh2gfw_ALLTEXSYNC_MAN* pATSM /* r19 */, sh2gfw_ModelDraw_MAN* pMD /* r18 */) {
    int chara[2]; // r29+0x88
    int cid, i; // r20, r2
    sh_Model* pModel; // r21
    sh2gfw_ModelDraw_MAN* TexPmd = NULL; // r2
    sh2gfw_Model_Header* sMH; // r2
    sh2gfw_Model_Header* Real_sMH; // r2
    sh2gfw_TEX_HEAD* pTH; // r2
    sh2gfw_CLUTS_HEAD* pCH; // r2
    int difpth; // r2
    int difpch;
    sMH = pMD->Model_Head;
    pModel = (u_char*) sMH + sMH->toModel_offset;

    
    switch (sMH->chara_id) {                              /* irregular */
        case HHL_JMS_CHARA_KIND:
        case HHH_JMS_CHARA_KIND:
            cid = 2;
            chara[0] = LLL_JMS_CHARA_KIND;
            chara[1] = HLL_JMS_CHARA_KIND;
            break;
        case RHLL_JMS_CHARA_KIND:
        case RHHL_JMS_CHARA_KIND:
        case RHHH_JMS_CHARA_KIND:
            cid = 2;
            chara[0] = LLL_JMS_CHARA_KIND;
            chara[1] = HLL_JMS_CHARA_KIND;
            break;
        case HHH_MAR_CHARA_KIND:
            cid = 1;
            chara[0] = LLL_MAR_CHARA_KIND;
            break;
        case RAGL_CHARA_KIND:
            cid = 1;
            chara[0] = AGL_CHARA_KIND;
            break;
        case HHH_EDI_CHARA_KIND:
            cid = 1;
            chara[0] = EN_LLL_EDI_CHARA_KIND;
            break;
        case EN_LLL_EDI_CHARA_KIND:
            cid = 1;
            chara[0] = HHH_EDI_CHARA_KIND;
            break;
        
        case ITEM_RI_KNIFE_CHARA_KIND:   
        case ITEM_RI_PHOTO_CHARA_KIND:
        case MIRROR_KIND(WEAPON_ID_START):
        case RWEAPON_HANDGUN_CHARA_KIND:
        case RWEAPON_SHOTGUN_CHARA_KIND:
        case RWEAPON_RIFLGUN_CHARA_KIND:
        case RWEAPON_SP_CHARA_KIND:
        case RWEAPON_KAKUZAI_CHARA_KIND:
        case RWEAPON_PIPE_CHARA_KIND:
        case RWEAPON_CSAW_CHARA_KIND:
        case RWEAPON_NATA_CHARA_KIND:
        case RWEAPON_COLT_NOTEX_CHARA_KIND:
            cid = 1;
            chara[0] = sMH->chara_id - MIRROR_MODE_CHARA_KIND_FLAG;
            break;
        default:
            ASSERT_ZERO_ON_LINE(2100);
    }


    
    for (i = 0; i < cid; i++) {
        TexPmd = sh2gfw_Get_pMD(chara[i]);
        if (TexPmd != NULL) break;
    }
    if (TexPmd == NULL) {
        printf("Shared texture model Initialize  failure!\n");
        ASSERT_ZERO_ON_LINE(2111);
    }
    
    
    
    Real_sMH = TexPmd->Model_Head;
    
    for (i = 0; i < Real_sMH->texnum; i++) {
        pTH = (u_char*) Real_sMH + ((u_int*) (Real_sMH + 1))[i]; // unclear if there's a struct for this?
        pCH = (u_char*) Real_sMH + ((u_int*) (Real_sMH + 1))[i + Real_sMH->texnum]; // but these ints are between the model header and the pModel
    
        sMH->pTexMAN[i] = sh2gfw_set_TexToTrasMan(pATSM, pTH, pCH, sMH, sMH->chara_id);


    
    
        pModel->pTexMAN[i] = sMH->pTexMAN[i];
        
        pMD->pTexMAN[i] = sMH->pTexMAN[i];
    }

    
    for (i = Real_sMH->texnum; i <  sMH->texnum; i++) {

        
        pTH = (u_char*) sMH + ((u_int*) (sMH + 1))[i]; // unclear if there's a struct for this?
        pCH = (u_char*) sMH + ((u_int*) (sMH + 1))[i + sMH->texnum]; // but these ints are between the model header and the pModel
        
        
        difpth = ((u_int) pTH - (u_int) sMH + Real_sMH->toTexHead_offset) - sMH->toTexHead_offset;
        difpch = ((u_int) pCH - (u_int) sMH + Real_sMH->toClutsHead_offset) - sMH->toClutsHead_offset;
        pTH = (u_char*) Real_sMH + difpth;
        pCH = (u_char*) Real_sMH + difpch;
        ASSERT_ON_LINE(pTH->check==0x9999, 2144);
        sMH->pTexMAN[i] = sh2gfw_set_TexToTrasMan(pATSM, pTH, pCH, sMH, sMH->chara_id);
        
        
        
        
        pModel->pTexMAN[i] = sMH->pTexMAN[i];
        
        pMD->pTexMAN[i] = sMH->pTexMAN[i];
        printf("caution! shared texture amount is not equal\n");
    }



    
    pMD->TB_change_VU1num = 0;
    pMD->TB_change_VU1now = 0;
    pMD->TB_change_VU0num = 0;
    pMD->TB_change_VU0now = 0;
    
    if (sMH->texnum > 1) {
        TextPos* pTP; // r6
        short* pitex; // r7
        int texblk_index; // r6
    
        int n_parts = pModel->n_vu1_parts; // r2
        Part* part = (u_char*) pModel + pModel->vu1_parts_offset; // r3
        Part* parts_top = part; // r2 @note order swapped with part
        int buff = 0xFFFF; // rr
        

        
        
        
        
        for (i = 0; i < n_parts; i++, part = (u_char*) part + part->size) {
            
            pitex = (u_char*) part + part->text_pos_indices_offset;
            pTP = (u_char*) pModel + pModel->text_poses_offset;
            texblk_index = pTP[pitex[0]].block_index;
            if (texblk_index == buff) continue;
            
            pMD->TB_change_VU1[pMD->TB_change_VU1num] = i;
            pMD->TB_index_VU1[pMD->TB_change_VU1num++] = texblk_index;
            buff = texblk_index;
         
        }
        
        
        pMD->TB_change_VU1[pMD->TB_change_VU1num] = n_parts;
        pMD->TB_index_VU1[pMD->TB_change_VU1num] = 0xFFFF;
        
        if (sMH->texnum > pMD->TB_change_VU1num) {
            
            n_parts = pModel->n_vu0_parts;
            parts_top = part = (u_char*) pModel + pModel->vu0_parts_offset;
            
            for (i = 0; i < n_parts; i++, part = (u_char*) part + part->size) {
                
                pitex = (u_char*) part + part->text_pos_indices_offset;
                pTP = (u_char*) pModel + pModel->text_poses_offset;
                texblk_index = pTP[pitex[0]].block_index;
                if (texblk_index == buff) continue;
                
                pMD->TB_change_VU0[pMD->TB_change_VU0num] = i;
                pMD->TB_index_VU0[pMD->TB_change_VU0num++] = texblk_index;
                buff = texblk_index;
            
            }
        
        } 
        
        
        pMD->TB_change_VU0[pMD->TB_change_VU0num] = n_parts;
        pMD->TB_index_VU0[pMD->TB_change_VU0num] = 0xFFFF;
        
    } else {

        pMD->TB_change_VU1[pMD->TB_change_VU1num++] = 0;
        pMD->TB_change_VU1[pMD->TB_change_VU1num] = pModel->n_vu1_parts;
    }
    
    
    
    return 1;

}
#else
INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_Init_ModelDrawData", Init_WithoutCharaTex);

INCLUDE_RODATA("asm/nonmatchings/GFW/sh2gfw_Init_ModelDrawData", @1612);

INCLUDE_RODATA("asm/nonmatchings/GFW/sh2gfw_Init_ModelDrawData", @1613_0x0038F490);

INCLUDE_RODATA("asm/nonmatchings/GFW/sh2gfw_Init_ModelDrawData", @1614_0x0038F4C0);

INCLUDE_RODATA("asm/nonmatchings/GFW/sh2gfw_Init_ModelDrawData", @1615_0x0038F4F0);

INCLUDE_RODATA("asm/nonmatchings/GFW/sh2gfw_Init_ModelDrawData", @1616);

INCLUDE_RODATA("asm/nonmatchings/GFW/sh2gfw_Init_ModelDrawData", @1617);
#endif
