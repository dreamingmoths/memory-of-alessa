#include "model3_sub_n.h"
#include "model_common.h"

int func_001D3780(void *work_) {
  ModelWork *work;

  work = work_;
  return (int)work->cluster_weights;
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_sub_n", Model3WorkEquipmentFlag);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_sub_n", func_001D37C0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_sub_n", func_001D37E0);

void func_001D3860(void) {
  if (D_01EE3080 == 0) {
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

void func_001D3990(float x, float z) {
  model3_junk.xyz_max[2] = z;
  D_01EE15E8 = z;
  model3_junk.xyz_min_wide[2] = x;
  model3_junk.xyz_min[2] = x;
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_sub_n", sh3_Model3UpdateTextures);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_sub_n", Model3UpdateMatrices);

void Model3UpdateEnvelopeMatrices(void *model_, void *work_) {
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

  if (0 < count) {
    pcm_offset = 0;
    pair_offset = 0;
    do {
      shMulMatrix(*(sceVu0FMATRIX *)((char *)dst + pcm_offset), mcw->skeleton_matrices[pairs[pair_offset + 1]],
                  *(sceVu0FMATRIX *)((char *)pcms + pcm_offset));
      i += 1;
      pcm_offset += 0x40;
      pair_offset += 2;
    } while (i < count);
  }
}
