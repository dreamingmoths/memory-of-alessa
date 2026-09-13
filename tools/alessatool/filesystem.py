# This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild
# type: ignore

import kaitaistruct
from kaitaistruct import KaitaiStruct, KaitaiStream, BytesIO


if getattr(kaitaistruct, 'API_VERSION', (0, 9)) < (0, 11):
    raise Exception("Incompatible Kaitai Struct Python API: 0.11 or later is required, but you have %s" % (kaitaistruct.__version__))

class SilentHillFileSystem(KaitaiStruct):
    def __init__(self, _io, _parent=None, _root=None):
        super(SilentHillFileSystem, self).__init__(_io)
        self._parent = _parent
        self._root = _root or self
        self._read()

    def _read(self):
        pass


    def _fetch_instances(self):
        pass

    class FsCdFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(SilentHillFileSystem.FsCdFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_bits_int_be(8)
            self.number = self._io.read_bits_int_be(24)
            self.name = self._io.read_u4le()
            self.lsn = self._io.read_s4le()
            self.size = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class FsFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(SilentHillFileSystem.FsFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pack = SilentHillFileSystem.ULong128(self._io, self, self._root)


        def _fetch_instances(self):
            self.pack._fetch_instances()
            _ = self.cd
            if hasattr(self, '_m_cd'):
                pass
                self._m_cd._fetch_instances()

            _ = self.check
            if hasattr(self, '_m_check'):
                pass
                self._m_check._fetch_instances()

            _ = self.hd
            if hasattr(self, '_m_hd'):
                pass
                self._m_hd._fetch_instances()

            _ = self.mgc
            if hasattr(self, '_m_mgc'):
                pass
                self._m_mgc._fetch_instances()

            _ = self.mgf
            if hasattr(self, '_m_mgf'):
                pass
                self._m_mgf._fetch_instances()

            _ = self.mgp
            if hasattr(self, '_m_mgp'):
                pass
                self._m_mgp._fetch_instances()


        @property
        def cd(self):
            if hasattr(self, '_m_cd'):
                return self._m_cd

            self._m_cd = SilentHillFileSystem.FsCdFile(self._io, self, self._root)
            return getattr(self, '_m_cd', None)

        @property
        def check(self):
            if hasattr(self, '_m_check'):
                return self._m_check

            self._m_check = SilentHillFileSystem.FsFileCheck(self._io, self, self._root)
            return getattr(self, '_m_check', None)

        @property
        def hd(self):
            if hasattr(self, '_m_hd'):
                return self._m_hd

            self._m_hd = SilentHillFileSystem.FsHdFile(self._io, self, self._root)
            return getattr(self, '_m_hd', None)

        @property
        def mgc(self):
            if hasattr(self, '_m_mgc'):
                return self._m_mgc

            self._m_mgc = SilentHillFileSystem.FsMgcFile(self._io, self, self._root)
            return getattr(self, '_m_mgc', None)

        @property
        def mgf(self):
            if hasattr(self, '_m_mgf'):
                return self._m_mgf

            self._m_mgf = SilentHillFileSystem.FsMgfFile(self._io, self, self._root)
            return getattr(self, '_m_mgf', None)

        @property
        def mgp(self):
            if hasattr(self, '_m_mgp'):
                return self._m_mgp

            self._m_mgp = SilentHillFileSystem.FsMgpFile(self._io, self, self._root)
            return getattr(self, '_m_mgp', None)


    class FsFileCheck(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(SilentHillFileSystem.FsFileCheck, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_bits_int_be(8)
            self.number = self._io.read_bits_int_be(24)
            self.pad0 = self._io.read_s4le()
            self.pad1 = self._io.read_s4le()
            self.pad2 = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class FsFileIndex(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(SilentHillFileSystem.FsFileIndex, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.index = SilentHillFileSystem.FsFileIndexIndex(self._io, self, self._root)


        def _fetch_instances(self):
            self.index._fetch_instances()
            _ = self.pack
            if hasattr(self, '_m_pack'):
                pass


        @property
        def pack(self):
            if hasattr(self, '_m_pack'):
                return self._m_pack

            self._m_pack = self._io.read_u8le()
            return getattr(self, '_m_pack', None)


    class FsFileIndexIndex(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(SilentHillFileSystem.FsFileIndexIndex, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.fp = self._io.read_u4le()
            self.name = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class FsHdFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(SilentHillFileSystem.FsHdFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_bits_int_be(8)
            self.padding = self._io.read_bits_int_be(24)
            self.name = self._io.read_u4le()
            self.offset = self._io.read_s4le()
            self.size = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class FsMgcFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(SilentHillFileSystem.FsMgcFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_bits_int_be(8)
            self.padding = self._io.read_bits_int_be(24)
            self.parent = self._io.read_u4le()
            self.start = self._io.read_u4le()
            self.end = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class FsMgfFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(SilentHillFileSystem.FsMgfFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_bits_int_be(8)
            self.padding = self._io.read_bits_int_be(24)
            self.parent = self._io.read_u4le()
            self.offset = self._io.read_s4le()
            self.size = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class FsMgpFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(SilentHillFileSystem.FsMgpFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_bits_int_be(8)
            self.padding = self._io.read_bits_int_be(24)
            self.file = self._io.read_u4le()
            self.start = self._io.read_u4le()
            self.end = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class ULong128(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(SilentHillFileSystem.ULong128, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.value = self._io.read_bytes(16)


        def _fetch_instances(self):
            pass
