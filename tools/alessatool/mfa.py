# This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

import kaitaistruct
from kaitaistruct import KaitaiStruct, KaitaiStream, BytesIO


if getattr(kaitaistruct, "API_VERSION", (0, 9)) < (0, 9):
    raise Exception("Incompatible Kaitai Struct Python API: 0.9 or later is required, but you have %s" % (kaitaistruct.__version__))

class Mfa(KaitaiStruct):
    def __init__(self, _io, _parent=None, _root=None):
        self._io = _io
        self._parent = _parent
        self._root = _root if _root else self
        self._read()

    def _read(self):
        self.commmand = (KaitaiStream.bytes_terminate(self._io.read_bytes(224), 0, False)).decode(u"ascii")
        self.file_info = []
        i = 0
        while True:
            _ = Mfa.Info(self._io, self, self._root)
            self.file_info.append(_)
            if _.file_ofs == 538976288:
                break
            i += 1
        self.filenames = []
        for i in range(self.num_files):
            self.filenames.append((self._io.read_bytes_term(0, False, True, True)).decode(u"ascii"))

        self.pad = self._io.read_u1()
        if not self.pad == 10:
            raise kaitaistruct.ValidationNotEqualError(10, self.pad, self._io, u"/seq/3")
        self.files = []
        for i in range(self.num_files):
            self.files.append(Mfa.File(self._io.pos(), i, self._io, self, self._root))

    class File(KaitaiStruct):
        def __init__(self, base, index, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self.base = base
            self.index = index
            self._read()

        def _read(self):
            pass

        @property
        def data(self):
            if hasattr(self, "_m_data"):
                return self._m_data

            _pos = self._io.pos()
            self._io.seek(self.data_ofs)
            self._m_data = self._io.read_bytes(self.len_data)
            self._io.seek(_pos)
            return getattr(self, "_m_data", None)

        @property
        def data_ofs(self):
            if hasattr(self, "_m_data_ofs"):
                return self._m_data_ofs

            self._m_data_ofs = (self.base + self._root.file_info[self.index].file_ofs)
            return getattr(self, "_m_data_ofs", None)

        @property
        def len_data(self):
            if hasattr(self, "_m_len_data"):
                return self._m_len_data

            self._m_len_data = self._root.file_info[self.index].file_size
            return getattr(self, "_m_len_data", None)

        @property
        def filename(self):
            if hasattr(self, "_m_filename"):
                return self._m_filename

            self._m_filename = self._root.filenames[((self._root.num_files - self.index) - 1)]
            return getattr(self, "_m_filename", None)


    class Info(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self._unnamed0 = self._io.read_u4le()
            self.file_ofs = self._io.read_u4le()
            self._unnamed2 = self._io.read_u4le()
            self.file_size = self._io.read_u4le()


    @property
    def num_files(self):
        if hasattr(self, "_m_num_files"):
            return self._m_num_files

        self._m_num_files = (len(self._root.file_info) - 1)
        return getattr(self, "_m_num_files", None)


