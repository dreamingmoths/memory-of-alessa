#ifndef SH_SOUND_H
#define SH_SOUND_H

#include "common.h"

// total size: 0x30
typedef struct Se3D_ChannelData {
    // Members
    signed int sd; // offset 0x0, size 0x4
    signed int room; // offset 0x4, size 0x4
    signed int status; // offset 0x8, size 0x4
    float pos[4] __attribute__((aligned(16))); // offset 0x10, size 0x10
    float vol; // offset 0x20, size 0x4
} Se3D_ChannelData;

// total size: 0xC this was an anon
typedef struct Change_List {
    // Members
    int sd_se; // offset 0x0, size 0x4
    int sd_3d; // offset 0x4, size 0x4
    int file; // offset 0x8, size 0x4
} Change_List;

void SeWait(int wait /* r17 */);
void SeForceWait(void);
int SeCallPos(int sd_no /* r20 */, float volume /* r20 */, float * pos /* r19 */, int status /* r18 */);
int Se3dPlayCheck(int sd_no /* r2 */);
void SeBgmChange(void);
void SeSoundLoad(void);
void SeSoundEffect3dLoad(int data /* r16 */);
void SeSoundEffectLoad(int data /* r16 */);
void SeSoundManager(void);
void Se2dManager(void);
void Se3dManager(void);
void SeBgmManager(void);
int Se3dControl(int sd_no /* r17 */, float volume /* r20 */, float* pos /* r16 */);

extern Se3D_ChannelData se_3d_channel_data[8];
extern Change_List change_list[242]; // size: 0xB58, address: 0x2B8880
extern int se_3d_load_data;

#endif // SH_SOUND_H
