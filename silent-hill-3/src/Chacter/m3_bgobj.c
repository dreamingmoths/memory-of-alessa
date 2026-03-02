#include "Chacter/m3_bgobj.h"

#define ROBJECT_MIRROR_X 0
#define ROBJECT_MIRROR_Y 1
#define ROBJECT_MIRROR_Z 2

extern void func_001DC9B0(SubCharacter *arg0, int value);
extern void func_001DCA40(SubCharacter *arg0, int value);
extern void func_001DD290(SubCharacter*, void(*)(SubCharacter*));
extern void func_001DD2A0(SubCharacter*, void(*)(SubCharacter*));


int RObjectInit(SubCharacter *this)
{
    func_001DC9B0(this, 0);
    func_001DCA40(this, 1);
    return 0;
}

void RObjectFunction(SubCharacter *this)
{
    SubCharacter *scp;
    float wall_pos;
    s64 mirror_mode;

    switch (this->step)
    {
    case OBJECT_STEP_INIT:
        RObjectInit(this);
        this->step++;
        break;
    case OBJECT_STEP_DRAW:
        scp = func_0012FD80(this->kind - 0x80, -1);
        wall_pos = func_00150C70();
        if (scp != NULL)
        {
            mirror_mode = func_00150C60();
            switch (mirror_mode)
            {
            case ROBJECT_MIRROR_X:
                this->pos.x = wall_pos + (wall_pos - scp->pos.x);
                this->pos.y = scp->pos.y;
                this->pos.z = scp->pos.z;
                this->rot.y = -scp->rot.y;
                break;
            case ROBJECT_MIRROR_Y:
                this->pos.x = scp->pos.x;
                this->pos.y = wall_pos + (wall_pos - scp->pos.z);
                this->pos.z = scp->pos.z;
                this->rot.y = scp->rot.y;
                this->rot.z = PI;
                break;
            case ROBJECT_MIRROR_Z:
                this->pos.x = scp->pos.x;
                this->pos.y = scp->pos.y;
                this->pos.z = wall_pos + (wall_pos - scp->pos.z);
                if (scp->rot.y >= 0.0f)
                {
                    this->rot.y = PI - scp->rot.y;
                }
                else
                {
                    this->rot.y = -PI - scp->rot.y;
                }
                break;
            }
        }
    }
}


void func_001430C0(SubCharacter *this) {
    func_001DD290(this, RObjectFunction);
    func_001DD2A0(this, RObjectFunction);
}
