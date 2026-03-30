#ifndef HH_MEMORY_MANAGE_H
#define HH_MEMORY_MANAGE_H

#include "sh2_common.h"

#define MEMORY_BLOCK_PACKET 0
#define MEMORY_BLOCK_OBJECT_WORK 1
#define MEMORY_BLOCK_TEXTURE_BUFFER 2

extern void HH_Class_Object_Initialize(void);
extern u_int HH_Effect_Object_Texture_DesignateEntryLevel_Discard(u_int Entry_Level /* r2 */);
extern u_int HH_Effect_Object_Texture_DesignateEntryLevel_Initialize(u_int Entry_Level /* r17 */);
extern void * MemShareGetEffect2WorkAddr(void);

u_int HH_MemoryManager_AllocateMemoryBlock_Check(u_int MemoryBlock_Type /* r2 */);

void * HH_MemoryManager_AllocateMemoryBlock_Get(u_int MemoryBlock_Type /* r2 */);

void * HH_MemoryManager_DesignateSize_Alignment16Address_Calculator(void * pAddress /* r2 */, u_int Size /* r2 */, u_int Number /* r2 */);

void * HH_MemoryManager_DesignateSize_Alignment64Address_Calculator(void * pAddress /* r2 */, u_int Size /* r2 */, u_int Number /* r2 */);

u_int HH_MemoryManager_MemoryBlock_All_Allocate();

u_int HH_MemoryManager_MemoryBlock_Allocate_Packet_and_ObjectWork();

u_int HH_MemoryManager_MemoryBlock_Allocate_TextureBuffer();

u_int HH_MemoryManager_MemoryBlock_All_Discard();

#endif
