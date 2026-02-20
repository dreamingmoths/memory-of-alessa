#include "sh2_common.h"
#include "model3_sub_n.h"
#include "model3_n.h"
#include "eeregs.h"

s8 *Model3SkeletonStructure(sh_Model *model)
{
    s8 *structure;
    int i;
    u8 mask;

    structure = (s8 *)((u8 *)model + model->skeleton_structure_offset);

    if (!(model->flag & 1))
    {
        for (i = 0; i < model->n_skeletons; i++)
        {
            u8 d = structure[i];

            mask = d;
            if (mask < 0xFE)
            {
                mask >>= 1;
            }

            structure[i] = mask;
        }
        model->flag |= 1;
    }

    return structure;
}

void SortEnvPrim(void) {
    EnvPacket* ep;

    // @todo: define envpacketdata here
    
    ep = (EnvPacket*)CharacterOt_RequestPacket(0xA);

    *ep = envpacketdata;
    ep->head_ep.fogcol_d = model3_junk.fogcol;

    CharacterOt_Append(0, (__int128*) &ep->head_ep);
    CharacterOt_Append(0xFFF, (__int128*) &ep->tail_ep);
}

#ifdef NON_MATCHING
void Model3Draw_n(void* scp_d_, void* model_, void* work_, float (*mwm)[4]) {
    float * weights; // r2
    struct SubCharacterDisp * scp_d = (SubCharacterDisp *) scp_d_; // r17
    struct sh_Model * shM = (sh_Model*) model_; // r2
    struct ModelWork * mwork = (ModelWork*) work_; // r16
    struct Model * model = (Model* )model_; // r2
    int d1_cid; // r2
    int pef; // r2

    *T0_COUNT;

    ModelCommonWorkFlip();


    Model3UpdateMatrices(model, mwork, mwm, scp_d->sc.model_type);



    sh2_Model3UpdateTextures(shM);









    Model3UpdateEnvelopeMatrices(model, mwork);



    Model3UpdateLightEnv(model_, work_);


    
    Model3UpdateGlobalAmbient();



    if (model->n_clusters != 0) {
    
        weights = Model3WorkClusterWeights(work_);
        ClusterAnimeGetWeights(scp_d->cluster_anime, weights);
    }





    Model3UpdateClusters(model, mwork);






    
    Exec_ModelDraw_OVFunc(scp_d);



    Model3DrawVu1Parts(model, mwork);




    sh2gfw_Init_CharacterOT();


    Model3DrawVu0Parts(model, mwork);


    
    pef = CharacterOt_IsEmpty();



    if (pef) {



        sh2_Model_DummySyncOT();


        sh2gfw_set_d1cid();
    
    } else {


        SortEnvPrim();


    
        CharacterOt_ExecPre();



    
        CharacterOt_ExecPost();


    
        sh2gfw_set_d1cid();

    }

    *T0_COUNT;
}
#endif

int Model3WorkSize(void* model_) {
    int size = 0x30;
    sh_Model* model = model_;

    size += model->n_skeletons * 0x40;
    size = (size + 0xf) & ~0xf;
    size += model->n_clusters * 0x4;
    size = (size + 0xf) & ~0xf;

    return size;
}

void Model3InitWork(void* model_ /* r2 */, void * work_ /* r2 */) {
    struct sh_Model * model = model_; // r16
    struct ModelWork * work = work_; // r2
    int i;
    int size; // r18
    void * top; // r17





    work->id = 0xFFFE0003;

    size = 0x30;

    top = work + 1;
    work->matrices = (sceVu0FMATRIX*)top;
    if (model->initial_matrices_offset != 0) {
        float (* initial)[4][4] = (sceVu0FMATRIX*)((int)model + model->initial_matrices_offset);
        int i;
        for (i = 0; i <  model->n_skeletons; i++) {
            sceVu0CopyMatrix(work->matrices[i], *initial++);
        }
    }
    size += model->n_skeletons * 0x40;
    size = (size + 0xf) & ~0xf;


    work->cluster_weights = (float*)((int)work + size);


    for (i = 0; i < model->n_clusters; i++) {
        work->cluster_weights[i] = 0.0f;
    }












    work->equipment_flag = 0x204041;



















    work->draw_hook = NULL;
    work->draw_hook_data = NULL;
}
