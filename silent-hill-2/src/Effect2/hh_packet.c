#include "Effect2/hh_packet.h"
#include "Effect2/hh_memory_manage.h"

#include "sce/libgraph.h"

// @todo: migrate .data

extern /* static */ u_long _GifTag_First[2]; // size: 0x8, address: 0x371720
extern /* static */ u_long _GifTag_Final[2]; // size: 0x8, address: 0x371730
extern /* static */ u_long _GifTag_GS_AD[2]; // size: 0x8, address: 0x371740
extern /* static */ u_long _GifTag_Sprite[2]; // size: 0x8, address: 0x371750
extern /* static */ u_long _GifTag_TriangleStrip[2]; // size: 0x8, address: 0x371760
extern /* static */ u_long _GifTag_TriangleFan[2]; // size: 0x8, address: 0x371770
extern /* static */ Queue_Object* pQueue; // size: 0x4, address: 0x371780

sceVif1Packet _Vif1_Packet; // size: 0x20, address: 0x1202290
/* static */ Queue_Object _queue; // size: 0x30, address: 0x1202260

static void QueueObject_Initialize(Queue_Object* pQueue);
static u_int QueueObject_enQueue(Queue_Object* pQueue, Queue_Element* pElement);
static u_int QueueObject_deQueue(Queue_Object* pQueue, Queue_Element* pElement);

static void QueueObject_Initialize(Queue_Object* pQueue) {
    pQueue->enQueue = 0;
    pQueue->deQueue = 0;
    pQueue->Length_Current = 0;
    pQueue->Length_Max = 8;
}

#pragma divbyzerocheck off

static u_int QueueObject_enQueue(Queue_Object* pQueue, Queue_Element* pElement) {
    u_int result = 0;

    if (pQueue->Length_Current < pQueue->Length_Max) {
        pQueue->Element[pQueue->enQueue++] = *pElement;
        pQueue->enQueue %= pQueue->Length_Max;
        pQueue->Length_Current++;
        result = 1;
    }
    return result;
}

static u_int QueueObject_deQueue(Queue_Object* pQueue, Queue_Element* pElement) {
    u_int result = 0;

    if (pQueue->Length_Current != 0) {
        *pElement = pQueue->Element[pQueue->deQueue++];
        pQueue->deQueue %= pQueue->Length_Max;
        pQueue->Length_Current--;
        result = 1;
    }
    return result;
}

#pragma divbyzerocheck on

u_int HH_Vif1PacketBuffer_Memory_Allocate_Check(void) {
    u_int result = 0;
    
    if (HH_MemoryManager_AllocateMemoryBlock_Check(0)) {
        result = 1;
    }
    return result;
}

sceVif1Packet* HH_Vif1Packet_Current_Get(void) {
    return &_Vif1_Packet;
}

void HH_Vif1PacketBuffer_Initialize(void) {
    u_long128* pPacketBuffer = HH_MemoryManager_AllocateMemoryBlock_Get(0);
    sceVif1Packet* pPacket = &_Vif1_Packet;
    
    sceVif1PkInit(pPacket, pPacketBuffer);
    QueueObject_Initialize(pQueue);

    
    
    
    {
        Queue_Element element = { NULL }; element.pAddress = _Vif1_Packet.pBase;        
        if (!QueueObject_enQueue(pQueue, &element)) {
            printf("----------Send Address Queue Over\n");
            ASSERT_ON_LINE(0, 397);
        }
    }
    
    sceVif1PkCnt(pPacket, 0);
    sceVif1PkOpenDirectCode(pPacket, 0);

}

void HH_Vif1PacketBuffer_Prefix_GifTag_Open(void) {
    sceVif1Packet* pPacket = &_Vif1_Packet;
    
    
    
    
    
    
    
    HH_Vif1PacketBuffer_GifTag_Open();
    sceVif1PkOpenGifTag(pPacket, *(u_long128*) _GifTag_First);
    
    
    
    *(u_long128*) pPacket->pCurrent = *(u_long128*) HH_ClassWrapper_GS_EnvironmentRegister_Frame_AlphaMask_Get();
    pPacket->pCurrent += 4;    
    sceVif1PkAddGsAD(pPacket, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF_1(448, SCE_GS_PSMCT16S, SCE_GS_TRUE));
    sceVif1PkAddGsAD(pPacket, SCE_GS_TEST_1, SCE_GS_SET_TEST_1(0, 1, 0, 0, 0, 0, 1, 2));
    
    
    
    
    
    
    
    
    
    
    
    sceVif1PkAddGsAD(pPacket, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP_1(1, 1, 0, 0, 0, 0));
    sceVif1PkAddGsAD(pPacket, SCE_GS_TEX1_1, SCE_GS_SET_TEX1_1(0, 0, 1, 5, 0, 3, 16));
}

void HH_Vif1PacketBuffer_Suffix_GifTag_Open(void) {
    sceVif1Packet* pPacket = &_Vif1_Packet;
    

    
    sceVif1PkCloseGifTag(pPacket);
    
    
    sceVif1PkOpenGifTag(pPacket, *(u_long128*) _GifTag_Final);
    
    sceVif1PkAddGsAD(pPacket, SCE_GS_TEST_1, SCE_GS_SET_TEST_1(1, 1, 0, 0, 0, 0, 1, 2));
    
    
    
    
    
    
    
    
    
    
    
    *(u_long128*) pPacket->pCurrent = *(u_long128*) HH_ClassWrapper_GS_EnvironmentRegister_Frame_NoMask_Get();
    pPacket->pCurrent += 4;
    sceVif1PkAddGsAD(pPacket, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF_1(448, SCE_GS_PSMCT16S, SCE_GS_FALSE));
    sceVif1PkAddGsAD(pPacket, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP_1(1, 1, 0, 0, 0, 0));
    
    sceVif1PkCloseGifTag(pPacket);
    
    HH_Vif1PacketBuffer_GifTag_Close();
}

void HH_Vif1PacketBuffer_GifTag_Open(void) {
    if (HH_Vif1Packet_FreePacketSize_Get() < 0) {
        printf("over size = %d\n", HH_Vif1Packet_FreePacketSize_Get());
        printf("%s:%d:packet over!!\n", "hh_packet.c", 495);
        ASSERT_ON_LINE(0, 496);
    }
}

void HH_Vif1PacketBuffer_GifTag_Close(void) {
    
    
    
    
    
    
    
    
    if (HH_Vif1Packet_FreePacketSize_Get() < 0) {
        printf("over size = %d\n", HH_Vif1Packet_FreePacketSize_Get());
        printf("%s:%d:packet over!!\n", "hh_packet.c", 535);
        ASSERT_ON_LINE(0, 536);
    }
}

void HH_Vif1Packet_Send(void) {
    sceVif1Packet* pPacket;
    Queue_Element element;
    int Command_ID;    
    pPacket = &_Vif1_Packet;
    sceVif1PkCloseDirectCode(pPacket);
    sceVif1PkEnd(pPacket, 0);
    sceVif1PkTerminate(pPacket);
    
    
    
    
    
    while (QueueObject_deQueue(pQueue, &element) != 0) {
        Command_ID = d1cSend(element.pAddress);
        
        
        
        
        
        
        
        
                
        
    } 

}

int HH_Vif1Packet_FreePacketSize_Get(void) {
    u_long128 *pPacketBuffer = HH_MemoryManager_AllocateMemoryBlock_Get(0);


    
    return ((u_int)(pPacketBuffer + 0x6000) / 16) - ((u_int)_Vif1_Packet.pCurrent / 16);

}

void HH_Vif1Packet_GeneralGifTag_GS_AD_Open(void) {
    sceVif1PkOpenGifTag(&_Vif1_Packet, *(u_long128*) _GifTag_GS_AD);
}

void HH_Vif1Packet_GeneralGifTag_Sprite_Open(void) {
    sceVif1PkOpenGifTag(&_Vif1_Packet, *(u_long128*) _GifTag_Sprite);
}

void HH_Vif1Packet_GeneralGifTag_TriangleStrip_Open(void) {
    sceVif1PkOpenGifTag(&_Vif1_Packet, *(u_long128*) _GifTag_TriangleStrip);
}

void HH_Vif1Packet_GeneralGifTag_TriangleFan_Open(void) {
    sceVif1PkOpenGifTag(&_Vif1_Packet, *(u_long128*) _GifTag_TriangleFan);
}
