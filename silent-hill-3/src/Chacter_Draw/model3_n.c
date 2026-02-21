#include "common.h"
#include "Chacter/character.h"
#include "Chacter_Draw/model3_n.h"
#include "Chacter_Draw/model3_sub_n.h"
#include "eeregs.h"

int Model3NSkeletons(void* model_) {
    sh_Model* model = (sh_Model*)model_;
    return model->n_skeletons;
}

s8* Model3SkeletonStructure(sh_Model* model) {
    s8* structure= (s8*)((u8*)model + model->skeleton_structure_offset);
    int i;
    u8 mask;

    if (!(model->flag & 1)) {
        for (i = 0; i < model->n_skeletons; i++) {
            u8 d = structure[i];
            mask = d;
            if ((u8) mask < 0xFE) {
                mask >>= 1;
            }
            structure[i] = mask;
        }
        model->flag |= 1;
    }

    return structure;
}


int Model3NClusters(void* model_) {
    sh_Model* model = model_;
    return model->n_clusters;
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_n", func_001D2F00);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_n", sh3_Model_MakeMatrixParams);

// sh2: https://decomp.me/scratch/pHyrW
void SortEnvPrim(void) {
    EnvPacket* ep;
    s64 var_v0;

    // @todo: define envpacketdata here
    // @todo: struct field names might be incorrect
    
    ep = (EnvPacket*)CharacterOt_RequestPacket(0xC);

    if ((func_001C5C30() != 0) || (func_0025CF20() != 0)) {
        envpacketdata.head_ep.test_d = 0x5000D;
    } else {
        envpacketdata.head_ep.test_d  = ((s64)D_00366900 << 4) | 0x5000D;
    }

    if (func_002D7B20() != 0) {
        envpacketdata.head_ep.fba_d = func_001CC6F0();
        envpacketdata.head_ep.test_d = ((s64)D_00366908 << 4) | 0x5000B;
    } else {
         envpacketdata.head_ep.fba_d = 0;
    }

    *ep = envpacketdata;
    ep->head_ep.fogcol_d = model3_junk.fogcol;

    CharacterOt_Append(0, (__int128*) &ep->head_ep);
    CharacterOt_Append(0xFFF, (__int128*) &ep->head_ep.unk0x70); // @todo maybe head and tail combined into the same struct?
}


void Model3Draw_n(void* scp_d_, void* model_, void* work_, float (*mwm)[4]) {
    struct Model * model = (Model* )model_; // r2
    struct ModelWork * mwork = (ModelWork*) work_; // r16
    struct SubCharacterDisp * scp_d = (SubCharacterDisp *) scp_d_; // r17
    int pef; // r2
    int unk;


    if (func_0023D040() != 0) {
        pef = *T0_COUNT;

        func_001C5C50();
        func_001C5CD0();
        model_common_work = (ModelCommonWork*) func_001C5CA0();
        model3_junk.fogcol = func_001D2E20();
        model3_junk._unknown = NULL;
        model3_junk.vi00 = NULL;
    
    
        Model3UpdateMatrices(model, mwork, mwm, scp_d->sc.status & 0x2000);

        sh3_Model3UpdateTextures((sh_Model *) model); 

        Model3UpdateEnvelopeMatrices(model, mwork);
    

        // @todo not really sure how any of this lines up to the sh2 code...
        if (func_001CC680() != 0) {
            if (func_001D0EB0() != 0) {
                unk = func_001D3780(mwork);
                func_00140A50(func_001CC670(), unk);
            }
            func_001D2C60(model, mwork);
            if (func_001D0F00() != 0) {
                func_001D2570(model, mwork);
            }
        }
        func_001D8B00(model, mwork);
        if (func_001D0DA0() != 0) {
            func_001D0F10();
            func_001D67E0(model, mwork);
            if (func_001D1080() != 0) {
                func_001D1190();
                func_001C5D70(0);
            } else {
                SortEnvPrim();
                func_001D10A0();
                func_001D12B0();
            }
        }
    
        pef = *T0_COUNT - pef;
    }
}

int Model3WorkSize(void* model_) {
    int size = 0x30;
    sh_Model* model = model_;

    size += model->n_skeletons * 0x40;
    size = (size + 0xf) & ~0xf;
    size += model->n_clusters * 0x4;
    size = (size + 0xf) & ~0xf;

    return size;
}

void Model3InitWork(void* model_, void * work_) {
    struct sh_Model * model = model_;
    struct ModelWork * work = work_;
    int i;
    int size;
    void * top;





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

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_n", Model3WorkClusterWeights);
