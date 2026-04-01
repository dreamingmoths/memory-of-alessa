# This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

import kaitaistruct
from kaitaistruct import KaitaiStruct, KaitaiStream, BytesIO


if getattr(kaitaistruct, "API_VERSION", (0, 9)) < (0, 9):
    raise Exception("Incompatible Kaitai Struct Python API: 0.9 or later is required, but you have %s" % (kaitaistruct.__version__))

class MwOverlayHeader(KaitaiStruct):
    def __init__(self, _io, _parent=None, _root=None):
        self._io = _io
        self._parent = _parent
        self._root = _root if _root else self
        self._read()

    def _read(self):
        self.identifier = self._io.read_bytes(3)
        self.version = self._io.read_u1()
        self.id = self._io.read_u4le()
        self.address = self._io.read_u4le()
        self.sz_text = self._io.read_u4le()
        self.sz_data = self._io.read_u4le()
        self.sz_bss = self._io.read_u4le()
        self.static_init = self._io.read_u4le()
        self.static_init_end = self._io.read_u4le()
        self.name = (KaitaiStream.bytes_terminate(self._io.read_bytes(32), 0, False)).decode(u"ascii")


