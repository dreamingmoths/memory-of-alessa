#include "sh2_common.h"

#include "sce/libvu0.h"
#include "sce/libgraph.h"

#include "gs.h"

#include "Chacter_Draw/model_common.h"
#include "Chacter_Draw/model3_structs.h"
#include "Chacter_Draw/sh2gfw_md_spclmapping.h"
#include "Chacter_Draw/light_n.h"

#include "Chacter/character.h"

#include "GFW/sh2_DrawEnvData.h"
#include "GFW/sh2gfw_Init_ModelDrawData.h"
#include "GFW/sh2gfw_Texpacket.h"

#define MDL3_VERSION 3

#line 47
void Model3Init(void) {
    static int initialized = false; // @ 0x00419F80

    if (!initialized) {
        static sceVu0FVECTOR xyz_min_wide = {16.0f, 16.0f, 0.0f, 0.0f};
        static sceVu0FVECTOR xyz_max_wide = {4080.0f, 4080.0f, 0.0f, 0.0f};
        
        static sceVu0FVECTOR xyz_min = {1024.0f, 1024.0f, 0.0f, 0.0f};
        static sceVu0FVECTOR xyz_max = {3072.0f, 3072.0f, 0.0f, 0.0f};

        static sceVu0FVECTOR rgba_max = {128.0f, 128.0f, 128.0f, 255.0f};
        
        static sceVu0FVECTOR global_ambient = {1.0f, 1.0f, 1.0f, 1.0f};

        static u_long giftag_0[2] = {
            SCE_GIF_SET_TAG(0, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1),
            GIF_REG(SCE_GIF_PACKED_AD, 0)
        };
        static u_long giftag_1[2] = {
            SCE_GIF_SET_TAG(0, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 1, 1, 1, 0, 0, 0, 0, 0), SCE_GIF_PACKED, 3),
            GIF_REGLIST(SCE_GS_ST, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_PRIM)
        };
        static u_long giftag_2[2] = {
            SCE_GIF_SET_TAG(0, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 1, 1, 1, 1, 0, 0, 0, 0), SCE_GIF_PACKED, 3),
            GIF_REGLIST(SCE_GS_ST, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_PRIM)
        };

        #line 75
        xyz_min_wide[2] = 2.0f;
        xyz_max_wide[2] = Env_ctl.camera_parms2[3];
        xyz_min[2] = 2.0f;
        xyz_max[2] = Env_ctl.camera_parms2[3];


        #line 82
        sceVu0CopyVector(model3_junk.xyz_min_wide, xyz_min_wide);
        sceVu0CopyVector(model3_junk.xyz_max_wide, xyz_max_wide);
        sceVu0CopyVector(model3_junk.xyz_min, xyz_min);
        sceVu0CopyVector(model3_junk.xyz_max, xyz_max);
        sceVu0CopyVector(model3_junk.rgba_max, rgba_max);
        sceVu0CopyVector(model3_junk.global_ambient, global_ambient);
        sceVu0CopyVector((float*) &model3_junk.giftag_0, (float*) &giftag_0);
        sceVu0CopyVector((float*) &model3_junk.giftag_1, (float*) &giftag_1);
        sceVu0CopyVector((float*) &model3_junk.giftag_2, (float*) &giftag_2);
        model3_junk.vi00 = (void*) SCRATCHPAD_START;
        
        initialized = true;
    }
}

#define MDL_SECTION(_offset) ((u_char*) model + model->_offset)
#line 119
void sh2_Model3UpdateTextures(sh_Model* model) {
    #line 121
    int n_texture_blocks = model->n_texture_blocks; // r17
    int* texture_blocks = (int*) MDL_SECTION(texture_blocks_offset); // r18
    int n_text_poses = model->n_text_poses; // r19
    TextPos* text_poses = (TextPos*) MDL_SECTION(text_poses_offset); // r20
    int spemap, envmap; // r2 @todo `envmap` is unused
    if (!(spemap = model->revision < MDL3_VERSION)) spemap = (model->flag & (1 << 30)) != 0;

    #line 133
    if (spemap) {
        model_common_work->specular_mapping_tex0 = sh2_SpecularMappingTEX0();
    }

    
    {
        int i; // r21
        for (i = 0; i < n_texture_blocks; i++) {

            #line 149
            int id = texture_blocks[i]; // r2
            sh2gfw_Thr_d2TextureSend(
                model->pTexMAN[id],
                1,
                &UniModelDW_Man.chr_cid[id],
                &UniModelDW_Man.chr_slotid[id]
            );
        
        }
    }


    #line 162
    {
        TextPosParam* params = model_common_work->text_pos_params; // r17
        int i; // r18
    
        for (i = 0; i < n_text_poses; i++) {
            TextPos* text_pos = &text_poses[i]; // r3
            TextPosParam* param = &params[i]; // r2

            #line 178
            u_long128* tmp_tex0 = sh2gfw_Get_RegTEX0(
                model->pTexMAN[text_pos->block_index],
                text_pos->texture_no,
                1
            ); // r2
            
            #line 185
            param->tex0 = *tmp_tex0;
        }
    }

}

#line 312
void Model3UpdateMatrices(Model* model, ModelWork* work, sceVu0FVECTOR* mwm, int model_type) {
    int n_skeletons = model->n_skeletons; // r16
    sceVu0FMATRIX* matrices = work->matrices; // r17
    sceVu0FMATRIX wvm; // r29+0x60
    sceVu0FMATRIX mvm; // r29+0xA0
    
    sceVu0FMATRIX xsin = {
        -1.0f, 0.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f, 0.0f,
         0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 0.0f, 1.0f
    }; // r29+0xE0
    int i; // r18
    
    sceVu0CopyMatrix(wvm, model3_junk.wvm);
    sceVu0MulMatrix(mvm, wvm, mwm);
    sceVu0MulMatrix(model_common_work->top_skeleton_matrix, mvm, matrices[0]);

    mvm[0][3] = mvm[0][2];
    mvm[1][3] = mvm[1][2];
    mvm[2][3] = mvm[2][2];
    mvm[3][3] = mvm[3][2];


    if (model_type != 0) {
        for (i = 0; i < n_skeletons; i++) {
            sceVu0FVECTOR* lvm = model_common_work->skeleton_matrices[i]; // r19
            sceVu0FVECTOR* lmm = matrices[i]; // r20
            
            shMulMatrix(lmm, xsin, lmm);
            shMulMatrix(lvm, mvm, lmm);
        }
    } else {
        for (i = 0; i < n_skeletons; i++) {
            sceVu0FVECTOR* lvm = model_common_work->skeleton_matrices[i]; // r2
            sceVu0FVECTOR* lmm = matrices[i]; // r2
            
            shMulMatrix(lvm, mvm, lmm);
        }
    }
}

#line 393
void Model3UpdateEnvelopeMatrices(Model* model) {
    int n_pairs = model->n_skeleton_pairs; // r16
    sceVu0FMATRIX* default_pcms = (sceVu0FMATRIX*) MDL_SECTION(default_pcms_offset); // r17
    sceVu0FMATRIX* skeleton_matrices = model_common_work->skeleton_matrices; // r2
    SkeletonPair* pairs = (SkeletonPair*) MDL_SECTION(skeleton_pairs_offset); // r18
    sceVu0FMATRIX* envelope_matrices = model_common_work->envelope_matrices; // r19
    int i; // r20

    for (i = 0; i < n_pairs; i++) {
        SkeletonPair* pair = &pairs[i]; // r2
        sceVu0FVECTOR* em = envelope_matrices[i];
        int child_no = pair->child_no;
        sceVu0FVECTOR* pcm = default_pcms[i];
        sceVu0FVECTOR* cvm = skeleton_matrices[child_no];

        // envelope matrix = child skeleton matrix * parent-child matrix
        shMulMatrix(em, cvm, pcm);
    }
}

#line 419
void Model3UpdateLightEnv(void) {
    static sceVu0FVECTOR base = {0.0f, 0.0f, 0.0f, 1.0f}; // @ 0x002A96F0
    
    static float radius = 800.0f; // @ 0x002A9700
    
    sceVu0FVECTOR wpos; // r29+0x10

    sceVu0ApplyMatrix(wpos, model_common_work->top_skeleton_matrix, base);
    sceVu0ApplyMatrix(wpos, model3_junk.vwm, wpos);
    
    LightUpdateInfoByPos(wpos, radius);
}

#line 438
void Model3UpdateGlobalAmbient(void) {

    
    sceVu0ScaleVector(
        (float*) model3_junk.global_ambient, // @note cast needed as a holy candle
        Env_ctl.ambient, 
        2.0f
    );
    sceVu0ScaleVector(model3_junk.global_ambient, model3_junk.global_ambient, Env_ctl.CharacterLightFactor[0]);
    
    #line 450
    model3_junk.global_ambient[3] *= 2.0f;
    #line 476
}
