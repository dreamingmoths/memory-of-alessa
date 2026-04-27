#include "Effect2/hh_class_object_execute.h"
#include "Effect2/hh_effect_object_def.h"
#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_packet.h"
#include "Event/stg_name.h"
#include "Chacter/character.h"
#include "common.h"

static void Prefix_Operation(void);

static void Suffix_Operation(void);

static void Debug_Functions(void);

static void Prefix_Operation(void) { /* empty */ }

static void Suffix_Operation(void) { /* empty */ }

static void Debug_Functions(void) { /* empty*/ }

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_object_execute", HH_Class_Object_Initialize);

void HH_Class_Object_Execute(void) {
    if (HH_Vif1PacketBuffer_Memory_Allocate_Check()) {
        HH_ClassWrapper_Matrix_Group_Update();
        HH_Vif1PacketBuffer_Initialize();
        HH_Vif1PacketBuffer_Prefix_GifTag_Open();
        Prefix_Operation();
        Debug_Functions();
        HH_Effect_Object_Manager();
        Suffix_Operation();
        HH_Vif1PacketBuffer_Suffix_GifTag_Open();
    }
}

void HH_Class_Object_Packet_Kick(void) {
    if (HH_Vif1PacketBuffer_Memory_Allocate_Check()) {
        HH_Vif1Packet_Send();
    }
}

#ifdef NON_MATCHING
void HH_Effect_Object_Blood_Pool_Impact_Post(float* Location) {
    ImpactQueue_Element descriptor; // r29+0x20

    int room_name  = RoomNameJms();

    switch (room_name) {
        case 0x63: 
        case 0x62: 
        case 0x80: 
        case 0x85: 
        case 0x7A: 
        case 0x7C: 
        case 0x7E: 
        case 0x82: 
        case 0xBB: 
        case 0xB6: 
        case 0xB7: 
        case 0xAB: 
        case 0xB8: 
        case 0xB9: 
        case 0x21: {

            
            float dir[4] /* = {0.0f, 0.0f, 0.0f, 0.0f} */; // r29+0x60
            
            descriptor.Class_Descriptor = 4;
            sceVu0CopyVector(&descriptor.Option.Vector[1], &dir);
            
            break;
        }
        default: descriptor.Class_Descriptor = 3;
    }

    
    descriptor.hInstance = 0;
    descriptor.pResultHandle_Address = 0;
    sceVu0CopyVector(&descriptor.Option, Location);

    
    ImpactDescriptor_Post(HH_Effect_Object_Infomeation_Get(), &descriptor);
}
#else 
INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_object_execute", HH_Effect_Object_Blood_Pool_Impact_Post);
#endif

void HH_Effect_Object_Blood_Splash_Impact_Post(float* Location, float* Direction, u_int Scp_Address, u_int Impact_Kind) {
    
    int room_name = RoomNameJms(); // r2
    ImpactQueue_Element descriptor; // r29+0x50
    SubCharacter* pSubChar; // r2

    switch (room_name) {
        case 7:
        case 33:
            descriptor.Class_Descriptor = 7;
            break;
        default:
            descriptor.Class_Descriptor = 5;
            break;
    }

    
    descriptor.hInstance = 0;
    descriptor.pResultHandle_Address = 0;
    
    
    pSubChar = (SubCharacter*) Scp_Address;
    sceVu0CopyVector(&descriptor.Option.Vector[0], &pSubChar->pos);
    descriptor.Option.Vector[0][1] = Location[1];
    descriptor.Option.Int_Value[0] = Scp_Address;
    if (Impact_Kind != 0) {
        float _Direction[4]; // r29+0x90

        
        sceVu0ScaleVectorXYZ(&_Direction, Direction, 5.0f);
        _Direction[0] *= -1.0f;
        _Direction[2] *= -1.0f;
        sceVu0CopyVector(&descriptor.Option.Vector[1], _Direction);
    } else {
        float _Direction[4]; // r29+0xA0
        
        
        sceVu0Normalize(_Direction, Direction);
        sceVu0ScaleVectorXYZ(_Direction, _Direction, 2000.0f);
        sceVu0CopyVector(&descriptor.Option.Vector[1], _Direction);
    }
    ImpactDescriptor_Post(HH_Effect_Object_Infomeation_Get(), &descriptor);
}


INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_object_execute", HH_Effect_Object_Ground_Impact_Post);

void HH_Effect_Object_Ground_Impact_Post_forEnemy(float* Foot_Location, u_int Foot_Kind) {
    int room_name = RoomNameJms(); // r2
    ImpactQueue_Element descriptor; // r29+0x30

    switch (room_name) {
        case 0x63: 
        case 0x80:
        case 0x85:
        case 0x7A:
        case 0x7C:
        case 0x7E:
        case 0x82:
        case 0xB6:
        case 0xB7:
        case 0xB8:
        case 0xB9:
        case 0x21:
        case 0x25:
        case 0x26:
            descriptor.hInstance = 0;
            descriptor.pResultHandle_Address = 0;
            sceVu0CopyVector(&descriptor.Option.Vector[0], Foot_Location);
            sceVu0CopyVector(&descriptor.Option.Vector[1], Foot_Location);
            descriptor.Class_Descriptor = 2;
            descriptor.Option.Vector[0][1] -= 50.0f;
            descriptor.Option.Vector[1][1] -= 50.0f;
            descriptor.Option.Int_Value[0] = Foot_Kind;
            ImpactDescriptor_Post(HH_Effect_Object_Infomeation_Get(), &descriptor);
    }
}

void HH_Effect_Object_WaterSplash_Impact_Post(float* Location) {
    static float direction[4] = {0.0f, -2500.0f, 0.0f, 1.0f}; // @ 0x0036ED30
    static float hoge = 3500.0f; // @ 0x0036ED40
    ImpactQueue_Element descriptor; // r29+0x10

    descriptor.hInstance = 0;
    descriptor.pResultHandle_Address = 0;
    sceVu0CopyVector(&descriptor.Option.Vector[0], Location);
    sceVu0CopyVector(&descriptor.Option.Vector[1], &direction);
    descriptor.Class_Descriptor = 18;
    descriptor.Option.Vector[0][1] -= 50.0f;
    descriptor.Option.Vector[1][1] -= 50.0f;
    descriptor.Option.Float_Value[0] = hoge;
    descriptor.Option.Int_Value[0] = 1;
    ImpactDescriptor_Post(HH_Effect_Object_Infomeation_Get(), &descriptor);
}
