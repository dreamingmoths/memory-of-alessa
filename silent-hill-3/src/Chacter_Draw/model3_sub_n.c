#include "model3_sub_n.h"
#include "model_common.h"
#include "libdma.h"
#include "eestruct.h"
#include "eeregs.h"
#include "libgraph.h"

float* func_001D3780(void *work_)
{
    ModelWork *work;
    work = work_;
    return work->cluster_weights;
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_sub_n", Model3WorkEquipmentFlag);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_sub_n", func_001D37C0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_sub_n", func_001D37E0);

void Model3Init(void) {    
    if (initialized == 0) {
        const static float xyz_min_wide[4] = {16.0, 16.0, 0.0, 0.0};
        const static float xyz_max_wide[4] = {4080.0, 4080.0, 0.0, 0.0};
        const static float xyz_min[4] = {1024.0, 1024.0, 0.0, 0.0};
        const static float xyz_max[4] = {3072.0, 3072.0, 0.0, 0.0};
        const static float rgba_max[4] = {128.0, 128.0, 128.0, 255.0};
        const static float global_ambient[4] = {1.0, 1.0, 1.0, 1.0};
        const static long giftag_0[2] = {
            SCE_GIF_SET_TAG(
                0,
                SCE_GS_TRUE,
                SCE_GS_FALSE,
                SCE_GS_SET_PRIM(SCE_GS_PRIM_POINT, 0, 0, 0, 0, 0, 0, 0, 0),
                SCE_GIF_PACKED,
                1
            ),
            GIF_REG(SCE_GIF_PACKED_AD, 0)
        };
        const static long giftag_1[2] = {
            SCE_GIF_SET_TAG(
                0,
                SCE_GS_TRUE,
                SCE_GS_TRUE,
                SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 1, 1, 1, 0, 0, 0, 0, 0),
                SCE_GIF_PACKED,
                3
            ),
            GIF_REG(SCE_GS_ST, 0) | GIF_REG(SCE_GS_RGBAQ, 1) | GIF_REG(SCE_GS_XYZF2, 2) | GIF_REG(SCE_GS_PRIM, 3)
        };
        const static long giftag_2[2] = {
            SCE_GIF_SET_TAG(
                0,
                SCE_GS_TRUE,
                SCE_GS_TRUE,
                SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 1, 1, 1, 1, 0, 0, 0, 0),
                SCE_GIF_PACKED,
                3
            ),
            GIF_REG(SCE_GS_ST, 0) | GIF_REG(SCE_GS_RGBAQ, 1) | GIF_REG(SCE_GS_XYZF2, 2) | GIF_REG(SCE_GS_PRIM, 3)
        };

        // @hack writing to rodata!?
        *(float*)&xyz_min_wide[2] = func_001B4210();
        *(float*)&xyz_max_wide[2] = func_001B4200();
        *(float*)&xyz_min[2] = func_001B4210();
        *(float*)&xyz_max[2] = func_001B4200();

        sceVu0CopyVector(model3_junk.xyz_min_wide, (float*) xyz_min_wide);
        sceVu0CopyVector(model3_junk.xyz_max_wide, (float*) xyz_max_wide);
        sceVu0CopyVector(model3_junk.xyz_min, (float*) xyz_min);
        sceVu0CopyVector(model3_junk.xyz_max, (float*) xyz_max);
        sceVu0CopyVector(model3_junk.rgba_max, (float*) &rgba_max);
        sceVu0CopyVector(model3_junk.global_ambient, (float*) &global_ambient);
        sceVu0CopyVector((float* ) &model3_junk.giftag_0, &giftag_0);
        sceVu0CopyVector((float* ) &model3_junk.giftag_1, &giftag_1);
        sceVu0CopyVector((float* ) &model3_junk.giftag_2, &giftag_2);
        model3_junk.vi00 = (void* )0x70000000;
        initialized = 1;
    }
}

void func_001D3990(float max_z, float min_z)
{
    model3_junk.xyz_min_wide[2] = min_z;
    model3_junk.xyz_min[2] = min_z;
    model3_junk.xyz_max_wide[2] = max_z;
    model3_junk.xyz_max[2] = max_z;
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_sub_n", sh3_Model3UpdateTextures)

const sceVu0FMATRIX D_003669A0 = {
    -1.0, 0.0, 0.0, 0.0,
     0.0, 1.0, 0.0, 0.0,
     0.0, 0.0, 1.0, 0.0,
     0.0, 0.0, 0.0, 1.0
};

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_sub_n", Model3UpdateMatrices);

void Model3UpdateEnvelopeMatrices(Model *model)
{
    int n_pairs = model->n_skeleton_pairs;
    sceVu0FMATRIX *default_pcms = (sceVu0FMATRIX *)((int)model + model->default_pcms_offset);
    sceVu0FMATRIX *skeleton_matrices = (sceVu0FMATRIX *)&model_common_work->skeleton_matrices[0];
    struct SkeletonPair *pairs = (struct SkeletonPair *)((int)model + model->skeleton_pairs_offset);
    sceVu0FMATRIX *envelope_matrices = &model_common_work->envelope_matrices[0];
    int i;

    for (i = 0; i < n_pairs; i++)
    {
        struct SkeletonPair *pair = &pairs[i];
        float(*em)[4] = envelope_matrices[i];
        int child_no = pair->child_no;
        float(*pcm)[4] = default_pcms[i];
        float(*cvm)[4] = skeleton_matrices[child_no];

        // envelope matrix = child skeleton matrix * parent-child matrix
        shMulMatrix(em, cvm, pcm);
    }
}
