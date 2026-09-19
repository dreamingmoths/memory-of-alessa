
from splat.segtypes.common.o import CommonSegO

class PS2SegVutext(CommonSegO):
    def get_linker_section(self) -> str:
        return ".text"
