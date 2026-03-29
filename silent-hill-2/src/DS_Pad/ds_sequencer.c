// E:\work\sh2(CVS全取得)\src\DS_Pad\ds_sequencer.c
#include "ds_sequencer.h"

void SequencerManager() {
    u_int i;
    EntryRecord *pER;
    u_int Handle;
    for (i = 0; i < 0x14U; i++) {
        pER = EntryRecord_Get_fromTableIndex(i);


        if (EntryRecord_Enable_Check(pER) != 0) {
            Handle = EntryRecord_Handle_Get(pER);


            switch (EntryRecord_Condition_Get(pER)) {
                case 2:

                    
                switch (EntryRecord_Type_Get(pER)) {
                    case 0:
                        Sequencer_Type_Hispeed(pER);
                        break;
                    case 1:
                        Sequencer_Type_Lowspeed(pER);
                        break;
                    case 2:
                        Sequencer_Type_Hispeed_Edit(pER);
                        break;
                    case 3:
                        Sequencer_Type_Lowspeed_Edit(pER);
                        break;
                }

                EventMessage_Post(Handle, 2U, 0.0f);

                if (EntryRecord_TimeOver_Check(pER) != 0) {
                    switch (EntryRecord_Type_Get(pER))
                    {
                    case 0:
                    case 1:
                        EventMessage_Post(Handle, 1U, 0.0f);
                        break;
                    case 2:
                    case 3:
                        EventMessage_Post(Handle, 6U, 0.0f);
                        EventMessage_Post(Handle, 3U, 0.0f);
                        break;
                    }
                }
                
                case 1:
                case 3:
                case 0: {
                    break;
                }
            }
        }
    }
}

void Sequencer_Type_Hispeed(EntryRecord *pER)
{
    DS_Record *pDSR;
    Record_Info *pInfo;

    int Node;
    int Node_Next;
    u_int now_act_lv_i;

    float time;
    float section_0;
    float section_1;

    pInfo = &pER->Info;
    time = pER->Time_Count;
    Node = Node_Current_Search(pInfo, time);
    Node_Next = Node_Next_Search(pInfo, time);

    if ((Node != -1) && (Node_Next != -1))
    {
        pDSR = (DS_Record *)pInfo->pAddress + Node;
        now_act_lv_i = 0;
        if (pDSR->Complement_Enable != 0)
        {
            now_act_lv_i = pDSR->Actuater_LV ? 1 : 0;
        }
        else
        {
            section_0 = pDSR->Time;
            section_1 = section_0 + Sequence_Different_Time_Get();
            if ((section_0 <= time) && (time < section_1))
            {
                now_act_lv_i = pDSR->Actuater_LV ? 1 : 0;
            }
        }

        now_act_lv_i *= pER->Ratio > 0.0f ? 1 : 0;

        TotalActuaterLV_Keeper(
            pER->Controller_ID,
            0u,
            now_act_lv_i);
    }
}

static void Sequencer_Type_Lowspeed(EntryRecord * pER /* r18 */)  {

    Record_Info * pInfo; // r16
    float time; // r20
    int Node; // r17
    int Node_Next; // r2
    DS_Record * pDSR; // r2
    float now_act_lv_f; // r29+0x50

    pInfo = &pER->Info;
    time = pER->Time_Count;
    Node = Node_Current_Search(pInfo, time);
    Node_Next = Node_Next_Search(pInfo, time);
    if ((Node != -1) && (Node_Next != -1)) {
        pDSR = (DS_Record*)pInfo->pAddress + Node;
        now_act_lv_f = 0.0f;
        if (pDSR->Complement_Enable != 0) {
            now_act_lv_f = ActuaterLV_Complement(pDSR, time);
        }
        
        now_act_lv_f *= pER->Ratio;
        TotalActuaterLV_Keeper(pER->Controller_ID, 1, now_act_lv_f);

    }
}

static void Sequencer_Type_Hispeed_Edit(EntryRecord * pER /* r16 */) {

    Record_Info * pInfo; // r2
    float time; // r20   
    DS_Record_Edit * pDSR; // r17
    u_int now_act_lv_i; // r18
    float section_0; // r21    
    float section_1; // r29+0x50
    
    time = pER->Time_Count;
    pDSR = EditNode_Current_Search(&pER->Info, time);
    if ((pDSR != NULL) && (pDSR->pNext != NULL)) {
        now_act_lv_i = 0;
        if (pDSR->Record.Complement_Enable != 0) {
            now_act_lv_i = pDSR->Record.Actuater_LV ? 1 : 0;
        } else {
            section_0 = pDSR->Record.Time;
            section_1 = section_0 + Sequence_Different_Time_Get();
            if ((section_0 <= time) && (time < section_1)) {
                now_act_lv_i = pDSR->Record.Actuater_LV ? 1 : 0;
            }
        }

        now_act_lv_i *= (pER->Ratio > 0.0f) ? 1 : 0;
        TotalActuaterLV_Keeper(pER->Controller_ID, 0, now_act_lv_i);
    }
}

static void Sequencer_Type_Lowspeed_Edit(EntryRecord * pER /* r16 */)  {

    Record_Info * pInfo; // r2
    float time; // r20
    DS_Record_Edit * pDSR; // r2    
    float now_act_lv_f; // r29+0x30

    time = pER->Time_Count;
    pDSR = EditNode_Current_Search(&pER->Info, time);
    if ((pDSR != NULL) && (pDSR->pNext != NULL)) {
        now_act_lv_f = 0.0f;
        if (pDSR->Record.Complement_Enable != 0) {
            now_act_lv_f = ActuaterLV_Complement_Edit(pDSR, time);
        }
        
        now_act_lv_f *= pER->Ratio;
        TotalActuaterLV_Keeper(pER->Controller_ID, 1, now_act_lv_f);
    }
}

static float ActuaterLV_Complement(DS_Record * pDSR /* r2 */, float Time /* r29 */) {

    float result; // r29
    float time_current; // r29    
    float time_next; // r29
    float comp_ratio; // r3
    float act_lv_current; // r29    
    float act_lv_next; // r29
    
    time_current = pDSR->Time;
    time_next = pDSR[1].Time;
    comp_ratio = (Time - time_current) / (time_next - time_current);
    act_lv_current = pDSR->Actuater_LV;
    act_lv_next = pDSR[1].Actuater_LV;
    result = act_lv_next * comp_ratio + act_lv_current * (1.0f - comp_ratio);
    
    return result;
}

static float ActuaterLV_Complement_Edit(DS_Record_Edit * pDSR /* r2 */, float Time /* r29 */) {

    float result; // r29
    float time_current; // r29
    float time_next; // r29
    float comp_ratio; // r3  
    float act_lv_current; // r29
    float act_lv_next; // r29

    time_current = pDSR->Record.Time;
    time_next = pDSR->pNext->Record.Time;
    comp_ratio = (Time - time_current) / (time_next - time_current);
    act_lv_current = pDSR->Record.Actuater_LV;
    act_lv_next = pDSR->pNext->Record.Actuater_LV;
    result = act_lv_next * comp_ratio + act_lv_current * (1.0f - comp_ratio);
    return result;
        
}


static int Node_Next_Search(Record_Info* pInfo, float Time) {
    u_int node_num = pInfo->pObject->DataNode_num;
    DS_Record * pDSR = pInfo->pAddress;

    int result = -1;
    u_int i;
    for (i = 0; i < node_num; i++, pDSR++) {
        if (Time < pDSR->Time) {
            result = i;
            break;
        }
    }

    return result;
}

static int Node_Current_Search(Record_Info * pInfo /* r2 */, float Time /* r29+0x10 */) {
    signed int result = -1; // r7
    signed int num = Node_Next_Search(pInfo, Time); // r2

    if (num > 0) {
        result = num - 1;
    }

    return result;
}

static DS_Record_Edit *EditNode_Current_Search(Record_Info *pInfo, float Time) {
    DS_Record_Edit * result;
    DS_Record_Edit * pDSR;

    result = NULL;
    pDSR = (DS_Record_Edit *)pInfo->pAddress;
    while (pDSR != NULL) {
        if (Time < pDSR->Record.Time) {
            result = pDSR->pPrev;
            break;
        }
        pDSR = pDSR->pNext;
    }
    return result;
}

// | Permission | Meaning                            |
// | ---------- | ---------------------------------- |
// | 0          | always allowed                     |
// | 1          | block if attribute already exists  |
// | 2          | block if ID already exists         |
// | 3          | block if attribute OR ID exists    |
// | 4          | block if attribute AND ID exists   |
#define DSR_PERMISSION_NONE        0
#define DSR_PERMISSION_ATTRIBUTE   1
#define DSR_PERMISSION_ID          2
#define DSR_PERMISSION_ATTR_OR_ID  3
#define DSR_PERMISSION_ATTR_AND_ID 4

u_int EntryRecord_Entry(u_int* pHandleArray, DS_Record_Header* pHeader, u_int ControllerID, f32 Ratio) {
    unsigned int result = 0; // r16
    unsigned int i; // r16

    // validate header & check that we have room for this record
    if ((DSR_FileFormat_ErrorChecker(pHeader) == 0) && (EntryRecord_EntryFreeCount_Get() >= pHeader->Object_Num)) {    
        unsigned int permission_check = 1;
        DS_Object_Info * pObject_Info = (DS_Object_Info*) (pHeader + 1);

        // check if we have permission to create the record

        switch (pObject_Info->Permission) {        
        case DSR_PERMISSION_ATTRIBUTE:
            if (EntryRecord_Attribute_Search(pObject_Info->Attribute) != 0) {
                permission_check = 0;
            }
            break;
        case DSR_PERMISSION_ID:
            if (EntryRecord_ID_Search(pObject_Info->ID) != 0) {
                permission_check = 0;
            }
            break;
        case DSR_PERMISSION_ATTR_OR_ID:
            if ((EntryRecord_Attribute_Search(pObject_Info->Attribute) != 0) || (EntryRecord_ID_Search(pObject_Info->ID) != 0)) {
                permission_check = 0;
            }
            break;
        case DSR_PERMISSION_ATTR_AND_ID:
            if ((EntryRecord_Attribute_Search(pObject_Info->Attribute) != 0) && (EntryRecord_ID_Search(pObject_Info->ID) != 0)) {
                permission_check = 0;
            }
            break;
        case DSR_PERMISSION_NONE:
            break;
        }

        // 0 & 1 are of a fixed size, and 2 & 3 have dynamic size
        if (permission_check != 0) {
            switch (pObject_Info->Type) {
                case 0:
                case 1: {
                    for (i = 0; i < pHeader->Object_Num; i++, pObject_Info++) {
                        EntryRecord * pER = EntryRecordTable_FreeSpace_Search();
                        pER->Enable = 1;
                        pER->Controller_ID = (u_short) ControllerID;
    
                        pER->Handle = EntryRecord_Handle_Create();
                        pER->Ratio = Ratio;
                        pER->Info.pObject = pObject_Info;
                        pER->Info.pAddress = (void*)((u_int)pHeader + pObject_Info->Offset);
    
                        pER->Time_Max = ((DS_Record*)pER->Info.pAddress + pER->Info.pObject->DataNode_num - 1)->Time;
    
                        if (pHandleArray != NULL) {
                            pHandleArray[i] = pER->Handle;
                        }
    
                        EntryRecord_EntryCount_Increment();
                    }
                    break;
                }
                case 2:
                case 3: {
                    for (i = 0; i < pHeader->Object_Num; i++, pObject_Info++) {
                        EntryRecord * pER = EntryRecordTable_FreeSpace_Search();
                        DS_Record_Edit * pTail; // r2
                        pER->Enable = 1;
                        pER->Controller_ID = (u_short) ControllerID;
                        pER->Handle = EntryRecord_Handle_Create();
                        pER->Ratio = Ratio;
                        pER->Info.pObject = pObject_Info;
                        pER->Info.pAddress = (void* ) pObject_Info->Offset;
    
    
                        pTail = pER->Info.pAddress;

                        while (pTail->pNext != NULL) {
                            pTail = pTail->pNext;
                        }
                        pER->Time_Max = pTail->Record.Time;
    
                        
                        if (pHandleArray != NULL) {
                            pHandleArray[i] = pER->Handle;
                        }
    
                        EntryRecord_EntryCount_Increment();
                    }
                    break;
                }
            }
    
            result = 1;


        }
    }
    return result;
}
