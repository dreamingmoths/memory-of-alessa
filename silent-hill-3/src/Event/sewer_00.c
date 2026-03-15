#include "sewer_00.h"

int func_01F6D680_sewer_00(void) {
  int ret;
  float t;
  Q data0;
  Q data1;

  switch (D_01F6FE00_sewer_00) {
  case 0:
    func_00316C50(0);
    func_0016ECE0(2);
    func_001C2290(2, 0.0f);
    D_01F6FE00_sewer_00 += 1;
  }

  ret = func_0016C540(D_01F6FB60_sewer_00, D_01F6FBC0_sewer_00);
  t = func_001643C0();

  if (t < 64.0f) {
    func_0013D250(0, D_01F6F8F0_sewer_00, 1.0f);
  }

  switch (D_01F6FE00_sewer_00) {
  case 1:
    if (t >= 65.0f) {
      func_0013D250(0, D_01F6F930_sewer_00, 1.0f);
      D_01F6FE00_sewer_00++;
    }
    break;
  case 2:
    if (t >= 98.0f) {
      func_0013D250(0, D_01F6F9A0_sewer_00, 1.0f);
      D_01F6FE00_sewer_00++;
    }
    break;
  }

  if (func_001646F0() == 2) {
    data0 = D_01F6FBE0_sewer_00;
    data1 = D_01F6FE10_sewer_00;
    func_001DA020(1, &data0, &data1);
  }

  if (ret != 0) {
    func_0013D280(0);
    D_01F6FE00_sewer_00 = 0;
    func_001C2290(5, 0.8f);
  }

  return ret;
}

int func_01F6D870_sewer_00(void) {
  switch (D_01F6FE00_sewer_00) {
  case 0:
    func_00190A20(2);
    func_0016CD00(D_01F6FBF0_sewer_00);
    func_001C2290(3, 0.8f);
    D_01F6FE00_sewer_00 = 1;
  case 1:
    if (func_001C2580(2) == 0) {
      return 0;
    }
    D_01F6FE00_sewer_00 = 2;
    func_001C2290(5, 0.8f);
  case 2:
    if (func_0016BED0(0xC3, 0x22) == 0) {
      return 0;
    }
    D_01F6FE00_sewer_00 = 3;
    func_001C2290(5, 0.8f);
  case 3:
    func_00190A20(0);
  default:
    D_01F6FE00_sewer_00 = 0;
    return 1;
  }
}

int func_01F6D980_sewer_00(void) {
  switch (D_01F6FE60_sewer_00) {
  case 0:
    func_0016C3C0();
    func_00190A20(2);
    D_01F6FE60_sewer_00 += 1;
    func_00317420(0x34);
    SeCall(1.0f, 0.0f, 0x2B21);
  case 1:
    if (func_0016C1C0(0x45) == 0) {
      return 0;
    }
    func_0016C3C0();
    D_01F6FE60_sewer_00 += 1;
    SeCall(1.0f, 0.0f, 0x2B21);
    func_00317490(0x34, 0.2f);
  case 2:
    if (func_0016C1C0(0x46) == 0) {
      return 0;
    }
    func_00190A20(0);
    D_01F6FE60_sewer_00 = 0;
    func_003174B0(0.2f);
    goto ret1;
  }

  goto ret1;

ret1:
  return 1;
}

int func_01F6DAB0_sewer_00(void) {
  sceVu0FMATRIX sp10;
  SubCharacter *heather;

loop:
  switch (D_01F6FE20_sewer_00) {
  case 0:
    func_00190A20(2);
    if ((D_1D31664 >> 2) & 1) {
      func_001C2290(2, 0.0f);
      D_01F6FE20_sewer_00 = 3;
      goto loop;
    }
    D_01F6FE20_sewer_00 += 1;
  case 1:
    if (func_0016C1C0(0x19) == 0) {
      return 0;
    }
    func_0016C3C0();
    if (func_0016CB70() == 0) {
      if ((D_1D31660 >> 21) & 1) {
        func_001C2290(3, 0.8f);
        D_01F6FE20_sewer_00 = 3;
        func_0013D250(0, D_01F6F9F0_sewer_00, 1.0f);
        D_1D31664 |= 4;
        func_00316C50(0);
        SeCall(1.0f, 0.0f, 0x3200);
        D_01F6FE30_sewer_00 = func_0016E0F0();
        goto loop;
      }
      D_01F6FE20_sewer_00 += 1;
      goto loop;
    }
    D_01F6FE20_sewer_00 = 4;
    goto loop;
  case 2:
    if ((D_1D31660 >> 24) & 1) {
      if (func_0016C1C0(0x1B) == 0) {
        return 0;
      }
      func_0016C3C0();
      D_01F6FE20_sewer_00 = 4;
      goto loop;
    } else {
      if (func_0016C1C0(0x1A) == 0) {
        return 0;
      }
      func_0016C3C0();
      D_01F6FE20_sewer_00 = 4;
      goto loop;
    }
  case 3:
    if (func_0016C540(D_01F6FC00_sewer_00, D_01F6FC60_sewer_00) == 0) {
      D_01F6FE28_sewer_00 = 1;
      heather = shCharacterGetSubCharacter(HEATHER_CHARA_ID, -1);
      func_001DC9E0(heather, 0);
      if (func_001643C0() >= 10.0f) {
        func_0013D250(0, D_01F6FA30_sewer_00, 1.0f);
      }
      return 0;
    }
    heather = shCharacterGetSubCharacter(HEATHER_CHARA_ID, -1);
    func_001DC9E0(heather, 1);
    func_0016D0E0(0x3202, D_01F6FE58_sewer_00);
    D_01F6FE58_sewer_00 = -1;
    func_0016E400(0x22, D_01F6FE30_sewer_00);
    func_0013D280(0);
    D_1D31644 |= 0x04000000;
    D_1D31660 |= 0x00100000;
    sceVu0UnitMatrix(sp10);
    sp10[3][0] = 0.0f;
    sp10[3][1] = 0.0f;
    sp10[3][2] = 0.0f;
    sp10[3][3] = 0.0f;
    func_001C2A80(1, sp10);
    func_001C2A80(2, sp10);
    func_001C2A80(3, sp10);
    D_01F6FE20_sewer_00 = 4;
    func_001C2290(5, 0.8f);
  case 4:
    D_01F6FE28_sewer_00 = 0;
    func_0016C3C0();
    func_00190A20(0);
    D_01F6FE20_sewer_00 = 0;
    return 1;
  }

  goto loop;
}

INCLUDE_ASM("asm/nonmatchings/Event/sewer_00", func_01F6DE40_sewer_00);

INCLUDE_ASM("asm/nonmatchings/Event/sewer_00", func_01F6DEC0_sewer_00);

INCLUDE_ASM("asm/nonmatchings/Event/sewer_00", func_01F6E060_sewer_00);

INCLUDE_ASM("asm/nonmatchings/Event/sewer_00", func_01F6E130_sewer_00);

INCLUDE_ASM("asm/nonmatchings/Event/sewer_00", func_01F6E270_sewer_00);
