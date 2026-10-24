from collections.abc import Callable
from dataclasses import dataclass
from ctypes import c_float
from functools import reduce
from pathlib import Path
from struct import unpack, calcsize
from io import BytesIO
from sys import stdout
from typing import TextIO, Type
from re import MULTILINE, finditer, sub

from kaitaistruct import KaitaiStream, KaitaiStruct
from kaitai.data.config import PROJECT_DATA_CONFIG
from kaitai.data.data_types import Pointer, ProjectDataConfig, SimpleData, String, StructData

from constants import CONFIG, INDENT_SIZE, PROJECT_CONFIG
from kaitai.sh2 import Sh2
from utils import AddressConversion, ExeInfoByName, SplatSymbolAddrsAtlas, get_exe_info_by_name, get_from_vram_conversion, load_yaml

class DataMigrationStore:
    '''A cache of information to be reused across data migration calls.'''
    atlas: SplatSymbolAddrsAtlas
    splat_yaml: dict
    kaitai_yaml: dict
    executable_path: Path

    data_config: ProjectDataConfig

    data_entry: SimpleData | StructData = None
    project: str | None = None

    exe_info_by_name: ExeInfoByName = dict()

    def set_data_entry(self, entry: SimpleData | StructData):
        self.data_entry = entry

    def reset_data_entry(self): 
        self.data_entry = None
    
    def set_data_entry_if_not_set(self, data_config: ProjectDataConfig, name: str):
        if not self.data_entry:
            table = data_config.table
            data_entry = next(filter(lambda entry : entry.name == name, table))
            self.data_entry = data_entry

    def read(self, project: str, name: str):
        serial = PROJECT_CONFIG[project]
        root = Path(project) / CONFIG / serial

        data_config = PROJECT_DATA_CONFIG[project]

        self.reset_data_entry()
        self.set_data_entry_if_not_set(data_config, name)

        data_entry = self.data_entry

        executable = data_entry.executable or serial
        exe_info_by_name = get_exe_info_by_name(
            root,
            serial,
            filter=executable,
            exe_info_by_name=self.exe_info_by_name,
            parse_attributes=True
        )
        exe_info = exe_info_by_name[executable == serial and "main" or executable]

        if self.project is not None:
            assert self.project == project, "the store is intended to hold data for only one project"
            return

        atlas = exe_info.atlas
        executable_path = exe_info.target_path / executable
        splat_yaml = load_yaml(exe_info.yaml_path)
        kaitai_yaml = load_yaml(data_config.library_path)

        self.project = project
        self.exe_info_by_name = exe_info_by_name
        self.atlas = atlas
        self.splat_yaml = splat_yaml
        self.kaitai_yaml = kaitai_yaml
        self.executable_path = executable_path
        self.data_config = data_config
        self.data_entry = data_entry

@dataclass
class DataMigrationRequest:
    '''
    Options to `run_data_migration`.
    '''
    project: str
    name: str
    stream: TextIO
    store: DataMigrationStore | None = None

@dataclass
class SimpleDataMigrationRequest:
    '''
    Options to `migrate_simple_data`, to migrate data that does not contain
    structs.
    '''
    name: str
    stream: TextIO
    atlas: SplatSymbolAddrsAtlas
    data: SimpleData
    splat_yaml: dict
    executable_path: Path

@dataclass
class StructDataMigrationRequest(SimpleDataMigrationRequest):
    '''
    Options to `migrate_struct_data`.
    '''
    data: StructData
    kaitai_yaml: dict
    namespace: Type[KaitaiStruct]

@dataclass
class KaitaiCFormatterOptions:
    '''
    Options to `c_print_kaitai`.
    '''
    request: StructDataMigrationRequest
    executable_file: BytesIO
    from_vram: AddressConversion
    index: int

class AlessastructDataOptions:
    TEST_ENVIRONMENT = False

def read_string(file: BytesIO, offset: int) -> str:
    '''
    Read a string at the specific offset.
    '''
    file.seek(offset)
    c = file.read(1)
    string = ""
    while c != b"\x00":
        dec = c.decode()
        if dec == '\t': dec = "\\t"
        elif dec == '\n': dec = "\\n"
        elif dec == '\r': dec = "\\r"
        string += dec
        c = file.read(1)
    return string

def find_smallest_float_string(f: float):
    '''
    Try to minimize the length of a decimal string representing a float.
    
    a slow, silly way
    '''
    float_string = str(f)
    f32 = c_float(f)

    if f32.value == 0:
        return "0.0f"

    assert f32.value == c_float(f).value

    size = len(float_string)

    for i in range(len(float_string), 0, -1):
        candidate = float_string[:i]
        if c_float(float(candidate)).value != f32.value:
            break
        size = i

    result = float_string[:size]

    match result:
        case "3.1415927":
            return "PI"
        case "-3.1415927":
            return "-PI"
        case "1.57079637":
            return "QUARTER_TURN"
        case "-1.57079637":
            return "-QUARTER_TURN"

    if "." not in result:
        result += ".0"

    return result + "f"

def pretty_print_kaitai(object: KaitaiStruct, indent=""):
    '''
    Debug print a parsed KaitaiStruct.
    '''
    object._fetch_instances()
    own_properties = hasattr(object, "member_names") and object.member_names or set(dir(object)) - set(dir(KaitaiStruct))
    for attr in own_properties:
        if attr.startswith("_"):
            continue
        value = getattr(object, attr)
        if isinstance(value, KaitaiStruct):
            print(f"{indent}{attr} => ")
            pretty_print_kaitai(value, indent=indent+"      => ")
        else:
            if isinstance(value, int):
                print(f"{indent}{attr}  => 0x{value:X}")
            elif isinstance(value, bytes):
                print(f"{indent}{attr}  => {", ".join(list(map(lambda v : f"{v:X}", list(value))))}")
            else:
                print(f"{indent}{attr}  => {value}")

def camel_to_snake(s: str):
    return "".join(["_" + c.lower() if c.isupper() else c for c in s]).lstrip("_")

def snake_to_camel(s: str):
    result = "".join(map(lambda s : s.capitalize(), s.split("_")))
    return result[0].lower() + result[1:]

def to_kaitai_id(s: str):
    s = camel_to_snake(s)
    return sub(r"(\d+)", lambda m : "_" + m.group(1), s)

def reflect_kaitai_structure(yaml: dict, type: Type[KaitaiStruct]):
    '''
    Get the YAML for the Kaitai type from the `.ksy` yaml.
    '''
    name = type.__name__
    typename = to_kaitai_id(name)
    if typename not in yaml["types"]:
        # try a different way
        typename = camel_to_snake(name)
    return yaml["types"][typename]

def c_print_kaitai(object: KaitaiStruct, options: KaitaiCFormatterOptions, indent=" " * (INDENT_SIZE * 2)):
    '''
    Write a parsed KaitaiStruct out as plain old data.
    '''
    request = options.request
    executable_file = options.executable_file

    atlas = request.atlas
    namespace = request.namespace
    data = request.data
    stream = request.stream
    kaitai_yaml = request.kaitai_yaml

    from_vram = options.from_vram

    index = options.index
    not_last = index < data.count - 1

    object._fetch_instances()
    object_class = object.__class__
    type_structure = reflect_kaitai_structure(kaitai_yaml, object.__class__)

    # union
    if "instances" in type_structure:
        first_union_member = next(iter(type_structure["instances"]))
        own_properties = [first_union_member]
        if not AlessastructDataOptions.TEST_ENVIRONMENT:
            print("🟠 warning: there is no way to choose union options yet")
            print(f"\tthe first union member was chosen for {object_class.__name__}:", first_union_member)

    # struct
    elif "seq" in type_structure:
        own_properties = map(lambda t : t["id"], filter(lambda t : "id" in t, type_structure["seq"]))
    stream.write(f"{indent[INDENT_SIZE:]}{{\n") # indent braces less

    for attr in own_properties:
        if attr.startswith("_"):
            continue
        value = getattr(object, attr)
        attr_str = snake_to_camel(attr) # @todo use `-orig-id` when this doesn't match

        if hasattr(namespace, "Pointer") and isinstance(value, getattr(namespace, "Pointer")):
            # pointer! look up the symbol name
            val = lookup_pointer(atlas, executable_file, from_vram, value.address)
            stream.write(f"{indent}/* .{attr_str} = */ {val},\n")

        elif isinstance(value, KaitaiStruct):
            # nested struct
            stream.write(f"{indent}/* .{attr_str} = */ ")
            c_print_kaitai(value, options, indent=indent+"    ")

        else:
            # something else, maybe a list, number, or string
            if isinstance(value, int):
                # number
                if data.hex:
                    stream.write(f"{indent}/* .{attr_str} = */ 0x{value:X},\n")
                else:
                    stream.write(f"{indent}/* .{attr_str} = */ {value},\n")

            elif isinstance(value, bytes):
                # hex array
                stream.write(f"{indent}/* .{attr_str} = */ {", ".join(list(map(lambda v : f"{v:X}", list(value))))},\n")

            elif isinstance(value, list):
                element = value[0]
                if isinstance(element, float):
                    # float array
                    stream.write(f"{indent}/* .{attr_str} = */ {{{", ".join(map(find_smallest_float_string, value)).replace("\0", "")}}},\n")
                else:
                    # string array
                    stream.write(f"{indent}/* .{attr_str} = */ \"{"".join(map(chr, value)).replace("\0", "")}\",\n")

            elif isinstance(value, float):
                # float
                stream.write(f"{indent}/* .{attr_str} = */ {find_smallest_float_string(value)},\n")
            else:
                # unknown
                stream.write(f"{indent}/* .{attr_str} = */ {value},\n")

    stream.write(f"{indent[INDENT_SIZE:]}}}{not_last and "," or ""}\n")  # indent braces less

def migrate_struct_data(request: StructDataMigrationRequest):
    atlas = request.atlas
    data = request.data
    splat_yaml = request.splat_yaml

    sym = data.address >= 0 and atlas.syms_by_addr[data.address] or atlas.syms_by_name[data.name]
    from_vram = get_from_vram_conversion(splat_yaml, rom=False)

    with open(request.executable_path, "rb") as executable_file:
        executable_file.seek(from_vram(sym.addr))
        stream = KaitaiStream(executable_file)

        request.stream.write('#include "macros.h"\n')
        request.stream.write('#include "math.h"\n')
        request.stream.write(f"UNLINKED({request.name}, {{\n")

        for i in range(data.count):
            item = data.type(stream)
            item._fetch_instances()

            ofs = executable_file.tell()
            options = KaitaiCFormatterOptions(
                request=request,
                from_vram=from_vram,
                executable_file=executable_file,
                index=i
            )
            c_print_kaitai(item, options)
            executable_file.seek(ofs)
        
        request.stream.write("});\n")

def default_to_str(value):
    if isinstance(value, bytes):
        assert len(value) == 1
        return str(int(value[0]))
    return str(value)

def make_pointer_to_str(atlas: SplatSymbolAddrsAtlas, executable_file: BytesIO, from_vram: AddressConversion):
    return lambda address : lookup_pointer(atlas, executable_file, from_vram, address)

def lookup_pointer(atlas: SplatSymbolAddrsAtlas, executable_file: BytesIO, from_vram: AddressConversion, address: int):
    val = None
    if address in atlas.syms_by_addr:
        sym = atlas.syms_by_addr[address]
        val = sym.name
        if isinstance(val, str) and val.startswith("@"):
            val = '"' + read_string(executable_file, from_vram(address)) + '"'
    elif address == 0:
        val = "NULL"
    assert val is not None, f"could not find symbol at {address:X}"
    return val

def migrate_simple_data(request: SimpleDataMigrationRequest):
    data = request.data
    stream = request.stream
    atlas = request.atlas

    pattern = data.pattern

    with open(request.executable_path, "rb") as file:
        from_vram = get_from_vram_conversion(request.splat_yaml, rom=False)

        is_string = data.type == String
        is_pointer = data.type == Pointer
        if is_pointer:
            total = reduce(lambda a, b : a * b, pattern or [1])
            fmt = f"<{total}L"
            to_str = data.to_str or make_pointer_to_str(atlas, file, from_vram)
        else:
            fmt = data.type
            to_str = data.to_str or default_to_str

        sym = data.address >= 0 and atlas.syms_by_addr[data.address] or atlas.syms_by_name[data.name]
        if is_string:
            stream.write('"' + read_string(file, from_vram(sym.addr)) + '"')
            return

        file.seek(from_vram(sym.addr))

        assert type(fmt) == str, fmt


        unpacked_values = unpack(fmt, file.read(calcsize(fmt)))
        n = pattern and len(pattern) or 0

        if n < 2:
            stream.write(f"{{ {", ".join(map(lambda value : to_str(value), unpacked_values))} }}\n")
        elif n == 2:
            result = "{\n"
            indent = "    "
            cursor = 0

            for i in range(pattern[0]):
                if cursor >= len(unpacked_values):
                    break
                result += f"{indent}{{ "
                for j in range(pattern[1]):
                    result += f"{to_str(unpacked_values[cursor])}"
                    if j != pattern[1] - 1:
                        result += ", "
                    cursor += 1
                result += " },\n"
            
            result += "};\n"
            stream.write(result)
        else:
            raise NotImplementedError("n > 2")


def run_data_migration(request: DataMigrationRequest):
    name = request.name
    project = request.project
    stream = request.stream

    try:
        store = request.store or DataMigrationStore()

        store.read(project, name)

        atlas = store.atlas
        data_config = store.data_config
        data_entry = store.data_entry
        splat_yaml = store.splat_yaml
        executable_path = store.executable_path
        kaitai_yaml = store.kaitai_yaml
        namespace = data_config.namespace

        if isinstance(data_entry, SimpleData):
            request = SimpleDataMigrationRequest(
                name=name,
                stream=stream,
                atlas=atlas,
                data=data_entry,
                splat_yaml=splat_yaml,
                executable_path=executable_path
            )
            migrate_simple_data(request)
        elif isinstance(data_entry, StructData):
            request = StructDataMigrationRequest(
                name=name,
                stream=stream,
                atlas=atlas,
                data=data_entry,
                splat_yaml=splat_yaml,
                kaitai_yaml=kaitai_yaml,
                namespace=namespace,
                executable_path=executable_path
            )
            migrate_struct_data(request)
        else:
            raise Exception(f"unexpected data config format")

        if not AlessastructDataOptions.TEST_ENVIRONMENT:
            print(f"🟣 data template written to {stream.name}")
    except StopIteration:
        print(f"🔴 could not find data entry ({name})")
    except Exception as exception:
        print(f"🔴 failed to migrate data ({name}):")
        raise exception
