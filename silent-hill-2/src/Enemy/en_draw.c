#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/sh2sys.h"

#include "gs.h"
#include "vec.h"
#include "sce/libgraph.h"

#include "Fog/spack.h"

#include "Collision/cl_main.h"

#include "Chacter/character.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_play.h"
#include "Chacter/m3_sc.h"

#include "Enemy/en_common.h"

#include "LoadBg/loadbg_cld.h"

static void enDrawTriangle(sceVu0FVECTOR pos, float rot, u_int color, float size);
static void enDrawBox(sceVu0FVECTOR pos, float rot, u_int color, float size1, float size2);
static void enDrawWall(sceVu0FVECTOR wall_pos1, sceVu0FVECTOR wall_pos2, sceVu0FVECTOR ppos, float prot);
static void enDrawColumn(sceVu0FVECTOR column_pos, float size, sceVu0FVECTOR ppos, float prot);

float view_rate = 0.0f;

#define EN_DRAW_ORIGIN_X ((int) X_COORD(-1568))
#define EN_DRAW_ORIGIN_Y ((int) Y_COORD(-1948))
#define enDrawX(value)   (EN_DRAW_ORIGIN_X + shVu0FloatToInt((value) / view_rate + 2048.0f))
#define enDrawY(value)   (EN_DRAW_ORIGIN_Y + shVu0FloatToInt((value) / view_rate * SCREEN_ASPECT_RATIO + 2048.0f))

void enDrawRadar(void) {
    EnLOCAL_DATA* dp; // r16
    int i; // r17
    float* ppos = (float*) &GetPlayerInfoForCameraCtrl()->pos; // r2
    float pr; // r20
    sceVu0FVECTOR vec; // r29+0xB0
    float rot; // r29+0xC0
    u_long c; // r5

    if (!playing.radar || GET_BIT(Sh2sys.main_status, 6)) return;
    view_rate = (playing.radar & 1) ? 60.0f : 90.0f;
    if (playing.radar < 3) {
        pr = -((shCharaInfo*) ppos)->rot.y - QUARTER_TURN; // ????????????
    } else {
        switch (RoomNameJms()) {
            case 1:
                pr = PI;
                break;
            default:
                pr = -QUARTER_TURN;
        }
    }
    
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -2, 0);
    spkAddressData(SCE_GS_SET_ALPHA(0, 1, 0, 1, 0), SCE_GS_ALPHA_1);
    spkAddressData(SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1), SCE_GS_TEST_1);
    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 15), 
                       GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZ3, SCE_GS_XYZ2, SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZ3, SCE_GS_XYZ2, SCE_GS_XYZ2, SCE_GS_XYZ2, SCE_GS_XYZ2, SCE_GS_XYZ2, SCE_GS_XYZ2, SCE_GS_XYZ2, SCE_GS_XYZ2));
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(0, 0, 0, 16, FLOAT_ONE);
    (*spack.pos++) = SCE_GS_SET_XYZ3(X_COORD(441), Y_COORD(61), 0);
    
    (*spack.pos++) = SCE_GS_SET_XYZ2(X_COORD(519), Y_COORD(139), 0);
    
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);;
    (*spack.pos++) = SCE_GS_SET_RGBAQ(128, 128, 128, 64, FLOAT_ONE);
    (*spack.pos++) = SCE_GS_SET_XYZ3(X_COORD(440), Y_COORD(60), 0);
    
    (*spack.pos++) = SCE_GS_SET_XYZ2(X_COORD(520), Y_COORD(60), 0);
    
    (*spack.pos++) = SCE_GS_SET_XYZ2(X_COORD(520), Y_COORD(140), 0);
    
    (*spack.pos++) = SCE_GS_SET_XYZ2(X_COORD(440), Y_COORD(140), 0);
    
    (*spack.pos++) = SCE_GS_SET_XYZ2(X_COORD(440), Y_COORD(59), 0);
    
    (*spack.pos++) = SCE_GS_SET_XYZ2(X_COORD(521), Y_COORD(59), 0);
    
    (*spack.pos++) = SCE_GS_SET_XYZ2(X_COORD(521), Y_COORD(141), 0);

    (*spack.pos++) = SCE_GS_SET_XYZ2(X_COORD(439), Y_COORD(141), 0);

    (*spack.pos++) = SCE_GS_SET_XYZ2(X_COORD(439), Y_COORD(59), 0);

    spkCloseOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
    spkAddressData(SCE_GS_SET_SCISSOR(377, 455, 77, 155), SCE_GS_SCISSOR_1);
    
    
    
    spkCloseGiftag();

    dp = enLocalWork.Data;
    for (i = 0; i < ENEMY_MAX; i++, dp++) {
        if (dp->kind && dp->scp->status & (1 << SCP_STATUS_BIT_4)) {
            shSubVector(vec, (float*) &dp->scp->pos, ppos);
            if (shFloatAbs(vec[0]) > 750.0f * view_rate || shFloatAbs(vec[2]) > 750.0f * view_rate) continue;
                
            shRotVectorY(vec, vec, pr);
            rot = dp->scp->rot.y + pr;
            if (dp->scp->battle.status & DEAD_FLAG) {
                c = SCE_GS_SET_RGBAQ(16, 16, 16, 96, 0);
            } else {
                c = SCE_GS_SET_RGBAQ(48, 255, 48, 64, 0);
            }
            switch (dp->kind) {
                case EnKIND_SCU:
                case EnKIND_MKN:
                case EnKIND_TYU:
                case EnKIND_RED:
                case EnKIND_ONI:
                case EnKIND_NSE:
                case EnKIND_EDB:
                case EnKIND_ARM:
                    enDrawTriangle(vec, rot, c, dp->size);
                    break;
                case EnKIND_IKE:
                    enDrawBox(vec, rot, (u_long) c, 1.2f * dp->size, dp->size); // @hack weird casts needed for match
                    
                    break;
                case EnKIND_PAP:
                    enDrawBox(vec, rot, (u_long) c, 0.5f * dp->size, 0.8f * dp->size);
                    
                    break;
                case EnKIND_BOS:
                    enDrawBox(vec, rot, c, dp->size * 0.8f, 0.5f * dp->size);
                    
                    break;
                case EnKIND_NIK:
                    break;
                case EnKIND_INS:
                    enDrawTriangle(vec, rot, c, 100.0f);
                    break;
                default:
                    enDrawTriangle(vec, rot, SCE_GS_SET_RGBAQ(0, 0, 0, 0, 0), dp->size);
                    break;
            }
        }
    }

    if (playing.radar < 3) {
        rot = -QUARTER_TURN;
    } else {
        rot = ((shCharaInfo*) ppos)->rot.y + pr; // ???????????? @hack
    } {    
        u_long color = SCE_GS_SET_RGBAQ(48, 255, 48, 64, 0); // @hack, not in dwarf
        shVectorZero(vec);
        enDrawTriangle(vec, rot, c = color, 200.0f);
    } {
        void** cl_list; /* r16 */ void* list_backup; /* r30 */
        CL_CLDHEADER* ch; // r17
        CL_HITPOLY_PLANE* wall, *pl; // r18, r19
        CL_HITPOLY_COLUMN* clmn, *pl2; // r18, r2
        int* ptr; /* r20 */ int act, usemax, kind, n; // r2, r16, r3, r21
        SubCharacter* mp = NULL; // r23
        CL_CLDHEADER** var_v0; // ? need a var for v0
        list_backup = cl_list = loadBgCLD_GetLoadedDataAddrList();
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 4), 
                       GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZ3, SCE_GS_XYZ2), -3, 4);

        for (; var_v0 = cl_list++, ch = *var_v0, ch != NULL; ) {
            if (ch->disable)
                continue;
            wall = (u_char*) ch + ch->wldofs;
            for (n = 0; n < 16; n++) {
                ptr = (int*) ((u_char*) ch + ch->b1ofs[n]);
                while (*ptr != -1) {
                    pl = &wall[*ptr];
                    if (pl->shape == 0) { // trongle?
                        enDrawWall(pl->p[0], pl->p[1], ppos, pr);
                        enDrawWall(pl->p[1], pl->p[2], ppos, pr);
                        enDrawWall(pl->p[2], pl->p[0], ppos, pr);
                    } else {
                        enDrawWall(pl->p[0], pl->p[1], ppos, pr);
                        enDrawWall(pl->p[1], pl->p[2], ppos, pr);
                        enDrawWall(pl->p[2], pl->p[3], ppos, pr);
                        enDrawWall(pl->p[3], pl->p[0], ppos, pr);
                    }
                    ptr++;
                }
            }

            wall = (u_char*) ch + ch->swdofs;
            for (n = 0; n < 16; n++) {
                ptr = (int*) ((u_char*) ch + ch->b3ofs[n]);
                while (*ptr != -1) {
                    pl = &wall[*ptr];
                    if (pl->shape == 0) { // trongle?
                        enDrawWall(pl->p[0], pl->p[1], ppos, pr);
                        enDrawWall(pl->p[1], pl->p[2], ppos, pr);
                        enDrawWall(pl->p[2], pl->p[0], ppos, pr);
                    } else {
                        enDrawWall(pl->p[0], pl->p[1], ppos, pr);
                        enDrawWall(pl->p[1], pl->p[2], ppos, pr);
                        enDrawWall(pl->p[2], pl->p[3], ppos, pr);
                        enDrawWall(pl->p[3], pl->p[0], ppos, pr);
                    }
                    ptr++;
                }
            }
        }

        act = clDynamicWallListAct ? 0 : 1;
        for (i = 0; i < clDynamicWallList[act].use; i++) {
            pl = clDynamicWallList[act].dw[i];
            while (pl->kind != 0) {
                if (pl->shape == 0) { // trongle?
                    enDrawWall(pl->p[0], pl->p[1], ppos, pr);
                    enDrawWall(pl->p[1], pl->p[2], ppos, pr);
                    enDrawWall(pl->p[2], pl->p[0], ppos, pr);
                } else {
                    enDrawWall(pl->p[0], pl->p[1], ppos, pr);
                    enDrawWall(pl->p[1], pl->p[2], ppos, pr);
                    enDrawWall(pl->p[2], pl->p[3], ppos, pr);
                    enDrawWall(pl->p[3], pl->p[0], ppos, pr);
                }
                pl++;
            }
        }
        spkCloseGiftag();
        
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 6),
                       GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZ3, SCE_GS_XYZ2, SCE_GS_XYZ2, SCE_GS_XYZ2), -3, 4);

        cl_list = list_backup;        
        for (; var_v0 = cl_list++, ch = *var_v0, ch != NULL; ) {
            if (ch->disable) continue;
            clmn = (u_char*) ch + ch->cldofs;
            for (n = 0; n < 16; n++) {
                ptr = (int*) ((u_char*) ch + ch->clofs[n]);
                while (*ptr != -1) {
                    pl2 = &clmn[*ptr];
                    enDrawColumn(pl2->p[0], pl2->p[1][3], ppos, pr);
                    ptr++;
                }
            }
        }
        
        act = clCharaListAct ? 0 : 1;
        usemax = clCharaListUse[act];
        for (i = 0; i < usemax; i++) {
            kind = clCharaList[act][i].sc->kind;
            if ((kind >= LLL_JMS_CHARA_KIND && 
                kind <= HHH_JMS_CHARA_KIND) || 
                (kind >= EN_SCU_CHARA_KIND && 
                 kind <= EN_XOO_CHARA_KIND)) continue;
            if (kind == LLL_MAR_CHARA_KIND) {
                mp = clCharaList[act][i].sc;
            } else {
                
                enDrawColumn(clCharaList[act][i].col.p[0], clCharaList[act][i].col.p[1][3], ppos, pr);
            }
        }
        spkCloseGiftag();
        if (mp) {
            shSubVector(vec, (float*) &mp->pos, ppos);
            if (shFloatAbs(vec[0]) <= 750.0f * view_rate && shFloatAbs(vec[2]) <= 750.0f * view_rate) {
              
                shRotVectorY(vec, vec, pr);
                rot = mp->rot.y + pr;
                enDrawTriangle(vec, rot, SCE_GS_SET_RGBAQ(192, 48, 192, 64, 0), 150.0f);
            }
        }
    }

    
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -5, 0);
    spkAddressData(SCE_GS_SET_SCISSOR(0, 511, 0, 511), SCE_GS_SCISSOR_1);
    
    spkCloseGiftag();
}

#line 1201
static void enDrawWall(sceVu0FVECTOR wall_pos1, sceVu0FVECTOR wall_pos2, sceVu0FVECTOR ppos, float prot) {
    sceVu0FVECTOR vec, vec2;
    sceVu0IVECTOR scr;
    u_long xyz;
    if (wall_pos1[0] == wall_pos2[0] && wall_pos1[2] == wall_pos2[2]) return;
    shVectorZero(scr);
    shSubVector(vec, wall_pos1, ppos);
    shSubVector(vec2, wall_pos2, ppos);
    shRotVectorY(vec, vec, prot);
    scr[2] = 0xfffffe;
    scr[0] = enDrawX(vec[2]);
    scr[1] = enDrawY(vec[0]);
    if (scr[0] < 0 || scr[1] < 0 || scr[0] > 65535 || scr[1] > 65535) return;
    xyz = shFastPackXyz(shVectorQWord(scr));
    shRotVectorY(vec2, vec2, prot);
    scr[0] = enDrawX(vec2[2]);
    scr[1] = enDrawY(vec2[0]);
    if (scr[0] < 0 || scr[1] < 0 || scr[0] > 65535 || scr[1] > 65535) return;
    
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINE, 0, 0, 0, SCE_GS_TRUE /* alpha blend */, 0, 0, 0, 0);
    if ((vec[1] > 250.0f && vec2[1] > 250.0f) || (vec[1] < -250.0f && vec2[1] < -250.0f)) {
        (*spack.pos++) = SCE_GS_SET_RGBAQ(0, 192, 64, 32, 0);            
    } else {
        (*spack.pos++) = SCE_GS_SET_RGBAQ(0, 80, 255, 64, 0);
    }
    (*spack.pos++) = xyz;
    (*spack.pos++) = shFastPackXyz(shVectorQWord(scr));
}

#line 1233
static void enDrawColumn(sceVu0FVECTOR column_pos, float size, sceVu0FVECTOR ppos, float prot) {
    sceVu0FVECTOR vec, vec2;
    sceVu0IVECTOR scr;
    u_long xyz1, xyz2, xyz3;
    shVectorZero(scr);
    scr[2] = 0xfffffe;
    shSubVector(vec, column_pos, ppos);
    shVectorCopy(vec2, vec);
    vec2[0] -= size;
    shRotVectorY(vec2, vec2, prot);
    scr[0] = enDrawX(vec2[2]);
    scr[1] = enDrawY(vec2[0]);
    if (scr[0] < 0 || scr[1] < 0 || scr[0] > 65535 || scr[1] > 65535) return;
    xyz1 = shFastPackXyz(shVectorQWord(scr));
    shVectorCopy(vec2, vec);
    vec2[2] += size;
    shRotVectorY(vec2, vec2, prot);
    scr[0] = enDrawX(vec2[2]);
    scr[1] = enDrawY(vec2[0]);
    if (scr[0] < 0 || scr[1] < 0 || scr[0] > 65535 || scr[1] > 65535) return;
    xyz2 = shFastPackXyz(shVectorQWord(scr));
    shVectorCopy(vec2, vec);
    vec2[2] -= size;
    shRotVectorY(vec2, vec2, prot);
    scr[0] = enDrawX(vec2[2]);
    scr[1] = enDrawY(vec2[0]);
    if (scr[0] < 0 || scr[1] < 0 || scr[0] > 65535 || scr[1] > 65535) return;
    xyz3 = shFastPackXyz(shVectorQWord(scr));
    shVectorCopy(vec2, vec);
    vec2[0] += size;
    shRotVectorY(vec2, vec2, prot);
    scr[0] = enDrawX(vec2[2]);
    scr[1] = enDrawY(vec2[0]);
    if (scr[0] < 0 || scr[1] < 0 || scr[0] > 65535 || scr[1] > 65535) return;
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blend */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(0, 80, 255, 64, 0);
    (*spack.pos++) = xyz1;
    (*spack.pos++) = xyz2;
    (*spack.pos++) = xyz3;
    (*spack.pos++) = shFastPackXyz(shVectorQWord(scr));
}

#line 1278
static void enDrawTriangle(sceVu0FVECTOR pos, float rot, u_int color, float size) {
    float x, y, dx, dy;
    x = pos[2];
    y = pos[0];
    dx = shCosF(rot) * size;
    dy = shSinF(rot) * size;
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 5), 
                   GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZ3, SCE_GS_XYZ3, SCE_GS_XYZ2), -4, 4);
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 0, 0, 0, SCE_GS_TRUE /* alpha blend */, 0, 0, 0, 0);
    (*spack.pos++) = color;
    (*spack.pos++) = SCE_GS_SET_XYZ3(enDrawX(x + dx),
                                     enDrawY(y + dy), 
                                     0xffffff);
    (*spack.pos++) = SCE_GS_SET_XYZ3(enDrawX(x - dx + dy),
                                     enDrawY(y - dy - dx),
                                     0xffffff);
    (*spack.pos++) = SCE_GS_SET_XYZ2(enDrawX(x - dx - dy),
                                     enDrawY(y - dy + dx),
                                     0xffffff);
    spkCloseGiftag();
}


/*

let dx = cos θ, dy = sin θ

┌          ┐ ┌   ┐    ┌                  ┐
│  dx  dy  │ │ x │    │  dx * x + dy * y │
│          │ │   │ =  │                  │
│ -dy  dx  │ │ y │    │ -dy * x + dx * y │
└          ┘ └   ┘    └                  ┘

*/
#line 1303
static void enDrawBox(sceVu0FVECTOR pos, float rot, u_int color, float size1, float size2) {
    float x, y, dx, dy;
    x = pos[2];
    y = pos[0];
    dx = shCosF(rot);
    dy = shSinF(rot);
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 6), 
                   GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZ3, SCE_GS_XYZ3, SCE_GS_XYZ2, SCE_GS_XYZ2), 
                   -4, 4);
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blend */, 0, 0, 0, 0);
    (*spack.pos++) = color;
    (*spack.pos++) = SCE_GS_SET_XYZ3(enDrawX(x + dx * size2 + dy * size1),
                                     enDrawY(y + dy * size2 - dx * size1), 
                                     0xffffff);
    (*spack.pos++) = SCE_GS_SET_XYZ3(enDrawX(x + dx * size2 - dy * size1),
                                     enDrawY(y + dy * size2 + dx * size1),
                                     0xffffff);
    (*spack.pos++) = SCE_GS_SET_XYZ2(enDrawX(x - dx * size2 + dy * size1),
                                     enDrawY(y - dy * size2 - dx * size1),
                                     0xffffff);
    (*spack.pos++) = SCE_GS_SET_XYZ2(enDrawX(x - dx * size2 - dy * size1),
                                     enDrawY(y - dy * size2 + dx * size1),
                                     0xffffff);
    spkCloseGiftag();
}
