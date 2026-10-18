#include "Multi_thr/filesys/filepath.h"

static s_char* devstr_cdrom0 = "cdrom0:";  // size: 0x4, address: 0x33B3B8
static s_char* devstr_host0  = "host0:";   // size: 0x4, address: 0x33B3C0

static int pathname_skipcheck(s_char* filename /* r2 */);
static int shPathMakeCd(char* fullpath /* r17 */, char* pathname /* r2 */, char* filename /* r2 */);
static int shPathMakeHd(char* fullpath /* r18 */, char* rootpath /* r2 */, char* pathname /* r2 */, char* filename /* r17 */);

#line 102
static int pathname_skipcheck(s_char* filename /* r2 */) {
    switch (filename[0]) {
        case '/':
        case '\\':
            return 0;
        case '.':
            switch (filename[1]) {
                case '/':
                case '\\':
                    return 0;
                case '.':
                    switch (filename[2]) {
                        case '/':
                        case '\\':
                            return 0;
                    }
            }
            break;
        default:
            if (filename[1] == ':') {
                if (filename[0] >= 'a' && filename[1] < '{')
                    return 0;
                if (filename[0] >= 'A' && filename[1] < '[')
                    return 0;
            }
    }

    return 1;
}












int shPathCheckExecRoot(s_char* filename) {
    return pathname_skipcheck(filename) == 0;
}





static int shPathMakeCd(char* fullpath /* r17 */, char* pathname /* r2 */, char* filename /* r2 */) {

    char* prefix = devstr_cdrom0; // r16
    char suffix[3] = ";1";        // r29+0x23C
    int len;                      // r2
    char* work;                   // r2
    char work1[256];              // r29+0x30
    char work2[260];              // r29+0x130

    if (pathname_skipcheck(filename)) {
        UtilStrPathCatL(work1, pathname, filename, sizeof(work1));
    } else {

        while(*filename == '.') filename++;
        UtilStrCpyL(work1, filename, sizeof(work1));
    }
    work1[255] = '\0';
    work = work1;
    while(*work == '.') work++;

    UtilStrPathCatL(work2, "/", work, sizeof(work1));

    UtilStrConvertCdPath(work2);
    len = UtilStrCat3L(fullpath, prefix, work2, suffix, 256);
    return len < 256;
}






static int shPathMakeHd(char* fullpath /* r18 */, char* rootpath /* r2 */, char* pathname /* r2 */, char* filename /* r17 */) {

    char* prefix = devstr_host0; // r16
    int len;                     // r2
    char work1[256];             // r29+0x40
    char work2[256];             // r29+0x140






    if (pathname_skipcheck(pathname)) {
        UtilStrPathCatL(work1, rootpath, pathname, sizeof(work1));
    } else {
        UtilStrCpyL(work1, pathname, sizeof(work1));
    }
    work1[255] = '\0';

    if (pathname_skipcheck(filename)) {
        UtilStrPathCatL(work2, work1, filename, sizeof(work2));
    } else {
        UtilStrCpyL(work2, filename, sizeof(work2));
    }
    work2[255] = '\0';

    UtilStrConvertHdPath(work2);
    len = UtilStrCatL(fullpath, prefix, work2, 256);
    return len < 256;
}


int shPathMakeIop(s_char* fullpath /* r2 */, s_char* filename /* r2 */) {
    s_char* ioppath;            // r2
    s_char* hdpath;             // r2
    s_char nullstr[1] = {};     // r29+0x1C
    if (execEnv_iop_path_hd == NULL) {

        ioppath = execEnv_iop_path;
        if (ioppath == NULL) ioppath = nullstr;
        return shPathMakeCd(fullpath, ioppath, filename);
    }


    hdpath = execEnv_host_path;
    if (hdpath == NULL) hdpath = nullstr;
    return shPathMakeHd(fullpath, hdpath, execEnv_iop_path_hd, filename);

}


int shPathMakeCdData(s_char* fullpath /* r2 */, s_char* filename /* r2 */) {
    s_char* datapath;           // r2
    s_char nullstr[1] = {};     // r29+0x1C
    datapath = execEnv_data_path;
    if (datapath == NULL) datapath = nullstr;

    return shPathMakeCd(fullpath, datapath, filename);
}


int shPathMakeHdData(s_char* fullpath /* r2 */, s_char* filename /* r2 */) {
    s_char* datapath;           // r2
    s_char* hdpath;             // r2
    s_char nullstr[1] = {};     // r29+0x1C
    datapath = execEnv_data_path;
    if (datapath == NULL) datapath = nullstr;
    hdpath = execEnv_host_path;
    if (hdpath == NULL) hdpath = nullstr;

    return shPathMakeHd(fullpath, hdpath, datapath, filename);
}


int shPathMakeCdDataBase(s_char* fullpath /* r2 */, s_char* filename /* r2 */) {
    s_char* datapath;           // r2
    s_char nullstr[1] = {};     // r29+0x1C
    datapath = execEnv_database_path;
    if (datapath == NULL) datapath = nullstr;

    return shPathMakeCd(fullpath, datapath, filename);
}


int shPathMakeHdDataBase(s_char* fullpath /* r2 */, s_char* filename /* r2 */) {
    s_char* datapath;           // r2
    s_char* hdpath;             // r2
    s_char nullstr[1] = {};     // r29+0x1C
    datapath = execEnv_database_path;
    if (datapath == NULL) datapath = nullstr;
    hdpath = execEnv_host_path;
    if (hdpath == NULL) hdpath = nullstr;

    return shPathMakeHd(fullpath, hdpath, datapath, filename);
}



int ___shPathMakeCdDataBase(s_char* fullpath /* r2 */, s_char* filename /* r2 */) {
    return shPathMakeCdDataBase(fullpath, filename);
}

int ___shPathMakeCdData(s_char* fullpath /* r2 */, s_char* filename /* r2 */) {
    return shPathMakeCdData(fullpath, filename);
}

int ___shPathMakeHdDataBase(s_char* fullpath /* r2 */, s_char* filename /* r2 */) {
    return shPathMakeHdDataBase(fullpath, filename);
}

int ___shPathMakeHdData(s_char* fullpath /* r2 */, s_char* filename /* r2 */) {
    return shPathMakeHdData(fullpath, filename);
}
