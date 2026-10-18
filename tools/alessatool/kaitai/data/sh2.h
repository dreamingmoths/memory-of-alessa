#ifndef __ALESSASTRUCT__
#define __ALESSASTRUCT__

/**
 * This header is not intended to be included in project source files. It can be
 * used for decomp.me contextx and alessastruct.
 */

 /*
 
to rebuild with alessastruct:


```sh
alessastruct --platform=ps2 --output=tools/alessatool/kaitai/sh2.ksy  \
    tools/alessatool/kaitai/data/sh2.h                                \
    -- -Iinclude -Isilent-hill-2/include -Isilent-hill-2/src          \
    -std=gnu89 -fshort-enums > alessastruct.log 2>&1
```

then:

```sh
kaitai-struct-compiler --target python tools/alessatool/kaitai/sh2.ksy --outdir tools/alessatool/kaitai
```



 */
#define __ALESSASTRUCT_README__

#include "sh2_common.h"
#include "SH2_common/mem_share.h"
#include "SH2_common/pad.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/sh2dt.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/sh_vu0.h"

#include "Chacter/chara_bound.h"
#include "Chacter/charaboundtbl.h"
#include "Chacter/character.h"
#include "Chacter/item_screen_obj.h"
#include "Chacter/m3_angela.h"
#include "Chacter/m3_bgobj.h"
#include "Chacter/m3_boat.h"
#include "Chacter/m3_bos.h"
#include "Chacter/m3_djames.h"
#include "Chacter/m3_dmaria.h"
#include "Chacter/m3_edb.h"
#include "Chacter/m3_eddie.h"
#include "Chacter/m3_ike.h"
#include "Chacter/m3_inu.h"
#include "Chacter/m3_laura.h"
#include "Chacter/m3_maria.h"
#include "Chacter/m3_mary.h"
#include "Chacter/m3_mkn.h"
#include "Chacter/m3_oni.h"
#include "Chacter/m3_pap.h"
#include "Chacter/m3_play_event.h"
#include "Chacter/m3_red.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_scu.h"
#include "Chacter/player_result.h"
#include "Chacter/sh2_character_manage.h"
#include "Chacter/sh_character_battle.h"
#include "Chacter/sh_character_status.h"

#include "Chacter_Draw/sh2gfw_model_light.h"
#include "Collision/cl_main.h"

#include "DBG/dbflow.h"
#include "DBG/dbfntprint.h"

#include "Effect/screen_effect.h"

#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_object_execute.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_effect_object_def.h"
#include "Effect2/hh_memory_manage.h"

#include "Enemy/en_arm.h"
#include "Enemy/en_common.h"
#include "Enemy/en_effect.h"
#include "Event/chara_admin.h"
#include "Event/chara_data_load.h"
#include "Event/chizu.h"
#include "Event/demoview.h"
#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/item.h"
#include "Event/picture.h"
#include "Event/stg_name.h"
#include "Event/title.h"

#include "Fog/fog.h"

#include "Font/fj_man.h"
#include "Font/font.h"

#include "GFW/sh2gfw_2d_filters.h"
#include "GFW/sh2gfw_LightSet.h"
#include "GFW/sh2gfw_structs.h"

#include "LoadBg/loadbg_common.h"

#include "MC/mc.h"
#include "MC/mc_menu.h"
#include "MC/savedata.h"

#include "gamemain.h"
#include "gs.h"
#include "logo.h"

#include "movie/movie_main.h"
#include "movie/pss_common.h"
#include "now_loading.h"
#include "pause.h"

#include "sce/eetypes.h"
#include "sce/libdma.h"
#include "sce/libscf.h"
#include "sce/libvifpk.h"
#include "sce/libvu0.h"

#include "sh2gfw_drawloop_main.h"
#include "shGs/sh2gfw_GS_NewLoopEnv.h"

#include "shared/Fog/fog.h"

#include "sound/sh_sd_call.h"
#include "sound/sh_sound.h"
#include "sound/snd_select.h"

#include "view/vb_main.h"
#include "view/vc_main.h"
#include "view/vc_util.h"

#endif
