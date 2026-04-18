# This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

import kaitaistruct
from kaitaistruct import KaitaiStruct, KaitaiStream, BytesIO


if getattr(kaitaistruct, "API_VERSION", (0, 9)) < (0, 9):
    raise Exception("Incompatible Kaitai Struct Python API: 0.9 or later is required, but you have %s" % (kaitaistruct.__version__))

class Mfa(KaitaiStruct):
    def __init__(self, skip_command_prelude, _io, _parent=None, _root=None):
        self._io = _io
        self._parent = _parent
        self._root = _root if _root else self
        self.skip_command_prelude = skip_command_prelude
        self._read()

    def _read(self):
        if not (self.skip_command_prelude):
            self.command_prelude = Mfa.CommandPrelude(self._io, self, self._root)

        self.num_files = self._io.read_u4le()
        self.archive_size = self._io.read_u4le()
        self.file_info = []
        for i in range(self.num_files):
            self.file_info.append(Mfa.Info(self._io, self, self._root))

        self.filenames = []
        for i in range(self.num_files):
            self.filenames.append((self._io.read_bytes_term(0, False, True, True)).decode(u"shift-jis"))

        self.pad = self._io.read_u1()
        if not self.pad == 10:
            raise kaitaistruct.ValidationNotEqualError(10, self.pad, self._io, u"/seq/5")
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


    class CommandPrelude(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.commmand = (self._io.read_bytes_term(12, False, True, True)).decode(u"shift-jis")
            self.line_feed = self._io.read_u1()
            if not self.line_feed == 10:
                raise kaitaistruct.ValidationNotEqualError(10, self.line_feed, self._io, u"/types/command_prelude/seq/1")
            self.spaces = []
            i = 0
            while True:
                _ = self._io.read_u1()
                self.spaces.append(_)
                if (self._io.pos() % 16) == 8:
                    break
                i += 1


    @property
    def header_size(self):
        if hasattr(self, "_m_header_size"):
            return self._m_header_size

        self._m_header_size = 2048
        return getattr(self, "_m_header_size", None)


