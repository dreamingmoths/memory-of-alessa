#ifndef DS_SEQUENCER_H
#define DS_SEQUENCER_H

#include "sh2_common.h"
#include "Chacter/character.h"

typedef struct DS_Object_Info {
    // total size: 0x10
    u_int Offset;       // offset 0x0, size 0x4
    u_int DataNode_num; // offset 0x4, size 0x4
    u_short Type;       // offset 0x8, size 0x2
    u_short ID;         // offset 0xA, size 0x2
    u_short Attribute;  // offset 0xC, size 0x2
    u_short Permission; // offset 0xE, size 0x2
} DS_Object_Info;

typedef struct Record_Info {
    // total size: 0x8
    struct DS_Object_Info* pObject; // offset 0x0, size 0x4
    void* pAddress;                 // offset 0x4, size 0x4
} Record_Info;

typedef struct EntryRecord {
    // total size: 0x24
    u_short Enable;          // offset 0x0, size 0x2
    u_short Controller_ID;   // offset 0x2, size 0x2
    u_int Handle;            // offset 0x4, size 0x4
    u_int Group_Handle;      // offset 0x8, size 0x4
    u_int Condition;         // offset 0xC, size 0x4
    float Time_Count;        // offset 0x10, size 0x4
    float Time_Max;          // offset 0x14, size 0x4
    float Ratio;             // offset 0x18, size 0x4
    struct Record_Info Info; // offset 0x1C, size 0x8
} EntryRecord;

typedef struct DS_Record {
    // total size: 0x8
    float Time;               // offset 0x0, size 0x4
    u_char Actuater_LV;       // offset 0x4, size 0x1
    u_char Complement_Enable; // offset 0x5, size 0x1
    u_char Reserved[2];       // offset 0x6, size 0x2
} DS_Record;

typedef struct DS_Record_Header {
    // total size: 0x20
    u_char DataName[16]; // offset 0x0, size 0x10
    u_int Revision;      // offset 0x10, size 0x4
    u_int Object_Num;    // offset 0x14, size 0x4
    u_int Reserved[2];   // offset 0x18, size 0x8
} DS_Record_Header;

typedef struct DS_Record_Edit {
    // total size: 0x10
    struct DS_Record Record;      // offset 0x0, size 0x8
    struct DS_Record_Edit* pPrev; // offset 0x8, size 0x4
    struct DS_Record_Edit* pNext; // offset 0xC, size 0x4
} DS_Record_Edit;

// total size: 0x18
typedef struct DSR_MUD {
    // Members
    float Different_Time;    // offset 0x0, size 0x4
    u_int Handle_History;    // offset 0x4, size 0x4
    u_int EntryRecord_Count; // offset 0x8, size 0x4
    u_int enQueue_Pos;       // offset 0xC, size 0x4
    u_int deQueue_Pos;       // offset 0x10, size 0x4
    u_int EventQueue_Count;  // offset 0x14, size 0x4
} DSR_MUD;

// total size: 0xC
typedef struct DSR_MU_EventDescriptor {
    // Members
    u_int Handle;  // offset 0x0, size 0x4
    u_int EventID; // offset 0x4, size 0x4
    float Value;   // offset 0x8, size 0x4
} DSR_MU_EventDescriptor;

u_int DSR_Entry0(void* pAddress, u_int ControllerID, float Ratio);

void DSR_Sequencer_Initialize(void);

void DSR_Sequencer(void);

void DSR_Sequence_Different_Time_Set(float Different_Time);

#endif
