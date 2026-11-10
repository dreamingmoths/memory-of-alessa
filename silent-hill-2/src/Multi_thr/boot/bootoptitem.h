#ifndef BOOTOPTITEM_H
#define BOOTOPTITEM_H

typedef struct BootOptItem {
    // total size: 0x18
    void* var; // offset 0x0, size 0x4
    s_char key[4]; // offset 0x4, size 0x4
    int (*get)(s_char*); // offset 0x8, size 0x4
    void (*put)(s_char*, int); // offset 0xC, size 0x4
    char* help; // offset 0x10, size 0x4
    int set; // offset 0x14, size 0x4
} BootOptItem;

#endif // BOOTOPTITEM_H
