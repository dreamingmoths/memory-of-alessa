#ifndef SH2GFW_UTIL_H
#define SH2GFW_UTIL_H

#include "sh2_common.h"

typedef struct {
  sceVu0FVECTOR vertex;
  sceVu0FVECTOR normal;
  sceVu0FVECTOR color;
  sceVu0FVECTOR texUV;
  sceVu0FVECTOR clipV;
} sh2gfw_Node;

typedef struct {
  sh2gfw_Node node[10];
  int  nodeNum;
} sh2gfw_NodeArray;

typedef struct {
  sh2gfw_NodeArray  triangle;
  sh2gfw_NodeArray  narray[2];
  sh2gfw_NodeArray  *in;
  sh2gfw_NodeArray  *out;
  int               rotflag; // 0 to 3
  int               flipflag; // 0 or 1
} sh2gfw_NodeArraySet;

typedef struct {
  int              xyzflag;
  u_int            clipmask;
} sh2gfw_ScissorPlane;

typedef struct{
  sh2gfw_ScissorPlane plane[6];
  int                 planeNum;
} sh2gfw_ScissorPlaneArray;

int sceVu0ViewVolumeClip(float* clip, sceVu0FVECTOR* local_clip, float* vertex);
void CopyNode(sh2gfw_Node* nod0, sh2gfw_Node* nod1);
void InitNodeArraySet(sh2gfw_NodeArraySet* scissorflip);
void ResetNodeArraySet(sh2gfw_NodeArraySet* scissorflip);
void FlipNodeArray(sh2gfw_NodeArraySet* scissorflip);
void PushTriangleNodeArray(sh2gfw_NodeArraySet* scissorflip, sh2gfw_Node* nod, int mode);
void InitScissorPlane(sh2gfw_ScissorPlaneArray* sp);
int ClipCheck(sh2gfw_Node* a, sh2gfw_Node* b);
void InterpNode(sh2gfw_Node* inter, sh2gfw_Node* inside, sh2gfw_Node* outside, float sgn, int xyzflag);
void ScissorTriangle(sh2gfw_NodeArraySet* scissorflip, sh2gfw_ScissorPlaneArray* planeset);
void MakeScissorPolygon(sh2gfw_NodeArraySet* scissorflip, int Prim, int flag, Q_WORDDATA** ppqwd);
void MakeScissorPacket(void* DataBuf, void** OutputBuf, void** SciBuf, int flag, int Prim, int VertexNum);
void sh2gfw_util_zeroq(Q_WORDDATA* qwd, int qsize);

#endif // SH2GFW_UTIL_H
