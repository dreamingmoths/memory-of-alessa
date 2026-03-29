// E:\work\sh2(CVS全取得)\src\DS_Pad\ds_sequencer.c
#ifndef DS_SEQUENCER_H
#define DS_SEQUENCER_H

#include "sh2_common.h"
#include "Chacter/character.h"

typedef struct DS_Object_Info
{
    // total size: 0x10
    u_int Offset;       // offset 0x0, size 0x4
    u_int DataNode_num; // offset 0x4, size 0x4
    u_short Type;       // offset 0x8, size 0x2
    u_short ID;         // offset 0xA, size 0x2
    u_short Attribute;  // offset 0xC, size 0x2
    u_short Permission; // offset 0xE, size 0x2
} DS_Object_Info;

typedef struct Record_Info
{
    // total size: 0x8
    struct DS_Object_Info *pObject; // offset 0x0, size 0x4
    void *pAddress;                 // offset 0x4, size 0x4
} Record_Info;

typedef struct EntryRecord
{
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

typedef struct DS_Record
{
    // total size: 0x8
    float Time;               // offset 0x0, size 0x4
    u_char Actuater_LV;       // offset 0x4, size 0x1
    u_char Complement_Enable; // offset 0x5, size 0x1
    u_char Reserved[2];       // offset 0x6, size 0x2
} DS_Record;

typedef struct DS_Record_Header {
    // total size: 0x20
    unsigned char DataName[16]; // offset 0x0, size 0x10
    u_int Revision; // offset 0x10, size 0x4
    u_int Object_Num; // offset 0x14, size 0x4
    u_int Reserved[2]; // offset 0x18, size 0x8
} DS_Record_Header;

typedef struct DS_Record_Edit {
    // total size: 0x10
    struct DS_Record Record; // offset 0x0, size 0x8
    struct DS_Record_Edit * pPrev; // offset 0x8, size 0x4
    struct DS_Record_Edit * pNext; // offset 0xC, size 0x4
} DS_Record_Edit;

sh2gfw_ModelDraw_MAN *sh2gfw_Get_pMD(int chara_id);
void SCSetModel(SubCharacter *scp, int model, int anime);
int shCharacter_Manage_SetDataAdresss(SubCharacter *scp);

extern int Node_Current_Search(Record_Info *pInfo /* r2 */, float Time /* r29+0x10 */);

extern int Node_Next_Search(Record_Info *pInfo /* r2 */, float Time /* r29 */);
extern float Sequence_Different_Time_Get(void);
extern void TotalActuaterLV_Keeper(u_int ControllerID /* r2 */, u_int ActuaterType /* r2 */, float ActuaterLV /* r29 */);
extern void Sequencer_Type_Hispeed(EntryRecord *pER /* r16 */);

static u_int EntryRecord_EntryFreeCount_Get(void);
static u_int EntryRecord_EntryCount_Increment(void);
static u_int EntryRecord_Handle_Create(void);
static u_int EntryRecord_ID_Search(u_int ID /* r18 */);
static u_int EntryRecord_Attribute_Search(u_int Attribute /* r18 */);
static EntryRecord * EntryRecordTable_FreeSpace_Search(void);
static u_int DSR_FileFormat_ErrorChecker(DS_Record_Header * pHeader /* r16 */);
static u_int EntryRecord_Entry(u_int * pHandleArray /* r21 */, DS_Record_Header * pHeader /* r20 */, u_int ControllerID /* r19 */, float Ratio /* r20 */);


static void Sequencer_Type_Hispeed(EntryRecord * pER /* r16 */);
static void Sequencer_Type_Lowspeed(EntryRecord * pER /* r18 */);
static void Sequencer_Type_Hispeed_Edit(EntryRecord * pER /* r16 */);
static void Sequencer_Type_Lowspeed_Edit(EntryRecord * pER /* r16 */);
static u_int EntryRecord_Enable_Check(EntryRecord * pER /* r2 */);
static u_int EntryRecord_TimeOver_Check(EntryRecord * pER /* r2 */);
static u_int EntryRecord_Type_Get(EntryRecord * pER /* r2 */);
static u_int EntryRecord_Condition_Get(EntryRecord * pER /* r2 */);
static u_int EntryRecord_Handle_Get(EntryRecord * pER /* r2 */);
static EntryRecord * EntryRecord_Get_fromTableIndex(u_int EntryTable_Index /* r2 */);
static u_int EventMessage_Post(u_int Handle /* r2 */, u_int EventID /* r2 */, float Value /* r29+0x30 */);

static float ActuaterLV_Complement(DS_Record * pDSR /* r2 */, float Time /* r29 */);

static DS_Record_Edit * EditNode_Current_Search(Record_Info * pInfo /* r2 */, float Time /* r29 */);
static float ActuaterLV_Complement_Edit(DS_Record_Edit * pDSR /* r2 */, float Time /* r29 */);


#endif
