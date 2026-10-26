#include "sh2_common.h"
#include "Chacter_Draw/vifot/sh_kt_vif1ot2.h"

static void Init2ndOT(ktVif1Ot2* ot);
static void Make2ndOT(ktVif1Ot2* ot);
static void Sort2(sceDmaTag* top_2, sceDmaTag* p);
static void SetNext(sceDmaTag* tag, sceDmaTag* p);
static sceDmaTag* Next(sceDmaTag* tag);
static u_int Depth2(sceDmaTag* tag);
static sceDmaTag* Link(sceDmaTag* tag);
UNMIGRATED (/* static */ sceDmaTag term); // size: 0x10, address: 0x2A94A0

#line 221
void ktVif1Ot2Init(ktVif1Ot2* ot, u_int n_bits_1, sceDmaTag* top_1, u_int n_bits_2, sceDmaTag* top_2) {
    sceDmaTag* p;
    int i;
    
    ot->top_1 = top_1;
    ot->top_2 = top_2;
    ot->n_bits_1 = n_bits_1;
    ot->n_bits_2 = n_bits_2;
    ot->length_1 = 1 << n_bits_1;
    ot->length_2 = 1 << n_bits_2;
    ot->mask_1 = (1 << n_bits_1) - 1;
    ot->mask_2 = ((1 << (n_bits_1 + n_bits_2)) - 1) - ot->mask_1;
    
    
    
    
    memset(ot->top_2, 0, ot->length_2 * sizeof(sceDmaTag));
    for (i = 0, p = ot->top_2; i < ot->length_2; i++, p++) {
        p->id = 32;
    }
    
    
    ktVif1Ot2Reset(ot);
    
    FlushCache(0);
}

#line 256
void ktVif1Ot2Reset(ktVif1Ot2* ot) {
    sceDmaTag* top = ot->top_1;
    u_int length = ot->length_1;
    
    memset(top, 0, sizeof(sceDmaTag) * length);
}

#ifdef NON_MATCHING
#line 264
void ktVif1Ot2Append(ktVif1Ot2* ot, u_int depth, u_long128* packet_) {
    u_int depth_1, depth_2;
    sceDmaTag* trunk;
    sceDmaTag* packet;
    
    depth_1 = depth & ot->mask_1;
    depth_2 = depth >> ot->n_bits_1;
    trunk = &ot->top_1[depth_1];
    packet = (sceDmaTag* ) packet_;
    
    
    packet->mark = depth_2;
    packet->next = trunk->next;
    trunk->next = packet;
}

#else
INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/vifot/sh_kt_vif1ot2", ktVif1Ot2Append);
#endif

#ifdef NON_MATCHING
#line 280
void ktVif1Ot2AppendFake(ktVif1Ot2* ot, u_int depth, u_long128* packet_, void* entity_) {
    u_int depth_1;
    u_int depth_2;
    sceDmaTag* trunk;
    sceDmaTag* packet;
    sceDmaTag* entity;


    
    depth_1 = depth & ot->mask_1;
    depth_2 = depth >> ot->n_bits_1;
    trunk = &ot->top_1[depth_1];
    entity = entity_;
    packet = (sceDmaTag* ) packet_;

    
    entity->mark = depth_2;
    entity->next = trunk->next;
    trunk->next  = packet;
}

#else
INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/vifot/sh_kt_vif1ot2", ktVif1Ot2AppendFake);
#endif

#line 301 
static void Init2ndOT(ktVif1Ot2* ot) {
    u_int length_2;
    sceDmaTag* top_2;
    sceDmaTag* pTagNext;
    int i;

    
    
    
    length_2 = ot->length_2;
    top_2 = ot->top_2;
    pTagNext = top_2;
    
    
    for (i = 0; i < length_2 - 1; i++, pTagNext++) {
        pTagNext->next = pTagNext + 1;
    
    }
    
    
    pTagNext->next = &term;













}

#line 355
static void Make2ndOT(ktVif1Ot2* ot) {
    
    sceDmaTag* top_2 = ot->top_2;
    sceDmaTag* top_1;
    s32 length_1, i;
    sceDmaTag* p, *link;
    
    top_1 = ot->top_1;
    length_1 = ot->length_1;

    
    for(i = length_1 - 1; i >= 0; i--) {
        p = Link(&top_1[i]);
        while (p != NULL) {
            link = Link(p);
            Sort2(top_2, p);
            p = link;
        }
    }
    
    
    SyncDCache(top_2, &top_2[ot->length_2]);






}

static void Sort2(sceDmaTag* top_2, sceDmaTag* p) {
    u_int depth_2 = Depth2(p);
    sceDmaTag* trunk = &top_2[depth_2];
    
    SetNext(p, Next(trunk));
    SetNext(trunk, p);
}

static void SetNext(sceDmaTag* tag, sceDmaTag* p) {
    tag->next = p;
}

static sceDmaTag* Next(sceDmaTag* tag) {
    return tag->next;
}

static u_int Depth2(sceDmaTag* tag) {
    return tag->mark;
}

static sceDmaTag* Link(sceDmaTag* tag) {
    return tag->next;
}

#line 439
void ktVif1Ot2KickPre(ktVif1Ot2* ot) {
   
    
    Init2ndOT(ot);
    
    Make2ndOT(ot);
    
    ktVif1Ot2Reset(ot);
}
