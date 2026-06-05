#include "common.h"
#include "Chacter/m3_sc.h"

/* start of split may be slightly off */

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC3F0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC420);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC450);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC470);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC4E0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC550);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC610);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC650);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC6A0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC700);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC7A0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC7E0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC820);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC840);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC860);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC870);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC8B0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC8F0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC950);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC980);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC9B0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DC9E0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DCA10);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DCA40);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DCA70);

u_int shCharacterGetAnimeAdr(SubCharacter* scp) {
    SubCharacterDisp* scp_d = scp;
    return scp_d->anime_adr;
};

u_short shCharacterGetModelID(SubCharacter* scp) {
    return scp->kind;
};

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", shCharacterGetSkeltonNum);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", shCharacterAnimeOneFrameSize);

void shCharacterExecAnimeOne(SubCharacter* scp) {
    SubCharacterDisp* scp_d = scp;
    SubCharacter* scp_wp;
    u_char weapon;

    switch (scp_d->sc.kind) {
        case HEATHER_CHARA_ID:
            func_001326B0();
            sh_HEATHER_SetUntouchUpper(scp_d->anime.top);
            shCharacterExecAnimeMain(&scp_d->anime, 2);
            sh_HEATHER_SetUntouchUnder(scp_d->anime2.top);
            shCharacterExecAnimeMain(&scp_d->anime2, 1);
            sh_HEATHER_ResetUntouchUnder(scp_d->anime2.top);
            func_00140060(&scp_d->anime2);
            func_00140330(scp_d->anime2.top);
            func_00132620();
            func_00136D20(scp_d);
            func_001321B0();
            break;

        default:
            shCharacterExecAnimeMain(&scp_d->anime, 0);
    }

    switch (scp_d->sc.kind) {
        case HEATHER_CHARA_ID:
            weapon = PlayerGetHeatherWeapon();
            if (!(scp_wp = shCharacterGetSubCharacter(WEAPON_ID_START + weapon, -1))) break;
            shUpdateWeaponMatrixAfterAnime(scp_wp, scp_d->sc.kind);
            break;
    }

    switch (scp_d->sc.kind) {
        case HEATHER_CHARA_ID:
            func_00191660(scp_d->sc.kind);
    }
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD020);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", shCharacterExecAnimeAll);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD1D0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD290);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD2A0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD2B0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD2C0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD2D0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD2E0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD2F0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD350);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD3B0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD440);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", shCharacterAnimeSet);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD650);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD6F0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD7B0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD7C0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD800);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD840);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD850);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD8A0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD8F0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD900);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD950);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD960);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DD9F0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DDA00);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DDA90);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DDAA0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", shCharacterAnimeFrameGet);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", shCharacterAnimeFrameGet_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", shCharacterAnimeFrameSet_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DDC30);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", shCharacterAnimeCounterSet_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", func_001DDCB0);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", shCharacterAnimeGetInfo1);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", shCharacterAnimeGetInfo1_);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_sc_anime", shCharacterAnimeGetInfo2_);
