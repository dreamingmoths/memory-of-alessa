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

long func_001D37E0(ModelWorkGroup *arg0, int equipment_id0, int equipment_id1, int equipment_id2, int equipment_id3)
{
    long id0;
    long id1;
    long id2;
    long id3;
    long one = 1;
    long mask;
    long temp;
    long temp2;

    id0 = equipment_id0;
    id1 = equipment_id1;
    id2 = equipment_id2;
    id3 = equipment_id3;

    mask = (one << id3) | ((one << id2) | (((one << id0) | 1) | (one << id1)));
    func_001D37C0(arg0->current, -1, mask);
    return (long)(int)mask;
}
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
        sceVu0CopyVector(model3_junk.unk00, D_00366930);
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
    model3_junk.unk00[2] = z;
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
    __int128 *src;
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
        *(s64 *)&model_common_work->specular_mapping_tex0 =
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

void Model3UpdateMatrices(void *model_, void *work_, float (*mwm)[4], int pef)
{
    int n_skeletons;
    sceVu0FMATRIX *matrices;
    int i;
    sceVu0FMATRIX work_camera_matrix;
    sceVu0FMATRIX top_skeleton_matrix;
    sceVu0FMATRIX pef_matrix;
    sceVu0FMATRIX *common_matrix;
    sceVu0FMATRIX *current_matrix;
    int offset;

    n_skeletons = ((Model *)model_)->n_skeletons;
    matrices = ((ModelWork *)work_)->matrices;

    (*(ModelMatrix *)pef_matrix) = (*(ModelMatrix *)D_003669A0);

    sceVu0CopyMatrix(work_camera_matrix, *(sceVu0FMATRIX *)&model3_junk.camera);
    sceVu0MulMatrix(top_skeleton_matrix, work_camera_matrix, mwm);
    sceVu0MulMatrix(model_common_work->top_skeleton_matrix, top_skeleton_matrix, *matrices);

    top_skeleton_matrix[0][3] = top_skeleton_matrix[0][2];
    top_skeleton_matrix[1][3] = top_skeleton_matrix[1][2];
    top_skeleton_matrix[2][3] = top_skeleton_matrix[2][2];
    top_skeleton_matrix[3][3] = top_skeleton_matrix[3][2];

    if (pef != 0)
    {
        if (0 < n_skeletons)
        {
            i = 0;
            offset = 0;
            do
            {
                current_matrix = (sceVu0FMATRIX *)((char *)matrices + offset);
                common_matrix = (sceVu0FMATRIX *)((char *)model_common_work + offset);
                shMulMatrix(*current_matrix, pef_matrix, *current_matrix);
                shMulMatrix(*common_matrix, top_skeleton_matrix, *current_matrix);
                i += 1;
                offset += 0x40;
            } while (i < n_skeletons);
        }
    }
    else
    {
        int matrix_offset;
        int index;

        if (0 < n_skeletons)
        {
            index = 0;
            matrix_offset = 0;
            do
            {
                shMulMatrix(*(sceVu0FMATRIX *)((char *)model_common_work + matrix_offset), top_skeleton_matrix,
                            *(sceVu0FMATRIX *)((char *)matrices + matrix_offset));
                index += 1;
                matrix_offset += 0x40;
            } while (index < n_skeletons);
        }
    }
}

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
        float(*pcm)[4] = default_pcms[i];             // r2
        float(*cvm)[4] = skeleton_matrices[child_no]; // r2

        // envelope matrix = child skeleton matrix * parent-child matrix
        shMulMatrix(em, cvm, pcm);
    }
}
