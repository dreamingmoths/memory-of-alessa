from pathlib import Path

from kaitai.sh2 import Sh2
from kaitai.data.data_types import SimpleData, StructData, StgName, ProjectDataConfig

from constants import ALESSATOOL

SH2_DATA = [
    StructData(name="chara_bound_tbl",                      type=Sh2.CharaBound,                       count=236                      ),
    StructData(name="_pObject_Class_List",                  type=Sh2.ObjectClass,                      count=48                       ),
    StructData(name="_MemoryPool_AssociationInfo_Table",    type=Sh2.MemoryPoolAssociationInfomeation, count=48                       ),
    StructData(name="_Object_Data_Table",                   type=Sh2.ObjectDataPoolInfomeation,        count=48                       ),
    StructData(name="item_screen_obj_data",                 type=Sh2.ShItemScreenObjectSettingData,    count=58                       ),
    StructData(name="EnIKEAnime",                           type=Sh2.EnAnimeData,                      count=21                       ),
    SimpleData(name="reset_stage_connect_2170",             type="<14h",                               pattern=[12, 2], to_str=StgName),
    SimpleData(name="_Object_Class_Priority_List",          type="<49I"                                                               ),
    StructData(name="ambush_apart",                         type=Sh2.EnAmbushData,                     count=9                        ),
    StructData(name="chz_crt_block",                        type=Sh2.ChizuCurrentBlock,                count=190                      ),
    StructData(name="chizu_marker_list",                    type=Sh2.ChizuMarkerList,                  count=36,        hex=False     ),
]

SH3_DATA = []

PROJECT_DATA_CONFIG = {
    "silent-hill-2": ProjectDataConfig(
        table=SH2_DATA,
        namespace=Sh2,
        library_path=Path(ALESSATOOL) / "kaitai/sh2.ksy",
        chara_list_path=Path("silent-hill-2/src/Chacter/chara_list.h")
    ),

    # not yet configured
    "silent-hill-3": ProjectDataConfig(
        table=SH3_DATA,
        namespace=None,
        library_path=None,
        chara_list_path=Path("silent-hill-3/src/Chacter/chara_list.h")
    ),
}
