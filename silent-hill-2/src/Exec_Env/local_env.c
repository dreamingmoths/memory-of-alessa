#include "sh2_common.h"

char* execEnv_data_path     = "";            // size: 0x4, address: 0x2AB3E0
char* execEnv_iop_path      = "";            // size: 0x4, address: 0x2AB3E8
char* execEnv_reboot_file   = "SLUS_202.28"; // size: 0x4, address: 0x2AB3F0

char* execEnv_host_path   = NULL; // size: 0x4, address: 0x5526A8
char* execEnv_iop_path_hd = NULL; // size: 0x4, address: 0x5526B0
int execEnv_hd_merge_file = 0;    // size: 0x4, address: 0x5526B8
