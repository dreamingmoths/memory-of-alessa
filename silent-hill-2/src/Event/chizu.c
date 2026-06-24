#include "common.h"
#include "Event/chizu.h"
#include "Chacter/character.h"
#include "Event/event.h"

static int ChizuSelect(void);

static int ChizuPossessionCheck(int chizu);

static void ChizuFileLoad(int load_chizu);

static void ChizuDisplay(void);

static void ChizuMarkerDraw(void);

static void ChizuControl(void);

static void ChizuConnectArrowDraw(void);

static int ChizuConnectCheck(int chizu, int connect);

static void ChizuCurrentPositionDraw(void);

static void ChizuCurrentPositionCheck(float* px, float* py);

extern /* static */ int chizu_crnt; // size: 0x4, address: 0x116DB80
extern /* static */ Chizu_CurrentBlock chz_crt_block[190]; // size: 0x8E8, address: 0x33BEF0

INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuMain);

INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuSelect);

INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuPossessionCheck);

INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuFileLoad);

INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuDisplay);

INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuMarkerDraw);

INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuControl);

INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuConnectArrowDraw);

INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuConnectCheck);

INCLUDE_ASM("asm/nonmatchings/Event/chizu", ChizuCurrentPositionDraw);

#define SET_MAP_POSITION(_x, _z) do { \
    *px = (_x * jms->pos.x) + chz_crt_block[room].cp_x; \
    *py = chz_crt_block[room].cp_y - (_z * jms->pos.z); \
} while (0);

// @todo: add room names
void ChizuCurrentPositionCheck(float* px, float* py) {
    SubCharacter* jms;
    int room = RoomNameJms(); // r18
    float tmp; // r29+0x70

    jms = sh2jms.player;

    switch (RoomNameJms()) {                              /* switch 1 */
        default:                                        /* switch 1 */
            // single precision
            SET_MAP_POSITION(0.00142f, 0.00196f);
            return;
        case 0x3:                                       /* switch 1 */
            // double precision
            SET_MAP_POSITION(0.00053, 0.00079);
            return;
        case 0x1:                                       /* switch 1 */
        case 0x2:                                       /* switch 1 */
        case 0x5:                                       /* switch 1 */
        case 0x6:                                       /* switch 1 */
        case 0x9:                                       /* switch 1 */
        case 0xA:                                       /* switch 1 */
        case 0xB:                                       /* switch 1 */
        case 0xC:                                       /* switch 1 */
        case 0xD:                                       /* switch 1 */
            *px = chz_crt_block[room].cp_x;
            *py = chz_crt_block[room].cp_y;
            return;
        case 0x8:
            if ((jms->pos.x> 30453.578906) && (jms->pos.x < 35960.0f)) {
                if (jms->pos.z >= -60828.847656 && (jms->pos.z <= -59016.0f)) {
                    *px = 212.4619f;
                    *py = 183.76071f;
                    return;
                }
            }
            SET_MAP_POSITION(0.00146f, 0.00196f);
            return;
        case 0x78:                                      /* switch 1 */
        case 0x79:                                      /* switch 1 */
        case 0x7A:                                      /* switch 1 */
        case 0x7B:                                      /* switch 1 */
        case 0x7C:                                      /* switch 1 */
        case 0x7D:                                      /* switch 1 */
        case 0x7E:                                      /* switch 1 */
        case 0x7F:                                      /* switch 1 */
        case 0x80:                                      /* switch 1 */
        case 0x81:                                      /* switch 1 */
        case 0x82:                                      /* switch 1 */
        case 0x83:                                      /* switch 1 */
        case 0x84:                                      /* switch 1 */
        case 0x85:                                      /* switch 1 */
        case 0x86:                                      /* switch 1 */
        case 0x87:                                      /* switch 1 */
        case 0x88:                                      /* switch 1 */
        case 0x89:                                      /* switch 1 */
        case 0x8A:                                      /* switch 1 */
        case 0x8B:                                      /* switch 1 */
        case 0x8C:                                      /* switch 1 */
        case 0x8D:                                      /* switch 1 */
            SET_MAP_POSITION(0.01007f, 0.0089f);
            tmp = *px;
            *px = -*py;
            *py = tmp;
            return;
        case 0x66:                                      /* switch 1 */
        case 0x67:                                      /* switch 1 */
        case 0x68:                                      /* switch 1 */
        case 0x69:                                      /* switch 1 */
        case 0x6A:                                      /* switch 1 */
        case 0x6B:                                      /* switch 1 */
        case 0x6C:                                      /* switch 1 */
        case 0x6D:                                      /* switch 1 */
        case 0x6E:                                      /* switch 1 */
        case 0x6F:                                      /* switch 1 */
        case 0x70:                                      /* switch 1 */
        case 0x71:                                      /* switch 1 */
        case 0x73:                                      /* switch 1 */
        case 0x74:                                      /* switch 1 */
            SET_MAP_POSITION(0.01377f, 0.010408f);
            tmp = *px;
            *px = *py;
            *py = -tmp;
            return;
        case 0x72:                                      /* switch 1 */
            SET_MAP_POSITION(0.01377f, 0.009988f);
            tmp = *px;
            *px = *py;
            *py = -tmp;
            return;
        case 0x20:                                      /* switch 1 */
        case 0x21:                                      /* switch 1 */
        case 0x22:                                      /* switch 1 */
        case 0x23:                                      /* switch 1 */
        case 0x24:                                      /* switch 1 */
        case 0x27:                                      /* switch 1 */
        case 0x28:                                      /* switch 1 */
            SET_MAP_POSITION(0.0087f, 0.0096f);
            if (!(GET_GAME_FLAG(GAME_FLAG_25)) && ((GET_GAME_FLAG(GAME_FLAG_26)) == 1)) {
                switch (chizu_crnt) {                   /* switch 2; irregular */
                case 7:                                 /* switch 2 */
                    *px += 24.965286f;
                    return;
                case 8:                                 /* switch 2 */
                    *px += 164.96529f;
                    return;
                }
            }
            break;
        case 0x25:                                      /* switch 1 */
        case 0x26:                                      /* switch 1 */
            SET_MAP_POSITION(0.00801f, 0.01037f);
            if (!(GET_GAME_FLAG(GAME_FLAG_25)) && ((GET_GAME_FLAG(GAME_FLAG_26)) == 1)) {
                switch (chizu_crnt) {                   /* switch 3; irregular */
                case 7:                                 /* switch 3 */
                    *px += 16.965286f;
                    return;
                case 8:                                 /* switch 3 */
                    *px += 158.96529f;
                    return;
                }
            }
            break;
        case 0xF:                                       /* switch 1 */
        case 0x10:                                      /* switch 1 */
        case 0x11:                                      /* switch 1 */
        case 0x13:                                      /* switch 1 */
        case 0x14:                                      /* switch 1 */
        case 0x16:                                      /* switch 1 */
        case 0x17:                                      /* switch 1 */
        case 0x18:                                      /* switch 1 */
        case 0x19:                                      /* switch 1 */
        case 0x1A:                                      /* switch 1 */
        case 0x1B:                                      /* switch 1 */
        case 0x1C:                                      /* switch 1 */
        case 0x1D:                                      /* switch 1 */
        case 0x1E:                                      /* switch 1 */
            SET_MAP_POSITION(0.0087f, 0.0096f);
            return;
        case 0x7:                                       /* switch 1 */
        case 0x12:                                      /* switch 1 */
        case 0x15:                                      /* switch 1 */
        case 0x1F:                                      /* switch 1 */
            SET_MAP_POSITION(0.00801f, 0.01037f);
            return;
        case 0x92:                                      /* switch 1 */
        case 0xA2:                                      /* switch 1 */
        case 0xAC:                                      /* switch 1 */
            SET_MAP_POSITION(0.0164f, 0.0209f);
            return;
        case 0x99:                                      /* switch 1 */
        case 0x9A:                                      /* switch 1 */
        case 0x9F:                                      /* switch 1 */
        case 0xA0:                                      /* switch 1 */
        case 0xA1:                                      /* switch 1 */
        case 0xA3:                                      /* switch 1 */
        case 0xA8:                                      /* switch 1 */
        case 0xA9:                                      /* switch 1 */
        case 0xAD:                                      /* switch 1 */
        case 0xAE:                                      /* switch 1 */
        case 0xAF:                                      /* switch 1 */
        case 0xB1:                                      /* switch 1 */
        case 0xB2:                                      /* switch 1 */
        case 0xB5:                                      /* switch 1 */
        case 0xB8:                                      /* switch 1 */
        case 0xB9:                                      /* switch 1 */
            SET_MAP_POSITION(0.01607f, 0.0207f);
            return;
        case 0x91:                                      /* switch 1 */
        case 0x93:                                      /* switch 1 */
        case 0x94:                                      /* switch 1 */
        case 0x95:                                      /* switch 1 */
        case 0x96:                                      /* switch 1 */
        case 0x97:                                      /* switch 1 */
        case 0x98:                                      /* switch 1 */
        case 0x9B:                                      /* switch 1 */
        case 0x9C:                                      /* switch 1 */
        case 0x9D:                                      /* switch 1 */
        case 0x9E:                                      /* switch 1 */
        case 0xA5:                                      /* switch 1 */
        case 0xA6:                                      /* switch 1 */
        case 0xA7:                                      /* switch 1 */
        case 0xAB:                                      /* switch 1 */
        case 0xB0:                                      /* switch 1 */
        case 0xB6:                                      /* switch 1 */
        case 0xB7:                                      /* switch 1 */
            SET_MAP_POSITION(0.0164f, 0.01875f);
            return;
        case 0x2B:                                      /* switch 1 */
        case 0x2C:                                      /* switch 1 */
        case 0x2D:                                      /* switch 1 */
        case 0x2E:                                      /* switch 1 */
        case 0x2F:                                      /* switch 1 */
        case 0x31:                                      /* switch 1 */
        case 0x32:                                      /* switch 1 */
        case 0x33:                                      /* switch 1 */
        case 0x34:                                      /* switch 1 */
        case 0x35:                                      /* switch 1 */
        case 0x36:                                      /* switch 1 */
        case 0x37:                                      /* switch 1 */
        case 0x38:                                      /* switch 1 */
        case 0x39:                                      /* switch 1 */
        case 0x3A:                                      /* switch 1 */
        case 0x3C:                                      /* switch 1 */
        case 0x3D:                                      /* switch 1 */
        case 0x3E:                                      /* switch 1 */
        case 0x3F:                                      /* switch 1 */
        case 0x40:                                      /* switch 1 */
        case 0x41:                                      /* switch 1 */
        case 0x42:                                      /* switch 1 */
        case 0x43:                                      /* switch 1 */
        case 0x44:                                      /* switch 1 */
        case 0x45:                                      /* switch 1 */
        case 0x49:                                      /* switch 1 */
        case 0x4A:                                      /* switch 1 */
        case 0x4B:                                      /* switch 1 */
        case 0x4C:                                      /* switch 1 */
        case 0x4D:                                      /* switch 1 */
        case 0x4E:                                      /* switch 1 */
        case 0x4F:                                      /* switch 1 */
        case 0x50:                                      /* switch 1 */
        case 0x51:                                      /* switch 1 */
        case 0x52:                                      /* switch 1 */
        case 0x53:                                      /* switch 1 */
        case 0x54:                                      /* switch 1 */
        case 0x55:                                      /* switch 1 */
        case 0x56:                                      /* switch 1 */
        case 0x57:                                      /* switch 1 */
        case 0x58:                                      /* switch 1 */
        case 0x59:                                      /* switch 1 */
            SET_MAP_POSITION(0.01477f, 0.019658f);
            return;
        case 0x3B:                                      /* switch 1 */
            SET_MAP_POSITION(0.014716f, 0.019583f);
            return;
        case 0x29:                                      /* switch 1 */
            if (jms->pos.y > -950.0f || ((jms->pos.z > -100000.0f) && jms->pos.y > -1200.0f)) {
                *px = 879.80005f + (0.013396f * jms->pos.x);
                *py = -1988.8f - (0.019375f * jms->pos.z);
                return;
            }
            if ((jms->pos.y > -2950.0f) || ((jms->pos.z > -100000.0f) && (jms->pos.y > -3200.0f))) {
                *px = 916.2002f + (0.013396f * jms->pos.x);
                *py = -1847.7001f - (0.019375f * jms->pos.z);
                return;
            }
            if ((jms->pos.y > -4950.0f) || ((jms->pos.z > -100000.0f) && (jms->pos.y > -5200.0f))) {
                *px = 916.40015f + (0.013396f * jms->pos.x);
                *py = -2086.5996f - (0.019375f * jms->pos.z);
                return;
            }
            *px = 631.7003f + (0.013396f * jms->pos.x);
            *py = -1956.7996f - (0.019375f * jms->pos.z);
            return;
        case 0x2A:                                      /* switch 1 */
            if (GET_GAME_FLAG(GAME_FLAG_19)) {
                *px = 1421.101f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 531.00037f;
                return;
            }
            if (GET_GAME_FLAG(GAME_FLAG_18)) {
                *px = 1421.101f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 289.90015f;
                return;
            }
            if (GET_GAME_FLAG(GAME_FLAG_17)) {
                *px = 1385.2999f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 426.99988f;
                return;
            }
            break;
        case 0x46:                                      /* switch 1 */
            if (GET_GAME_FLAG(GAME_FLAG_19)) {
                *px = 240.9f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 6029.8965f;
                return;
            }
            if (GET_GAME_FLAG(GAME_FLAG_18)) {
                *px = 238.69986f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 5789.196f;
                return;
            }
            if (GET_GAME_FLAG(GAME_FLAG_17)) {
                *px = 203.69986f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 5931.196f;
                return;
            }
            break;
        case 0x48:                                      /* switch 1 */
            if ((jms->pos.y >= 1700.0f)) {
                *px = 0.0f;
                *py = -1000.0f;
                return;
            }
            if ((jms->pos.y > -1000.0f) || ((jms->pos.y < -1001.0f) && (jms->pos.z > -99992.0f) && (jms->pos.y >= -1000.0f))) {
                *px = 1404.0f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 4336.0f;
                return;
            }
            if ((jms->pos.y > -3000.0f) || ((jms->pos.y < -3001.0f) && (jms->pos.z > -100009.0f) && (jms->pos.y >= -3000.0f))) {
                *px = 1438.0f + (0.01477f * sh2jms.player->pos.x);
                *py = (0.019658f * -sh2jms.player->pos.z) - 4191.0f;
                return;
            }
            *px = 1438.0f + (0.01477f * sh2jms.player->pos.x);
            *py = 6.0f + ((0.019658f * -sh2jms.player->pos.z) - 4432.0f);
            return;
        case 0x47:                        
            if ((jms->pos.y >= 1001.0f) || ((jms->pos.y >= 1000.0f) && (jms->pos.z > -220067.0f))) {
                *px = 878.0f + (0.013396f * jms->pos.x);
                *py = -31.899994f - (0.019375f * jms->pos.z);
                return;
            }
            if ((jms->pos.y >= -1000.0f) || ((jms->pos.z > -219978.0f)) && (jms->pos.y > -1001.0f)) {
                *px = 878.80005f + (0.013396f * jms->pos.x);
                *py = -211.9f - (0.019375f * jms->pos.z);
                return;
            }
            if ((jms->pos.y >= -2998.0f) || ((jms->pos.z > -220003.0f) && (jms->pos.y > -3000.0f))) {
                *px = 915.0f + (0.013396f * jms->pos.x);
                *py = -73.899994f - (0.019375f * jms->pos.z);
                return;
            }
            if ((jms->pos.y > -5000.0f) || ((jms->pos.z > -220011.0f) && (jms->pos.y >= -5000.0f))) {
                *px = 915.0f + (0.013396f * jms->pos.x);
                *py = -313.9f - (0.019375f * jms->pos.z);
                return;
            }
            *px = 630.0f + (0.013396f * jms->pos.x);
            *py = -183.9f - (0.019375f * jms->pos.z);
            break;
        }
}

#undef SET_MAP_POSITION

