import os
import sys
import stat
import subprocess

from dataclasses import dataclass
from hashlib import sha1
from pathlib import Path
from constants import ALESSASTRUCT, ALESSASTRUCT_SH2_PYTHON, ALESSATOOL_KAITAI, KAITAI_STRUCT_COMPILER, KAITAI_STRUCT_COMPILER_UNIVERSAL_FOLDER, KAITAI_STRUCT_COMPILER_ZIP
from traceback import print_exception
from urllib.request import urlretrieve
from zipfile import ZipFile

@dataclass
class AlessastructVersionInfo:
    platform: str
    hash: str
    url: str

ALESSASTRUCT_URL_BASE = "https://github.com/dreamingmoths/alessastruct/releases/download"
KAITAI_STRUCT_URL     = "https://github.com/kaitai-io/kaitai_struct_compiler/releases/download/0.11/kaitai-struct-compiler-0.11.zip"
ALESSASTRUCT_VERSIONS = [
    AlessastructVersionInfo(
        platform="linux", 
        hash="ef5feda2a814eb5554e1a690a3ee919cd69dcea4",
        url="v0.0.1/alessastruct-linux-x86_64"
    ),
    AlessastructVersionInfo(
        platform="macos", 
        hash="7217d2cb9eee22a611d3ab352562c6d84a64c7ac",
        url="v0.0.1/alessastruct-macos-arm64"
    ),
]

ALESSASTRUCT_INVOCATION = [
    "--platform=ps2",
    f"--output={ALESSATOOL_KAITAI}/sh2.ksy",
    f"{ALESSATOOL_KAITAI}/data/sh2.h",
    "--",
    "-Iinclude",
    "-Isilent-hill-2/include",
    "-Isilent-hill-2/src",
    "-std=gnu89",
    "-fshort-enums"
]

KAITAI_STRUCT_COMPILER_INVOCATION = [
    "--target=python",
    f"{ALESSATOOL_KAITAI}/sh2.ksy",
    f"--outdir={ALESSATOOL_KAITAI}"
]

def get_target_platform():
    return sys.platform == "darwin" and "macos" or "linux"

def get_version_info_by_hash(target_hash: str):
    for version_info in ALESSASTRUCT_VERSIONS:
        if version_info.hash == target_hash:
             return version_info
    return None

def get_version_info_by_platform(target_platform: str):
    for version_info in ALESSASTRUCT_VERSIONS:
        if version_info.platform == target_platform:
             return version_info
    return None

def print_progress(block_number: int, read_size: int, total_size: int):
    percent = min(100.0 * ((block_number * read_size) / total_size), 100.0)
    print(f"\rdownloading... {percent:.2f}%", end=percent == 100.0 and "\n" or "") 

def make_file_executable(path: Path):
    st = os.stat(path)
    os.chmod(path, st.st_mode | stat.S_IEXEC)

def download_file(url: str, path: Path):
    urlretrieve(url, path.as_posix(), print_progress)

def verify_alessastruct(alessastruct_path: Path) -> bool:
    version_info      = None

    if alessastruct_path.exists():
        alessastruct_hash = sha1(alessastruct_path.read_bytes()).hexdigest()
        version_info = get_version_info_by_hash(alessastruct_hash)
        if version_info:
            print(f"🌺 found an alessastruct version for {version_info.platform}")
        else:
            print(f"out-of-date alessastruct version: {alessastruct_hash}")
    else:
        print(f"couldn't find an alessastruct version")

    if not version_info:
        try:
            target_platform = get_target_platform()
            version_info = get_version_info_by_platform(target_platform)
            url = f"{ALESSASTRUCT_URL_BASE}/{version_info.url}"

            download_file(url, alessastruct_path)
            make_file_executable(alessastruct_path)

            print(f"🟣 updated alessastruct version from {version_info.url}")
            print(f"   @ {alessastruct_path.as_posix()}")
        except Exception as exception:
            print(f"🔴 failed to update alessastruct version")
            print_exception(exception)

    if not version_info:
        return False

    return True

def strtobool(value: str) -> bool:
    value = value.lower()
    if value in ("y", "yes", "t", "true", "on", "1"):
        return True
    elif value in ("n", "no", "f", "false", "off", "0"):
        return False
    else:
        raise ValueError("invalid truth value %r" % (value,))

def download_kaitai_struct_compiler():
    kaitai_struct_path = Path(KAITAI_STRUCT_COMPILER)
    zip_path = Path(KAITAI_STRUCT_COMPILER_ZIP)

    download_file(KAITAI_STRUCT_URL, zip_path)

    zip_file = ZipFile(zip_path)
    zip_file.extractall(zip_path.parent)

    make_file_executable(kaitai_struct_path)

    zip_path.unlink()

    return kaitai_struct_path

def find_kaitai_struct_compiler(kaitai_struct_path: Path) -> Path | None:
    if not kaitai_struct_path.exists():
        kaitai_struct_path = Path("kaitai-struct-compiler")

    try:
        process = subprocess.run([kaitai_struct_path.as_posix(), "--version"], capture_output=True)
        print(f"🌺 {process.stdout.decode().strip()}")
    except Exception:
        result = input("🔴 could not run the kaitai struct compiler. download the universal zip (y/n)?: ")
        if strtobool(result):
            try:
                kaitai_struct_path = download_kaitai_struct_compiler()
                print(f"🟣 downloaded kaitai struct compiler")
            except Exception as exception:
                print(f"🔴 failed to download kaitai struct compiler")
                print_exception(exception)
        else:
            return None

    return kaitai_struct_path

def clean_alessastruct_dependencies():
    result = input("this will delete the local copy of the kaitai struct compiler and alessastruct. continue (y/n)?: ")
    if strtobool(result):
        subprocess.run(["rm", "-rf", KAITAI_STRUCT_COMPILER_UNIVERSAL_FOLDER])
        subprocess.run(["rm", "-f",  ALESSASTRUCT])

def run_alessastruct(alessastruct_path: Path):
    subprocess.run([alessastruct_path.as_posix(), *ALESSASTRUCT_INVOCATION])

def compile_kaitai_struct(kaitai_struct_path: Path):
    subprocess.run([kaitai_struct_path.as_posix(), *KAITAI_STRUCT_COMPILER_INVOCATION])

def postprocess_python_output():
    with open(ALESSASTRUCT_SH2_PYTHON, "r") as python_file:
        text = python_file.read()
        text = text.replace(".as = ",     ".as_ = "    )
        text = text.replace(".global = ", ".global_ = ")

    with open(ALESSASTRUCT_SH2_PYTHON, "w") as python_file:
        python_file.write(text)

def update_alessastruct():
    alessastruct_path  = Path(ALESSASTRUCT)
    if not verify_alessastruct(alessastruct_path): return
    
    kaitai_struct_path = Path(KAITAI_STRUCT_COMPILER)
    kaitai_struct_path = find_kaitai_struct_compiler(kaitai_struct_path)
    if not kaitai_struct_path: return

    print("🌺 updating...")

    run_alessastruct(alessastruct_path)
    compile_kaitai_struct(kaitai_struct_path)
    postprocess_python_output()

    print("🌺 alessastruct updated")
