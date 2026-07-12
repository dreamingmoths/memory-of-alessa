#include "SH2_common/data_load.h"
#include "SH2_common/playing_info.h"
#include "data/fs_structs.h"
#include "Font/font.h"
#include "Multi_thr/filesys/fcread.h"
#include "eekernel.h"
#include "eeregs.h"

// @todo: rename symbols

// @todo: migrate data

extern /* static */ fsFileIndex* msg_buffer_on_memory_446; // @ 0x011B6FF8
extern /* static */ fsFileIndex* file_stage_444[53][6]; // @ 0x0034C9D0
extern /* static */ fsFileIndex* file_result_443[6]; // @ 0x0034C9B0
extern /* static */ fsFileIndex* file_m_card_442[6]; // @ 0x0034C990
extern /* static */ fsFileIndex* file_memo_441[6]; // @ 0x0034C970
extern /* static */ fsFileIndex* file_option_440[6]; // @ 0x0034C950
extern /* static */ fsFileIndex* file_item_439[6]; // @ 0x0034C930
extern /* static */ fsFileIndex* msg_station_on_memory_445; // @ 0x011B6FF0
extern /* static */ fsFileIndex* file_common_438[6]; // @ 0x0034C910

extern /* static */ int bufpage_481; // @ 0x011B7000

int DataLoadMessage(int msg /* r2 */) {

    int fid = -2; // r2




































    
    switch (msg) {        
        case 0:
            if (file_common_438[playing.language] != msg_station_on_memory_445) {
                fid = FcRead(file_common_438[playing.language], msg_station);
                msg_station_on_memory_445 = file_common_438[playing.language];
            }
            break;
        
        case 1:
            if (file_item_439[playing.language] != msg_buffer_on_memory_446) {
                fid = FcRead(file_item_439[playing.language], msg_buffer);
                msg_buffer_on_memory_446 = file_item_439[playing.language];
            }
            break;
        
        case 2:
            if (file_option_440[playing.language] != msg_buffer_on_memory_446) {
                fid = FcRead(file_option_440[playing.language], msg_buffer);
                msg_buffer_on_memory_446 = file_option_440[playing.language];
            }
            break;
        
        case 3:
            if (file_memo_441[playing.language] != msg_buffer_on_memory_446) {
                fid = FcRead(file_memo_441[playing.language], msg_buffer);
                msg_buffer_on_memory_446 = file_memo_441[playing.language];
            }
            break;
        
        case 4:
            if (file_m_card_442[playing.language] != msg_buffer_on_memory_446) {
                fid = FcRead(file_m_card_442[playing.language], msg_buffer);
                msg_buffer_on_memory_446 = file_m_card_442[playing.language];
            }
            break;
        
        case 5:
            if (file_result_443[playing.language] != msg_buffer_on_memory_446) {
                fid = FcRead(file_result_443[playing.language], msg_buffer);
                msg_buffer_on_memory_446 = file_result_443[playing.language];
            }
            break;

        case 6:
            if (file_stage_444[playing.stage][playing.language] != msg_buffer_on_memory_446) {
                
                fid = FcRead(file_stage_444[playing.stage][playing.language], msg_buffer);
                
                msg_buffer_on_memory_446 = file_stage_444[playing.stage][playing.language];
            }
            break;
    }
    
    return fid;
    
}

void shMemCopy(void* ds, void* sr, int datasize) {
    int now; // r3   

    
    bufpage_481 ^= 1;

    SyncDCache(sr, ((char*)sr + datasize));
    InvalidDCache(sr,((char*)sr + datasize));
    
    SyncDCache(ds, ((char*)ds + datasize));
    InvalidDCache(ds, ((char*)ds + datasize));
    
    
    now = datasize;
    

    
    while (*D9_CHCR & 0x100);
    
    
    while (now >= SH2_BUFPAGE_SIZE) {
        *D9_SADR = SCRATCHPAD_START + 0x2000 + bufpage_481 * SH2_BUFPAGE_SIZE;   
        *D9_MADR = (u_int)sr + datasize - now; 
        *D9_QWC = 0x100;
        do {            
        } while (*D8_CHCR & 0x100);
        *D9_CHCR = 0x101;
        
        *D8_SADR = SCRATCHPAD_START + 0x2000 + bufpage_481 * SH2_BUFPAGE_SIZE;
        *D8_MADR = (u_int)ds + datasize - now;
        *D8_QWC = 0x100;
        do {            
        } while (*D9_CHCR & 0x100);
        *D8_CHCR = 0x100;
        
        bufpage_481 ^= 1;
        now -= SH2_BUFPAGE_SIZE;
    }
    
    do {            
    } while (*D8_CHCR & 0x100);
    
    if (now == 0) return;
    
    *D9_SADR = SCRATCHPAD_START + 0x2000 + bufpage_481 * SH2_BUFPAGE_SIZE;
    *D9_MADR = (u_int)sr + datasize - now; 
    *D9_QWC = now >> 4;
    
    while (*D9_CHCR & 0x100);
    *D9_CHCR = 0x101;
    
    *D8_SADR = SCRATCHPAD_START + 0x2000 + bufpage_481 * SH2_BUFPAGE_SIZE;
    *D8_MADR = (u_int)ds + datasize - now; 
    *D8_QWC = now >> 4;    
    
    while (*D9_CHCR & 0x100);
    *D8_CHCR = 0x100;
    
    
    while (*D8_CHCR & 0x100);
       


}
