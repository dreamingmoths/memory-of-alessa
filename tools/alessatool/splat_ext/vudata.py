from splat.segtypes.common.o import CommonSegO

class PS2SegVudata(CommonSegO):
    def get_linker_section(self) -> str:
        return ".data"
