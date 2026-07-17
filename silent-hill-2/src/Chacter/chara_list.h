#ifndef SH2_CHARA_KINDS_H
#define SH2_CHARA_KINDS_H

/* ===================================================================================== */
/*                                    classification                                     */
/* ===================================================================================== */

#define HUMAN_CHARA_KIND                                                                 1
#define ENEMY_CHARA_KIND                                                                 2
#define OBJECT_SKELETAL_OUTDOOR_CHARA_KIND                                               3
#define OBJECT_ANIMATED_CHARA_KIND                                                       4
#define OBJECT_STAY_CHARA_KIND                                                           5
#define OBJECT_G_CHARA_KIND                                                              6
#define OBJECT_X_CHARA_KIND                                                              7
#define WEAPON_CHARA_KIND                                                                8

#define HUMAN_CHARA_KIND_START                                      (HUMAN_CHARA_KIND << 8)
#define ENEMY_CHARA_KIND_START                                      (ENEMY_CHARA_KIND << 8)
#define OBJECT_SKELETAL_OUTDOOR_CHARA_KIND_START  (OBJECT_SKELETAL_OUTDOOR_CHARA_KIND << 8)
#define OBJECT_ANIMATED_CHARA_KIND_START                  (OBJECT_ANIMATED_CHARA_KIND << 8)
#define OBJECT_G_CHARA_KIND_START                                (OBJECT_G_CHARA_KIND << 8)
#define OBJECT_X_CHARA_KIND_START                                (OBJECT_X_CHARA_KIND << 8)
#define OBJECT_STAY_CHARA_KIND_START                          (OBJECT_STAY_CHARA_KIND << 8)

/* ===================================================================================== */
/*                               characters (0x100 - 0x199)                              */
/* ===================================================================================== */

/* =========================== normal models (0x100 - 0x10D) =========================== */

/**
 * Lowest detail James model, used while outdoors.
 * 
 * Has hidden meshes for each hand pose on both hands.
 */
#define LLL_JMS_CHARA_KIND                                                            0x100

/**
 * Medium detail `LLL_JMS`, except it has a transparent hair mesh.
 */
#define HLL_JMS_CHARA_KIND                                                            0x101

/**
 * High-medium detail James model.
 * 
 * It has bones for James's left hand, rather than hidden meshes.
 */
#define HHL_JMS_CHARA_KIND                                                            0x102

/**
 * Highest detail James model, used during cutscenes.
 * 
 * Has facial animations, bones in both hands, and transparent hair.
 */
#define HHH_JMS_CHARA_KIND                                                            0x103

/**
 * Laura's model.
 */
#define LAU_CHARA_KIND                                                                0x104

/**
 * Low detail Maria model. Used during gameplay in main scenario, Letter From
 * Silent Heaven.
 */
#define LLL_MAR_CHARA_KIND                                                            0x105

/**
 * High detail Maria model, used during cutscenes.
 * 
 * Has transparent hair.
 */
#define HHH_MAR_CHARA_KIND                                                            0x106

/**
 * Angela's model.
 */
#define AGL_CHARA_KIND                                                                0x107

/**
 * Eddie's cutscene model.
 */
#define HHH_EDI_CHARA_KIND                                                            0x108

/**
 * Mary's model.
 */
#define MRY_CHARA_KIND                                                                0x109

/**
 * Ill Mary's model.
 *
 * She's dressed in yellow floral clothing, and the skin of her face appears to
 * be covered in sores and scabs.
 */
#define HHH_MXX_CHARA_KIND                                                            0x10a

/**
 * The boat James takes.
 */
#define BOAT_CHARA_KIND                                                               0x10b

/**
 * The evil dog that rules the world.
 */
#define INU_CHARA_KIND                                                                0x10d

/* =========================== mirror models (0x120 - 0x12D) =========================== */

#define MIRROR_MODE_CHARA_KIND_FLAG                                                (1 << 5)

/**
 * Mirror version of `LLL_JMS_CHARA_KIND`.
 */
#define RLLL_JMS_CHARA_KIND                                                           0x120

/**
 * Mirror version of `HLL_JMS_CHARA_KIND`.
 */
#define RHLL_JMS_CHARA_KIND                                                           0x121

/**
 * Mirror version of `HHL_JMS_CHARA_KIND`.
 */
#define RHHL_JMS_CHARA_KIND                                                           0x122

/**
 * Mirror version of `HHH_JMS_CHARA_KIND`.
 */
#define RHHH_JMS_CHARA_KIND                                                           0x123

/**
 * Mirror version of `LAU_CHARA_KIND`.
 */
#define RLAU_CHARA_KIND                                                               0x124

/**
 * Mirror version of `RLLL_MAR_CHARA_KIND`.
 */
#define RLLL_MAR_CHARA_KIND                                                           0x125

/**
 * Mirror version of `RHHH_MAR_CHARA_KIND`.
 */
#define RHHH_MAR_CHARA_KIND                                                           0x126

/**
 * Mirror version of `RHHH_MAR_NOTEX_CHARA_KIND`.
 */
#define RHHH_MAR_NOTEX_CHARA_KIND                                                     0x126

/**
 * Mirror version of `RHHH_MAR_CHARA_KIND`.
 */
#define RHHH_MAR_CHARA_KIND                                                           0x126

/**
 * Mirror version of `RHHH_MAR_NOTEX_CHARA_KIND`.
 */
#define RHHH_MAR_NOTEX_CHARA_KIND                                                     0x126

/**
 * Mirror version of `RAGL_CHARA_KIND`.
 */
#define RAGL_CHARA_KIND                                                               0x127

/**
 * Mirror version of `RHHH_EDI_CHARA_KIND`.
 */
#define RHHH_EDI_CHARA_KIND                                                           0x128

/**
 * Mirror version of `RMRY_CHARA_KIND`.
 */
#define RMRY_CHARA_KIND                                                               0x129

/**
 * Mirror version of `RMXX_CHARA_KIND`.
 */
#define RMXX_CHARA_KIND                                                               0x12a

/**
 * Mirror version of `RBOAT_CHARA_KIND`.
 */
#define RBOAT_CHARA_KIND                                                              0x12b

/**
 * Mirror version of `RINU_CHARA_KIND`.
 */
#define RINU_CHARA_KIND                                                               0x12d

/**
 * Mirror version of `RLXX_MAR_CHARA_KIND`.
 */
#define RLXX_MAR_CHARA_KIND                                                           0x12e

/**
 * Mirror version of `RLXX_MAR_NOTEX_CHARA_KIND`.
 */
#define RLXX_MAR_NOTEX_CHARA_KIND                                                     0x12e

/**
 * Checks whether this character kind is a James model.
 */
#define IS_PLAYER_KIND(_kind) ((_kind) >= 0x100 && (_kind) <= 0x103)

/* ===================================================================================== */
/*                                enemies (0x200 - 0x299)                                */
/* ===================================================================================== */

/**
 * Lying Figure.
 */
#define EN_SCU_CHARA_KIND                                                             0x200

/**
 * Mannequin.
 */
#define EN_MKN_CHARA_KIND                                                             0x201

/**
 * Creeper.
 */
#define EN_TYU_CHARA_KIND                                                             0x202

/**
 * Flesh Lips.
 */
#define EN_IKE_CHARA_KIND                                                             0x203

/**
 * Abstract Daddy.
 */
#define EN_PAP_CHARA_KIND                                                             0x204

/**
 * Eddie.
 */
#define EN_LLL_EDI_CHARA_KIND                                                         0x205

/**
 * Boss.
 */
#define EN_BOS_CHARA_KIND                                                             0x206

/**
 * Bubble Head Nurse.
 */
#define EN_NSE_CHARA_KIND                                                             0x207

/**
 * Pyramid Head.
 */
#define EN_RED_CHARA_KIND                                                             0x208

/**
 * Pyramid Head (with spear).
 */
#define EN_ONI_CHARA_KIND                                                             0x209

/**
 * Mandarin.
 */
#define EN_ARM_CHARA_KIND                                                             0x20a

/**
 * Otherworld Nurse.
 */
#define EN_XOO_CHARA_KIND                                                             0x20b

/**
 * Creeper (Item).
 */
#define EN_TY2_CHARA_KIND                                                             0x20c

/**
 * Baby Creepers.
 */
#define EN_TY3_CHARA_KIND                                                             0x20d

/**
 * Checks whether this character kind is an enemy model.
 */
#define IS_ENEMY_KIND(_kind) ((_kind) >= 0x200 && (_kind) < 0x300)

/**
 * Checks whether this `SubCharacter` is an enemy model.
 */
#define IS_SCP_ENEMY(_scp) (((_scp)->kind >> 8) == 2)

/* ===================================================================================== */
/*                            worldly items (0x300 - 0x399)                              */
/* ===================================================================================== */

#define ITEM_C1B_CHARA_KIND                                                           0x300
#define ITEM_C2B_CHARA_KIND                                                           0x301
#define ITEM_C3B_CHARA_KIND                                                           0x302
#define ITEM_C4B_CHARA_KIND                                                           0x303
#define ITEM_C5B_CHARA_KIND                                                           0x304
#define ITEM_C6B_CHARA_KIND                                                           0x305
#define ITEM_C7B_CHARA_KIND                                                           0x306
#define ITEM_C8B_CHARA_KIND                                                           0x307
#define ITEM_C9B_CHARA_KIND                                                           0x308
#define ITEM_CAB_CHARA_KIND                                                           0x309
#define ITEM_CBB_CHARA_KIND                                                           0x30a
#define ITEM_CCB_CHARA_KIND                                                           0x30b
#define ITEM_TLR_CHARA_KIND                                                           0x30c
#define ITEM_DHB_CHARA_KIND                                                           0x30d
#define ITEM_DHV_CHARA_KIND                                                           0x30e
#define ITEM_URA2_CHARA_KIND                                                          0x30f
#define ITEM_URA0_CHARA_KIND                                                          0x310
#define ITEM_URA1_CHARA_KIND                                                          0x311
#define ITEM_KAB_CHARA_KIND                                                           0x312
#define ITEM_URA3_CHARA_KIND                                                          0x313

/* ===================================================================================== */
/*                          collectible items (0x400 - 0x499)                            */
/* ===================================================================================== */

#define ITEM_I_KEYCOU_CHARA_KIND                                                      0x402
#define ITEM_I_RADIO_CHARA_KIND                                                       0x403
#define ITEM_I_KAKUZAI_CHARA_KIND                                                     0x404
#define ITEM_I_BEAR_CHARA_KIND                                                        0x405
#define ITEM_I_BEAR2_CHARA_KIND                                                       0x406
#define ITEM_I_FLIGHT_CHARA_KIND                                                      0x407
#define ITEM_I_LETTER_CHARA_KIND                                                      0x408
#define ITEM_B_TEL_CHARA_KIND                                                         0x409
#define ITEM_B_D00_CHARA_KIND                                                         0x40a
#define ITEM_B_REI_CHARA_KIND                                                         0x40b
#define ITEM_B_DOO_CHARA_KIND                                                         0x40c
#define ITEM_I_HANDGUN_CHARA_KIND                                                     0x40d
#define ITEM_I_MAGAZINE_CHARA_KIND                                                    0x40e
#define ITEM_I_LRING_CHARA_KIND                                                       0x40f
#define ITEM_B_D03_CHARA_KIND                                                         0x410
#define ITEM_B_PIA_CHARA_KIND                                                         0x411
#define ITEM_B_D02_CHARA_KIND                                                         0x412
#define ITEM_B_AMI_CHARA_KIND                                                         0x414
#define ITEM_PXX_CHARA_KIND                                                           0x415
#define ITEM_I_PURSE_CHARA_KIND                                                       0x416
#define ITEM_I_KEYSPE_CHARA_KIND                                                      0x417
#define ITEM_I_J_LIGHT_CHARA_KIND                                                     0x418
#define ITEM_B_D01_CHARA_KIND                                                         0x419
#define ITEM_I_MDRUG_CHARA_KIND                                                       0x41a
#define ITEM_I_MTABLET_CHARA_KIND                                                     0x41b
#define ITEM_B_ROP_CHARA_KIND                                                         0x41c
#define ITEM_I_NEEDLE_CHARA_KIND                                                      0x41d
#define ITEM_I_KEYELEVATOR_CHARA_KIND                                                 0x41e
#define ITEM_I_KEY_CLOCK_CHARA_KIND                                                   0x41f
#define ITEM_B_D05_CHARA_KIND                                                         0x420
#define ITEM_B_NIK_CHARA_KIND                                                         0x421
#define ITEM_B_CLO_CHARA_KIND                                                         0x422
#define ITEM_I_KNIFE_CHARA_KIND                                                       0x423
#define ITEM_I_PHOTO_CHARA_KIND                                                       0x424
#define ITEM_DMR_CHARA_KIND                                                           0x425
#define ITEM_B_DO4_CHARA_KIND                                                         0x426
#define ITEM_B_TAN_CHARA_KIND                                                         0x427
#define ITEM_D09_CHARA_KIND                                                           0x428
#define ITEM_B_D06_CHARA_KIND                                                         0x429
#define ITEM_I_COLT_CHARA_KIND                                                        0x42a
#define ITEM_DM2_CHARA_KIND                                                           0x42b
#define ITEM_B_DOR_CHARA_KIND                                                         0x42c
#define ITEM_I_JUICE_CHARA_KIND                                                       0x42d
#define ITEM_B_PIZ_CHARA_KIND                                                         0x42e
#define ITEM_B_BOL_CHARA_KIND                                                         0x42f
#define ITEM_I_HARI_CHARA_KIND                                                        0x430
#define ITEM_B_D08_CHARA_KIND                                                         0x431
#define ITEM_I_VIDEO_CHARA_KIND                                                       0x432
#define ITEM_I_LETTERM_CHARA_KIND                                                     0x433
#define ITEM_I_HEADPHONE_CHARA_KIND                                                   0x434
#define ITEM_B_HUL_CHARA_KIND                                                         0x435
#define ITEM_B_CHA_CHARA_KIND                                                         0x436
#define ITEM_B_STI_CHARA_KIND                                                         0x437
#define ITEM_B_D10_CHARA_KIND                                                         0x438
#define ITEM_MX2_CHARA_KIND                                                           0x439
#define ITEM_B_ORI_CHARA_KIND                                                         0x43a
#define ITEM_B_D1X_CHARA_KIND                                                         0x43b
#define ITEM_B_D8X_CHARA_KIND                                                         0x43d
#define ITEM_I_OIL_CHARA_KIND                                                         0x43e
#define ITEM_BDCARD_CHARA_KIND                                                        0x43f
#define ITEM_I_REVO_CHARA_KIND                                                        0x440
#define ITEM_RI_KNIFE_CHARA_KIND                                                      0x443
#define ITEM_RI_PHOTO_CHARA_KIND                                                      0x444
#define ITEM_RI_REVO_CHARA_KIND                                                       0x460
#define ITEM_RI_REVO_NOTEX_CHARA_KIND                                                 0x460

/* ===================================================================================== */
/*                      non-collectible decorative items (0x500 - 0x599)                 */
/* ===================================================================================== */

#define ITEM_GOM_CHARA_KIND                                                           0x506
#define ITEM_ATE_01_CHARA_KIND                                                        0x507
#define ITEM_ATE_02_CHARA_KIND                                                        0x508
#define ITEM_ATE_03_CHARA_KIND                                                        0x509
#define ITEM_ATE_04_CHARA_KIND                                                        0x50a
#define ITEM_ATE_05_CHARA_KIND                                                        0x50b
#define ITEM_B_NAT_CHARA_KIND                                                         0x50c
#define ITEM_NAT_CHARA_KIND                                                           0x50c
#define ITEM_TVC_CHARA_KIND                                                           0x50e
#define ITEM_ALI_01_CHARA_KIND                                                        0x50f
#define ITEM_ALI_02_CHARA_KIND                                                        0x510
#define ITEM_ALI_03_CHARA_KIND                                                        0x511
#define ITEM_ALI_04_CHARA_KIND                                                        0x512
#define ITEM_ALI_05_CHARA_KIND                                                        0x513
#define ITEM_BOX_CHARA_KIND                                                           0x514
#define ITEM_MNE_CHARA_KIND                                                           0x516
#define ITEM_LSI_CHARA_KIND                                                           0x517
#define ITEM_HED_CHARA_KIND                                                           0x518
#define ITEM_EVK_CHARA_KIND                                                           0x519
#define ITEM_TOM_CHARA_KIND                                                           0x51a
#define ITEM_ORI_CHARA_KIND                                                           0x51b
#define ITEM_NAK_CHARA_KIND                                                           0x51c
#define ITEM_CDA_CHARA_KIND                                                           0x51f
#define ITEM_CDB_CHARA_KIND                                                           0x520
#define ITEM_CUA_CHARA_KIND                                                           0x521
#define ITEM_CUB_CHARA_KIND                                                           0x522
#define ITEM_FAN_CHARA_KIND                                                           0x523
#define ITEM_ORG_CHARA_KIND                                                           0x524
#define ITEM_ORG_CHARA_KIND                                                           0x524
#define ITEM_B_DHA_CHARA_KIND                                                         0x525
#define ITEM_BOX_01_CHARA_KIND                                                        0x526
#define ITEM_BOX_02_CHARA_KIND                                                        0x527
#define ITEM_BAF_CHARA_KIND                                                           0x52b
#define ITEM_NEO_CHARA_KIND                                                           0x52c
#define ITEM_NEF_CHARA_KIND                                                           0x52d
#define ITEM_NEP_CHARA_KIND                                                           0x52e
#define ITEM_B_ELL_CHARA_KIND                                                         0x530
#define ITEM_B_POP_CHARA_KIND                                                         0x531
#define ITEM_3SK_CHARA_KIND                                                           0x532
#define ITEM_XAG_CHARA_KIND                                                           0x534
#define ITEM_S00_CHARA_KIND                                                           0x53b
#define ITEM_S01_CHARA_KIND                                                           0x53c
#define ITEM_S02_CHARA_KIND                                                           0x53d
#define ITEM_S03_CHARA_KIND                                                           0x53e
#define ITEM_S04_CHARA_KIND                                                           0x53f
#define ITEM_S05_CHARA_KIND                                                           0x540
#define ITEM_S06_CHARA_KIND                                                           0x541
#define ITEM_S07_CHARA_KIND                                                           0x542
#define ITEM_S08_CHARA_KIND                                                           0x543
#define ITEM_S09_CHARA_KIND                                                           0x544
#define ITEM_S0A_CHARA_KIND                                                           0x545
#define ITEM_S0B_CHARA_KIND                                                           0x546
#define ITEM_S0C_CHARA_KIND                                                           0x547
#define ITEM_S0D_CHARA_KIND                                                           0x548
#define ITEM_S0E_CHARA_KIND                                                           0x549
#define ITEM_S0F_CHARA_KIND                                                           0x54a
#define ITEM_S0G_CHARA_KIND                                                           0x54b
#define ITEM_S0H_CHARA_KIND                                                           0x54c
#define ITEM_S0I_CHARA_KIND                                                           0x54d
#define ITEM_S0J_CHARA_KIND                                                           0x54e
#define ITEM_S0K_CHARA_KIND                                                           0x54f
#define ITEM_S0L_CHARA_KIND                                                           0x550
#define ITEM_S0M_CHARA_KIND                                                           0x551
#define ITEM_S0N_CHARA_KIND                                                           0x552
#define ITEM_S0O_CHARA_KIND                                                           0x553
#define ITEM_S0P_CHARA_KIND                                                           0x554
#define ITEM_EVJ_CHARA_KIND                                                           0x556
#define ITEM_NOA_CHARA_KIND                                                           0x557
#define ITEM_NOR_CHARA_KIND                                                           0x558
#define ITEM_TRE_CHARA_KIND                                                           0x559
#define ITEM_KUM_CHARA_KIND                                                           0x55a
#define ITEM_DLG_CHARA_KIND                                                           0x55b
#define ITEM_PIZ_CHARA_KIND                                                           0x55c
#define ITEM_MAL_CHARA_KIND                                                           0x55d
#define ITEM_HOU_CHARA_KIND                                                           0x55e
#define ITEM_HIN_CHARA_KIND                                                           0x55f
#define ITEM_BAB_CHARA_KIND                                                           0x561
#define ITEM_ENX_CHARA_KIND                                                           0x565
#define ITEM_S0X_CHARA_KIND                                                           0x566
#define ITEM_S1X_CHARA_KIND                                                           0x567
#define ITEM_W1X_CHARA_KIND                                                           0x568
#define ITEM_W2X_CHARA_KIND                                                           0x569
#define ITEM_W2X_NOTEX_CHARA_KIND                                                     0x569
#define ITEM_W3X_CHARA_KIND                                                           0x56a
#define ITEM_W3X_NOTEX_CHARA_KIND                                                     0x56a
#define ITEM_W4X_CHARA_KIND                                                           0x56b
#define ITEM_W4X_NOTEX_CHARA_KIND                                                     0x56b
#define ITEM_W5X_CHARA_KIND                                                           0x56c
#define ITEM_W5X_NOTEX_CHARA_KIND                                                     0x56c
#define ITEM_W6X_CHARA_KIND                                                           0x56d
#define ITEM_W6X_NOTEX_CHARA_KIND                                                     0x56d
#define ITEM_W7X_CHARA_KIND                                                           0x56e
#define ITEM_W8X_CHARA_KIND                                                           0x56f
#define ITEM_W9X_CHARA_KIND                                                           0x570
#define ITEM_U0X_CHARA_KIND                                                           0x571
#define ITEM_B_D2X_CHARA_KIND                                                         0x572

/* ===================================================================================== */
/*                             "g" items (0x600 - 0x699)                                 */
/* ===================================================================================== */

#define ITEM_G_DRINK_CHARA_KIND                                                       0x600
#define ITEM_G_FIRSTAID_CHARA_KIND                                                    0x601
#define ITEM_G_HANDGUN_CHARA_KIND                                                     0x602
#define ITEM_G_HANDBUL_CHARA_KIND                                                     0x603
#define ITEM_G_KAKUZAI_CHARA_KIND                                                     0x604
#define ITEM_G_JLIGHT_CHARA_KIND                                                      0x605
#define ITEM_G_RADIO_CHARA_KIND                                                       0x606
#define ITEM_G_KEYPURPLE_CHARA_KIND                                                   0x607
#define ITEM_G_HAIR_CHARA_KIND                                                        0x608
#define ITEM_G_NEEDLE_CHARA_KIND                                                      0x609
#define ITEM_G_KEYELEVATOR_CHARA_KIND                                                 0x60a
#define ITEM_G_LETTERM_CHARA_KIND                                                     0x60b

/* ===================================================================================== */
/*                             "x" items (0x700 - 0x799)                                 */
/* ===================================================================================== */

#define ITEM_X_DRINK_CHARA_KIND                                                       0x700
#define ITEM_X_FIRSTAID_CHARA_KIND                                                    0x701
#define ITEM_X_HANDGUN_CHARA_KIND                                                     0x702
#define ITEM_X_HANDBUL_CHARA_KIND                                                     0x703
#define ITEM_X_KAKUZAI_CHARA_KIND                                                     0x704
#define ITEM_X_JLIGHT_CHARA_KIND                                                      0x705
#define ITEM_X_RADIO_CHARA_KIND                                                       0x706
#define ITEM_X_KEYPURPLE_CHARA_KIND                                                   0x707
#define ITEM_X_HAIR_CHARA_KIND                                                        0x708
#define ITEM_X_NEEDLE_CHARA_KIND                                                      0x709
#define ITEM_X_KEYELEVATOR_CHARA_KIND                                                 0x70a
#define ITEM_X_LETTERM_CHARA_KIND                                                     0x70b
#define ITEM_X_WAXDOLL_CHARA_KIND                                                     0x70d
#define ITEM_X_VIDEO_CHARA_KIND                                                       0x70e
#define ITEM_X_THINNER_CHARA_KIND                                                     0x70f
#define ITEM_X_SPANNER_CHARA_KIND                                                     0x710
#define ITEM_X_RINGLEAD_CHARA_KIND                                                    0x711
#define ITEM_X_RINGCOPPER_CHARA_KIND                                                  0x712
#define ITEM_X_REDRELIG_CHARA_KIND                                                    0x713
#define ITEM_X_PLIER_CHARA_KIND                                                       0x714
#define ITEM_X_PURSE_CHARA_KIND                                                       0x715
#define ITEM_X_PICTSTAND_CHARA_KIND                                                   0x716
#define ITEM_X_OIL_CHARA_KIND                                                         0x717
#define ITEM_X_SNOW_CHARA_KIND                                                        0x718
#define ITEM_X_MERMAID_CHARA_KIND                                                     0x719
#define ITEM_X_CINDERELLA_CHARA_KIND                                                  0x71a
#define ITEM_X_KEYHOS_CHARA_KIND                                                      0x71b
#define ITEM_X_COINPRISONER_CHARA_KIND                                                0x71c
#define ITEM_X_COINSNAKE_CHARA_KIND                                                   0x71d
#define ITEM_X_CUP_CHARA_KIND                                                         0x71e
#define ITEM_X_COINELDER_CHARA_KIND                                                   0x71f
#define ITEM_X_CANOPEN_CHARA_KIND                                                     0x720
#define ITEM_X_LOSTMEMORY_CHARA_KIND                                                  0x721
#define ITEM_X_KEYGATE_CHARA_KIND                                                     0x722
#define ITEM_X_RIFLEBUL_CHARA_KIND                                                    0x723
#define ITEM_X_SHOTBUL_CHARA_KIND                                                     0x724
#define ITEM_X_MAGAZINE_CHARA_KIND                                                    0x725
#define ITEM_X_KEYBRONZE_CHARA_KIND                                                   0x726
#define ITEM_X_BEAR_CHARA_KIND                                                        0x727
#define ITEM_X_KEYRAPIS_CHARA_KIND                                                    0x728
#define ITEM_X_KEYROOF_CHARA_KIND                                                     0x729
#define ITEM_X_KEYBASE_CHARA_KIND                                                     0x72a
#define ITEM_X_BATTERY_CHARA_KIND                                                     0x72b
#define ITEM_X_KEYEMERG_CHARA_KIND                                                    0x72c
#define ITEM_X_JUICE_CHARA_KIND                                                       0x72d
#define ITEM_X_KEYCLOCK_CHARA_KIND                                                    0x72e
#define ITEM_X_KEY202_CHARA_KIND                                                      0x72f
#define ITEM_X_KEYNORTH_CHARA_KIND                                                    0x730
#define ITEM_X_KEYLYNE_CHARA_KIND                                                     0x731
#define ITEM_X_KEYCOURT_CHARA_KIND                                                    0x732
#define ITEM_X_AMPLE_CHARA_KIND                                                       0x733
#define ITEM_X_LIGHTBULB_CHARA_KIND                                                   0x734
#define ITEM_X_KEYBAR_CHARA_KIND                                                      0x735
#define ITEM_X_KEYFISH_CHARA_KIND                                                     0x736
#define ITEM_X_PLATE_PIG_CHARA_KIND                                                   0x737
#define ITEM_X_PLATE_KICK_CHARA_KIND                                                  0x738
#define ITEM_X_PLATE_FEMALE_CHARA_KIND                                                0x739
#define ITEM_X_HORSE_CHARA_KIND                                                       0x73a
#define ITEM_X_WP_RIFLGUN_CHARA_KIND                                                  0x73b
#define ITEM_X_LIGHTER_CHARA_KIND                                                     0x73c
#define ITEM_X_KEY312_CHARA_KIND                                                      0x73d
#define ITEM_X_KEYEMPLOY_CHARA_KIND                                                   0x73e
#define ITEM_X_KEYSPIRAL_CHARA_KIND                                                   0x73f
#define ITEM_X_EGGRUST_CHARA_KIND                                                     0x740
#define ITEM_X_EGGRED_CHARA_KIND                                                      0x741
#define ITEM_X_KEYFALSE_CHARA_KIND                                                    0x742
#define ITEM_X_WP_SHOTGUN_CHARA_KIND                                                  0x743
#define ITEM_X_WP_SP_CHARA_KIND                                                       0x744
#define ITEM_X_WP_PIPE_CHARA_KIND                                                     0x745
#define ITEM_X_WP_CSAW_CHARA_KIND                                                     0x746
#define ITEM_X_KEY3F_CHARA_KIND                                                       0x747
#define ITEM_X_BIRTHDAY_CHARA_KIND                                                    0x748
#define ITEM_X_BULLET_RIVOLVER_CHARA_KIND                                             0x749
#define ITEM_X_BULLT_REVOLVER_CHARA_KIND                                              0x749
#define ITEM_X_CHINANIFE_CHARA_KIND                                                   0x74a
#define ITEM_X_COSMOS_CHARA_KIND                                                      0x74b
#define ITEM_X_HOUBAN_BLACK_CHARA_KIND                                                0x74c
#define ITEM_X_HOUBAN_RED_CHARA_KIND                                                  0x74d
#define ITEM_X_HOUBAN_WHITE_CHARA_KIND                                                0x74e
#define ITEM_X_KEYACACIA_CHARA_KIND                                                   0x74f
#define ITEM_X_MACH_CHARA_KIND                                                        0x750
#define ITEM_X_REVOLVER_CHARA_KIND                                                    0x751
#define ITEM_X_PRESENT_CHARA_KIND                                                     0x752
#define ITEM_X_SEKIHI_WHITE_CHARA_KIND                                                0x753
#define ITEM_X_SEKIHI_BLACK_CHARA_KIND                                                0x754
#define ITEM_X_SEKIHI_RED_CHARA_KIND                                                  0x755


/* ===================================================================================== */
/*                                weapons (0x800 - 0x899)                                */
/* ===================================================================================== */

#define WEAPON_ID_START                                                               0x800
#define WEAPON_HANDGUN_CHARA_KIND                                                     0x801
#define WEAPON_SHOTGUN_CHARA_KIND                                                     0x802
#define WEAPON_RIFLGUN_CHARA_KIND                                                     0x803
#define WEAPON_SP_CHARA_KIND                                                          0x804
#define WEAPON_KAKUZAI_CHARA_KIND                                                     0x805
#define WEAPON_PIPE_CHARA_KIND                                                        0x806
#define WEAPON_CSAW_CHARA_KIND                                                        0x807
#define WEAPON_NATA_CHARA_KIND                                                        0x808
#define WEAPON_COLT_CHARA_KIND                                                        0x809
#define WEAPON_CHINANIFE_CHARA_KIND                                                   0x80a
#define RWEAPON_HANDGUN_CHARA_KIND                                                    0x821
#define RWEAPON_SHOTGUN_CHARA_KIND                                                    0x822
#define RWEAPON_RIFLGUN_CHARA_KIND                                                    0x823
#define RWEAPON_SP_CHARA_KIND                                                         0x824
#define RWEAPON_KAKUZAI_CHARA_KIND                                                    0x825
#define RWEAPON_PIPE_CHARA_KIND                                                       0x826
#define RWEAPON_CSAW_CHARA_KIND                                                       0x827
#define RWEAPON_NATA_CHARA_KIND                                                       0x828
#define RWEAPON_COLT_CHARA_KIND                                                       0x829
#define RWEAPON_COLT_NOTEX_CHARA_KIND                                                 0x829
#define RWEAPON_CHINANIFE_CHARA_KIND                                                  0x82a
#define RWEAPON_CHINANIFE_NOTEX_CHARA_KIND                                            0x82a

#define WEAPON_ID(_kind)                                                    ((_kind) & 0xff)

#endif // SH2_CHARA_KINDS_H
