#ifndef PAD_H
#define PAD_H

#include "sh2_common.h"

#define PAD_KEY_SELECT     (1 << 2)
#define PAD_KEY_START      (1 << 3)
#define PAD_KEY_DPAD_RIGHT (1 << 8)
#define PAD_KEY_DPAD_LEFT  (1 << 9)
#define PAD_KEY_DPAD_UP    (1 << 10)
#define PAD_KEY_DPAD_DOWN  (1 << 11)
#define PAD_KEY_TRIANGLE   (1 << 12)
#define PAD_KEY_CIRCLE     (1 << 13)
#define PAD_KEY_CROSS      (1 << 14)
#define PAD_KEY_SQUARE     (1 << 15)
#define PAD_KEY_L1         (1 << 16)
#define PAD_KEY_R1         (1 << 17)
#define PAD_KEY_L2         (1 << 18)
#define PAD_KEY_R2         (1 << 19)

// total size: 0x26
struct shGameKeyAssign {
    // Members
    unsigned short type;   // offset 0x0, size 0x2
    u_char DIR_AX;         // offset 0x2, size 0x1
    u_char DIR_AY;         // offset 0x3, size 0x1
    u_char DIR_BX;         // offset 0x4, size 0x1
    u_char DIR_BY;         // offset 0x5, size 0x1
    u_char DIR_CX;         // offset 0x6, size 0x1
    u_char DIR_CY;         // offset 0x7, size 0x1
    unsigned short DRINK;  // offset 0x8, size 0x2
    unsigned short RADIO;  // offset 0xA, size 0x2
    unsigned short LIGHT;  // offset 0xC, size 0x2
    unsigned short ITEM;   // offset 0xE, size 0x2
    unsigned short MAP;    // offset 0x10, size 0x2
    unsigned short DECIDE; // offset 0x12, size 0x2
    unsigned short CANCEL; // offset 0x14, size 0x2
    unsigned short SKIP;   // offset 0x16, size 0x2
    unsigned short PAUSE;  // offset 0x18, size 0x2
    unsigned short ACTION; // offset 0x1A, size 0x2
    unsigned short DASH;   // offset 0x1C, size 0x2
    unsigned short LSLIDE; // offset 0x1E, size 0x2
    unsigned short RSLIDE; // offset 0x20, size 0x2
    unsigned short READY;  // offset 0x22, size 0x2
    unsigned short VIEW;   // offset 0x24, size 0x2
};

// total size: 0x60
typedef struct Pad_KeyConfig {
    // Members
    int enter;       // offset 0x0, size 0x4
    int cancel;      // offset 0x4, size 0x4
    int skip;        // offset 0x8, size 0x4
    int front_move;  // offset 0xC, size 0x4
    int back_move;   // offset 0x10, size 0x4
    int right_turn;  // offset 0x14, size 0x4
    int left_turn;   // offset 0x18, size 0x4
    int right_move;  // offset 0x1C, size 0x4
    int left_move;   // offset 0x20, size 0x4
    int action;      // offset 0x24, size 0x4
    int attack;      // offset 0x28, size 0x4
    int dash;        // offset 0x2C, size 0x4
    int light;       // offset 0x30, size 0x4
    int item;        // offset 0x34, size 0x4
    int search_view; // offset 0x38, size 0x4
    int ready;       // offset 0x3C, size 0x4
    int pause;       // offset 0x40, size 0x4
    int map;         // offset 0x44, size 0x4
    int padding[6];  // offset 0x48, size 0x18
} Pad_KeyConfig;

// @todo: clean up

void shPadInit(void);

void libShPadRead(int a, int b, void* c); // NOT SURE ABOUT THIS

void shPadSetGameKeyAssign(void);
void shQzero(void*, int);
float shGetDT(void);
u_int dbFlag(u_int flag /* r2 */);
int dbSwitchSysPadPort(void);
static unsigned long kc2ga(unsigned long kconf_button /* r2 */);
void shGameKeyGetAssign(struct shGameKeyAssign* assign /* r2 */);
int shPadTrigger(int port /* r17 */, int key /* r16 */);
int shSysKeyNormalize(char* paddata /* r2 */);
int shPadRepeat(int port /* r17 */, int key /* r16 */);

extern struct Pad_KeyConfig key_config;
extern u_char pad_bak[2][20];
extern u_char pad[2][32];
extern int pad_x;
extern float padf[2][20];
extern int repeat[2];

#endif
