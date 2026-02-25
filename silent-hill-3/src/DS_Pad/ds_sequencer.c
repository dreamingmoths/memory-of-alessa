
#include "common.h"
#include "DS_Pad/ds_sequencer.h"

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013B520);

void Sequencer_Type_Hispeed(MysterySequenceData *unk, EntryRecord *pER)
{
    DS_Record *pDSR;
    Record_Info *pInfo;

    int Node;
    int Node_Next;
    u32 now_act_lv_i;

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
            section_1 = section_0 + Sequence_Different_Time_Get(unk);

            if ((section_0 <= time) && (time < section_1))
            {
                now_act_lv_i = pDSR->Actuater_LV ? 1 : 0;
            }
        }

        now_act_lv_i *= pER->Ratio > 0.0f ? 1 : 0;
        unk->data.ActuaterLV[0] += now_act_lv_i;
    }
}

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013B840);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013B900);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013BA30);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013BAC0);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", Sequence_Different_Time_Get);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013BAE0);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013BAF0);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013BB20);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013BB30);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013BB40);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013BB50);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013BB90);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013BBD0);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013BBE0);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013BBF0);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013BC00);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013C110);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013C190);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013C210);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013C250);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013C2A0);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013C2F0);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013C330);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013C340);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013C5F0);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013C6B0);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013C6F0);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013C790);

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

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013C8C0);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013C900);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013CA30);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013CA80);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013CA90);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013CAA0);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013CB20);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013CBA0);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013CC30);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013CC40);

INCLUDE_ASM("asm/nonmatchings/DS_Pad/ds_sequencer", func_0013CCC0);
