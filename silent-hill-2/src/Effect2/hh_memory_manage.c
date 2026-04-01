#include "Effect2/hh_memory_manage.h"
#include "Effect2/hh_class_object_execute.h"
#include "Effect2/hh_effect_object_texture.h"
#include "SH2_common/mem_share.h"

static u_long128 _texture_buffer_always[1][17536];

static void* _pMemroyBlock_Table[4] = {
    0, // MEMORY_BLOCK_PACKET
    0, // MEMORY_BLOCK_OBJECT_WORK
    0, // MEMORY_BLOCK_TEXTURE_BUFFER
    &_texture_buffer_always
};

static u_int MemoryBlock_Allocate(u_int MemoryBlock_Type, void * pAddress);

static u_int AllocateMemoryBlock_Check(u_int MemoryBlock_Type);

static void * AllocateMemoryBlock_Get(u_int MemoryBlock_Type);

static u_int AllocateMemoryBlock_Release(u_int MemoryBlock_Type);

static void * AllocateMemoryBlock_Get(u_int MemoryBlock_Type);

static u_int AllocateMemoryBlock_Release(u_int MemoryBlock_Type);

static u_int MemoryBlock_Allocate(u_int MemoryBlock_Type, void * pAddress) {
    u_int result = 1;
    _pMemroyBlock_Table[MemoryBlock_Type] = pAddress;

    return result;
}

static u_int AllocateMemoryBlock_Check(u_int MemoryBlock_Type) {
    u_int result = 0;

    if (AllocateMemoryBlock_Get(MemoryBlock_Type) != NULL) {
        result = 1;
    }
    return result;
}

static void* AllocateMemoryBlock_Get(u_int MemoryBlock_Type) {
    return _pMemroyBlock_Table[MemoryBlock_Type];
}

static u_int AllocateMemoryBlock_Release(u_int MemoryBlock_Type) {
    u_int result = 0;


    if (_pMemroyBlock_Table[MemoryBlock_Type] != NULL) {

        _pMemroyBlock_Table[MemoryBlock_Type] = NULL;

        result = 1;
    }

    return result;
}

u_int HH_MemoryManager_AllocateMemoryBlock_Check(u_int MemoryBlock_Type) {
    return AllocateMemoryBlock_Check(MemoryBlock_Type);
}

void* HH_MemoryManager_AllocateMemoryBlock_Get(u_int MemoryBlock_Type) {
    return AllocateMemoryBlock_Get(MemoryBlock_Type);
}

void* HH_MemoryManager_DesignateSize_Alignment16Address_Calculator(void* pAddress, u_int Size, u_int Number) {
    void * result; // r2
    u_int Next_Address; // r2
    u_int Address = (u_int) pAddress;

    if ((Address & 0xF) == 0) {
        pAddress = (void*) (Address + Size * Number);

        if ((u_int) pAddress & 0xF) {
            
            Next_Address = ((u_int) pAddress - (((u_int) pAddress & 0xF))) + 0x10;
            pAddress = (void*) Next_Address;
        }
        return pAddress;
    } else 
        ASSERT_ON_LINE(0, 243);
}

void* HH_MemoryManager_DesignateSize_Alignment64Address_Calculator(void* pAddress, u_int Size, u_int Number) {
    void * result; // r2
    u_int Next_Address; // r2
    u_int Address = (u_int) pAddress;

    if ((Address & 0x3F) == 0) {
        pAddress = (void*) (Address + Size * Number);

        if ((u_int) pAddress & 0x3F) {            
            Next_Address = ((u_int) pAddress - (((u_int) pAddress & 0x3F))) + 0x40;
            pAddress = (void*) Next_Address;
        }
        return pAddress;
    } else
        ASSERT_ON_LINE(0, 273);
}

u_int HH_MemoryManager_MemoryBlock_All_Allocate(void) {
    u_int result = 0; // r16
    void * pAddress; // r2


    if ((pAddress = MemShareGetEffect2WorkAddr()) != 0) {
        result = 1;
    } else {
        if ((pAddress = MemShareGetEffect2WorkAddr()) != 0) {
            result = 1;
        }
    }
    if (result != 0) {

        u_int Base = (u_int) pAddress;
        u_int End;

        
        MemoryBlock_Allocate(MEMORY_BLOCK_PACKET, pAddress);
        pAddress = HH_MemoryManager_DesignateSize_Alignment64Address_Calculator(pAddress, 0x60000U, 1);
        
        MemoryBlock_Allocate(MEMORY_BLOCK_OBJECT_WORK, pAddress);
        pAddress = HH_MemoryManager_DesignateSize_Alignment64Address_Calculator(pAddress, 0x80000U, 1);
        

        MemoryBlock_Allocate(MEMORY_BLOCK_TEXTURE_BUFFER, pAddress);
        pAddress = HH_MemoryManager_DesignateSize_Alignment64Address_Calculator(pAddress, 0x44800, 4);
        End = (u_int) pAddress;
        
        printf("All Allocate Size = %d kB\n", (End - Base) >> 10);
    }

    
    return result;
}

u_int HH_MemoryManager_MemoryBlock_Allocate_Packet_and_ObjectWork(void) {
    u_int result = 0;
    void* pAddress;


    if ((pAddress = MemShareGetEffect2WorkAddr()) != NULL) {
        result = 1;
    } else {
        if ((pAddress = MemShareGetEffect2WorkAddr()) != NULL) {
            result = 1;
        }
    }
    if (result != 0) {

        MemoryBlock_Allocate(MEMORY_BLOCK_PACKET, pAddress);
        pAddress = HH_MemoryManager_DesignateSize_Alignment64Address_Calculator(pAddress, 0x60000, 1);
        MemoryBlock_Allocate(MEMORY_BLOCK_OBJECT_WORK, pAddress);


        
        HH_Class_Object_Initialize();
    }
    return result;
}

u_int HH_MemoryManager_MemoryBlock_Allocate_TextureBuffer(void) {
    u_int result = 0;
    void* pAddress;


    if ((pAddress = MemShareGetEffect2WorkAddr()) != NULL) {
        result = 1;
    } else {
        if ((pAddress = MemShareGetEffect2WorkAddr()) != NULL) {
            result = 1;
        }
    }
    if (result != 0) {

        pAddress = HH_MemoryManager_DesignateSize_Alignment64Address_Calculator(pAddress, 0x60000, 1);
        pAddress = HH_MemoryManager_DesignateSize_Alignment64Address_Calculator(pAddress, 0x80000, 1);
        MemoryBlock_Allocate(MEMORY_BLOCK_TEXTURE_BUFFER, pAddress);

        
        HH_Effect_Object_Texture_DesignateEntryLevel_Initialize(2);
        HH_Effect_Object_Texture_DesignateEntryLevel_Initialize(3);
    }
    
    return result;
}

u_int HH_MemoryManager_MemoryBlock_All_Discard(void) {
    u_int result = 1;
    
    HH_Effect_Object_Texture_DesignateEntryLevel_Discard(2);

    result *= AllocateMemoryBlock_Release(0);
    result *= AllocateMemoryBlock_Release(1);
    result *= AllocateMemoryBlock_Release(2);

    return result;
}
