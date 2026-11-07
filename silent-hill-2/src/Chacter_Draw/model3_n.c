#include "sh2_common.h"

#include "sce/libgraph.h"

#include "Chacter_Draw/model_common.h"
#include "Chacter_Draw/model3_n.h"
#include "Chacter_Draw/model3_sub_n.h"

#include "view/vb_main.h"
#include "view/camera_dat.h"

#include "Event/event.h"
#include "GFW/sh2_DrawEnvData.h"

#define ROOT_BONE       0xFF
#define MDL_HEADER_SIZE 0x30

static void Exec_ModelDraw_OVFunc(void* pp);

// thank you: cuddly shrew (anon)
#line 51
static u_int UIntFogcol(void) {
    u_int fogcol;
    *(u_int*) &fogcol = Env_ctl.fogcolor.ui32[0]; // r29+0xC ?? cursed
    
    return fogcol;
}


#line 110
int Model3NSkeletons(void* model_) {
    Model* model = (Model*) model_; // r2
    return model->n_skeletons;
}

#line 120
s_char* Model3SkeletonStructure(void* model_) {
    u_int mask = 1 << 0; // r2
    Model* model = (Model*) model_; // r2
    s_char* structure = (s_char*) model_ + model->skeleton_structure_offset; // r2

    if (!(model->flag & mask)) {
        int i; // r5
        
        for (i = 0; i < model->n_skeletons; i++) {
            u_char d = structure[i]; // r3
            if (d < ROOT_BONE - 1) {
                d = (u_int) d >> 1;
            }
            structure[i] = d;
        }
        model->flag |= mask;
    }
    return structure;
}

#line 145
int Model3NClusters(void* model_) {
    Model* model = (Model*) model_; // r2
    return model->n_clusters;
}

void Model3DrawPre(void) {
    #line 229
    Model3LoadMpg1();
    #line 245
}

#line 257
void sh2_Model_MakeMatrixParams(void) {

    sceVu0FVECTOR* vsm = model3_junk.vsm; // @todo: dwarf order is different; reordered for match
    float nearz = Env_ctl.camera_parms[3]; // r29+0x30
    float farz = Env_ctl.camera_parms2[2]; // r29+0x30
    sceVu0FVECTOR* vsp; // r2
    ModelCommonWork* mcw; // r16
    float ftmp; // r3
    float scrz; // r29+0x30

    vwGetViewPosition(model3_junk.camera);
    sceVu0CopyMatrix(model3_junk.wvm, VbWvsMatrix.wvm);
    sceVu0CopyMatrix(model3_junk.vsm, cam0.view_screen);

    sceVu0CopyMatrix(model3_junk.wsm, cam0.world_screen);

    
    sceVu0InversMatrix(model3_junk.vwm, model3_junk.wvm);

    model3_junk.fogcol = UIntFogcol();

    
    ftmp = 1.0f / (farz - nearz);


    {
        sceVu0FVECTOR* vsp = model_common_work->vsp;

    
        vsp[0][0] = vsm[0][0];
        vsp[0][1] = vsm[1][1];
        vsp[0][2] = vsm[3][2];
        vsp[0][3] = (Env_ctl.fogparm.fl32[0] * Env_ctl.fogparm.fl32[1] * (Env_ctl.fogparm.fl32[3] - Env_ctl.fogparm.fl32[2])) / (Env_ctl.fogparm.fl32[0] - Env_ctl.fogparm.fl32[1]);
        vsp[1][0] = vsm[2][0];
        vsp[1][1] = vsm[2][1];
        vsp[1][2] = vsm[2][2];
        vsp[1][3] = (Env_ctl.fogparm.fl32[0] * Env_ctl.fogparm.fl32[2] - Env_ctl.fogparm.fl32[1] * Env_ctl.fogparm.fl32[3]) / (Env_ctl.fogparm.fl32[0] - Env_ctl.fogparm.fl32[1]);
    }





    {      
        sceVu0FVECTOR* p = model_common_work->vcp;
    
        p[0][0] = 2.0f * vsm[0][0] / 512.0f;
        p[0][1] = 2.0f * vsm[1][1] / 448.0f;
        p[0][2] = ftmp * (farz + nearz);
        p[0][3] = 1.0f;
        p[1][0] = 0;
        p[1][1] = 0;
        scrz = farz * nearz;
        p[1][2] = ftmp * (-2.0f * scrz);
        p[1][3] = 0;
    }


    
    {
        sceVu0FVECTOR* p = model_common_work->vcp_gs;
        p[0][0] = 2.0f * vsm[0][0] / 4080.0f;
        p[0][1] = 2.0f * vsm[1][1] / 4080.0f;
        p[0][2] = ftmp * (farz + nearz);
        p[0][3] = 1.0f;
        p[1][0] = 0;
        p[1][1] = 0;
        p[1][2] = ftmp * (-2.0f * scrz);
        p[1][3] = 0;
    }



    
    
    mcw = model_common_work;
    ModelCommonWorkFlip();
    model_common_work->vsp = mcw->vsp;
    model_common_work->vcp = mcw->vcp;
    model_common_work->vcp_gs = mcw->vcp_gs;

    #line 352
}

static void SortEnvPrim(void) {
    static EnvPacket envpacketdata = {
        /* .headEp = */ {
            /* .dmatagTag = */ DMAnext | 6,
            /* .vifcode0 = */ SCE_VIF1_SET_NOP(0),
            /* .vifcode1 = */ SCE_VIF1_SET_DIRECT(6, 0),
            /* .giftagTag = */ SCE_GIF_SET_TAG(5, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1),
            /* .giftagReg = */ SCE_GIF_PACKED_AD,
            /* .testD = */ 
                SCE_GS_SET_TEST(
                    SCE_GS_TRUE /* alpha test */, SCE_GS_ALPHA_ALWAYS, 0, 0, 0, 0, 
                    SCE_GS_TRUE /* depth test */ , SCE_GS_DEPTH_GEQUAL
                ),
            /* .testA = */ 
                SCE_GS_SET_TEST(
                    SCE_GS_TRUE /* alpha test */, SCE_GS_ALPHA_LEQUAL, 4, 0, 0, 0, 
                    SCE_GS_FALSE, SCE_GS_DEPTH_NEVER
                ),
            /* .texaD = */ SCE_GS_SET_TEXA(128, 0, 128),
            /* .texaA = */ SCE_GS_SET_TEXA(59, 0, 0),
            /* .fbaD = */ SCE_GS_SET_FBA(0),
            /* .fbaA = */ SCE_GS_SET_FBA(74),
            /* .alphaD = */ SCE_GS_SET_ALPHA(0, 1, 0, 1, 0),
            /* .alphaA = */ SCE_GS_SET_ALPHA(2 /* 0 */, 0, 0, 1, 0),
            /* .fogcolD = */ SCE_GS_SET_FOGCOL(0, 0, 0),
            /* .fogcolA = */ SCE_GS_SET_FOGCOL(61, 0, 0),
        },
        /* .tailEp = */ {
            /* .dmatagTag = */ DMAnext | 2,
            /* .vifcode0 = */ SCE_VIF1_SET_NOP(0),
            /* .vifcode1 = */ SCE_VIF1_SET_DIRECT(2, 0),
            /* .giftagTag = */ SCE_GIF_SET_TAG(1, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1),
            /* .giftagReg = */ SCE_GIF_PACKED_AD,
            /* .fbaD = */ SCE_GS_SET_FBA(5),
            /* .fbaA = */ SCE_GS_SET_FBA(8),
        }
    };
    
    EnvPacket* ep = CharacterOt_RequestPacket(10); // r16
    
    *ep = envpacketdata;
    ep->head_ep.fogcol_d = model3_junk.fogcol;
    
    CharacterOt_Append(0x000, &ep->head_ep);
    CharacterOt_Append(0xfff, &ep->tail_ep);  
}

extern int d1_cid_; // @todo this is fake lol

#line 473
void Model3Draw_n(void* scp_d_, void* model_, void* work_, sceVu0FMATRIX mwm) {
    int pef; int d1_cid = d1_cid_; // r2
    Model* model = (Model*) model_; // r2
    ModelWork* mwork = (ModelWork*) work_; // r16
    sh_Model* shM; // r2
    SubCharacterDisp* scp_d = (SubCharacterDisp*) scp_d_; // r17
    
    
    pef = *T0_COUNT;

    
    ModelCommonWorkFlip();

    #line 498
    Model3UpdateMatrices(model, mwork, mwm, scp_d->sc.model_type);











    shM = (Model*) model_;
    #line 512
    sh2_Model3UpdateTextures(shM);









    Model3UpdateEnvelopeMatrices(model, mwork);



    Model3UpdateLightEnv(model, mwork);


    
    Model3UpdateGlobalAmbient();



    if (model->n_clusters != 0) {
        float* weights; // r2
        weights = Model3WorkClusterWeights(mwork);
        ClusterAnimeGetWeights(scp_d->cluster_anime, weights);
    }





    Model3UpdateClusters(model, mwork);






    #line 552
    Exec_ModelDraw_OVFunc(scp_d);



    Model3DrawVu1Parts(model, mwork);




    sh2gfw_Init_CharacterOT();

    Model3DrawVu0Parts(model, mwork);

    #line 597
    if (CharacterOt_IsEmpty()) {



        sh2_Model_DummySyncOT();


        sh2gfw_set_d1cid();
    
    } else {


        SortEnvPrim();


    
        CharacterOt_ExecPre();



    
        CharacterOt_ExecPost();








        
        sh2gfw_set_d1cid();

    }

    pef = *T0_COUNT - pef;

    #line 645
}

int Model3WorkSize(void* model_) {
    Model* model = (Model*) model_; // r2
    int size = MDL_HEADER_SIZE;
    size += model->n_skeletons * 64;
    size = ALIGN16(size);
    size += model->n_clusters * 4;
    size = ALIGN16(size);
    return size;
}

void Model3InitWork(void* model_, void* work_) {
    sh_Model* model = model_; // r16
    ModelWork* work = work_; // r2
    void* top; // r17
    int size; // r18

    work->id = 0xFFFE0003; // @note this is a magic number found in the mdl files. version number?

    size = MDL_HEADER_SIZE;

    top = work + 1;
    work->matrices = (sceVu0FMATRIX*) top;
    if (model->initial_matrices_offset != 0) {
        sceVu0FMATRIX* initial= (sceVu0FMATRIX*) ((int) model + model->initial_matrices_offset);
        int i;
        for (i = 0; i <  model->n_skeletons; i++) {
            sceVu0CopyMatrix(work->matrices[i], *initial++);
        }
    }
    size += model->n_skeletons * 64;
    size = ALIGN16(size);


    work->cluster_weights = (float*)((int) work + size);
    
    {
        int i;

        for (i = 0; i < model->n_clusters; i++) {
            work->cluster_weights[i] = 0.0f;
        }
    }

    work->equipment_flag = 0x204041; // @tood how to interpret this value?

    work->draw_hook = NULL;
    work->draw_hook_data = NULL;
}

sceVu0FMATRIX* Model3WorkMatrices(void* work_) {
    ModelWork* work = (ModelWork*) work_; // r2
    return work->matrices;
}

float* Model3WorkClusterWeights(void* work_) {
    ModelWork* work = (ModelWork*) work_; // r2
    return work->cluster_weights;
}

static void Exec_ModelDraw_OVFunc(void* pp) {
    SubCharacterDisp* scp_d = (SubCharacterDisp*) pp; // r2 // @note unused
    if (stage)
        if (stage->gfw_func)
            if (stage->gfw_func->CharaDraw_Hook)
                stage->gfw_func->CharaDraw_Hook(pp, model3_junk.global_ambient);
}

