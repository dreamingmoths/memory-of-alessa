#ifndef LIB_MC_H
#define LIB_MC_H

#include "sce/eetypes.h"

typedef struct
{
	u_char Resv2,Sec,Min,Hour;
	u_char Day,Month;
	u_short Year;
} sceMcStDateTime;

typedef struct
{
	sceMcStDateTime _Create;
	sceMcStDateTime _Modify;
	u_int FileSizeByte;
	u_short AttrFile;
	u_short Reserve1;
	u_int Reserve2;
	u_int PdaAplNo;
	u_char EntryName[32];
} sceMcTblGetDir __attribute__((aligned (64)));

int sceMcInit(void);

#endif // LIB_MC_H
