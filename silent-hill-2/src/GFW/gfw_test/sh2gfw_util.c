#include "sh2_common.h"
#include "sce/libvu0.h"
#include "sce/libgraph.h"
#include "GFW/gfw_test/sh2gfw_util.h"
#include "view/camera_dat.h"
#include "view/vb_main.h"

/**
 * from sample: ee/sample/graphics/scis_vu0/defines.h
 * see https://decomp.me/scratch/jRjd4 for a messier, more line-number-matching version
 */
#pragma divbyzerocheck off

sceVu0FMATRIX world_view;   // size: 0x40, address: 0x614E50
sceVu0FMATRIX world_screen; // size: 0x40, address: 0x614E10
sceVu0FMATRIX view_clip;    // size: 0x40, address: 0x614DD0
sceVu0FMATRIX world_clip;   // size: 0x40, address: 0x614D90

int sceVu0ViewVolumeClip(sceVu0FVECTOR clip, sceVu0FMATRIX local_clip, sceVu0FVECTOR vertex) {
    register int ret;

    asm __volatile__(
       "lqc2    vf4,0x0(%2);\
        lqc2    vf5,0x10(%2);\
        lqc2    vf6,0x20(%2);\
        lqc2    vf7,0x30(%2);\
        lqc2    vf8,0x0(%3);\
        vmulax.xyzw     ACC, vf4,vf8;\
        vmadday.xyzw    ACC, vf5,vf8;\
        vmaddaz.xyzw    ACC, vf6,vf8;\
        vmaddw.xyzw      vf12,vf7,vf8;\
        vclipw.xyz   vf12, vf12;\
        vnop;\
        vnop;\
        vnop;\
        sqc2    vf12, 0x0(%1);\
        vnop;\
        cfc2    %0, $vi18"
        : "=&r"(ret) : "r"(clip), "r"(local_clip), "r"(vertex));

    return ret;
};

void CopyNode(sh2gfw_Node* nod0, sh2gfw_Node* nod1) {
    sceVu0CopyVector(nod0->vertex, nod1->vertex);
    sceVu0CopyVector(nod0->normal, nod1->normal);
    sceVu0CopyVector(nod0->color, nod1->color);
    sceVu0CopyVector(nod0->texUV, nod1->texUV);
    sceVu0CopyVector(nod0->clipV, nod1->clipV);
}

void InitNodeArraySet(sh2gfw_NodeArraySet* scissorflip) {
    scissorflip->rotflag          = 0;
    scissorflip->flipflag         = 0;
    scissorflip->in               = &scissorflip->narray[scissorflip->flipflag];
    scissorflip->out              = &scissorflip->narray[!scissorflip->flipflag];
    scissorflip->in->nodeNum      = 0;
    scissorflip->out->nodeNum     = 0;
    scissorflip->triangle.nodeNum = 3;
};

void ResetNodeArraySet(sh2gfw_NodeArraySet* scissorflip) {
    scissorflip->flipflag     = 0;
    scissorflip->in           = &scissorflip->narray[scissorflip->flipflag];
    scissorflip->out          = &scissorflip->narray[!scissorflip->flipflag];
    scissorflip->in->nodeNum  = 0;
    scissorflip->out->nodeNum = 0;
};

void FlipNodeArray(sh2gfw_NodeArraySet* scissorflip) {
    scissorflip->flipflag     = !scissorflip->flipflag;
    scissorflip->in           = &scissorflip->narray[scissorflip->flipflag];
    scissorflip->out          = &scissorflip->narray[!scissorflip->flipflag];
    scissorflip->out->nodeNum = 0;
};

void PushTriangleNodeArray(sh2gfw_NodeArraySet* scissorflip, sh2gfw_Node* nod, int mode) {
    if (mode != 0) {
        sceVu0CopyVector(scissorflip->triangle.node[0].normal, nod->normal);
        sceVu0CopyVector(scissorflip->triangle.node[1].normal, nod->normal);
        sceVu0CopyVector(scissorflip->triangle.node[2].normal, nod->normal);
        sceVu0CopyVector(scissorflip->triangle.node[0].color, nod->color);
        sceVu0CopyVector(scissorflip->triangle.node[1].color, nod->color);
        sceVu0CopyVector(scissorflip->triangle.node[2].color, nod->color);
    }
    CopyNode(&scissorflip->triangle.node[scissorflip->rotflag++], nod);
    scissorflip->rotflag %= 3;
};

void InitScissorPlane(sh2gfw_ScissorPlaneArray* sp) {
    sp->planeNum          = 6;
    sp->plane[0].clipmask = 0x820;
    sp->plane[0].xyzflag  = 2 | 0x10; // -z plane
    sp->plane[1].clipmask = 0x410;
    sp->plane[1].xyzflag  = 2; // +z plane
    sp->plane[2].clipmask = 0x208;
    sp->plane[2].xyzflag  = 1 | 0x10; // -y plane
    sp->plane[3].clipmask = 0x104;
    sp->plane[3].xyzflag  = 1; // +y plane
    sp->plane[4].clipmask = 0x82;
    sp->plane[4].xyzflag  = 0 | 0x10; // -x plane
    sp->plane[5].clipmask = 0x41;
    sp->plane[5].xyzflag  = 0; // +x plane
};

int ClipCheck(sh2gfw_Node* a, sh2gfw_Node* b) {
    register int ret;

    __asm__ __volatile__(
   "lqc2  vf10, 0x40(%1);\
    lqc2  vf11, 0x40(%2);\
    vclipw.xyz  vf10, vf10w;\
    vclipw.xyz  vf11, vf11w;\
    vnop;\
    vnop;\
    vnop;\
    vnop;\
    vnop;\
    cfc2  %0, $vi18"
        : "=&r"(ret) : "r"(a), "r"(b));

    return ret;
};

void InterpNode(sh2gfw_Node* inter, sh2gfw_Node* inside, sh2gfw_Node* outside,
                float sgn, int xyzflag) {
    /*
    len01 = (out->clipV[flag]- sgn*out->clipV[3])
           - (in->clipV[flag] - sgn*in->clipV[3]);
    ans = (inside->clipV[flag] - sgn*inside->clipV[3]);
    ans01 = fabs(ans/len01);
    */
    __asm__ __volatile__(
   "lqc2  vf10, 0x40(%1);\
    lqc2  vf11, 0x40(%2);\
    lqc2  vf21, 0x00(%1);\
    lqc2  vf22, 0x10(%1);\
    lqc2  vf23, 0x20(%1);\
    lqc2  vf24, 0x30(%1);\
    lqc2  vf25, 0x00(%2);\
    lqc2  vf26, 0x10(%2);\
    lqc2  vf27, 0x20(%2);\
    lqc2  vf28, 0x30(%2);\
    vsub.xyzw  vf15, vf11, vf10 ;\
    vsub.xyzw  vf25, vf25, vf21 ;\
    vsub.xyzw  vf26, vf26, vf22 ;\
    vsub.xyzw  vf27, vf27, vf23 ;\
    vsub.xyzw  vf28, vf28, vf24 ;\
    mfc1     $8, %3;\
    qmtc2    $8, vf09             ;\
    vmulx.w  vf12w, vf10w, vf09x  ;\
    vmulx.w  vf13w, vf11w, vf09x  ;\
    vsubw.xyzw  vf16, vf10, vf12w ;\
    vsubw.xyzw  vf17, vf11, vf13w  ;\
    vabs.xyzw vf16, vf16;\
    vabs.xyzw vf17, vf17;\
    qmfc2    $9,  vf16            ;\
    qmfc2    $10, vf17;\
  LOOP:\
    beq      %4, $0, LOOP_END;\
    prot3w   $9, $9;\
    prot3w   $10, $10;\
    addi     %4, %4, -1;\
    j        LOOP;\
    nop;\
  LOOP_END:\
    qmtc2  $9, vf16 ;\
    qmtc2  $10, vf17            ;\
    vadd.xyz  vf18, vf17, vf16  ;\
    vdiv   Q, vf16x, vf18x      ;\
    vwaitq;\
    vaddq.xyzw  vf20, vf00, Q;\
    vabs.x     vf20x, vf20x;\
    vmulx.xyzw  vf15, vf15, vf20x ;\
    vmulx.xyzw  vf25, vf25, vf20x ;\
    vmulx.xyzw  vf26, vf26, vf20x ;\
    vmulx.xyzw  vf27, vf27, vf20x ;\
    vmulx.xyzw  vf28, vf28, vf20x ;\
    vadd.xyzw vf19, vf10, vf15 ;\
    vadd.xyzw vf25, vf25, vf21 ;\
    vadd.xyzw vf26, vf26, vf22 ;\
    vadd.xyzw vf27, vf27, vf23 ;\
    vadd.xyzw vf28, vf28, vf24 ;\
    sqc2  vf25, 0x00(%0);\
    sqc2  vf26, 0x10(%0);\
    sqc2  vf27, 0x20(%0);\
    sqc2  vf28, 0x30(%0);\
    sqc2  vf19, 0x40(%0)" ::"r"(inter),
        "r"(inside), "r"(outside),
        "f"(sgn), "r"(xyzflag) : "$8", "$9", "$10", "memory");
};

void ScissorTriangle(sh2gfw_NodeArraySet* scissorflip,
                     sh2gfw_ScissorPlaneArray* planeset) {
    int i, j;
    int clip;
    int mask;
    int xyz;
    float sgn;
    sh2gfw_ScissorPlane* plane;
    sh2gfw_NodeArray* inarray  = &scissorflip->triangle;
    sh2gfw_NodeArray* outarray = scissorflip->out;
    sh2gfw_Node *currN, *nextN;
    sh2gfw_Node interN;

    for (i = 0; i < planeset->planeNum; i++) {
        plane = &planeset->plane[i];
        sgn   = (plane->xyzflag & 0x10) ? -1.0 : 1.0;
        mask  = plane->clipmask;
        xyz   = plane->xyzflag & 0xf;

        for (j = 0; j < inarray->nodeNum; j++) {
            currN = &inarray->node[j];
            nextN = &inarray->node[(j + 1) % inarray->nodeNum];

            clip = mask & ClipCheck(currN, nextN);

            if (clip == 0) { // each vertex is inside
                CopyNode(&outarray->node[outarray->nodeNum++], currN);
            } else if ((clip & 0x3f) && (clip & 0xfc0)) {      // each vertex is outside
                                                               // do nothing
            } else if ((clip & 0x3f) && (clip & 0xfc0) == 0) { // current is inside
                InterpNode(&interN, currN, nextN, sgn, xyz);
                CopyNode(&outarray->node[outarray->nodeNum++], currN);
                CopyNode(&outarray->node[outarray->nodeNum++], &interN);
            } else if ((clip & 0x3f) == 0 && (clip & 0xfc0)) { // next is inside
                InterpNode(&interN, nextN, currN, sgn, xyz);
                CopyNode(&outarray->node[outarray->nodeNum++], &interN);
            }
        }
        FlipNodeArray(scissorflip);
        inarray  = scissorflip->in;
        outarray = scissorflip->out;
    }
};

void MakeScissorPolygon(sh2gfw_NodeArraySet* scissorflip, int Prim, int flag, Q_WORDDATA** ppqwd) {
    int j = 0, outsize = 0; // r19
    float Q;
    sh2gfw_NodeArray* in = scissorflip->in;
    sceVu0IVECTOR v01, c01;
    sceVu0FVECTOR tex;
    Q_WORDDATA* qwd = *ppqwd; // r21

    if (flag == 0)
        Prim = (Prim & 0xfff8) | 0x5; // triangle fan
    else
        Prim = (Prim & 0xffe8) | 0x02; // triangle fan

    /* commented out sdk code here */

    outsize += 1;

    for (j = 0; j < in->nodeNum; j++) {

        sceVu0RotTransPers(v01, world_screen, in->node[j].vertex, 1);
        sceVu0ApplyMatrix(tex, world_screen, in->node[j].vertex);
        Q = 1.0 / tex[3];
        sceVu0ScaleVector(tex, in->node[j].texUV, Q);
        sceVu0FTOI0Vector(c01, in->node[j].color);

        qwd[outsize++].ul128 = *((u_long128*) tex);
        qwd[outsize++].ul128 = *((u_long128*) c01);
        qwd[outsize++].ul128 = *((u_long128*) v01);
    }

    if (1 < outsize) {

        qwd->ul64[1] = 0x0512L;
        qwd->ul64[0] = SCE_GIF_SET_TAG(in->nodeNum, 1, 1, Prim, SCE_GIF_PACKED, 3);
        *ppqwd       = qwd + outsize;
        return;
    }

    *ppqwd = qwd;
}

void MakeScissorPacket(void* DataBuf, void** OutputBuf, void** SciBuf, int flag, int Prim, int VertexNum) {
    int j, outsize = 0; // r20
    u_int clipflag = 0;
    float Q;
    sh2gfw_Node node;

    Q_WORDDATA* qwd;                 // r2
    Q_WORDDATA* outqwd = *OutputBuf; // r22
    Q_WORDDATA* sciqwd = *SciBuf;    // r29+0x140
    Q_WORDDATA* scitop = *SciBuf;    // r30

    sceVu0IVECTOR Vertex01, Color01;
    sceVu0FVECTOR tex, clip, GScolor;
    sceVu0FMATRIX *vertex, *normal, *texUV, *color;
    sh2gfw_NodeArraySet* scissorflip;
    sh2gfw_ScissorPlaneArray* planeset;
    int k; // r2

    vertex = (sceVu0FVECTOR*) DataBuf;
    normal = (sceVu0FVECTOR*) DataBuf + 1;
    texUV  = (sceVu0FVECTOR*) DataBuf + 2;
    color  = (sceVu0FVECTOR*) DataBuf + 3;

    sceVu0CopyMatrix(world_view, VbWvsMatrix.wvm);
    sceVu0CopyMatrix(world_screen, VbWvsMatrix.wsm);
    sceVu0CopyMatrix(view_clip, cam0.view_clip);

    sceVu0MulMatrix(world_clip, view_clip, world_view);

    InitNodeArraySet((sh2gfw_NodeArraySet*) SCRATCHPAD_START);
    InitScissorPlane((sh2gfw_ScissorPlaneArray*) (SCRATCHPAD_START + sizeof(sh2gfw_NodeArraySet)));

    outsize += 2;
    sciqwd++;

    for (j = 0; j < VertexNum; j++) {

        clipflag |= 0x3f & sceVu0ViewVolumeClip(clip, world_clip, vertex[j]);

        sceVu0RotTransPers(Vertex01, world_screen, vertex[j], 1);

        sceVu0CopyVector(GScolor, color[j]);
        sceVu0FTOI0Vector(Color01, GScolor);

        sceVu0CopyVector(node.vertex, vertex[j]);
        sceVu0CopyVector(node.normal, normal[j]);
        sceVu0CopyVector(node.color, GScolor);
        sceVu0CopyVector(node.texUV, texUV[j]);
        sceVu0CopyVector(node.clipV, clip);

        if ((Prim & 0x8) != 0)
            PushTriangleNodeArray((sh2gfw_NodeArraySet*) SCRATCHPAD_START, &node, 0);

        else
            PushTriangleNodeArray((sh2gfw_NodeArraySet*) SCRATCHPAD_START, &node, 1);

        if (clipflag & 0x3ffff) {

            if ((Prim & 0x4 && j >= 2) || (Prim & 0x3 && (j + 1) % 3 == 0)) {

                Vertex01[3] |= 0x8000;

                ScissorTriangle((sh2gfw_NodeArraySet*) SCRATCHPAD_START, (sh2gfw_ScissorPlaneArray*) (SCRATCHPAD_START + sizeof(sh2gfw_NodeArraySet)));
                MakeScissorPolygon((sh2gfw_NodeArraySet*) SCRATCHPAD_START, Prim, flag, &sciqwd);

                ResetNodeArraySet((sh2gfw_NodeArraySet*) SCRATCHPAD_START);
            }
        }

        clipflag = clipflag << 6; // keep flag bits (recent two points)

        sceVu0ApplyMatrix(tex, world_screen, vertex[j]);

        Q = 1.0 / tex[3];
        sceVu0ScaleVector(tex, texUV[j], Q); // for Perspective correction
        outqwd[outsize++].ul128 = *((u_long128*) tex);
        outqwd[outsize++].ul128 = *((u_long128*) Color01);
        outqwd[outsize++].ul128 = *((u_long128*) Vertex01);
    }

    outqwd->ui32[0] = DMAcnt | (u_int) (outsize - 1);
    outqwd->ui32[1] = 0;
    outqwd->ui32[2] = 0;
    outqwd->ui32[3] = ((outsize - 1) | 0x50000000); // STMOD?

    outqwd->ul64[3] = 0x512L;
    outqwd->ul64[2] = SCE_GIF_SET_TAG(VertexNum, 1, 1, Prim, SCE_GIF_PACKED, 3);

    j = ((int) sciqwd - (int) scitop) >> 4;
    if (j < 4) {

        j               = 0;
        scitop->ui32[0] = 0x10000000;
        scitop->ui32[1] = 0;
        scitop->ui32[2] = 0;
        scitop->ui32[3] = 0;
    } else {

        scitop->ui32[0] = ((j - 1) | DMAcnt);
        scitop->ui32[1] = 0;
        scitop->ui32[2] = 0;
        scitop->ui32[3] = ((j - 1) | 0x50000000);
    }
    *OutputBuf = *(Q_WORDDATA**) OutputBuf + outsize;
    *SciBuf    = *(Q_WORDDATA**) SciBuf + j;
}

void sh2gfw_util_zeroq(Q_WORDDATA* qwd, int qsize) {
    u_long128 zero128 = 0;
    while (qsize > 0) qwd[--qsize].ul128 = zero128;
}
