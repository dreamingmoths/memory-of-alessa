#include "city_00.h"

void func_01F6D680_city_00(void) {
    D_01F6DB80_city_00 = 0;
}

void func_01F6D690_city_00(void) {
    City00Struct sp;
    City00Entry* var_s0;
    City00Entry* temp_s1;

    D_01F6DB80_city_00 = 1;
    func_001C2C10(&sp, &sp.unk10);
    var_s0 = sp.unk0;
    
    temp_s1 = shCharacterGetSubCharacter(0x1048, 0xE7);
    func_0016CC50(0x1048, 0, &var_s0[1].unk0, &sp.unk20);
    vec_copy(&temp_s1->unk20, &var_s0[1].unk30);
    vec_copy(&temp_s1->unk30, &sp.unk20);

    temp_s1 = shCharacterGetSubCharacter(0x1049, 0xE8);
    func_0016CC50(0x1049, 0, &var_s0[2].unk0, &sp.unk20);
    vec_copy(&temp_s1->unk20, &var_s0[2].unk30);
    vec_copy(&temp_s1->unk30, &sp.unk20);
    
    temp_s1 = shCharacterGetSubCharacter(0x104A, 0xE9);
    func_0016CC50(0x104A, 0, &var_s0[3].unk0, &sp.unk20);
    vec_copy(&temp_s1->unk20, &var_s0[3].unk30);
    vec_copy(&temp_s1->unk30, &sp.unk20);
    
    temp_s1 = shCharacterGetSubCharacter(0x104B, 0xEA);
    func_0016CC50(0x104B, 0, &var_s0[4].unk0, &sp.unk20);
    vec_copy(&temp_s1->unk20, &var_s0[4].unk30);
    vec_copy(&temp_s1->unk30, &sp.unk20);
    
    temp_s1 = shCharacterGetSubCharacter(0x104C, 0xEB);
    func_0016CC50(0x104C, 0, &var_s0[5].unk0, &sp.unk20);
    vec_copy(&temp_s1->unk20, &var_s0[5].unk30);
    vec_copy(&temp_s1->unk30, &sp.unk20);
}

void func_01F6D7F0_city_00(void) {
    if (D_01F6DB80_city_00 == 0) {
        func_01F6D690_city_00();
    }
}
