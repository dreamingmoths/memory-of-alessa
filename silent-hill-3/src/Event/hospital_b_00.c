#include "Chacter/m3_bgobj.h"
#include "Chacter/m3_sc.h"
#include "hospital_b_00.h"

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6D680_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6D820_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6DA90_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6DBF0_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6DD80_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6DE10_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E060_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E110_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E230_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E290_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E360_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E4E0_hospital_b_00);

void func_01F6E5B0_hospital_b_00(void) {
    SubCharacter* scp;
    int score;
    int action;
    int* cur;

    action = GetActionLevel();
    score = D_1D31918 + D_1D3191C;

    for (cur = &D_01F70540_hospital_b_00; *cur != 0; cur++) {
        scp = shCharacterGetSubCharacter(NURSE_CHARA_ID, *cur);

        if (scp != NULL && !func_001E2110(scp)) {
            switch (*cur) {
                case 317:
                    if (score < 120) {
                        shCharacter_Manage_Delete(NURSE_CHARA_ID, *cur);
                    }
                    break;
                case 318:
                    if (score < 190) {
                        shCharacter_Manage_Delete(NURSE_CHARA_ID, *cur);
                    }
                    break;
                case 319:
                    if (score < 260) {
                        shCharacter_Manage_Delete(NURSE_CHARA_ID, *cur);
                    }
                    break;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E6C0_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E880_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E980_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6EA00_hospital_b_00);
