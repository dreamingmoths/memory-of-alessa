#include "Event/stg_name.h"
#include "Event/event.h"

#include "Chacter/character.h"

// @todo: migrate data

extern /* static */ Block block_a[23]; // size: 0x5C, address: 0x2B9DF0
extern /* static */ Block block_b[55]; // size: 0xDC, address: 0x2B9E50
extern /* static */ Block block_c[76]; // size: 0x130, address: 0x2B9F30
extern /* static */ Block block_d[6]; // size: 0x18, address: 0x2BA060

extern /* static */ u_char room_to_block[211][4]; // size: 0x34C, address: 0x2B9AA0

static int RoomNameExtra(int tpwoin);
static int RoomNameTownEast(int tpwoin);
static int RoomNameBowling(int tpwoin);
static int RoomNameHeaven(int tpwoin);
static int RoomNameApart(int tpwoin);
static int RoomNameHospital(int tpwoin);
static int RoomNameDelusion(int tpwoin);
static int RoomNameHotelFace(int tpwoin);
static int RoomNameHotelBack(int tpwoin);
static int RoomNameLastStage(int tpwoin);
static int RoomNameMansion(int tpwoin);

int RoomNameJms(void) {    
    if (sh2jms.player != NULL) return RoomName(0, sh2jms.player->pos.x, sh2jms.player->pos.z);        
    else return 0;
}

int RoomName(int glb_crd, float pos_x, float pos_z) {
    int tpwoin;
    int x;  
    int z;
   
    x = FTOI(16.0f + pos_x / 20000.0f);
    z = FTOI(16.0f + pos_z / 20000.0f);
    tpwoin = z + (x << 5);
    
    
    if (glb_crd == 0) glb_crd = stage->glb_crd;
    
    switch (glb_crd) {
        
        case 1: return 3;
        case 2: return RoomNameTownEast(tpwoin);
        case 3: return 8;
        case 4: return 14;
        case 5: return 2;
        case 6: return RoomNameExtra(tpwoin);
        case 7: return RoomNameBowling(tpwoin);
        case 8: return RoomNameHeaven(tpwoin);
        case 9: return RoomNameApart(tpwoin);
        case 10: return RoomNameHospital(tpwoin);
        case 11: return RoomNameDelusion(tpwoin);
        case 12: return RoomNameHotelFace(tpwoin);
        case 13: return RoomNameHotelBack(tpwoin);
        case 14: return RoomNameLastStage(tpwoin);
        case 15: return 191;
        case 16: return RoomNameMansion(tpwoin);
    }          
    
    return 0;        
}

static int RoomNameExtra(int tpwoin) {
    switch ((tpwoin - (!(tpwoin & 0x20) ? 0 : 32)) - (!(tpwoin & 1) ? 0 : 1)) {
        case 0x210: return 5;
        case 0x1D0: return 1;
        case 0x20E: return 6;
        case 0x1CE: return 190;
    }    
    return 0;
    
}

static int RoomNameTownEast(int tpwoin) {
    switch (tpwoin) {
        case 0x26C:
        case 0x28C:
        case 0x2AC:
        case 0x26B:
        case 0x28B:
        case 0x2AB: return 7;
    }
    return 4;
}

static int RoomNameBowling(int tpwoin) {
    switch ((tpwoin - (!(tpwoin & 0x20) ? 0 : 32)) - (!(tpwoin & 1) ? 0 : 1)) {      
        case 0x210: return 11;
        case 0x20E: return 9;
        case 0x1D0: return 10;
    }    
    return 0;    
}

static int RoomNameHeaven(int tpwoin) {
    switch ((tpwoin - (!(tpwoin & 0x20) ? 0 : 32)) - (!(tpwoin & 1) ? 0 : 1)) {
        case 0x210: return 0xC;
        case 0x1D0: return 0xD;                
    }    
    return 0;
}

static int RoomNameApart(int tpwoin) {
    switch (tpwoin) {
        case 0x1AD:
        case 0x1AC: 
        case 0x1AB:  
        case 0x1AA: return 0x12;
        case 0x18D: 
        case 0x18C:
        case 0x16D:   
        case 0x16C: return 0x11;
    }                                       
    switch ((tpwoin - (!(tpwoin & 0x20) ? 0 : 32)) - (!(tpwoin & 1) ? 0 : 1)) {
        case 0x18E: return 0xF;
        case 0x14E: return 0x10;
        case 0x1CA: return 0x13;
        case 0x1CC: return 0x14;
        case 0x150: return 0x15;
        case 0x1D2: return 0x16;
        case 0x1D0: return 0x17;
        case 0x190: return 0x18;
        case 0x192: return 0x19;
        case 0x1CE: return 0x1A;
        case 0x210: return 0x1B;
        case 0x212: return 0x1C;
        case 0x1D4: return 0x1D;
        case 0x214: return 0x1E;
        case 0x250: return 0x1F;
        case 0x2CE: return 0x20;
        case 0x24E: return 0x22;
        case 0x24C: return 0x23;
        case 0x24A: return 0x24;
        case 0x28C: return 0x25;
        case 0x28E: return 0x26;
        case 0x20E: return 0x27;
        case 0x20A: return 0x28;
        case 0x28A: return 0x21;
    }   
    
    return 0;     
}

static int RoomNameHospital(int tpwoin) {
    switch ((tpwoin - (!(tpwoin & 0x20) ? 0 : 0x20)) - (!(tpwoin & 1) ? 0 : 1)) {                              /* irregular */
        case 0x18A: return 0x29;
        case 0x14E: return 0x2A;
        case 0x20E: return 0x2B;
        case 0x1CC: return 0x2C;
        case 0x18E: return 0x2D;
        case 0x18C: return 0x2E;
        case 0x1CA: return 0x2F;
        case 0x10E: return 0x30;
        case 0x10A: return 0x31;
        case 0x14C: return 0x32;
        case 0x1CE: return 0x33;
        case 0x10C: return 0x34;
        case 0x1D2: return 0x35;
        case 0x1D0: return 0x36;
        case 0x192: return 0x37;
        case 0x112: return 0x38;
        case 0x190: return 0x39;
        case 0x110: return 0x3A;
        case 0x150: return 0x3B;
        case 0x194: return 0x3C;
        case 0x254: return 0x3D;
        case 0x214: return 0x3E;
        case 0x212: return 0x3F;
        case 0x2D2: return 0x40;
        case 0x292: return 0x41;
        case 0x290: return 0x42;
        case 0x2D4: return 0x43;
        case 0x250: return 0x44;
        case 0x252: return 0x45;
        case 0x1C0: return 0x46;
        case 0x184: return 0x47;
        case 0x144: return 0x48;
        case 0x180: return 0x49;
        case 0x1C2: return 0x4A;
        case 0x102: return 0x4B;
        case 0x104: return 0x4C;
        case 0x1C4: return 0x4D;
        case 0x142: return 0x4E;
        case 0x140: return 0x4F;
        case 0x188: return 0x50;
        case 0x186: return 0x51;
        case 0x1C8: return 0x52;
        case 0x1C6: return 0x53;
        case 0x208: return 0x54;
        case 0x248: return 0x55;
        case 0x286: return 0x56;
        case 0x246: return 0x57;
        case 0x206: return 0x58;
        case 0x204: return 0x59;
        case 0x200: return 0x5A;
        case 0x202: return 0x5B;        
    }
    return 0;
}

static int RoomNameDelusion(int tpwoin) {
    switch (tpwoin) {
        case 0x1F2:                                     
        case 0x1F3:                                     
        case 0x1F4:                                     
        case 0x1F5: return 0x5D;
        case 0x1D2:                                     
        case 0x1D3: return 0x5E;
        case 0x1AC:                                      
        case 0x18C: return 0x60;
        case 0x1D4:                                     
        case 0x1D5: return 0x61;
        case 0x1AE: return 0x62;
        case 0x132:                                     
        case 0x112: return 0x63;
        case 0x1AF:                                     
        case 0x18F: return 0x64;
        case 0x133: return 0x65;
        case 0x174:                                     
        case 0x154: return 0x66;
        case 0x1B5:                                     
        case 0x195: return 0x67;                                                                                         
        case 0x16F:        
        case 0x16E:
        case 0x14F:return 0x6A;
        case 0x1B4:                                     
        case 0x194: return 0x6B;
        case 0x134:
        case 0x113:
        case 0x114: return 0x6D;
        case 0x135:                                     
        case 0x115: return 0x6E;
        case 0x1EC:                                     
        case 0x1CC: return 0x6F;                                             
        case 0x1AD:
        case 0x18D: return 0x70;
        case 0x18E: return 0x71;
        case 0x175:
        case 0x155: return 0x74;                                                                            
        case 0x1EF: 
        case 0x1CF: return 0x75;            
        case 0x1EE:                                     
        case 0x1CE: return 0x76;
        case 0x1ED:                                     
        case 0x1CD: return 0x77;
    }                                        
    switch ((tpwoin - (!(tpwoin & 0x20) ? 0 : 32)) - (!(tpwoin & 1) ? 0 : 1)) {
        case 0x1D0: return 0x5C;
        case 0x190: return 0x5F;
        case 0x152: return 0x68;
        case 0x150: return 0x69;
        case 0x192: return 0x6C;
        case 0x110: return 0x72;
        case 0x10E: return 0x73;
        case 0x1CA: return 0x78;
        case 0x214: return 0x79;
        case 0x2D2: return 0x7A;
        case 0x292: return 0x7B;
        case 0x2D0: return 0x7C;
        case 0x252: return 0x7D;
        case 0x24E: return 0x7E;
        case 0x2D4: return 0x7F;
        case 0x250: return 0x80;
        case 0x294: return 0x81;
        case 0x20C: return 0x82;
        case 0x24A: return 0x83;
        case 0x254: return 0x84;
        case 0x290: return 0x85;
        case 0x24C: return 0x86;
        case 0x20E: return 0x87;
        case 0x20A: return 0x88;
        case 0x210: return 0x89;
        case 0x212: return 0x8A;
        case 0x2CE: return 0x8B;
        case 0x2CC: return 0x8C;
        case 0x28E: return 0x8D;
        case 0x28C: return 0x8E;
        case 0x28A: return 0x8F;
        case 0x2CA: return 0x90;        
    }
    return 0;   
}

static int RoomNameHotelFace(int tpwoin) {
    switch (tpwoin) {
        case 0x132:
        case 0x133: return 0x96;
    }
    switch ((tpwoin - (!(tpwoin & 0x20) ? 0 : 32)) - (!(tpwoin & 1) ? 0 : 1)) {
        case 0x14E: return 0x91;
        case 0x1D0: return 0x92;
        case 0x1D2: return 0x93;
        case 0x194: return 0x94;
        case 0x1D4: return 0x95;
        case 0x152: return 0x97;
        case 0x192: return 0x98;
        case 0x190: return 0x99;
        case 0x150: return 0x9A;
        case 0x20C: return 0x9B;
        case 0x28C: return 0x9C;
        case 0x24C: return 0x9D;
        case 0x20A: return 0x9E;
        case 0x20E: return 0x9F;
        case 0x24E: return 0xA0;
        case 0x28E: return 0xA1;
        case 0x250: return 0xA2;
        case 0x210: return 0xA3;
        case 0x290: return 0xA4;
        case 0x1CE: return 0xA5;
        case 0x18E: return 0xA6;
        case 0x14C: return 0xA7;
        case 0x1CC: return 0xA8;
        case 0x18C: return 0xA9;            
    }
    return 0;    
}

static int RoomNameHotelBack(int tpwoin) {
    switch ((tpwoin - (!(tpwoin & 0x20) ? 0 : 32)) - (!(tpwoin & 1) ? 0 : 1)) {                              /* irregular */
        case 0x14C: return 0xAA;
        case 0x14E: return 0xAB;
        case 0x1D0: return 0xAC;
        case 0x190: return 0xAD;
        case 0x150: return 0xAE;
        case 0x1D2: return 0xAF;
        case 0x20C: return 0xB0;
        case 0x20E: return 0xB1;
        case 0x24E: return 0xB2;
        case 0x28E: return 0xB3;
        case 0x24C: return 0xB4;
        case 0x210: return 0xB5;
        case 0x1CE: return 0xB6;
        case 0x18E: return 0xB7;
        case 0x1CC: return 0xB8;
        case 0x18C: return 0xB9;
        case 0x250: return 0xBA;
        case 0x252: return 0xBB;
    }
    return 0;
}

static int RoomNameLastStage(int tpwoin) {
    switch ((tpwoin - (!(tpwoin & 0x20) ? 0 : 32)) - (!(tpwoin & 1) ? 0 : 1)) {
        case 0x1D0: return 0xBC;
        case 0x210: return 0xBD;     
    }
    return 0;
}

static int RoomNameMansion(int tpwoin) {
    switch ((tpwoin - (!(tpwoin & 0x20) ? 0 : 32)) - (!(tpwoin & 1) ? 0 : 1)) {
        case 0x210: return 0xC0;
        case 0x250: return 0xC1;
        case 0x1CE: return 0xC2;
        case 0x20E: return 0xC3;
        case 0x290: return 0xC4;
        case 0x1D4: return 0xC5;
        case 0x1D0: return 0xC6;
        case 0x24E: return 0xC7;
        case 0x194: return 0xC8;
        case 0x20C: return 0xC9;
        case 0x254: return 0xCA;
        case 0x214: return 0xCB;
        case 0x24C: return 0xCC;
        case 0x212: return 0xCD;
        case 0x1CC: return 0xCE;
        case 0x252: return 0xCF;
        case 0x192: return 0xD0;
        case 0x24A: return 0xD1;
        case 0x20A: return 0xD2;
    }
    return 0;
}

int BlockNumber(int* ret, int glb_crd, float pos_x, float pos_z) {
    Block* block; 
    int no;
    int result;
    int room;
    int x; int z; 
    int xz;   
    int i;
    if (glb_crd == 0) glb_crd = stage->glb_crd;
    
    for (i = 0; i < 4; i++) ret[i] = 0;
    room = RoomName(glb_crd, pos_x, pos_z);
    
    if (!BgIsOut(glb_crd)) {
        for (i = 0; i < 4; i++) 
            ret[i] = (glb_crd << 16) | room_to_block[room][i];        
        return 0;    
    }
    
    x = (pos_x >= 0.0f ? 1 : -1) + FTOI(pos_x / 20000.0f);
    z = (pos_z >= 0.0f ? 1 : -1) + FTOI(pos_z / 20000.0f);    
    xz = ((z > 0 ? z - 1 : z) + 16) + (((x > 0 ? x - 1 : x) + 16) << 5);

    switch (glb_crd) {
        
        case 1: default: block = block_a; no = 23; break;
        case 2:          block = block_b; no = 55; break;
        case 3:          block = block_c; no = 76; break;
        case 4:          block = block_d; no = 7;  break;
    }
    
    result = 0;
    while (TRUE) { 
        if (no == 0) break;    
        no = (no < 2) ? 0 : ((no + 1) >> 1);
        if (block->xz < xz) block -= no;
        else if (xz < block->xz) block += no;
        else if (block->xz == xz) {
            result = block->block; 
            break;
        }
    }    
    *ret = (glb_crd << 16) | result;
    
    return 1;
}

int BgIsOut(int glb_crd) {
    if (glb_crd == 0) glb_crd = stage->glb_crd;
    
    ASSERT_ON_LINE(glb_crd > Glb_crd_null && glb_crd < Glb_crd_num, 963);

    return ((glb_crd >= 1) && (glb_crd < 5));
}
