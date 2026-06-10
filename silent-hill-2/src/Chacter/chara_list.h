#ifndef SH2_CHARA_KINDS_H
#define SH2_CHARA_KINDS_H

/* ===================================================================================== */
/*                               characters (0x100 - 0x199)                              */
/* ===================================================================================== */
#define LLL_JMS_CHARA_ID      0x100 // lowest detail James model
#define HLL_JMS_CHARA_ID      0x101
#define HHL_JMS_CHARA_ID      0x102
#define HHH_JMS_CHARA_ID      0x103 // highest detail James model

#define CHR_RLLL_JMS_CHARA_ID 0x120 // lowest detail mirror James model
#define CHR_RHLL_JMS_CHARA_ID 0x121
#define CHR_RHHL_JMS_CHARA_ID 0x122
#define CHR_RHHH_JMS_CHARA_ID 0x123 // highest detail mirror James model

#define LAU_CHARA_ID          0x104 // Laura

#define LLL_MAR_CHARA_ID      0x105 // low detail Maria model
#define HHH_MAR_CHARA_ID      0x106 // high detail Maria model

#define AGL_CHARA_ID          0x107 // Angela

#define BOAT_CHARA_ID         0x10B

#define IS_PLAYER_KIND(_kind) ((_kind) >= 0x100 && (_kind) <= 0x103)

/* ===================================================================================== */
/*                                enemies (0x200 - 0x299)                                */
/* ===================================================================================== */

// Lying Figure
#define EN_SCU_CHARA_ID     0x200

// Mannequin
#define EN_MKN_CHARA_ID     0x201

// Creeper
#define EN_TYU_CHARA_ID     0x202

// Flesh Lips
#define EN_IKE_CHARA_ID     0x203

// Abstract Daddy
#define EN_PAP_CHARA_ID     0x204

// Eddie
#define EN_LLL_EDI_CHARA_ID 0x205

// Boss
#define EN_BOS_CHARA_ID     0x206

// Bubble Head Nurse
#define EN_NSE_CHARA_ID     0x207

// Pyramid Head
#define EN_RED_CHARA_ID     0x208

// Pyramid Head (with spear)
#define EN_ONI_CHARA_ID     0x209

// Mandarin
#define EN_ARM_CHARA_ID     0x20a

// Otherworld Nurse
#define EN_XOO_CHARA_ID     0x20b

// Creeper (Item)
#define EN_TY2_CHARA_ID     0x20c

// Baby Creepers
#define EN_TY3_CHARA_ID     0x20d

#define IS_ENEMY_KIND(_kind) ((_kind) >= 0x200 && (_kind) < 0x300)

/* ===================================================================================== */
/*                                weapons (0x800 - 0x899)                                */
/* ===================================================================================== */

#define WEAPON_ID_START 0x800

#endif // SH2_CHARA_KINDS_H
