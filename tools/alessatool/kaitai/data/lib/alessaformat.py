import os
import sys
from ctypes import c_char_p, c_float, cast, cdll

from utils import get_library_ext
from kaitai.data.float import end_float_string, find_smallest_float_string

class Alessaformat:
    DYLIB_NAME = "libalessaformat"
    SUPPORTED_PLATFORMS = ("darwin", "linux", "linux2")
    PRINT_PLATFORM_WARNING = True

    lib = None

    warned_once = False

    def __init__(self):
        self.formatter = lambda f : self.pretty_print_float(f)

    def open_dylib(self):
        if self.lib is not None:
            return 

        if sys.platform not in Alessaformat.SUPPORTED_PLATFORMS:
            self.warn_about_platform()
            return

        dirname = os.path.dirname(__file__)
        dylib_path = os.path.join(dirname, f"{Alessaformat.DYLIB_NAME}.{get_library_ext()}")

        if not os.path.exists(dylib_path):
            self.warn_about_existence(dylib_path)
            return

        self.lib = self._open_dylib(dylib_path)

    def _open_dylib(self, dylib_path: str):
        lib = cdll.LoadLibrary(dylib_path)
        lib.pretty_float.restype = c_char_p
        lib.pretty_float.argtypes = [c_float]

        return lib

    def pretty_print_float(self, f: float) -> str:
        if self.lib is not None:
            result = self.lib.pretty_float(f)
            string = cast(result, c_char_p).value.decode()
            return end_float_string(string)
        else:
            self.warn_about_init()
            return find_smallest_float_string(f)

    def warn_about_platform(self):
        if self.should_warn_about_platform():
            self.warn(f"libalessaformat is not supported yet for {sys.platform}.")

    def warn_about_init(self):
        if self.should_warn_about_init():
            self.warn(f"libalessaformat wasn't initialized.")

    def warn_about_existence(self, dylib_path: str):
        if self.should_warn_about_existence():
            self.warn(f"libalessaformat doesn't exist at {os.path.relpath(dylib_path)}.")

    def warn(self, message: str):
        print(f"warning: {message}")
        print("\tfloat formatting may not be ideal.")
        print("\trun `alessatool migrate --update` to download alessaformat.")
        self.warned_once = True

    def should_warn_about_platform(self):
        return self.PRINT_PLATFORM_WARNING and not self.warned_once

    def should_warn_about_init(self):
        return not self.warned_once

    def should_warn_about_existence(self):
        return not self.warned_once

alessaformat = Alessaformat()
