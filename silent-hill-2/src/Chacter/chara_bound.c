#include "Chacter/chara_bound.h"
#include "Chacter/charaboundtbl.h"

float CharaGetBoundR(int chara_id) {    
    int i; // r4
    int n; // r2

    n = CharaBoundTblNum();
    for(i = 0; i < n; i++) {
        if (chara_id == chara_bound_tbl[i].chara_id) {
            return chara_bound_tbl[i].r;
        }
    }    
    
    return 2500.0f;    
}
