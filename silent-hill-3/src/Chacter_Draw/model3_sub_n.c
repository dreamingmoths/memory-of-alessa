#include "model3_sub_n.h"
#include "model_common.h"

int func_001D3780(void *work_)
{
    ModelWork *work;

    work = work_;
    return (int)work->cluster_weights;
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_sub_n", Model3WorkEquipmentFlag);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_sub_n", func_001D37C0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_sub_n", func_001D37E0);

void func_001D3860(void)
{
    if (D_01EE3080 == 0)
    {
        D_00366918 = func_001B4210();
        D_00366928 = func_001B4200();
        D_00366938 = func_001B4210();
        D_00366948 = func_001B4200();

        sceVu0CopyVector(model3_junk.xyz_max, D_00366910);
        sceVu0CopyVector(model3_junk.xyz_min_wide, D_00366920);
        sceVu0CopyVector(D_01EE15E0, D_00366930);
        sceVu0CopyVector(model3_junk.xyz_min, D_00366940);
        sceVu0CopyVector(model3_junk.xyz_max_wide, D_00366950);
        sceVu0CopyVector(model3_junk.rgba_max, D_00366960);
        sceVu0CopyVector(model3_junk.global_ambient, D_00366970);
        sceVu0CopyVector(*(sceVu0FVECTOR *)&model3_junk.giftag_0, D_00366980);
        sceVu0CopyVector(*(sceVu0FVECTOR *)&model3_junk.giftag_1, D_00366990);

        model3_junk.vi00 = (void *)(u_int)0x70000000;
        D_01EE3080 = 1;
    }
}

void func_001D3990(float x, float z)
{
    model3_junk.xyz_max[2] = z;
    D_01EE15E8 = z;
    model3_junk.xyz_min_wide[2] = x;
    model3_junk.xyz_min[2] = x;
}

void sh3_Model3UpdateTextures(void *model_)
{
    int offset;
    int tex;
    int tex0;
    int n_texture_blocks;
    int n_text_poses;
    int *texture_blocks;
    ModelTextPose *text_poses;
    int i;
    Model *model;
    int should_call;
    int arg_or_flag;
    int text_poses_offset;
    int texture_blocks_offset;
    int tex1;
    ModelTextPose *pose;
    u128 *src;
    char *dst_base;

    model = model_;
    texture_blocks_offset = model->texture_blocks_offset;
    text_poses_offset = model->text_poses_offset;
    texture_blocks = (int *)((char *)model + texture_blocks_offset);
    n_texture_blocks = model->n_texture_blocks;
    n_text_poses = model->n_text_poses;
    text_poses = (ModelTextPose *)((char *)model + text_poses_offset);
    arg_or_flag = (int)model;
    should_call = model->revision < 3U;
    if (!should_call)
    {
        arg_or_flag = model->flag;
        should_call = (arg_or_flag & 0x40000000) != 0;
    }
    if (should_call)
    {
        *(s64 *)((char *)model_common_work + 0x62A0) =
            func_001CC710(arg_or_flag, text_poses_offset, texture_blocks_offset);
    }
    if (0 < n_texture_blocks)
    {
        i = 0;
        offset = 0;
        do
        {
            tex = *(int *)((char *)texture_blocks + offset);
            tex0 = func_001D0D80(tex);
            tex1 = func_001D0DF0(tex);
            sh3gfw_Thr_d2TextureSend(tex0, 0, tex1, func_001D0DB0(tex));
            i += 1;
            offset += 4;
        } while (i < n_texture_blocks);
    }
    dst_base = (char *)model_common_work + 0x60A0;
    i = 0;
    if (0 < n_text_poses)
    {
        offset = 0;
        do
        {
            pose = (ModelTextPose *)((char *)text_poses + offset);
            src = func_001B5B00(func_001D0D80(pose->texture_id), pose->text_pos_param, 1);
            *(s64 *)(dst_base + offset) = *src;
            i += 1;
            offset += 8;
        } while (i < n_text_poses);
    }
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_sub_n", Model3UpdateMatrices);

void Model3UpdateEnvelopeMatrices(void *model_, void *work_)
{
    ModelCommonWork *mcw;
    Model *model;
    int count;
    sceVu0FMATRIX *pcms;
    unsigned char *pairs;
    sceVu0FMATRIX *dst;
    int i;
    int pcm_offset;
    int pair_offset;

    model = model_;
    i = 0;
    mcw = model_common_work;
    count = model->n_skeleton_pairs;
    pcms = (sceVu0FMATRIX *)((char *)model + model->default_pcms_offset);
    pairs = (unsigned char *)model + model->skeleton_pairs_offset;
    dst = mcw->envelope_matrices;
    (void)work_;

    if (0 < count)
    {
        pcm_offset = 0;
        pair_offset = 0;
        do
        {
            shMulMatrix(*(sceVu0FMATRIX *)((char *)dst + pcm_offset), mcw->skeleton_matrices[pairs[pair_offset + 1]],
                        *(sceVu0FMATRIX *)((char *)pcms + pcm_offset));
            i += 1;
            pcm_offset += 0x40;
            pair_offset += 2;
        } while (i < count);
    }
}
