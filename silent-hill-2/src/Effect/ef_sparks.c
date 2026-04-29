#include "Effect/ef_sparks.h"
#include "SH2_common/sh_vu0.h"

static void SetSparksSize(float* width, float* height);
static void SetSparksKind(int* kind);
static void SetSparksStartPos(int kind, float* trans);
static void SetSparksSpeed(int kind, float* speed);
static void SetSparksRGBA(int* rgba);
static void RenewSparksPos(EFCTSparksPlane* sparks);
static void DrawSparks(EFCTSparksObject* sparks);
static void CountSparksLifeTimer(EFCTSparksObject* sparks);
static void RenewSparksRGBA(EFCTSparksObject* sparks);
static void MoveSparks(EFCTSparksObject* sparks);
static void SetSparksVertex(float* pos, float width, float height, float* trans, EFCTVertexData* VertexData);

static void SetSparksSize(float* width /* r17 */, float* height /* r16 */) {
    *width = 20.0f + (5.0f * shRandF());
    *height = 20.0f + (5.0f * shRandF());
}

static void SetSparksKind(int* kind /* r16 */) {
    if (shRandF() > 0.5f) {
        *kind = 0;
        return;
    }
    *kind = 1;
}

static void SetSparksStartPos(int kind /* r17 */, float* trans /* r16 */) {

    float rate; // r29+0x30
    
    trans[0] = 150.0f * shRandF();
    if (kind == 0) {
        trans[0] = -trans[0];
    }
    trans[1] = 375.0f * (-1.0f * shRandF());
    rate = 50.0f;
    trans[2] = shSway1f(-rate, rate);
}

static void SetSparksSpeed(int kind /* r17 */, float* speed /* r16 */)  {

    float min; // r29+0x30
    float max; // r29+0x30
    
    speed[0] = 50.0f + (100.0f * shRandF());
    if (kind == 0) {
        speed[0] = -speed[0];
    }
    speed[1] = -625.0f + (-150.0f * shRandF());
    min = -100.0f;
    max = 100.0f;
    speed[2] = shSway1f(min, max);
}

static void SetSparksRGBA(int* rgba /* r16 */) {

    float rate; // r20
    rate = 0.3f + (0.7f * shRandF());
    rgba[0] = (u_short) (128.0f * rate);
    rgba[1] = (u_short) (120.0f * rate);
    rgba[2] = (u_short) (120.0f * rate);
    rgba[3] = 0x62;
}

static void RenewSparksPos(EFCTSparksPlane* sparks /* r16 */) {
    float ratio = shSinF(PI * (sparks->timer / sparks->life_span));
    sparks->pos[0] = sparks->speed[0] * ratio;
    sparks->pos[2] = sparks->speed[2] * ratio;


    ratio =  (sparks->timer / sparks->life_span);
    sparks->pos[1] = sparks->speed[1] * ratio;


    
}

void DrawSparks(EFCTSparksObject* sparks /* r16 */) {
    if (sparks == NULL) {
        printf("ef_sparks.c:216> assert:(%s)\n", "0"); //unsure about the second arg lmao
        while(1);
    }
    CountSparksLifeTimer(sparks);
    MoveSparks(sparks);
    RenewSparksRGBA(sparks);
    EFCTThreeDWork(&sparks->base_obj);
    ClipEffectObject2(&sparks->base_obj);
    DrawPrimitive(&sparks->base_obj);
}

static void CountSparksLifeTimer(EFCTSparksObject* sparks /* r17 */) {

    int i; // r8

    if (sparks != NULL) {    
        for (i = 0; i < 2; i++) {
            sparks->plane[i].timer += EFCTGetPassingTimePerFrame();
            if (sparks->plane[i].timer > sparks->plane[i].life_span) {
                sparks->plane[i].timer = 0.0f;
            }
        }
    }
}

static void RenewSparksRGBA(EFCTSparksObject* sparks /* r20 */) {

    float ratio; // r20
    int rgba[4]; // r29+0x70
    int i; // r16

    for (i = 0; i < 2; i++) {
        ratio = shSinF(PI * (0.5f * (1.0f + (sparks->plane[i].timer / sparks->plane[i].life_span))));
        rgba[0] = (u_short)(sparks->plane[i].rgba[0] * ratio);
        rgba[1] = (u_short)(sparks->plane[i].rgba[1] * ratio);
        rgba[2] = (u_short)(sparks->plane[i].rgba[2] * ratio);
        ratio = shSinF(PI * (sparks->plane[i].timer / sparks->plane[i].life_span));
        rgba[3] = (u_short)(sparks->plane[i].rgba[3] * ratio);
        EFCTResetRGBA(rgba, &sparks->base_obj.pVertex[i * 4]);
    }
}

static void MoveSparks(EFCTSparksObject* sparks /* r17 */) {

    int i; // r16
    float width; // r20        
    float height; // r21

    for (i = 0; i < 2; i++) {
        if (sparks->plane[i].timer == 0.0f) {
            SetSparksSize(&sparks->plane[i].width, &sparks->plane[i].height);
            SetSparksKind(&sparks->plane[i].kind);
            SetSparksStartPos(sparks->plane[i].kind, sparks->plane[i].trans);
            SetSparksSpeed(sparks->plane[i].kind, sparks->plane[i].speed);
            SetSparksRGBA(sparks->plane[i].rgba);
        }

        width = sparks->plane[i].width;
        height = sparks->plane[i].height;
        RenewSparksPos(&sparks->plane[i]);        
        SetSparksVertex(sparks->plane[i].pos, width, height, sparks->plane[i].trans, &sparks->base_obj.pVertex[i * 4]);
    }
}

static void SetSparksVertex(float* pos /* r2 */, float width /* r29 */, float height /* r29 */, float* trans /* r2 */, EFCTVertexData* VertexData /* r2 */) {
    
    VertexData[0].LocalPos[0] = trans[0] + (pos[0] + -width * 0.5f);
    VertexData[0].LocalPos[1] = trans[1] + (pos[1] + -height * 0.5f);
    VertexData[0].LocalPos[2] = pos[2] + trans[2];
    VertexData[0].LocalPos[3] = 1.0f;
    
    VertexData[1].LocalPos[0] = trans[0] + (pos[0] + width * 0.5f);
    VertexData[1].LocalPos[1] = trans[1] + (pos[1] + -height * 0.5f);
    VertexData[1].LocalPos[2] = pos[2] + trans[2];
    VertexData[1].LocalPos[3] = 1.0f;
    
    VertexData[2].LocalPos[0] = trans[0] + (pos[0] + -width * 0.5f);
    VertexData[2].LocalPos[1] = trans[1] + (pos[1] + height * 0.5f);
    VertexData[2].LocalPos[2] = pos[2] + trans[2];
    VertexData[2].LocalPos[3] = 1.0f;
    
    VertexData[3].LocalPos[0] = trans[0] + (pos[0] + width * 0.5f);
    VertexData[3].LocalPos[1] = trans[1] + (pos[1] + height * 0.5f);
    VertexData[3].LocalPos[2] = pos[2] + trans[2];
    VertexData[3].LocalPos[3] = 1.0f;
}
