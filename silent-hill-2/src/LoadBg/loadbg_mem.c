#include "LoadBg/loadbg_mem.h"
#include "Multi_thr/filesys/fileserv.h"
#include "Multi_thr/filesys/fcread.h"
#include "Multi_thr/util/utilstr.h"

int _loadBgMem_CmpUnitLR(loadBgMem_UnitL* UnitL, loadBgMem_UnitR* UnitR) {
    if (UnitL == NULL) return -4;    
    if (UnitR == NULL) return -5;
    if (UnitL->file == NULL) {
        
        return (UnitR->file == NULL) ? 4 : 3;
    }
    
    
    if (UnitR->file == NULL) {
        if (UnitL->fid < 0) 
            return 2;
        else 
            return -3;
    }
    if ((UnitL->file == UnitR->file) && (UnitL->unitID == UnitR->unitID)) {
        
        if (UnitL->fid < 0) 
            return 1;
        else 
            return -2;
    }
    if (UnitL->fid < 0) return 0;
    return -1;



}

int _loadBgMem_CheckUnitC(loadBgMem_UnitC* UnitC, fsFileIndex* file, u_short unitID) {
    if (UnitC == NULL) return -3;       
    if (UnitC->file != file) return 0;
    return UnitC->unitID != unitID ^ 1;


}

int _loadBgMem_SyncUnitL(loadBgMem_UnitL* UnitL) {
    int fid;
    if (UnitL == NULL) return -2;
    if (UnitL->file == NULL) {
        UnitL->unitID = 0;
        UnitL->fid = -1;
        return -1;
    }
    fid = UnitL->fid;
    if (fid < 0) return 1;
    if (fsSync(1, fid) < 0) return 0;
    UnitL->fid = -1;
    
    return 2;
}

int _loadBgMem_ClearUnitL(loadBgMem_UnitL* UnitL) {
    switch (_loadBgMem_SyncUnitL(UnitL)) {   
        case -2:
        default:
            return -1;
        
        case 1:
        case 2:
            UnitL->file = NULL;
            UnitL->unitID = 0;
            UnitL->fid = -1;              
        case -1:
            return 1;
        
        case 0:
            return 0;
    }
}

int _loadBgMem_ClearUnitC(loadBgMem_UnitC* UnitC) {
    if (UnitC == NULL) return -1;
    if (UnitC->file != NULL) {
        UnitC->file = NULL;
        UnitC->unitID = 0;
        return 1;
    }
    return 0;

}

int _loadBgMem_AddUnitC(loadBgMem_UnitC* UnitC, loadBgMem_UnitC* prevC) {
    loadBgMem_UnitC* nextC;

    if (UnitC == NULL) return 0;    
    if (prevC == NULL) return 0;
    
    nextC = prevC->nextC;
    if (nextC != NULL) nextC->prevC = UnitC;    
    prevC->nextC = UnitC;
    UnitC->nextC = nextC;
    UnitC->prevC = prevC;
    return 1;
}

void _loadBgMem_TakeoutUnitC(loadBgMem_CacheCtrl* cache, loadBgMem_UnitC* UnitC) {
    loadBgMem_UnitC* headC;
    loadBgMem_UnitC* tailC; 
    loadBgMem_UnitC* prevC;    
    loadBgMem_UnitC* nextC;
    if ((cache != NULL) && (UnitC != NULL)) {
        headC = cache->headC;
        tailC = cache->tailC;
        if (headC == NULL) {
            ASSERT_ON_LINE(headC==0&&tailC==0, 352);
        }        
        prevC = UnitC->prevC;
        nextC = UnitC->nextC;
        if (headC == UnitC) {
            ASSERT_ON_LINE(prevC==0, 357);
            cache->headC = nextC;
        } else {
            ASSERT_ON_LINE(prevC!=0, 360);
            prevC->nextC = nextC;  
        }
        if (tailC == UnitC) {
            ASSERT_ON_LINE(nextC==0, 364);
            cache->tailC = prevC;
        } else {
            ASSERT_ON_LINE(nextC!=0, 367);
            nextC->prevC = prevC;
        }
        UnitC->prevC = NULL;
        UnitC->nextC = NULL;
    }
}

void _loadBgMem_ShiftUnitC(loadBgMem_CacheCtrl* cache, loadBgMem_UnitC* UnitC) {
    loadBgMem_UnitC* tailC;
    loadBgMem_UnitC* headC;
    if ((cache != NULL) && (UnitC != NULL)) {
        ASSERT_ON_LINE(UnitC->prevC==0, 382);
        ASSERT_ON_LINE(UnitC->nextC==0, 383);
        tailC = cache->tailC;
        if (tailC == NULL) {
            
            headC = cache->headC;
            ASSERT_ON_LINE(headC==0&&tailC==0, 388);
        }
        cache->tailC = UnitC;
        if (tailC != NULL) tailC->nextC = UnitC;
        else cache->headC = UnitC;
        ASSERT_ON_LINE(cache->headC!=0, 393);
        UnitC->prevC = tailC;
        UnitC->nextC = NULL;
    }
}

void _loadBgMem_PushUnitC(loadBgMem_CacheCtrl* cache, loadBgMem_UnitC* UnitC) {
    loadBgMem_UnitC* headC;
    loadBgMem_UnitC* tailC;
    if ((cache != NULL) && (UnitC != NULL)) {
        ASSERT_ON_LINE(UnitC->prevC==0, 406);
        ASSERT_ON_LINE(UnitC->nextC==0, 407);
        headC = cache->headC;
        if (headC == NULL) {
            
            tailC = cache->tailC;
            ASSERT_ON_LINE(headC==0&&tailC==0, 412);
        }
        cache->headC = UnitC;
        if (headC != NULL) headC->prevC = UnitC;
        else cache->tailC = UnitC;
        ASSERT_ON_LINE(cache->tailC!=0, 417);
        UnitC->prevC = NULL;
        UnitC->nextC = headC;
    }
}

loadBgMem_UnitC* _loadBgMem_SearchOldestUnitC(loadBgMem_CacheCtrl* cache) {
    if (cache == NULL) return NULL;    
    return cache->tailC;
}


loadBgMem_UnitC* _loadBgMem_SearchUnitC(loadBgMem_CacheCtrl* cache, fsFileIndex* file, u_short unitID) {
    loadBgMem_UnitC* UnitC;
    if (cache == NULL) return NULL;   
    if (file == NULL) return NULL;
    for (UnitC = cache->headC; UnitC != NULL; UnitC = UnitC->nextC) {
        if (_loadBgMem_CheckUnitC(UnitC, file, unitID) == 1) {
            break;
        }
    }
    return UnitC;
}

loadBgMem_UnitC* _loadBgMem_SearchUnitR2C(loadBgMem_CacheCtrl* cache, loadBgMem_UnitR* UnitR) {
    fsFileIndex* file;
    u_short unitID;
    if (UnitR == NULL) return NULL;
    file = UnitR->file;
    unitID = UnitR->unitID;
    return _loadBgMem_SearchUnitC(cache, file, unitID);
}

loadBgMem_UnitC* _loadBgMem_SearchUnitL2C(loadBgMem_CacheCtrl* cache, loadBgMem_UnitL* UnitL) {
    fsFileIndex* file;
    u_short unitID;
    if (UnitL == NULL) return NULL;
    file = UnitL->file;
    unitID = UnitL->unitID;
    return _loadBgMem_SearchUnitC(cache, file, unitID);
}

void _loadBgMem_MoveMemC2L(loadBgMem_LoadCtrl* ctrl, loadBgMem_CacheCtrl* cache, loadBgMem_UnitL* UnitL, loadBgMem_UnitC* UnitC) {
    int UnitSize;
    char* BufL; char* BufC;
    int unitNoL; int unitNoC;
    ASSERT_ON_LINE(ctrl!=0, 480);
    ASSERT_ON_LINE(cache!=0, 481);  
    UnitSize = ctrl->UnitSize;
    BufL = ctrl->Buffer;
    BufC = cache->Buffer;       
    
    
    
    ASSERT_ON_LINE(UnitL!=0, 488);
    ASSERT_ON_LINE(UnitC!=0, 489);
    unitNoL = UnitL->unitNo;
    unitNoC = UnitC->unitNo;
    BufL += (unitNoL * UnitSize);
    BufC += (unitNoC * UnitSize);
    
    UtilMemCpy(BufL, BufC, UnitSize);
    UnitL->file = UnitC->file;
    UnitL->unitID = UnitC->unitID;
    UnitL->fid = -1;
}

void _loadBgMem_MoveMemL2C(loadBgMem_LoadCtrl* ctrl, loadBgMem_CacheCtrl* cache, loadBgMem_UnitL* UnitL, loadBgMem_UnitC* UnitC) {
    int UnitSize;
    char* BufL; char* BufC;
    int unitNoL; int unitNoC;
    ASSERT_ON_LINE(ctrl!=0, 510);
    ASSERT_ON_LINE(cache!=0, 511);     
    UnitSize = ctrl->UnitSize;
    BufL = ctrl->Buffer;
    BufC = cache->Buffer;       
    
    
    
    ASSERT_ON_LINE(UnitL!=0, 518);
    ASSERT_ON_LINE(UnitC!=0, 519);
    unitNoL = UnitL->unitNo;
    unitNoC = UnitC->unitNo;
    BufL += unitNoL * UnitSize;
    BufC += unitNoC * UnitSize;
    
    UtilMemCpy(BufC, BufL, UnitSize);
    UnitC->file = UnitL->file;
    UnitC->unitID = UnitL->unitID;
}

void _loadBgMem_SwapMemLC(loadBgMem_LoadCtrl* ctrl, loadBgMem_CacheCtrl* cache, loadBgMem_UnitL* UnitL, loadBgMem_UnitC* UnitC) {
    int UnitSize;
    char* BufL; char* BufC; int unitNoL; int unitNoC;
    fsFileIndex* file; u_short unitID;
    ASSERT_ON_LINE(ctrl!=0, 539);
    ASSERT_ON_LINE(cache!=0, 540);
    UnitSize = ctrl->UnitSize;
    BufL = ctrl->Buffer;
    BufC = cache->Buffer;
    
    
    
    ASSERT_ON_LINE(UnitL!=0, 547);
    ASSERT_ON_LINE(UnitC!=0, 548);
    unitNoL = UnitL->unitNo;
    unitNoC = UnitC->unitNo;
    UtilMemSwap(BufL + unitNoL * UnitSize, BufC + unitNoC * UnitSize, UnitSize);
    
    
    
    
    
    
    file = UnitL->file;
    unitID = UnitL->unitID;
    UnitL->file = UnitC->file;
    UnitL->unitID = UnitC->unitID;
    UnitC->file = file;
    UnitC->unitID = unitID;
    
    UnitL->fid = -1;
}

int _loadBgMem_LoadMemR2L(loadBgMem_LoadCtrl* ctrl, loadBgMem_UnitL* UnitL, loadBgMem_UnitR* UnitR) {
    int UnitSize;
    char* BufL;
    int offset;
    fsFileIndex* file;
    int fid; int unitID; int unitNo;
   
    ASSERT_ON_LINE(ctrl!=0, 579);
    UnitSize = ctrl->UnitSize;
    BufL = ctrl->Buffer;
    
    
    ASSERT_ON_LINE(UnitL!=0, 584);
    ASSERT_ON_LINE(UnitR!=0, 585);
    unitNo = UnitL->unitNo;
    ASSERT_ON_LINE(unitNo==UnitR->unitNo, 587);
    BufL += (unitNo * UnitSize);
    file = UnitR->file;
    unitID = UnitR->unitID;
    offset = unitID * UnitSize;
    
    fid = FcReadPart(file, BufL, offset, UnitSize);
    if (fid >= 0) {
        UnitL->file = file;
        UnitL->unitID = unitID;
        UnitL->fid = fid;
        return 1;
    }
    return 0;

}

int _loadBgMem_InitLoad(loadBgMem_LoadCtrl* ctrl, int UnitSize, int Units, loadBgMem_UnitL* UnitLArray, loadBgMem_UnitR* UnitRArray, s_char* Buffer) {
    int i;
    loadBgMem_UnitL* UnitL;
    loadBgMem_UnitR* UnitR;
    if (ctrl != NULL) {
        ASSERT_ON_LINE((UnitSize%2048)==0, 641);
        ASSERT_ON_LINE((((int)Buffer)%64)==0, 642);
        ctrl->UnitSize = UnitSize;
        ctrl->Units = Units;
        ctrl->UnitLArray = UnitLArray;
        ctrl->UnitRArray = UnitRArray;
        ctrl->Buffer = Buffer;;
        for (i = 0; i < Units; i++, UnitLArray++, UnitRArray++, Buffer += UnitSize) {
            UnitL = UnitLArray;
            
            UnitL->file = NULL;
            UnitL->unitID = 0;
            UnitL->unitNo = i;
            UnitL->fid = -1;
            UnitL->pad = 0;
            UnitR = UnitRArray;            
            UnitR->file = NULL;
            UnitR->unitID = 0;
            UnitR->unitNo = i;
            UnitR->sectID = 0;
            UnitR->nextR = NULL;
        }
    }
    return ctrl != NULL;
}

int _loadBgMem_InitCache(loadBgMem_CacheCtrl* cache, int UnitSize, int Units, loadBgMem_UnitC* UnitCArray, s_char* Buffer) {
    int i;
    loadBgMem_UnitC* UnitC;
    loadBgMem_UnitC* headC; 
    loadBgMem_UnitC* tailC;
    if (cache != NULL) {
        ASSERT_ON_LINE((UnitSize%2048)==0, 679);
        ASSERT_ON_LINE((((int)Buffer)%64)==0, 680);
        cache->UnitSize = UnitSize;
        cache->Units = Units;
        cache->UnitCArray = UnitCArray;
        cache->Buffer = Buffer;
        for (i = 0, UnitC = UnitCArray; i < Units; i++, UnitC++, Buffer += UnitSize) {
            UnitC->file = NULL;
            UnitC->unitID = 0;
            UnitC->unitNo = i;
            UnitC->prevC = NULL;
            UnitC->nextC = NULL;
            UtilMemSet(Buffer, 0, UnitSize);
        }
        headC = NULL;
        tailC = NULL;
        for (i = 0, UnitC = UnitCArray; i < Units; i++, UnitC++) {
            if (!_loadBgMem_AddUnitC(UnitC, tailC)) {
                headC = UnitC;
            }
            tailC = UnitC;
        }
        cache->headC = headC;
        cache->tailC = tailC;
    }
    return cache != NULL;
}

int _loadBgMem_ClearRequest(loadBgMem_LoadCtrl* ctrl) {
    loadBgMem_UnitR* UnitR;
    int i;  
    int Units;
    if (ctrl == NULL) return 0;
    Units = ctrl->Units;    
    for (i = 0, UnitR = ctrl->UnitRArray; i < Units; i++, UnitR++) {
        UnitR->file = NULL;
        UnitR->unitID = 0;
        UnitR->unitNo = i;
        UnitR->sectID = 0;
        UnitR->nextR = NULL;
    }
    ctrl->headR = NULL;
    return 1;
}

#pragma divbyzerocheck off

int loadBgMem_SetRequest(loadBgMem_LoadCtrl* ctrl, loadBgMem_Sect** SectList) {
    loadBgMem_UnitR* UnitRArray;
    loadBgMem_UnitR* headR;
    loadBgMem_UnitR* tailR;
    loadBgMem_Sect* Sect;
    loadBgMem_Sect** Sect_p;
    int UnitSize;
    int Units;
    char* Buffer;
    int ret;
    
    if (ctrl == NULL) return 0;

    ret = 0;

    Units = ctrl->Units;
    UnitSize = ctrl->UnitSize;
    UnitRArray = ctrl->UnitRArray;
    Buffer = ctrl->Buffer;
    headR = NULL;
    tailR = NULL;

    for (Sect_p = SectList; (Sect = *Sect_p) != NULL; Sect_p++) {
        int Dir;
        int sUnits; int sUnits0;
        int overwrite;
        int sectID;
        int reduceRate8;
        loadBgMem_File* sFile;
        int sFiles;
        loadBgMem_UnitR* UnitR;
        char* addr;
        int sofsS; int sofsE;
        int unitNoS; int unitNoE;

        
        Dir = Sect->upper ? -1 : 1;
        overwrite = Sect->overwrite;
        sectID = Sect->sectID;
        sFiles = Sect->files;
        reduceRate8 = Sect->reduceRate8;


        sofsS = Sect->ofsS;
        sofsE = Sect->ofsE;


        ASSERT_ON_LINE(sofsS%UnitSize==0, 776);
        ASSERT_ON_LINE(sofsE%UnitSize==0, 777);
        unitNoS = sofsS / UnitSize;
        unitNoE = sofsE / UnitSize;
        sUnits = unitNoE - unitNoS;
        UnitR = &UnitRArray[unitNoS];
        ASSERT_ON_LINE(unitNoE<=Units, 782);


        if (Dir < 0) {
            UnitR += sUnits - 1;
        }
        sUnits0 = sUnits;        
        if (reduceRate8 > 0) {


            if (reduceRate8 >= 8) reduceRate8 = 8;
            sUnits = (sUnits * (8 - reduceRate8)) / 8;

        }
            for (sFile = Sect->filelist; (sFiles > 0) && (sUnits > 0); sFiles--, sFile++) {
                fsFileIndex* file;
                int fUnits; int unitID;
                int fofsS; int fofsE;
                int unitIDS; int unitIDE;
            
                file = sFile->file;
                
                fofsS = sFile->ofsS;
                fofsE = sFile->ofsE;
                
                
                
                
                unitIDS = fofsS / UnitSize;
                unitIDE = (fofsE + UnitSize - 1) / UnitSize;
                fUnits = unitIDE - unitIDS;
                unitID = (Dir > 0) ? unitIDS : unitIDE - 1;
                
                
                addr = Buffer + (UnitR - UnitRArray) * UnitSize;
                for (; (fUnits > 0) && (sUnits > 0); fUnits--, sUnits--, UnitR += Dir, unitID += Dir) {
                    
                    
                    
                    
                    if (file != NULL) {
                        
                        
                        
                        
                        
                        if ((UnitR->sectID == 0) || ((overwrite != 0) && (UnitR->sectID > sectID))) {
                            
                            
                            UnitR->file = file;
                            UnitR->unitID = unitID;
                            UnitR->sectID = sectID;
                            ret++;
                            if (UnitR->nextR == NULL) {
                                
                                if (tailR != NULL) {
                                    tailR->nextR = UnitR;
                                } else {
                                    ASSERT_ON_LINE(headR==0, 840);
                                    headR = UnitR;
                                }
                                tailR = UnitR;
                                UnitR->nextR = NULL;
                            }
                        }
                    }
                }
                if (fUnits <= 0) {

                    if (Dir < 0) {
                        addr = Buffer + (UnitSize * ((UnitR + 1) - UnitRArray));
                    }
                    sFile->addr = addr;
                }
                ASSERT_ON_LINE(fUnits<=sUnits0-sUnits, 856);
            
            }            

    }

    ctrl->headR = headR;
    return ret;
}

#pragma divbyzerocheck on

int _loadBgMem_SyncLoadUnits(loadBgMem_LoadCtrl* ctrl) {
    loadBgMem_UnitL* UnitL;
    int Units;
    int ret;
    
    if (ctrl == NULL) return 0;

    Units = ctrl->Units;
    UnitL = ctrl->UnitLArray;
    
    ret = 0;
    for (; Units > 0; Units--, UnitL++) {
        switch (_loadBgMem_SyncUnitL(UnitL)) {
            case 0:
                ret++;
                break;
            case 1:
            case 2:
            case -1:
                break;
            case -2:
            default:
                ASSERT_ON_LINE(0, 890);
                break;
        }
    }
    
    return ret;
}

int loadBgMem_CheckRequest(loadBgMem_LoadCtrl* ctrl, int* reqUnits) {
    loadBgMem_UnitL* UnitL; 
    loadBgMem_UnitR* UnitR;
    int UnitSize;
    int Units;
    int ret;   
    int req;
    
    if (ctrl == NULL) {
        if (reqUnits != NULL) *reqUnits = 1;
        return 1;
    }
    
    Units = ctrl->Units;
    
    UnitL = ctrl->UnitLArray;
    UnitR = ctrl->UnitRArray;
    
    ret = 0;
    req = 0;
    for (; Units > 0; Units--, UnitL++, UnitR++) {
        
        switch (_loadBgMem_CmpUnitLR(UnitL, UnitR)) {
            case 3:
                ret++; req++; break;
            case -3:
            case 2:
            case 4:
                break;
            case 1:
                req++; break;
            case 0:
                ret++; req++; break;
            case -1:
                ret++; req++; break;
            case -2:
                ret++; req++; break;
            
            
            default:
            case -5:
            case -4:
                ASSERT_ON_LINE(0, 942);
                break;
        }   
    }
    
    for (Units = 0, UnitR = ctrl->headR; UnitR != NULL; Units++, UnitR = UnitR->nextR) {
    
        
        
        
    }

    ASSERT_ON_LINE(Units==req, 954);
        
    if (reqUnits != NULL) *reqUnits = req;
    
    return ret;
}

int _loadBgMem_CleanupNonRequest(loadBgMem_LoadCtrl* ctrl) {
    loadBgMem_UnitL* UnitL;
    loadBgMem_UnitR* UnitR;
    int i;
    int Units;
    int result;      
    int ret;
    if (ctrl == NULL) return 0;
    Units = ctrl->Units;
    ret = 1;
    for (i = 0, UnitL = ctrl->UnitLArray, UnitR = ctrl->UnitRArray; i < Units; i++, UnitL++, UnitR++) {
    
        
        
        result = _loadBgMem_CmpUnitLR(UnitL, UnitR);
        switch (result) {
            
            
            case -3:
            case 2:
                if (_loadBgMem_ClearUnitL(UnitL) != 1) {
            
                    ret = 0;
                }
                break;
            case -1:
            case 0:
            case 1:
            case 3:
            case 4:
            case -2:
                break;
            case -5:
            case -4:
            default:
                ASSERT_ON_LINE(!"???", 997);
            break;
        }
    }
    return ret;
}

int loadBgMem_LoadRequest(loadBgMem_LoadCtrl* ctrl, loadBgMem_CacheCtrl* cache, int cache_access_limit, int file_access_limit, int* cache_in_access_count, int* cache_out_access_count, int* file_access_count, int* miss_access_count) {
    loadBgMem_UnitL* UnitLArray;
    loadBgMem_UnitR* UnitR;
    int UnitSize;
    int fa_cnt;
    int ca_in = 0;
    int ca_out = 0;
    int ca_hit = 0; 
    int miss = 0;

    if (ctrl == NULL) {
        if (cache_in_access_count != NULL) *cache_in_access_count = 0;
        if (cache_out_access_count != NULL) *cache_out_access_count = 0;
        if (file_access_count != NULL) *file_access_count = 0;
        if (miss_access_count != NULL) *miss_access_count = 1;

        return 1;
    }

    UnitSize = ctrl->UnitSize;

    if (cache != NULL) {
        ASSERT_ON_LINE(UnitSize==cache->UnitSize, 1038);
    }

    UnitLArray = ctrl->UnitLArray;
    
    
    fa_cnt = _loadBgMem_SyncLoadUnits(ctrl);

    for (UnitR = ctrl->headR ; UnitR != 0; UnitR = UnitR->nextR) {
        loadBgMem_UnitL* UnitL;
        loadBgMem_UnitC* UnitC;
        int result;
        
        UnitL = UnitLArray + UnitR->unitNo;

        result = _loadBgMem_CmpUnitLR(UnitL, UnitR);
        switch (result) {
            case 1:
            case 2:
            case 4:
                break;


            case 0:
            case 3:
                UnitC = _loadBgMem_SearchUnitR2C(cache, UnitR);
                if (UnitC != 0) {
            
                    _loadBgMem_TakeoutUnitC(cache, UnitC);
                    if (ca_in + ca_out < cache_access_limit) {
                        ca_hit++;
                        if (result == 3) {
                            
                            _loadBgMem_MoveMemC2L(ctrl, cache, UnitL, UnitC);
                            
                            _loadBgMem_ClearUnitC(UnitC);
                            
                            _loadBgMem_ShiftUnitC(cache, UnitC);
                            ca_out++;
                        } else {
                            loadBgMem_UnitC* findC;
                            
                            
                            findC = _loadBgMem_SearchUnitL2C(cache, UnitL);
                            if (findC != NULL) {
                            
                                
                                _loadBgMem_TakeoutUnitC(cache, findC);
                                
                                _loadBgMem_PushUnitC(cache, findC);
                                
                                _loadBgMem_MoveMemC2L(ctrl, cache, UnitL, UnitC);
                                
                                _loadBgMem_ClearUnitC(UnitC);
                                
                                _loadBgMem_ShiftUnitC(cache, UnitC);
                                ca_out++;
                            } else {
                                
                                _loadBgMem_SwapMemLC(ctrl, cache, UnitL, UnitC);
                                ca_in++;
                                ca_out++;
                                
                                _loadBgMem_PushUnitC(cache, UnitC);
                            }
                        }
                    } else {
                        
                        miss++;
                        _loadBgMem_PushUnitC(cache, UnitC);
                    }
                } else {
                    if (fa_cnt < file_access_limit) {
                        
                        
                        UnitC = _loadBgMem_SearchOldestUnitC(cache);
                        if ((result == 3) || (UnitC == NULL)) {
                        
                            
                            _loadBgMem_LoadMemR2L(ctrl, UnitL, UnitR);
                            fa_cnt++;
                        } else {
                            
                            if ((ca_in + ca_out) < cache_access_limit) {
                                loadBgMem_UnitC* findC;
                                
                            
                                
                                findC = _loadBgMem_SearchUnitL2C(cache, UnitL);
                                if (findC != NULL) {
                                
                                    
                                    _loadBgMem_TakeoutUnitC(cache, findC);
                                    
                                    _loadBgMem_PushUnitC(cache, findC);
                                
                                } else {
                                
                                    
                                    _loadBgMem_TakeoutUnitC(cache, UnitC);
                                    
                                    _loadBgMem_MoveMemL2C(ctrl, cache, UnitL, UnitC);
                                    
                                    _loadBgMem_PushUnitC(cache, UnitC);
                                }
                                
                                _loadBgMem_LoadMemR2L(ctrl, UnitL, UnitR);
                                ca_in++;
                                fa_cnt++;
                            } else {
                                miss += 2;
                            }
                        }
                    } else {
                        miss++;
                    }
                }
                break;
            case -1:
                miss++;
                break;
            case -3:
            case -2:
                break;
            case -5:
            case -4:
            default:
                ASSERT_ON_LINE(0, 1164);
            break;
        }
    
    }

    if (cache_in_access_count != NULL) *cache_in_access_count = ca_in;
    if (cache_out_access_count != NULL) *cache_out_access_count = ca_out;
    if (file_access_count != NULL) *file_access_count = fa_cnt;
    if (miss_access_count != NULL) *miss_access_count = miss;

    return fa_cnt + miss;
}
