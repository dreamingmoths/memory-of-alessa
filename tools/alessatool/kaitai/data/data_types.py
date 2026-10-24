from enum import Enum
from pathlib import Path
from typing import Type
from dataclasses import dataclass
from collections.abc import Callable
from kaitaistruct import KaitaiStruct

@dataclass
class Pointer:
    address: int

@dataclass
class String:
    pass

@dataclass
class StructData:
    name: str
    type: Type[KaitaiStruct]
    count: int
    address: int = -1
    executable: str = None
    hex: bool = False

@dataclass
class SimpleData:
    name: str
    type: str | Pointer
    pattern: list[int] = None
    to_str: Callable[[any], str] = None
    address: int = -1
    executable: str = None

type DataTable = list[SimpleData | StructData]

@dataclass
class ProjectDataConfig:
    table: DataTable
    namespace: Type[KaitaiStruct]
    library_path: Path
    chara_list_path: Path

class StgName(Enum):
    Stg_null = 0x00
    Stg_tgs_trial = 0x01
    Stg_toilet = 0x02
    Stg_observation = 0x03
    Stg_forest = 0x04
    Stg_town_east = 0x05
    Stg_apart_e1f = 0x06
    Stg_apart_e2f = 0x07
    Stg_apart_e3fw = 0x08
    Stg_apart_e3fe = 0x09
    Stg_apart_w1f = 0x0A
    Stg_apart_w2f = 0x0B
    Stg_apart_stair = 0x0C
    Stg_apart_out = 0x0D
    Stg_town_west = 0x0E
    Stg_bowling = 0x0F
    Stg_to_heaven = 0x10
    Stg_heaven_night = 0x11
    Stg_hospital_1f_f = 0x12
    Stg_hospital_2f_f = 0x13
    Stg_hospital_3f_f = 0x14
    Stg_hospital_rf_f = 0x15
    Stg_hospital_1fw_b = 0x16
    Stg_hospital_1fe_b = 0x17
    Stg_hospital_2f_b = 0x18
    Stg_hospital_3f_b = 0x19
    Stg_hospital_bf_b = 0x1A
    Stg_hospital_pass = 0x1B
    Stg_society = 0x1C
    Stg_delusion_2 = 0x1D
    Stg_delusion_3 = 0x1E
    Stg_prison_n = 0x1F
    Stg_prison_s = 0x20
    Stg_prison_bf = 0x21
    Stg_labyrinth_w = 0x22
    Stg_labyrinth_e = 0x23
    Stg_labyrinth_n = 0x24
    Stg_eddie_boss = 0x25
    Stg_lake = 0x26
    Stg_hotel_bf_f = 0x27
    Stg_hotel_1f_f = 0x28
    Stg_hotel_2f_f = 0x29
    Stg_hotel_3f_f = 0x2A
    Stg_hotel_bf_b = 0x2B
    Stg_hotel_1f_b = 0x2C
    Stg_hotel_2f_b = 0x2D
    Stg_hotel_3f_b = 0x2E
    Stg_hotel_fire = 0x2F
    Stg_end_recovery = 0x30
    Stg_end_maria = 0x31
    Stg_end_suicide = 0x32
    Stg_end_rebirth = 0x33
    Stg_end_dog = 0x34
    Stg_num = 0x35

