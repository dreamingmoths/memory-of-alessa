#ifndef LOADBG_CLD_H
#define LOADBG_CLD_H

typedef struct loadBgCLD_Ctrl {
    // total size: 0x104
    signed int mapid[16]; // offset 0x0, size 0x40
    void * addr[16]; // offset 0x40, size 0x40
    signed int size[16]; // offset 0x80, size 0x40
    void * list[17]; // offset 0xC0, size 0x44
} loadBgCLD_Ctrl;

extern /* static */ loadBgCLD_Ctrl lbCLD_Ctrl;
void * * loadBgCLD_GetLoadedDataAddrList();

#endif
