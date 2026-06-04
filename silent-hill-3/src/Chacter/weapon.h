#ifndef SH3_WEAPON_H
#define SH3_WEAPON_H

/* from 0x001a84c0 */
#define WEAPON_NONE             0x0
#define WEAPON_HANDGUN          0x1
#define WEAPON_RIFLE            0x2
#define WEAPON_SUBMACHINE_GUN   0x3
#define WEAPON_KNIFE            0x4
#define WEAPON_STEEL_PIPE       0x5
#define WEAPON_KATANA           0x6
#define WEAPON_MAUL             0x7
#define WEAPON_STUN_GUN         0x8
#define WEAPON_LIGHT_SABER      0x9
#define WEAPON_FLAMETHROWER     0xA
#define WEAPON_GOLD_PIPE        0xD
#define WEAPON_SILVER_PIPE      0xE
#define WEAPON_SILENCED_HANDGUN 0xF
#define WEAPON_SILENCED_SMG     0x10
#define WEAPON_UNLIMITED_SMG    0x11
#define WEAPON_SILENCED_USMG    0x12

/* weapon IDs from 0x1D30B12; unclear purpose */
#define EQUIPPED_WEAPON_NONE           0x4
#define EQUIPPED_WEAPON_HANDGUN        0x5
#define EQUIPPED_WEAPON_SUBMACHINE_GUN 0x6
#define EQUIPPED_WEAPON_SHOTGUN        0x7
#define EQUIPPED_WEAPON_KNIFE          0x8
#define EQUIPPED_WEAPON_PIPE           0x9
#define EQUIPPED_WEAPON_MAUL           0xA
#define EQUIPPED_WEAPON_STUN_GUN       0xB
#define EQUIPPED_WEAPON_KATANA         0xC
#define EQUIPPED_WEAPON_BEAM_SABER     0xD
#define EQUIPPED_WEAPON_FLAMETHROWER   0xE

#define WP_HGUN_CHARA_ID   0x801
#define WP_SHO_CHARA_ID    0x802
#define WP_SUB_CHARA_ID    0x803
#define WP_KNIFE_CHARA_ID  0x804
#define WP_PIPE_CHARA_ID   0x805
#define WP_SWO_CHARA_ID    0x806
#define WP_HUM_CHARA_ID    0x807
#define WP_STU_CHARA_ID    0x808
#define WP_LIG_CHARA_ID    0x809
#define WP_FIR_CHARA_ID    0x80a
#define WP_PIPEG_CHARA_ID  0x80d
#define WP_PIPES_CHARA_ID  0x80e
#define WP_HGUNS_CHARA_ID  0x80f
#define WP_SUBS_CHARA_ID   0x810
#define WP_U_SUB_CHARA_ID  0x811
#define WP_U_SUBS_CHARA_ID 0x812

#endif // SH3_WEAPON_H
