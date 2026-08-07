'''
alessatool/debug

troubleshoot issues with nonmatching builds.

example:

alessatool debug --executable SLUS_206.22

run `alessatool debug --help` for more information.
'''

from sys import stdout, stdin
from pathlib import Path
from subprocess import run
from dataclasses import dataclass
from constants import *
from struct import unpack

from utils import parse_symbol_addrs

@dataclass
class DebugArgs:
    project: str
    config_path: Path

def debug_nonmatching(args: DebugArgs):
    parse_symbol_addrs
