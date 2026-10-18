# This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild
# type: ignore

import kaitaistruct
from kaitaistruct import KaitaiStruct, KaitaiStream, BytesIO


if getattr(kaitaistruct, 'API_VERSION', (0, 9)) < (0, 11):
    raise Exception("Incompatible Kaitai Struct Python API: 0.11 or later is required, but you have %s" % (kaitaistruct.__version__))

class Sh2(KaitaiStruct):
    def __init__(self, _io, _parent=None, _root=None):
        super(Sh2, self).__init__(_io)
        self._parent = _parent
        self._root = _root or self
        self._read()

    def _read(self):
        pass


    def _fetch_instances(self):
        pass

    class AnimeInfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.AnimeInfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.name = self._io.read_u2le()
            self.frame = self._io.read_u2le()
            self.speed = self._io.read_s2le()
            self.start = self._io.read_u2le()
            self.end = self._io.read_u2le()
            self.loop = self._io.read_u1()
            self.pad = self._io.read_s1()


        def _fetch_instances(self):
            pass


    class Anon12(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Anon12, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.status = self._io.read_s4le()
            self.ctrl = self._io.read_s4le()
            self.file = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.readrest = self._io.read_s4le()
            self.writerest = self._io.read_s4le()
            self.is_paused = self._io.read_s4le()
            self.is_started = self._io.read_s4le()
            self.proceed_zero_count = self._io.read_s2le()
            self._unnamed8 = self._io.read_bytes(2)
            self.cnt = self._io.read_s4le()
            self.st_frame = self._io.read_s4le()
            self.movieabort = self._io.read_s4le()
            self.framecnt = self._io.read_s4le()
            self.maskon = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.file._fetch_instances()


    class AudioDec(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.AudioDec, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.state = self._io.read_s4le()
            self.sshd = Sh2.SpuStreamHeader(self._io, self, self._root)
            self.ssbd = Sh2.SpuStreamBody(self._io, self, self._root)
            self.hdr_count = self._io.read_s4le()
            self.data = Sh2.Pointer(u"data", self._io, self, self._root)
            self.put = self._io.read_s4le()
            self.count = self._io.read_s4le()
            self.size = self._io.read_s4le()
            self.total_bytes = self._io.read_s4le()
            self.iop_buff = self._io.read_s4le()
            self.iop_buff_size = self._io.read_s4le()
            self.iop_last_pos = self._io.read_s4le()
            self.iop_pause_pos = self._io.read_s4le()
            self.total_bytes_sent = self._io.read_s4le()
            self.iop_zero = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.sshd._fetch_instances()
            self.ssbd._fetch_instances()
            self.data._fetch_instances()


    class Block(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Block, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.xz = self._io.read_s2le()
            self.block = self._io.read_s2le()


        def _fetch_instances(self):
            pass


    class CameraDat(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CameraDat, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pos = []
            for i in range(4):
                self.pos.append(self._io.read_f4le())

            self.zdir = []
            for i in range(4):
                self.zdir.append(self._io.read_f4le())

            self.ydir = []
            for i in range(4):
                self.ydir.append(self._io.read_f4le())

            self.rot = []
            for i in range(4):
                self.rot.append(self._io.read_f4le())

            self.clip_volume = []
            for i in range(4):
                self.clip_volume.append(self._io.read_f4le())

            self.world_view = []
            for i in range(16):
                self.world_view.append(self._io.read_f4le())

            self.view_screen = []
            for i in range(16):
                self.view_screen.append(self._io.read_f4le())

            self.view_clip = []
            for i in range(16):
                self.view_clip.append(self._io.read_f4le())

            self.world_screen = []
            for i in range(16):
                self.world_screen.append(self._io.read_f4le())

            self.world_clip = []
            for i in range(16):
                self.world_clip.append(self._io.read_f4le())

            self.clip_screen = []
            for i in range(16):
                self.clip_screen.append(self._io.read_f4le())

            self.camera_pam = []
            for i in range(4):
                self.camera_pam.append(self._io.read_f4le())

            self.screen_pam1 = []
            for i in range(4):
                self.screen_pam1.append(self._io.read_f4le())

            self.screen_pam2 = []
            for i in range(4):
                self.screen_pam2.append(self._io.read_f4le())

            self.rot_zdir = []
            for i in range(4):
                self.rot_zdir.append(self._io.read_f4le())

            self.rot_ydir = []
            for i in range(4):
                self.rot_ydir.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.pos)):
                pass

            for i in range(len(self.zdir)):
                pass

            for i in range(len(self.ydir)):
                pass

            for i in range(len(self.rot)):
                pass

            for i in range(len(self.clip_volume)):
                pass

            for i in range(len(self.world_view)):
                pass

            for i in range(len(self.view_screen)):
                pass

            for i in range(len(self.view_clip)):
                pass

            for i in range(len(self.world_screen)):
                pass

            for i in range(len(self.world_clip)):
                pass

            for i in range(len(self.clip_screen)):
                pass

            for i in range(len(self.camera_pam)):
                pass

            for i in range(len(self.screen_pam1)):
                pass

            for i in range(len(self.screen_pam2)):
                pass

            for i in range(len(self.rot_zdir)):
                pass

            for i in range(len(self.rot_ydir)):
                pass



    class ChangeList(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ChangeList, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.sd_se = self._io.read_s4le()
            self.sd_3d = self._io.read_s4le()
            self.file = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class CharaAdminRoomDistance(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CharaAdminRoomDistance, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.rm0 = self._io.read_s2le()
            self.rm1 = self._io.read_s2le()


        def _fetch_instances(self):
            pass


    class CharaBound(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CharaBound, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.chara_id = self._io.read_s4le()
            self.r = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class CharaDataDemoList(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CharaDataDemoList, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.kind = self._io.read_s4le()
            self.model = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.animation = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.shadow = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.cluster = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.model._fetch_instances()
            self.animation._fetch_instances()
            self.shadow._fetch_instances()
            self.cluster._fetch_instances()


    class CharaDataEntryList(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CharaDataEntryList, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.category = self._io.read_s4le()
            self.delete = self._io.read_s2le()
            self.kind = self._io.read_s2le()
            self.model = Sh2.CharaDataEntryListOne(self._io, self, self._root)
            self.animation = Sh2.CharaDataEntryListOne(self._io, self, self._root)
            self.shadow = Sh2.CharaDataEntryListOne(self._io, self, self._root)
            self.cluster = Sh2.CharaDataEntryListOne(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.model._fetch_instances()
            self.animation._fetch_instances()
            self.shadow._fetch_instances()
            self.cluster._fetch_instances()


    class CharaDataEntryListOne(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CharaDataEntryListOne, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.load = self._io.read_s4le()
            self.file = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.adress = Sh2.Pointer(u"data", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.file._fetch_instances()
            self.adress._fetch_instances()


    class CharaDataExtra(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CharaDataExtra, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.adress = Sh2.Pointer(u"data", self._io, self, self._root)
            self.size = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.adress._fetch_instances()


    class CharaDataItemFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CharaDataItemFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.kind = self._io.read_s4le()
            self.file = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.file._fetch_instances()


    class CharaDataMemAdmin(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CharaDataMemAdmin, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.category = self._io.read_s1()
            self.priority = self._io.read_s1()
            self.kind = self._io.read_s2le()
            self.model = Sh2.CharaDataMemAdminOne(self._io, self, self._root)
            self.animation = Sh2.CharaDataMemAdminOne(self._io, self, self._root)
            self.shadow = Sh2.CharaDataMemAdminOne(self._io, self, self._root)
            self.cluster = Sh2.CharaDataMemAdminOne(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.model._fetch_instances()
            self.animation._fetch_instances()
            self.shadow._fetch_instances()
            self.cluster._fetch_instances()


    class CharaDataMemAdminOne(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CharaDataMemAdminOne, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.file = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.adress = Sh2.Pointer(u"data", self._io, self, self._root)
            self.size = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.file._fetch_instances()
            self.adress._fetch_instances()


    class CharaDataStandardList(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CharaDataStandardList, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.kind = self._io.read_s4le()
            self.model = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.animation = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.shadow = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.model._fetch_instances()
            self.animation._fetch_instances()
            self.shadow._fetch_instances()


    class CharaDataWeaponFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CharaDataWeaponFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.equip = self._io.read_s2le()
            self.kind = self._io.read_s2le()
            self.james_anim = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.weapon_model = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.weapon_model_r = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.shadow_model = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.james_anim._fetch_instances()
            self.weapon_model._fetch_instances()
            self.weapon_model_r._fetch_instances()
            self.shadow_model._fetch_instances()


    class CharacterInfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CharacterInfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.spray_time = self._io.read_f4le()
            self.running_time = self._io.read_f4le()
            self.tired = self._io.read_s4le()
            self.tired_max = self._io.read_s4le()
            self.spirit = self._io.read_s4le()
            self.weapon = self._io.read_s4le()
            self.spray_set = self._io.read_u1()
            self._unnamed7 = self._io.read_bytes(7)
            self.ci_sc = []
            for i in range(32):
                self.ci_sc.append(Sh2.CiSubCharacter(self._io, self, self._root))

            self.total = self._io.read_s1()
            self._unnamed10 = self._io.read_bytes(15)


        def _fetch_instances(self):
            pass
            for i in range(len(self.ci_sc)):
                pass
                self.ci_sc[i]._fetch_instances()



    class ChizuConnectInfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ChizuConnectInfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.up = self._io.read_s1()
            self.down = self._io.read_s1()
            self.right = self._io.read_s1()
            self.left = self._io.read_s1()


        def _fetch_instances(self):
            pass


    class ChizuCurrentBlock(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ChizuCurrentBlock, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.chizu = self._io.read_s4le()
            self.cp_x = self._io.read_f4le()
            self.cp_y = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class ChizuMarkerList(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ChizuMarkerList, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.tex = Sh2.Pointer(u"chizu_marker_tex", self._io, self, self._root)
            self.data = Sh2.Pointer(u"data", self._io, self, self._root)
            self.head = self._io.read_s4le()
            self.tail = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.tex._fetch_instances()
            self.data._fetch_instances()


    class ChizuMarkerTex(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ChizuMarkerTex, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.u0 = self._io.read_s2le()
            self.v0 = self._io.read_s2le()
            self.u1 = self._io.read_s2le()
            self.v1 = self._io.read_s2le()


        def _fetch_instances(self):
            pass


    class CiSubCharacter(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CiSubCharacter, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.status = self._io.read_u4le()
            self.sub_status = self._io.read_u4le()
            self.sub_st = self._io.read_u4le()
            self.kind = self._io.read_s2le()
            self.id = self._io.read_s2le()
            self.pos = Sh2.Vector4(self._io, self, self._root)
            self.rot = Sh2.Vector4(self._io, self, self._root)
            self.pos_spd = Sh2.Vector4(self._io, self, self._root)
            self.ot_spd = Sh2.Vector4(self._io, self, self._root)
            self.b_pos = Sh2.Vector4(self._io, self, self._root)
            self.b_rot = Sh2.Vector4(self._io, self, self._root)
            self.en_first_status = self._io.read_s4le()
            self.eye_y = self._io.read_f4le()
            self.center_y = self._io.read_f4le()
            self.spd = self._io.read_f4le()
            self.spd_org = self._io.read_f4le()
            self.spd_y = self._io.read_f4le()
            self.spd_roty = self._io.read_f4le()
            self.battle_hp = self._io.read_f4le()
            self.battle_hp_max = self._io.read_f4le()
            self.battle_hp_rate = self._io.read_f4le()
            self.battle_status = self._io.read_u4le()
            self._unnamed22 = self._io.read_bytes(4)


        def _fetch_instances(self):
            pass
            self.pos._fetch_instances()
            self.rot._fetch_instances()
            self.pos_spd._fetch_instances()
            self.ot_spd._fetch_instances()
            self.b_pos._fetch_instances()
            self.b_rot._fetch_instances()


    class ClBattleQue(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClBattleQue, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.kind = self._io.read_u2le()
            self.btlid = self._io.read_u2le()
            self.sc = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self._unnamed3 = self._io.read_bytes(8)
            self.svs = []
            for i in range(4):
                self.svs.append(self._io.read_f4le())

            self.sve = []
            for i in range(4):
                self.sve.append(self._io.read_f4le())

            self.evs = []
            for i in range(4):
                self.evs.append(self._io.read_f4le())

            self.eve = []
            for i in range(4):
                self.eve.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            self.sc._fetch_instances()
            for i in range(len(self.svs)):
                pass

            for i in range(len(self.sve)):
                pass

            for i in range(len(self.evs)):
                pass

            for i in range(len(self.eve)):
                pass



    class ClBattleResult(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClBattleResult, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.enable = self._io.read_s4le()
            self.id = self._io.read_u4le()
            self.atr = self._io.read_s4le()
            self._unnamed3 = self._io.read_bytes(4)
            self.pos = []
            for i in range(4):
                self.pos.append(self._io.read_f4le())

            self.vec = []
            for i in range(4):
                self.vec.append(self._io.read_f4le())

            self.kind = self._io.read_u2le()
            self.btlid = self._io.read_u2le()
            self._raw_obj = self._io.read_bytes(4)
            _io__raw_obj = KaitaiStream(BytesIO(self._raw_obj))
            self.obj = Sh2.ClBattleResultAnon6(_io__raw_obj, self, self._root)
            self._unnamed9 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            for i in range(len(self.pos)):
                pass

            for i in range(len(self.vec)):
                pass

            self.obj._fetch_instances()


    class ClBattleResultAnon6(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClBattleResultAnon6, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._unnamed0 = self._io.read_bytes(4)


        def _fetch_instances(self):
            pass
            _ = self.cl
            if hasattr(self, '_m_cl'):
                pass
                self._m_cl._fetch_instances()

            _ = self.en
            if hasattr(self, '_m_en'):
                pass
                self._m_en._fetch_instances()

            _ = self.pl
            if hasattr(self, '_m_pl'):
                pass
                self._m_pl._fetch_instances()


        @property
        def cl(self):
            if hasattr(self, '_m_cl'):
                return self._m_cl

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_cl = Sh2.Pointer(u"cl_hitpoly_column", self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_cl', None)

        @property
        def en(self):
            if hasattr(self, '_m_en'):
                return self._m_en

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_en = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_en', None)

        @property
        def pl(self):
            if hasattr(self, '_m_pl'):
                return self._m_pl

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_pl = Sh2.Pointer(u"cl_hitpoly_plane", self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_pl', None)


    class ClCharaList(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClCharaList, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.col = Sh2.ClHitpolyColumn(self._io, self, self._root)
            self.wcol = Sh2.ClHitpolyColumn(self._io, self, self._root)
            self.sc = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self._unnamed3 = self._io.read_bytes(12)
            self.opos = []
            for i in range(4):
                self.opos.append(self._io.read_f4le())

            self.pos = []
            for i in range(4):
                self.pos.append(self._io.read_f4le())

            self.mvec = []
            for i in range(4):
                self.mvec.append(self._io.read_f4le())

            self.wallcv = []
            for i in range(4):
                self.wallcv.append(self._io.read_f4le())

            self.mang = self._io.read_f4le()
            self.wflg = self._io.read_s4le()
            self._unnamed10 = self._io.read_bytes(8)
            self.ccvec = []
            for i in range(4):
                self.ccvec.append(self._io.read_f4le())

            self.movflg = self._io.read_s2le()
            self.batflg = self._io.read_s2le()
            self.heightfunc = Sh2.Pointer(u"data", self._io, self, self._root)
            self._unnamed15 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            self.col._fetch_instances()
            self.wcol._fetch_instances()
            self.sc._fetch_instances()
            for i in range(len(self.opos)):
                pass

            for i in range(len(self.pos)):
                pass

            for i in range(len(self.mvec)):
                pass

            for i in range(len(self.wallcv)):
                pass

            for i in range(len(self.ccvec)):
                pass

            self.heightfunc._fetch_instances()


    class ClCldheader(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClCldheader, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.sx = self._io.read_f4le()
            self.sz = self._io.read_f4le()
            self.b0size = self._io.read_s4le()
            self.b1size = self._io.read_s4le()
            self.b2size = self._io.read_s4le()
            self.b3size = self._io.read_s4le()
            self.csize = self._io.read_s4le()
            self.disable = self._io.read_s4le()
            self.b0ofs = []
            for i in range(16):
                self.b0ofs.append(self._io.read_s4le())

            self.b1ofs = []
            for i in range(16):
                self.b1ofs.append(self._io.read_s4le())

            self.b2ofs = []
            for i in range(16):
                self.b2ofs.append(self._io.read_s4le())

            self.b3ofs = []
            for i in range(16):
                self.b3ofs.append(self._io.read_s4le())

            self.clofs = []
            for i in range(16):
                self.clofs.append(self._io.read_s4le())

            self.fldofs = self._io.read_u4le()
            self.wldofs = self._io.read_u4le()
            self.cedofs = self._io.read_u4le()
            self.swdofs = self._io.read_u4le()
            self.cldofs = self._io.read_u4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.b0ofs)):
                pass

            for i in range(len(self.b1ofs)):
                pass

            for i in range(len(self.b2ofs)):
                pass

            for i in range(len(self.b3ofs)):
                pass

            for i in range(len(self.clofs)):
                pass



    class ClDynamicfloorList(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClDynamicfloorList, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.use = self._io.read_s4le()
            self.dw = []
            for i in range(16):
                self.dw.append(Sh2.Pointer(u"cl_hitpoly_plane", self._io, self, self._root))



        def _fetch_instances(self):
            pass
            for i in range(len(self.dw)):
                pass
                self.dw[i]._fetch_instances()



    class ClDynamicwallList(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClDynamicwallList, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.use = self._io.read_s4le()
            self.dw = []
            for i in range(32):
                self.dw.append(Sh2.Pointer(u"cl_hitpoly_plane", self._io, self, self._root))



        def _fetch_instances(self):
            pass
            for i in range(len(self.dw)):
                pass
                self.dw[i]._fetch_instances()



    class ClHitpolyColumn(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClHitpolyColumn, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.kind = self._io.read_u1()
            self.shape = self._io.read_u1()
            self.pad = self._io.read_u2le()
            self.weight = self._io.read_u4le()
            self.material = self._io.read_u4le()
            self.flg = self._io.read_s4le()
            self.p = []
            for i in range(8):
                self.p.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.p)):
                pass



    class ClHitpolyHead(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClHitpolyHead, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.kind = self._io.read_u1()
            self.shape = self._io.read_u1()
            self.pad = self._io.read_u2le()
            self.weight = self._io.read_u4le()
            self.material = self._io.read_u4le()
            self.flg = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class ClHitpolyPlane(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClHitpolyPlane, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.kind = self._io.read_u1()
            self.shape = self._io.read_u1()
            self.pad = self._io.read_u2le()
            self.weight = self._io.read_u4le()
            self.material = self._io.read_u4le()
            self.flg = self._io.read_s4le()
            self.p = []
            for i in range(16):
                self.p.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.p)):
                pass



    class ClHitresult(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClHitresult, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.chk = self._io.read_s4le()
            self._unnamed1 = self._io.read_bytes(12)
            self.cp = []
            for i in range(4):
                self.cp.append(self._io.read_f4le())

            self.cv = []
            for i in range(4):
                self.cv.append(self._io.read_f4le())

            self.pd = Sh2.Pointer(u"cl_hitpoly_head", self._io, self, self._root)
            self._unnamed5 = self._io.read_bytes(12)


        def _fetch_instances(self):
            pass
            for i in range(len(self.cp)):
                pass

            for i in range(len(self.cv)):
                pass

            self.pd._fetch_instances()


    class ClSelectMap(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClSelectMap, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.base = Sh2.Pointer(u"data", self._io, self, self._root)
            self.sect = self._io.read_u1()
            self._unnamed2 = self._io.read_bytes(3)


        def _fetch_instances(self):
            pass
            self.base._fetch_instances()


    class ClVhitChara(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClVhitChara, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.sc = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self._unnamed1 = self._io.read_bytes(12)
            self.cp = []
            for i in range(4):
                self.cp.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            self.sc._fetch_instances()
            for i in range(len(self.cp)):
                pass



    class ClVhitResult(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClVhitResult, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.kind = self._io.read_s4le()
            self._unnamed1 = self._io.read_bytes(12)
            self._raw_hobj = self._io.read_bytes(48)
            _io__raw_hobj = KaitaiStream(BytesIO(self._raw_hobj))
            self.hobj = Sh2.ClVhitResultAnon1(_io__raw_hobj, self, self._root)


        def _fetch_instances(self):
            pass
            self.hobj._fetch_instances()


    class ClVhitResultAnon1(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClVhitResultAnon1, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._unnamed0 = self._io.read_bytes(48)


        def _fetch_instances(self):
            pass
            _ = self.chara
            if hasattr(self, '_m_chara'):
                pass
                self._m_chara._fetch_instances()

            _ = self.wall
            if hasattr(self, '_m_wall'):
                pass
                self._m_wall._fetch_instances()


        @property
        def chara(self):
            if hasattr(self, '_m_chara'):
                return self._m_chara

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_chara = Sh2.ClVhitChara(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_chara', None)

        @property
        def wall(self):
            if hasattr(self, '_m_wall'):
                return self._m_wall

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_wall = Sh2.ClVhitWall(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_wall', None)


    class ClVhitWall(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClVhitWall, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.cp = []
            for i in range(4):
                self.cp.append(self._io.read_f4le())

            self.nl = []
            for i in range(4):
                self.nl.append(self._io.read_f4le())

            self.pd = Sh2.Pointer(u"cl_hitpoly_head", self._io, self, self._root)
            self._unnamed3 = self._io.read_bytes(12)


        def _fetch_instances(self):
            pass
            for i in range(len(self.cp)):
                pass

            for i in range(len(self.nl)):
                pass

            self.pd._fetch_instances()


    class ClWallhitdat(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClWallhitdat, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.kind = self._io.read_s4le()
            self._unnamed1 = self._io.read_bytes(12)
            self.cv = []
            for i in range(4):
                self.cv.append(self._io.read_f4le())

            self.pl = Sh2.Pointer(u"cl_hitpoly_plane", self._io, self, self._root)
            self._unnamed4 = self._io.read_bytes(12)
            self.normal = []
            for i in range(4):
                self.normal.append(self._io.read_f4le())

            self.nang = self._io.read_f4le()
            self._unnamed7 = self._io.read_bytes(12)


        def _fetch_instances(self):
            pass
            for i in range(len(self.cv)):
                pass

            self.pl._fetch_instances()
            for i in range(len(self.normal)):
                pass



    class Cluster1(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Cluster1, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.n_keys = self._io.read_u2le()
            self.elements = []
            i = 0
            while not self._io.is_eof():
                self.elements.append(Sh2.Element1(self._io, self, self._root))
                i += 1



        def _fetch_instances(self):
            pass
            for i in range(len(self.elements)):
                pass
                self.elements[i]._fetch_instances()



    class ClusterAnimeWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ClusterAnimeWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.ca = []
            for i in range(32):
                self.ca.append(Sh2.ShClusterAnime(self._io, self, self._root))



        def _fetch_instances(self):
            pass
            for i in range(len(self.ca)):
                pass
                self.ca[i]._fetch_instances()



    class CscVu1(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.CscVu1, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.micro = []
            for i in range(6):
                self.micro.append(Sh2.Pointer(u"data", self._io, self, self._root))



        def _fetch_instances(self):
            pass
            for i in range(len(self.micro)):
                pass
                self.micro[i]._fetch_instances()



    class DdsFrame(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.DdsFrame, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.frame = self._io.read_f4le()
            self._unnamed1 = self._io.read_bytes(12)
            self.camera = Sh2.DdsFrameAnon9(self._io, self, self._root)
            self.light = []
            for i in range(6):
                self.light.append(Sh2.DdsFrameAnon10(self._io, self, self._root))

            self.character = []
            for i in range(7):
                self.character.append(Sh2.DdsFrameAnon11(self._io, self, self._root))



        def _fetch_instances(self):
            pass
            self.camera._fetch_instances()
            for i in range(len(self.light)):
                pass
                self.light[i]._fetch_instances()

            for i in range(len(self.character)):
                pass
                self.character[i]._fetch_instances()



    class DdsFrameAnon10(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.DdsFrameAnon10, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.position = []
            for i in range(4):
                self.position.append(self._io.read_f4le())

            self.interest = []
            for i in range(4):
                self.interest.append(self._io.read_f4le())

            self.roll = self._io.read_f4le()
            self._unnamed3 = self._io.read_bytes(12)
            self.color = []
            for i in range(4):
                self.color.append(self._io.read_f4le())

            self.falloff = []
            for i in range(2):
                self.falloff.append(self._io.read_f4le())

            self.cone = []
            for i in range(2):
                self.cone.append(self._io.read_f4le())

            self.visible = self._io.read_s4le()
            self._unnamed8 = self._io.read_bytes(12)


        def _fetch_instances(self):
            pass
            for i in range(len(self.position)):
                pass

            for i in range(len(self.interest)):
                pass

            for i in range(len(self.color)):
                pass

            for i in range(len(self.falloff)):
                pass

            for i in range(len(self.cone)):
                pass



    class DdsFrameAnon11(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.DdsFrameAnon11, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.position = []
            for i in range(4):
                self.position.append(self._io.read_f4le())

            self.visible = self._io.read_s4le()
            self._unnamed2 = self._io.read_bytes(12)


        def _fetch_instances(self):
            pass
            for i in range(len(self.position)):
                pass



    class DdsFrameAnon9(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.DdsFrameAnon9, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.position = []
            for i in range(4):
                self.position.append(self._io.read_f4le())

            self.interest = []
            for i in range(4):
                self.interest.append(self._io.read_f4le())

            self.roll = self._io.read_f4le()
            self.plane = self._io.read_f4le()
            self._unnamed4 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            for i in range(len(self.position)):
                pass

            for i in range(len(self.interest)):
                pass



    class DebugPrintInfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.DebugPrintInfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.xofs = self._io.read_s4le()
            self.yofs = self._io.read_s4le()
            self.x = self._io.read_s4le()
            self.y = self._io.read_s4le()
            self.w = self._io.read_s4le()
            self.h = self._io.read_s4le()
            self.tab = self._io.read_s4le()
            self.xofs_r = self._io.read_s4le()
            self.yofs_r = self._io.read_s4le()
            self.y_r = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class DramaDemoAnimInfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.DramaDemoAnimInfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.name = []
            for i in range(32):
                self.name.append(self._io.read_s1())

            self.kind = self._io.read_s2le()
            self.id = self._io.read_s2le()
            self.start = self._io.read_s2le()
            self.end = self._io.read_s2le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.name)):
                pass



    class DramaDemoMessageTime(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.DramaDemoMessageTime, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.start = self._io.read_u2le()
            self.end = self._io.read_u2le()


        def _fetch_instances(self):
            pass


    class DramaDemoPlayInfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.DramaDemoPlayInfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.demo_no = self._io.read_s4le()
            self.adr_dds_top = Sh2.Pointer(u"data", self._io, self, self._root)
            self.adr_anim = Sh2.Pointer(u"data", self._io, self, self._root)
            self.adr_msg_time = Sh2.Pointer(u"drama_demo_message_time", self._io, self, self._root)
            self.msg_start = self._io.read_s2le()
            self.voice_sd_no = self._io.read_s2le()
            self.adr_voice = Sh2.Pointer(u"data", self._io, self, self._root)
            self.stream_no = self._io.read_s4le()
            self.stream_start = self._io.read_f4le()
            self.add_pos_x = self._io.read_f4le()
            self.add_pos_z = self._io.read_f4le()


        def _fetch_instances(self):
            pass
            self.adr_dds_top._fetch_instances()
            self.adr_anim._fetch_instances()
            self.adr_msg_time._fetch_instances()
            self.adr_voice._fetch_instances()


    class Element1(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Element1, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.frame = self._io.read_u2le()
            self.weight = self._io.read_s2le()


        def _fetch_instances(self):
            pass


    class EnAmbushData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnAmbushData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pl_x_min = self._io.read_f4le()
            self.pl_z_min = self._io.read_f4le()
            self.pl_x_max = self._io.read_f4le()
            self.pl_z_max = self._io.read_f4le()
            self.pos_x = self._io.read_f4le()
            self.pos_z = self._io.read_f4le()
            self.dir = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class EnAnimeData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnAnimeData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.anime = self._io.read_u2le()
            self.loop = self._io.read_u1()
            self._unnamed2 = self._io.read_bytes(1)


        def _fetch_instances(self):
            pass


    class EnArmData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnArmData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.hand_pos = []
            for i in range(4):
                self.hand_pos.append(self._io.read_f4le())

            self.old_pos = []
            for i in range(4):
                self.old_pos.append(self._io.read_f4le())

            self.near_count = self._io.read_s4le()
            self.dist = self._io.read_f4le()
            self.arm = self._io.read_s1()
            self.attack = self._io.read_s1()
            self.scount = self._io.read_s1()
            self.signs = self._io.read_s1()
            self.count = self._io.read_s1()
            self.dir = self._io.read_s1()
            self._unnamed10 = self._io.read_bytes(2)


        def _fetch_instances(self):
            pass
            for i in range(len(self.hand_pos)):
                pass

            for i in range(len(self.old_pos)):
                pass



    class EnBosData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnBosData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.target = []
            for i in range(4):
                self.target.append(self._io.read_f4le())

            self.insect_dp = Sh2.Pointer(u"data", self._io, self, self._root)
            self.near_count = self._io.read_s4le()
            self.dist = self._io.read_f4le()
            self.move_speed = self._io.read_f4le()
            self.rot_speed = self._io.read_f4le()
            self.rot_add = self._io.read_f4le()
            self.y_speed = self._io.read_f4le()
            self.mode = self._io.read_s4le()
            self.end_count = self._io.read_s4le()
            self.signs = self._io.read_s1()
            self.count = self._io.read_s1()
            self._unnamed12 = self._io.read_bytes(2)


        def _fetch_instances(self):
            pass
            for i in range(len(self.target)):
                pass

            self.insect_dp._fetch_instances()


    class EnCommunication(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnCommunication, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pos = []
            for i in range(4):
                self.pos.append(self._io.read_f4le())

            self.kind = self._io.read_s4le()
            self.type = self._io.read_s4le()
            self.time = self._io.read_s4le()
            self.dist = self._io.read_f4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.pos)):
                pass



    class EnEdbData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnEdbData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.target = []
            for i in range(4):
                self.target.append(self._io.read_f4le())

            self.rot = self._io.read_f4le()
            self.arot = self._io.read_f4le()
            self.speed = self._io.read_f4le()
            self.bullet = self._io.read_s1()
            self.mark = []
            for i in range(3):
                self.mark.append(self._io.read_s1())

            self.mark_n = self._io.read_s1()
            self.turn = self._io.read_s1()
            self.afford = self._io.read_s1()
            self.ccount = self._io.read_s1()
            self.pcount = self._io.read_s1()
            self._unnamed11 = self._io.read_bytes(3)


        def _fetch_instances(self):
            pass
            for i in range(len(self.target)):
                pass

            for i in range(len(self.mark)):
                pass



    class EnForbiddenarea(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnForbiddenarea, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x0 = self._io.read_f4le()
            self.z0 = self._io.read_f4le()
            self.x1 = self._io.read_f4le()
            self.z1 = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class EnIkeData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnIkeData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.handpos = []
            for i in range(4):
                self.handpos.append(self._io.read_f4le())

            self.swing = self._io.read_f4le()
            self.near_count = self._io.read_s4le()
            self.dist = self._io.read_f4le()
            self.direc = self._io.read_s1()
            self.signs = self._io.read_s1()
            self.count = self._io.read_s1()
            self.pipe_count = self._io.read_s1()


        def _fetch_instances(self):
            pass
            for i in range(len(self.handpos)):
                pass



    class EnInsData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnInsData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.view_rot = []
            for i in range(4):
                self.view_rot.append(self._io.read_f4le())

            self.rot_add = []
            for i in range(4):
                self.rot_add.append(self._io.read_f4le())

            self.leader = Sh2.Pointer(u"data", self._io, self, self._root)
            self.def_speed = self._io.read_f4le()
            self.move_speed = self._io.read_f4le()
            self.speed_add = self._io.read_f4le()
            self.rot_speed = self._io.read_f4le()
            self.y_speed = self._io.read_f4le()
            self.twin_dist = self._io.read_f4le()
            self.dist_add = self._io.read_f4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.view_rot)):
                pass

            for i in range(len(self.rot_add)):
                pass

            self.leader._fetch_instances()


    class EnLocalData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnLocalData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.kind = self._io.read_s1()
            self.kind2 = self._io.read_s1()
            self.mlv = self._io.read_s1()
            self.slv = self._io.read_s1()
            self.sslv = self._io.read_s1()
            self.type = self._io.read_s1()
            self.weight = self._io.read_u1()
            self.lie = self._io.read_s1()
            self.d_count = self._io.read_s1()
            self.last_atk = self._io.read_s1()
            self.anim = self._io.read_s1()
            self.anim_loop = self._io.read_u1()
            self.anim_s = self._io.read_s2le()
            self._unnamed13 = self._io.read_bytes(2)
            self.flag = self._io.read_u4le()
            self.anim_n = self._io.read_s4le()
            self.anim_step = self._io.read_s4le()
            self.scp = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.path = Sh2.EnPathData(self._io, self, self._root)
            self.vec = []
            for i in range(4):
                self.vec.append(self._io.read_f4le())

            self.endurance = self._io.read_f4le()
            self.endurance_max = self._io.read_f4le()
            self.hb_x = self._io.read_f4le()
            self.hb_z = self._io.read_f4le()
            self.hb_s = self._io.read_f4le()
            self.tx = self._io.read_f4le()
            self.tz = self._io.read_f4le()
            self.tx2 = self._io.read_f4le()
            self.tz2 = self._io.read_f4le()
            self.trx = self._io.read_f4le()
            self.trz = self._io.read_f4le()
            self.size = self._io.read_f4le()
            self.new_size = self._io.read_f4le()
            self.tall = self._io.read_f4le()
            self.new_tall = self._io.read_f4le()
            self.center_y = self._io.read_f4le()
            self.new_center = self._io.read_f4le()
            self.eye_y = self._io.read_f4le()
            self.new_eye = self._io.read_f4le()
            self.p_dist = self._io.read_f4le()
            self.radio = self._io.read_f4le()
            self.timer = self._io.read_s4le()
            self.sound_wait = self._io.read_s4le()
            self.randseed = self._io.read_s4le()
            self._raw__unnamed44 = self._io.read_bytes(64)
            _io__raw__unnamed44 = KaitaiStream(BytesIO(self._raw__unnamed44))
            self._unnamed44 = Sh2.EnLocalDataAnon2(_io__raw__unnamed44, self, self._root)


        def _fetch_instances(self):
            pass
            self.scp._fetch_instances()
            self.path._fetch_instances()
            for i in range(len(self.vec)):
                pass

            self._unnamed44._fetch_instances()


    class EnLocalDataAnon2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnLocalDataAnon2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._unnamed0 = self._io.read_bytes(64)


        def _fetch_instances(self):
            pass
            _ = self.arm
            if hasattr(self, '_m_arm'):
                pass
                self._m_arm._fetch_instances()

            _ = self.bos
            if hasattr(self, '_m_bos'):
                pass
                self._m_bos._fetch_instances()

            _ = self.edb
            if hasattr(self, '_m_edb'):
                pass
                self._m_edb._fetch_instances()

            _ = self.ike
            if hasattr(self, '_m_ike'):
                pass
                self._m_ike._fetch_instances()

            _ = self.ins
            if hasattr(self, '_m_ins'):
                pass
                self._m_ins._fetch_instances()

            _ = self.mkn
            if hasattr(self, '_m_mkn'):
                pass
                self._m_mkn._fetch_instances()

            _ = self.nik
            if hasattr(self, '_m_nik'):
                pass
                self._m_nik._fetch_instances()

            _ = self.nse
            if hasattr(self, '_m_nse'):
                pass
                self._m_nse._fetch_instances()

            _ = self.oni
            if hasattr(self, '_m_oni'):
                pass
                self._m_oni._fetch_instances()

            _ = self.pap
            if hasattr(self, '_m_pap'):
                pass
                self._m_pap._fetch_instances()

            _ = self.red
            if hasattr(self, '_m_red'):
                pass
                self._m_red._fetch_instances()

            _ = self.scu
            if hasattr(self, '_m_scu'):
                pass
                self._m_scu._fetch_instances()

            _ = self.tyu
            if hasattr(self, '_m_tyu'):
                pass
                self._m_tyu._fetch_instances()


        @property
        def arm(self):
            if hasattr(self, '_m_arm'):
                return self._m_arm

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_arm = Sh2.EnArmData(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_arm', None)

        @property
        def bos(self):
            if hasattr(self, '_m_bos'):
                return self._m_bos

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_bos = Sh2.EnBosData(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_bos', None)

        @property
        def edb(self):
            if hasattr(self, '_m_edb'):
                return self._m_edb

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_edb = Sh2.EnEdbData(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_edb', None)

        @property
        def ike(self):
            if hasattr(self, '_m_ike'):
                return self._m_ike

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_ike = Sh2.EnIkeData(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_ike', None)

        @property
        def ins(self):
            if hasattr(self, '_m_ins'):
                return self._m_ins

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_ins = Sh2.EnInsData(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_ins', None)

        @property
        def mkn(self):
            if hasattr(self, '_m_mkn'):
                return self._m_mkn

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_mkn = Sh2.EnMknData(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_mkn', None)

        @property
        def nik(self):
            if hasattr(self, '_m_nik'):
                return self._m_nik

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_nik = Sh2.EnNikData(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_nik', None)

        @property
        def nse(self):
            if hasattr(self, '_m_nse'):
                return self._m_nse

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_nse = Sh2.EnNseData(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_nse', None)

        @property
        def oni(self):
            if hasattr(self, '_m_oni'):
                return self._m_oni

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_oni = Sh2.EnOniData(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_oni', None)

        @property
        def pap(self):
            if hasattr(self, '_m_pap'):
                return self._m_pap

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_pap = Sh2.EnPapData(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_pap', None)

        @property
        def red(self):
            if hasattr(self, '_m_red'):
                return self._m_red

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_red = Sh2.EnRedData(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_red', None)

        @property
        def scu(self):
            if hasattr(self, '_m_scu'):
                return self._m_scu

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_scu = Sh2.EnScuData(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_scu', None)

        @property
        def tyu(self):
            if hasattr(self, '_m_tyu'):
                return self._m_tyu

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_tyu = Sh2.EnTyuData(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_tyu', None)


    class EnLocalWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnLocalWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.data = []
            for i in range(32):
                self.data.append(Sh2.EnLocalData(self._io, self, self._root))

            self.communication = []
            for i in range(8):
                self.communication.append(Sh2.EnCommunication(self._io, self, self._root))

            self.forbidden_area = []
            for i in range(2):
                self.forbidden_area.append(Sh2.EnForbiddenarea(self._io, self, self._root))

            self.sound_queue = []
            for i in range(8):
                self.sound_queue.append(Sh2.EnSoundQueue(self._io, self, self._root))

            self.communication_num = self._io.read_s4le()
            self.forbidden_num = self._io.read_s4le()
            self.sound_queue_num = self._io.read_s4le()
            self.status = self._io.read_u4le()
            self.this = Sh2.Pointer(u"en_local_data", self._io, self, self._root)
            self._unnamed9 = self._io.read_bytes(12)
            self.hit_result = Sh2.ClVhitResult(self._io, self, self._root)
            self.max3d_sounds = self._io.read_s4le()
            self.active_enemy = self._io.read_s4le()
            self._unnamed13 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            for i in range(len(self.data)):
                pass
                self.data[i]._fetch_instances()

            for i in range(len(self.communication)):
                pass
                self.communication[i]._fetch_instances()

            for i in range(len(self.forbidden_area)):
                pass
                self.forbidden_area[i]._fetch_instances()

            for i in range(len(self.sound_queue)):
                pass
                self.sound_queue[i]._fetch_instances()

            self.this._fetch_instances()
            self.hit_result._fetch_instances()


    class EnMknData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnMknData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.stpos = []
            for i in range(4):
                self.stpos.append(self._io.read_f4le())

            self.target = []
            for i in range(4):
                self.target.append(self._io.read_f4le())

            self.tp = Sh2.Pointer(u"data", self._io, self, self._root)
            self.fall = self._io.read_f4le()
            self.frame = self._io.read_s2le()
            self.dc = self._io.read_s1()
            self.dcm = self._io.read_s1()


        def _fetch_instances(self):
            pass
            for i in range(len(self.stpos)):
                pass

            for i in range(len(self.target)):
                pass

            self.tp._fetch_instances()


    class EnNikData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnNikData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.swing = []
            for i in range(4):
                self.swing.append(self._io.read_f4le())

            self.acc = []
            for i in range(4):
                self.acc.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.swing)):
                pass

            for i in range(len(self.acc)):
                pass



    class EnNseData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnNseData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.speed = self._io.read_f4le()
            self.tspeed = self._io.read_f4le()
            self.signs = self._io.read_s1()
            self.count = self._io.read_s1()
            self.dc = self._io.read_s1()
            self.dcm = self._io.read_s1()


        def _fetch_instances(self):
            pass


    class EnOniData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnOniData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.id = self._io.read_s1()
            self.check = self._io.read_s1()
            self.warp = self._io.read_s1()
            self._unnamed3 = self._io.read_bytes(1)
            self.timer2 = self._io.read_s2le()
            self._unnamed5 = self._io.read_bytes(2)
            self.other = Sh2.Pointer(u"data", self._io, self, self._root)
            self.tp = Sh2.Pointer(u"data", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.other._fetch_instances()
            self.tp._fetch_instances()


    class EnPapData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnPapData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.target = []
            for i in range(4):
                self.target.append(self._io.read_f4le())

            self.dc = self._io.read_s1()
            self.dcm = self._io.read_s1()
            self.signs = self._io.read_s1()
            self.count = self._io.read_s1()


        def _fetch_instances(self):
            pass
            for i in range(len(self.target)):
                pass



    class EnPathData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnPathData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.angle = self._io.read_f4le()
            self.markangle = self._io.read_f4le()
            self.dist = self._io.read_f4le()
            self.step = self._io.read_s1()
            self.deadend = self._io.read_s1()
            self.timer = self._io.read_s2le()


        def _fetch_instances(self):
            pass


    class EnRedData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnRedData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.attack_count = self._io.read_s4le()
            self.boss_timer = self._io.read_s4le()
            self.tp = Sh2.Pointer(u"data", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.tp._fetch_instances()


    class EnScuData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnScuData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.stpos = []
            for i in range(4):
                self.stpos.append(self._io.read_f4le())

            self.target = []
            for i in range(4):
                self.target.append(self._io.read_f4le())

            self.ambush = Sh2.Pointer(u"en_ambush_data", self._io, self, self._root)
            self.count = self._io.read_s4le()
            self.dc = self._io.read_s1()
            self.dcm = self._io.read_s1()
            self._unnamed6 = self._io.read_bytes(2)


        def _fetch_instances(self):
            pass
            for i in range(len(self.stpos)):
                pass

            for i in range(len(self.target)):
                pass

            self.ambush._fetch_instances()


    class EnSoundQueue(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnSoundQueue, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.scp = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.num = self._io.read_s4le()
            self.vol = self._io.read_f4le()
            self.time = self._io.read_f4le()


        def _fetch_instances(self):
            pass
            self.scp._fetch_instances()


    class EnTyuData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnTyuData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.point = []
            for i in range(4):
                self.point.append(self._io.read_f4le())

            self.tcomm = Sh2.Pointer(u"en_communication", self._io, self, self._root)
            self.near_count = self._io.read_s4le()
            self.dist = self._io.read_f4le()
            self.count = self._io.read_s2le()
            self.moves = self._io.read_s1()
            self._unnamed6 = self._io.read_bytes(1)


        def _fetch_instances(self):
            pass
            for i in range(len(self.point)):
                pass

            self.tcomm._fetch_instances()


    class EnemyList(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EnemyList, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.kind = self._io.read_s2le()
            self.id = self._io.read_s2le()
            self.pos_x = self._io.read_s4le()
            self.pos_z = self._io.read_s4le()
            self.pos_y = self._io.read_s2le()
            self.rot_y = self._io.read_s2le()
            self.status = self._io.read_s2le()
            self.condition = self._io.read_u2le()


        def _fetch_instances(self):
            pass


    class EventDoorSound(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EventDoorSound, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.open = self._io.read_s2le()
            self.close = self._io.read_s2le()
            self.unlock = self._io.read_s2le()
            self.jam = self._io.read_s2le()
            self.lock = self._io.read_s2le()
            self.pad = self._io.read_s2le()


        def _fetch_instances(self):
            pass


    class EventList(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.EventList, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.flag = self._io.read_s4le()
            self.cond = self._io.read_s4le()
            self.rslt0 = self._io.read_s4le()
            self.rslt1 = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class FilesBgBlock(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FilesBgBlock, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.map = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.cld = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.cam = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.kg2 = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.tex = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.ex0 = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.ex1 = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)
            self.ex2 = Sh2.Pointer(u"fs_file_index", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.map._fetch_instances()
            self.cld._fetch_instances()
            self.cam._fetch_instances()
            self.kg2._fetch_instances()
            self.tex._fetch_instances()
            self.ex0._fetch_instances()
            self.ex1._fetch_instances()
            self.ex2._fetch_instances()


    class FilterParams(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FilterParams, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.base_ix = self._io.read_s2le()
            self.base_iy = self._io.read_s2le()
            self.fo_timer = self._io.read_s2le()
            self.max_timer = self._io.read_s2le()
            self.target_sec = self._io.read_s1()
            self.fio_ratio = self._io.read_s1()
            self.blur_mode = self._io.read_s1()
            self.blur_ratio = self._io.read_s1()
            self.lesser_a = self._io.read_s1()
            self.greater_a = self._io.read_s1()
            self.sw_flg = self._io.read_s1()
            self.dp_flg = self._io.read_s1()
            self.soft_iter = self._io.read_u1()
            self.soft_cit = self._io.read_u1()
            self.soft_aref = self._io.read_u1()
            self.soft_mode = self._io.read_s1()
            self.soft_shift = self._io.read_s1()
            self.trim_alpha = self._io.read_s1()
            self.tex_trim_ex = self._io.read_s2le()
            self.tex_trim_ey = self._io.read_s2le()
            self.tex_trim_sx = self._io.read_s2le()
            self.tex_trim_sy = self._io.read_s2le()
            self._unnamed22 = self._io.read_bytes(2)
            self.dof_z_depth = self._io.read_s4le()
            self.key_alpha = self._io.read_u1()
            self.testkind = self._io.read_u1()
            self.s1_iter = self._io.read_u1()
            self.s1_alpha = self._io.read_u1()
            self.s1_shift = self._io.read_s1()
            self.s1_base_ix = self._io.read_s1()
            self.s2_iter = self._io.read_u1()
            self.s2_alpha = self._io.read_u1()
            self.s2_shift = self._io.read_s1()
            self.s2_base_ix = self._io.read_s1()
            self._unnamed34 = self._io.read_bytes(2)


        def _fetch_instances(self):
            pass


    class FilterWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FilterWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.gs_filter_kind = self._io.read_s4le()
            self.flg = self._io.read_s4le()
            self.kind_history = self._io.read_s4le()
            self.mode = self._io.read_s4le()
            self.filter_data = []
            for i in range(8):
                self.filter_data.append(Sh2.QWorddata(self._io, self, self._root))

            self._raw_copy_filter_color = self._io.read_bytes(16)
            _io__raw_copy_filter_color = KaitaiStream(BytesIO(self._raw_copy_filter_color))
            self.copy_filter_color = Sh2.QWorddata(_io__raw_copy_filter_color, self, self._root)


        def _fetch_instances(self):
            pass
            for i in range(len(self.filter_data)):
                pass
                self.filter_data[i]._fetch_instances()

            self.copy_filter_color._fetch_instances()


    class FogAsmData1(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FogAsmData1, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.part_size = self._io.read_f4le()
            self.wall_range = self._io.read_f4le()
            self.rev_rate = self._io.read_f4le()
            self.part_m_rate = self._io.read_f4le()
            self.escape_range = self._io.read_f4le()
            self.r_escape_range = self._io.read_f4le()
            self.alpha_max = self._io.read_f4le()
            self.pad1 = self._io.read_f4le()
            self.minus_alpha = self._io.read_f4le()
            self.rand_rate1 = self._io.read_f4le()
            self.rand_rate2 = self._io.read_f4le()
            self.rand_rate3 = self._io.read_f4le()
            self.fadepos = self._io.read_f4le()
            self.r_fadepos = self._io.read_f4le()
            self.pad2 = self._io.read_f4le()
            self.pad3 = self._io.read_f4le()
            self.maxpos = self._io.read_f4le()
            self.maxpos_x2 = self._io.read_f4le()
            self.screendiv = self._io.read_f4le()
            self.r_maxpos = self._io.read_f4le()
            self.gridrate = self._io.read_f4le()
            self.r_height = self._io.read_f4le()
            self.alpha = self._io.read_f4le()
            self.double_rate = self._io.read_f4le()
            self.higher_y = self._io.read_f4le()
            self.lower_y = self._io.read_f4le()
            self.y_max = self._io.read_f4le()
            self.higher_y2 = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class FogAsmData2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FogAsmData2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.center_x = self._io.read_f4le()
            self.center_y = self._io.read_f4le()
            self.part_size_proj = self._io.read_f4le()
            self.center_w = self._io.read_f4le()
            self.screen_width = self._io.read_f4le()
            self.screen_height = self._io.read_f4le()
            self.pad1 = self._io.read_f4le()
            self.w_width = self._io.read_f4le()
            self.part_size = self._io.read_f4le()
            self.pixel_aspect = self._io.read_f4le()
            self.part_size_proj2 = self._io.read_f4le()
            self.r_part_size = self._io.read_f4le()
            self.tex_sth = self._io.read_f4le()
            self.floor_y = self._io.read_f4le()
            self.tex_move_speed = self._io.read_f4le()
            self.n128 = self._io.read_f4le()
            self.near_w = self._io.read_f4le()
            self.near_w2 = self._io.read_f4le()
            self.r_near_w2 = self._io.read_f4le()
            self.nr_128 = self._io.read_f4le()
            self.light_max = self._io.read_f4le()
            self.light_rate = self._io.read_f4le()
            self.light_under = self._io.read_f4le()
            self.r_light_under = self._io.read_f4le()
            self.d_rate = self._io.read_f4le()
            self.d_under = self._io.read_f4le()
            self.d_rate2 = self._io.read_f4le()
            self.proj = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class FogAsmData3(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FogAsmData3, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.maxpos = self._io.read_f4le()
            self.r_screendiv = self._io.read_f4le()
            self.movespeed = self._io.read_f4le()
            self.r_double = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class FogAsmDataP(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FogAsmDataP, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.part = Sh2.Pointer(u"fog_part_data", self._io, self, self._root)
            self.packet = Sh2.Pointer(u"data", self._io, self, self._root)
            self.asm_data = Sh2.Pointer(u"data", self._io, self, self._root)
            self.world_screen = Sh2.Pointer(u"data", self._io, self, self._root)
            self.world_view = Sh2.Pointer(u"data", self._io, self, self._root)
            self.camera_pos = Sh2.Pointer(u"data", self._io, self, self._root)
            self.world_pos = Sh2.Pointer(u"data", self._io, self, self._root)
            self.light_pos = Sh2.Pointer(u"data", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.part._fetch_instances()
            self.packet._fetch_instances()
            self.asm_data._fetch_instances()
            self.world_screen._fetch_instances()
            self.world_view._fetch_instances()
            self.camera_pos._fetch_instances()
            self.world_pos._fetch_instances()
            self.light_pos._fetch_instances()


    class FogBlowPoint(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FogBlowPoint, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pos = []
            for i in range(4):
                self.pos.append(self._io.read_f4le())

            self.vec = []
            for i in range(4):
                self.vec.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.pos)):
                pass

            for i in range(len(self.vec)):
                pass



    class FogColisHead(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FogColisHead, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.wall1 = self._io.read_u2le()
            self.wall2 = self._io.read_u2le()
            self.obj1 = self._io.read_u2le()
            self.obj2 = self._io.read_u2le()
            self.area = self._io.read_u2le()
            self.env = self._io.read_u2le()


        def _fetch_instances(self):
            pass


    class FogEnvData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FogEnvData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.part_num = self._io.read_s2le()
            self.max_pos = self._io.read_s2le()
            self.part_size = self._io.read_s2le()
            self.escape_range = self._io.read_s2le()
            self.floor_y = self._io.read_s2le()
            self.limit_y = self._io.read_s2le()
            self.limit_height = self._io.read_s2le()
            self.water_y = self._io.read_s2le()
            self.wind_def = self._io.read_u1()
            self.flag = self._io.read_u1()
            self.double = self._io.read_u1()
            self.alpha = self._io.read_u1()
            self.grid_rate = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class FogObjData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FogObjData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pos = []
            for i in range(4):
                self.pos.append(self._io.read_f4le())

            self.mv = []
            for i in range(4):
                self.mv.append(self._io.read_f4le())

            self.type = self._io.read_s4le()
            self.rer = self._io.read_f4le()
            self.id = self._io.read_u8le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.pos)):
                pass

            for i in range(len(self.mv)):
                pass



    class FogPackWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FogPackWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.packet = []
            for i in range(6400):
                self.packet.append(Sh2.U16(self._io, self, self._root))

            self.pk_env = Sh2.Pointer(u"data", self._io, self, self._root)
            self.pk_screen = Sh2.Pointer(u"data", self._io, self, self._root)
            self.pk_tex0 = Sh2.Pointer(u"data", self._io, self, self._root)
            self.pk_vifmark = Sh2.Pointer(u"data", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            for i in range(len(self.packet)):
                pass
                self.packet[i]._fetch_instances()

            self.pk_env._fetch_instances()
            self.pk_screen._fetch_instances()
            self.pk_tex0._fetch_instances()
            self.pk_vifmark._fetch_instances()


    class FogPartData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FogPartData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pos = []
            for i in range(4):
                self.pos.append(self._io.read_f4le())

            self.mv = []
            for i in range(4):
                self.mv.append(self._io.read_f4le())

            self.dd = []
            for i in range(4):
                self.dd.append(self._io.read_f4le())

            self.degree = []
            for i in range(4):
                self.degree.append(self._io.read_f4le())

            self.tdx = self._io.read_f4le()
            self.tdy = self._io.read_f4le()
            self.alp = self._io.read_f4le()
            self.dpos = self._io.read_s4le()
            self.alp_now = self._io.read_f4le()
            self.alp_add = self._io.read_f4le()
            self.bounce = self._io.read_s4le()
            self.erase = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.pos)):
                pass

            for i in range(len(self.mv)):
                pass

            for i in range(len(self.dd)):
                pass

            for i in range(len(self.degree)):
                pass



    class FogWallData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FogWallData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.normal = []
            for i in range(4):
                self.normal.append(self._io.read_f4le())

            self.v0 = []
            for i in range(4):
                self.v0.append(self._io.read_f4le())

            self.min = []
            for i in range(4):
                self.min.append(self._io.read_f4le())

            self.max = []
            for i in range(4):
                self.max.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.normal)):
                pass

            for i in range(len(self.v0)):
                pass

            for i in range(len(self.min)):
                pass

            for i in range(len(self.max)):
                pass



    class FogWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FogWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.part = []
            for i in range(700):
                self.part.append(Sh2.FogPartData(self._io, self, self._root))

            self.grid_dense = []
            for i in range(512):
                self.grid_dense.append(self._io.read_f4le())

            self.wall = []
            for i in range(188):
                self.wall.append(Sh2.FogWallData(self._io, self, self._root))

            self.obj = []
            for i in range(168):
                self.obj.append(Sh2.FogObjData(self._io, self, self._root))

            self.world_screen_m = []
            for i in range(16):
                self.world_screen_m.append(self._io.read_f4le())

            self.world_view_m = []
            for i in range(16):
                self.world_view_m.append(self._io.read_f4le())

            self.camera_pos_v = []
            for i in range(4):
                self.camera_pos_v.append(self._io.read_f4le())

            self.old_camera_v = []
            for i in range(4):
                self.old_camera_v.append(self._io.read_f4le())

            self.world_pos_v = []
            for i in range(4):
                self.world_pos_v.append(self._io.read_f4le())

            self.local_pos_v = []
            for i in range(4):
                self.local_pos_v.append(self._io.read_f4le())

            self.map_pos_v = []
            for i in range(4):
                self.map_pos_v.append(self._io.read_f4le())

            self.light_pos_v = []
            for i in range(4):
                self.light_pos_v.append(self._io.read_f4le())

            self.wind_v = []
            for i in range(4):
                self.wind_v.append(self._io.read_f4le())

            self.fewdense = []
            for i in range(4):
                self.fewdense.append(self._io.read_f4le())

            self.stay_point = []
            for i in range(4):
                self.stay_point.append(self._io.read_f4le())

            self.limit_y = self._io.read_f4le()
            self.limit_y2 = self._io.read_f4le()
            self.water_y = self._io.read_f4le()
            self.speed_level = self._io.read_f4le()
            self.sc_degree = []
            for i in range(4):
                self.sc_degree.append(self._io.read_f4le())

            self.sc_tdx = self._io.read_f4le()
            self.sc_tdy = self._io.read_f4le()
            self.max_pos = self._io.read_f4le()
            self.fade_pos = self._io.read_f4le()
            self.part_size = self._io.read_f4le()
            self.projection = self._io.read_f4le()
            self.escape_range = self._io.read_f4le()
            self.grid_rate = self._io.read_f4le()
            self.floor_y = self._io.read_f4le()
            self.part_num = self._io.read_s2le()
            self.wall_num = self._io.read_s2le()
            self.obj_max = self._io.read_s2le()
            self.obj_num = self._io.read_s2le()
            self.obj_num2 = self._io.read_s2le()
            self.alpha = self._io.read_s2le()
            self.wind_def = self._io.read_s2le()
            self.double = self._io.read_s1()
            self.load_step = self._io.read_s1()
            self.global_ = self._io.read_s1()
            self._unnamed39 = self._io.read_bytes(1)
            self.area_max = self._io.read_u2le()
            self.flag = self._io.read_u2le()
            self._unnamed42 = self._io.read_bytes(2)
            self.color = self._io.read_u4le()
            self.sum_w = self._io.read_s4le()
            self.fid = self._io.read_s4le()
            self.wind_timer = self._io.read_s4le()
            self.colis_head = Sh2.Pointer(u"fog_colis_head", self._io, self, self._root)
            self.area_top = Sh2.Pointer(u"fog_area_data", self._io, self, self._root)
            self.env_top = Sh2.Pointer(u"fog_env_data", self._io, self, self._root)
            self.env_now = Sh2.Pointer(u"fog_env_data", self._io, self, self._root)
            self._unnamed51 = self._io.read_bytes(4)


        def _fetch_instances(self):
            pass
            for i in range(len(self.part)):
                pass
                self.part[i]._fetch_instances()

            for i in range(len(self.grid_dense)):
                pass

            for i in range(len(self.wall)):
                pass
                self.wall[i]._fetch_instances()

            for i in range(len(self.obj)):
                pass
                self.obj[i]._fetch_instances()

            for i in range(len(self.world_screen_m)):
                pass

            for i in range(len(self.world_view_m)):
                pass

            for i in range(len(self.camera_pos_v)):
                pass

            for i in range(len(self.old_camera_v)):
                pass

            for i in range(len(self.world_pos_v)):
                pass

            for i in range(len(self.local_pos_v)):
                pass

            for i in range(len(self.map_pos_v)):
                pass

            for i in range(len(self.light_pos_v)):
                pass

            for i in range(len(self.wind_v)):
                pass

            for i in range(len(self.fewdense)):
                pass

            for i in range(len(self.stay_point)):
                pass

            for i in range(len(self.sc_degree)):
                pass

            self.colis_head._fetch_instances()
            self.area_top._fetch_instances()
            self.env_top._fetch_instances()
            self.env_now._fetch_instances()


    class FogWork2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FogWork2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.part_num = self._io.read_s2le()
            self.blow_point_num = self._io.read_s2le()
            self.blow_point_id = self._io.read_s4le()
            self.blow_point = Sh2.Pointer(u"fog_blow_point", self._io, self, self._root)
            self.blow_timer = []
            for i in range(16):
                self.blow_timer.append(self._io.read_s4le())

            self.blow_interval = self._io.read_s4le()
            self.gravity = self._io.read_f4le()
            self.expand = self._io.read_f4le()


        def _fetch_instances(self):
            pass
            self.blow_point._fetch_instances()
            for i in range(len(self.blow_timer)):
                pass



    class FontData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FontData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.tex_head = []
            for i in range(12):
                self.tex_head.append(self._io.read_u4le())

            self.clut_head = []
            for i in range(12):
                self.clut_head.append(self._io.read_u4le())

            self.clut = []
            for i in range(8):
                self.clut.append(self._io.read_u4le())

            self.texbuf = []
            for i in range(131072):
                self.texbuf.append(self._io.read_u1())

            self.tex0 = self._io.read_u8le()
            self.fonttype = self._io.read_s4le()
            self.rgb_u = self._io.read_u4le()
            self.rgb_d = self._io.read_u4le()
            self.rgb_s = []
            for i in range(4):
                self.rgb_s.append(self._io.read_u4le())

            self.alpha = self._io.read_u4le()
            self.alpha_base = self._io.read_u4le()
            self.flag = self._io.read_u4le()
            self.x = self._io.read_u2le()
            self.y = self._io.read_u2le()
            self.wide_w = self._io.read_u2le()
            self.wide_h = self._io.read_u2le()
            self.right_x = self._io.read_u2le()
            self.right_y = self._io.read_u2le()
            self.wm = self._io.read_u2le()
            self.hm = self._io.read_u2le()
            self.wait_count = self._io.read_s2le()
            self.wait_type = self._io.read_s2le()
            self.page_sound = self._io.read_s2le()
            self.code = []
            for i in range(400):
                self.code.append(self._io.read_u2le())

            self.upper = []
            for i in range(400):
                self.upper.append(self._io.read_s2le())

            self.lower = []
            for i in range(400):
                self.lower.append(self._io.read_s2le())

            self.top = self._io.read_s2le()
            self.bottom = self._io.read_s2le()
            self.st_num = self._io.read_s2le()
            self.w_st_num = self._io.read_s2le()
            self.prl_count = self._io.read_s2le()
            self.preload = self._io.read_s2le()
            self.shadow_max = self._io.read_s2le()
            self.shadow_now = self._io.read_s2le()
            self.sel_xl = self._io.read_u2le()
            self.sel_xr = self._io.read_u2le()
            self.sel_yu = []
            for i in range(4):
                self.sel_yu.append(self._io.read_u2le())

            self.sel_yd = []
            for i in range(4):
                self.sel_yd.append(self._io.read_u2le())

            self.sel_max = self._io.read_s2le()
            self.sel_now = self._io.read_s2le()
            self.mes_v = []
            for i in range(640):
                self.mes_v.append(self._io.read_u2le())

            self._unnamed41 = self._io.read_bytes(2)
            self.mes_str_now = Sh2.Pointer(u"data", self._io, self, self._root)
            self.mes_str = Sh2.Pointer(u"data", self._io, self, self._root)
            self.prl_str = Sh2.Pointer(u"data", self._io, self, self._root)
            self.stream = Sh2.Pointer(u"font_stream_data", self._io, self, self._root)
            self.w_stream = Sh2.Pointer(u"wfont_stream_data", self._io, self, self._root)
            self.m_stream = Sh2.Pointer(u"mfont_stream_data", self._io, self, self._root)
            self.stream_max = self._io.read_u2le()
            self.w_stream_max = self._io.read_u2le()
            self.m_stream_max = self._io.read_u2le()
            self.m_code = []
            for i in range(256):
                self.m_code.append(self._io.read_u2le())

            self.m_upper = []
            for i in range(256):
                self.m_upper.append(self._io.read_s2le())

            self.m_lower = []
            for i in range(256):
                self.m_lower.append(self._io.read_s2le())

            self.m_top = self._io.read_s2le()
            self.m_bottom = self._io.read_s2le()
            self.m_st_num = self._io.read_s2le()
            self.m_base_x = self._io.read_s4le()
            self.m_base_y = self._io.read_s4le()
            self.m_base_z = self._io.read_s4le()
            self.m_rgba = self._io.read_u4le()
            self.m_sx = self._io.read_s4le()
            self.m_sy = self._io.read_s4le()
            self.m_w = self._io.read_s4le()
            self.m_h = self._io.read_s4le()
            self.m_x = self._io.read_s4le()
            self.m_y = self._io.read_s4le()
            self.bar_blink = self._io.read_f4le()
            self.p_cur = Sh2.Pointer(u"data", self._io, self, self._root)
            self.base_x = self._io.read_s4le()
            self.base_y = self._io.read_s4le()
            self.base_z = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.tex_head)):
                pass

            for i in range(len(self.clut_head)):
                pass

            for i in range(len(self.clut)):
                pass

            for i in range(len(self.texbuf)):
                pass

            for i in range(len(self.rgb_s)):
                pass

            for i in range(len(self.code)):
                pass

            for i in range(len(self.upper)):
                pass

            for i in range(len(self.lower)):
                pass

            for i in range(len(self.sel_yu)):
                pass

            for i in range(len(self.sel_yd)):
                pass

            for i in range(len(self.mes_v)):
                pass

            self.mes_str_now._fetch_instances()
            self.mes_str._fetch_instances()
            self.prl_str._fetch_instances()
            self.stream._fetch_instances()
            self.w_stream._fetch_instances()
            self.m_stream._fetch_instances()
            for i in range(len(self.m_code)):
                pass

            for i in range(len(self.m_upper)):
                pass

            for i in range(len(self.m_lower)):
                pass

            self.p_cur._fetch_instances()


    class FontStreamData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FontStreamData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x = self._io.read_u2le()
            self.y = self._io.read_u2le()
            self.w = self._io.read_u2le()
            self.h = self._io.read_u2le()
            self.u = self._io.read_u2le()
            self.v = self._io.read_u2le()
            self.rgb_u = self._io.read_u4le()
            self.rgb_d = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class FsCdFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FsCdFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_bits_int_le(8)
            self.number = self._io.read_bits_int_le(24)
            self.name = Sh2.Pointer(u"data", self._io, self, self._root)
            self.lsn = self._io.read_s4le()
            self.size = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.name._fetch_instances()


    class FsFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FsFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._unnamed0 = self._io.read_bytes(16)


        def _fetch_instances(self):
            pass
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

            _ = self.pack
            if hasattr(self, '_m_pack'):
                pass
                self._m_pack._fetch_instances()


        @property
        def cd(self):
            if hasattr(self, '_m_cd'):
                return self._m_cd

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_cd = Sh2.FsCdFile(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_cd', None)

        @property
        def check(self):
            if hasattr(self, '_m_check'):
                return self._m_check

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_check = Sh2.FsFileAnon7(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_check', None)

        @property
        def hd(self):
            if hasattr(self, '_m_hd'):
                return self._m_hd

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_hd = Sh2.FsHdFile(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_hd', None)

        @property
        def mgc(self):
            if hasattr(self, '_m_mgc'):
                return self._m_mgc

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_mgc = Sh2.FsMgcFile(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_mgc', None)

        @property
        def mgf(self):
            if hasattr(self, '_m_mgf'):
                return self._m_mgf

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_mgf = Sh2.FsMgfFile(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_mgf', None)

        @property
        def mgp(self):
            if hasattr(self, '_m_mgp'):
                return self._m_mgp

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_mgp = Sh2.FsMgpFile(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_mgp', None)

        @property
        def pack(self):
            if hasattr(self, '_m_pack'):
                return self._m_pack

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_pack = Sh2.U16(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_pack', None)


    class FsFileAnon7(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FsFileAnon7, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_bits_int_le(8)
            self.number = self._io.read_bits_int_le(24)
            self.pad0 = self._io.read_s4le()
            self.pad1 = self._io.read_s4le()
            self.pad2 = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class FsFileIndex(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FsFileIndex, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._unnamed0 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            _ = self.index
            if hasattr(self, '_m_index'):
                pass
                self._m_index._fetch_instances()

            _ = self.pack
            if hasattr(self, '_m_pack'):
                pass


        @property
        def index(self):
            if hasattr(self, '_m_index'):
                return self._m_index

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_index = Sh2.FsFileIndexAnon8(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_index', None)

        @property
        def pack(self):
            if hasattr(self, '_m_pack'):
                return self._m_pack

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_pack = self._io.read_u8le()
            self._io.seek(_pos)
            return getattr(self, '_m_pack', None)


    class FsFileIndexAnon8(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FsFileIndexAnon8, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.fp = Sh2.Pointer(u"fs_file", self._io, self, self._root)
            self.name = Sh2.Pointer(u"data", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.fp._fetch_instances()
            self.name._fetch_instances()


    class FsHdFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FsHdFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_bits_int_le(8)
            self.padding = self._io.read_bits_int_le(24)
            self.name = Sh2.Pointer(u"data", self._io, self, self._root)
            self.offset = self._io.read_s4le()
            self.size = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.name._fetch_instances()


    class FsMgcFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FsMgcFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_bits_int_le(8)
            self.padding = self._io.read_bits_int_le(24)
            self.parent = Sh2.Pointer(u"fs_file", self._io, self, self._root)
            self.start = Sh2.Pointer(u"data", self._io, self, self._root)
            self.end = Sh2.Pointer(u"data", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.parent._fetch_instances()
            self.start._fetch_instances()
            self.end._fetch_instances()


    class FsMgfFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FsMgfFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_bits_int_le(8)
            self.padding = self._io.read_bits_int_le(24)
            self.parent = Sh2.Pointer(u"fs_file", self._io, self, self._root)
            self.offset = self._io.read_s4le()
            self.size = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.parent._fetch_instances()


    class FsMgpFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.FsMgpFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_bits_int_le(8)
            self.padding = self._io.read_bits_int_le(24)
            self.file = Sh2.Pointer(u"fs_file", self._io, self, self._root)
            self.start = Sh2.Pointer(u"fs_mgc_file", self._io, self, self._root)
            self.end = Sh2.Pointer(u"fs_mgc_file", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.file._fetch_instances()
            self.start._fetch_instances()
            self.end._fetch_instances()


    class GameFlag(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.GameFlag, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.flag = []
            for i in range(255):
                self.flag.append(self._io.read_u4le())

            self.time_deai = self._io.read_f4le()
            self.enemy = []
            for i in range(32):
                self.enemy.append(self._io.read_u4le())

            self.safe = []
            for i in range(4):
                self.safe.append(self._io.read_u1())

            self.rotate = []
            for i in range(4):
                self.rotate.append(self._io.read_s1())

            self.guruguru = []
            for i in range(4):
                self.guruguru.append(self._io.read_s1())

            self.cylinder = []
            for i in range(4):
                self.cylinder.append(self._io.read_s1())

            self.clock = self._io.read_u2le()
            self.carbon = self._io.read_u2le()
            self.runaway = []
            for i in range(4):
                self.runaway.append(self._io.read_s1())

            self.hanging = self._io.read_u2le()
            self.pad = self._io.read_s2le()
            self.trunk = []
            for i in range(4):
                self.trunk.append(self._io.read_s1())



        def _fetch_instances(self):
            pass
            for i in range(len(self.flag)):
                pass

            for i in range(len(self.enemy)):
                pass

            for i in range(len(self.safe)):
                pass

            for i in range(len(self.rotate)):
                pass

            for i in range(len(self.guruguru)):
                pass

            for i in range(len(self.cylinder)):
                pass

            for i in range(len(self.runaway)):
                pass

            for i in range(len(self.trunk)):
                pass



    class GfwFunc(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.GfwFunc, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.spec_draw = Sh2.Pointer(u"data", self._io, self, self._root)
            self.pre_draw = Sh2.Pointer(u"data", self._io, self, self._root)
            self.post_draw = Sh2.Pointer(u"data", self._io, self, self._root)
            self.chara_draw_hook = Sh2.Pointer(u"data", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.spec_draw._fetch_instances()
            self.pre_draw._fetch_instances()
            self.post_draw._fetch_instances()
            self.chara_draw_hook._fetch_instances()


    class HhClassWrapperWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.HhClassWrapperWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.view_frustum_primitive_clip_matrix = []
            for i in range(16):
                self.view_frustum_primitive_clip_matrix.append(self._io.read_f4le())

            self.view_frustum_bounding_box_clip_matrix = []
            for i in range(16):
                self.view_frustum_bounding_box_clip_matrix.append(self._io.read_f4le())

            self.always_front_world_view_matrix = []
            for i in range(16):
                self.always_front_world_view_matrix.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.view_frustum_primitive_clip_matrix)):
                pass

            for i in range(len(self.view_frustum_bounding_box_clip_matrix)):
                pass

            for i in range(len(self.always_front_world_view_matrix)):
                pass



    class IVector4(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.IVector4, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x = self._io.read_s4le()
            self.y = self._io.read_s4le()
            self.z = self._io.read_s4le()
            self.w = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class ImpactQueueElement(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ImpactQueueElement, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.class_descriptor = self._io.read_u4le()
            self.h_instance = self._io.read_u4le()
            self.p_result_handle_address = Sh2.Pointer(u"data", self._io, self, self._root)
            self.reserved = self._io.read_u4le()
            self.option = Sh2.ImpactQueueElementOption(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.p_result_handle_address._fetch_instances()
            self.option._fetch_instances()


    class ImpactQueueElementOption(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ImpactQueueElementOption, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.vector = []
            for i in range(8):
                self.vector.append(self._io.read_f4le())

            self.float_value = []
            for i in range(2):
                self.float_value.append(self._io.read_f4le())

            self.int_value = []
            for i in range(2):
                self.int_value.append(self._io.read_s4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.vector)):
                pass

            for i in range(len(self.float_value)):
                pass

            for i in range(len(self.int_value)):
                pass



    class ImpactQueueObject(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ImpactQueueObject, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.en_queue = self._io.read_u4le()
            self.de_queue = self._io.read_u4le()
            self.length_current = self._io.read_u4le()
            self.length_max = self._io.read_u4le()
            self.p_element = Sh2.Pointer(u"impact_queue_element", self._io, self, self._root)
            self._unnamed5 = self._io.read_bytes(12)


        def _fetch_instances(self):
            pass
            self.p_element._fetch_instances()


    class Item(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Item, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.flag = []
            for i in range(2):
                self.flag.append(self._io.read_u4le())

            self.number = []
            for i in range(11):
                self.number.append(self._io.read_u2le())

            self.light_switch = self._io.read_u1()
            self.radio_switch = self._io.read_u1()
            self.radio_volume = self._io.read_u1()
            self.equip = self._io.read_u1()
            self._unnamed6 = self._io.read_bytes(2)
            self.ampoule_efficacy = self._io.read_f4le()
            self.event_use = []
            for i in range(3):
                self.event_use.append(self._io.read_u2le())

            self.short_pad = self._io.read_u2le()
            self.last_cursor = self._io.read_u1()
            self._unnamed11 = self._io.read_bytes(3)


        def _fetch_instances(self):
            pass
            for i in range(len(self.flag)):
                pass

            for i in range(len(self.number)):
                pass

            for i in range(len(self.event_use)):
                pass



    class ItemList(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ItemList, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pos_x = self._io.read_f4le()
            self.pos_z = self._io.read_f4le()
            self.pos_y = self._io.read_u2le()
            self.rot_y = self._io.read_u2le()
            self.st = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class Ixy(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Ixy, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x = self._io.read_s4le()
            self.y = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class Kanri(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Kanri, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pos = []
            for i in range(4):
                self.pos.append(self._io.read_f4le())

            self.ang = []
            for i in range(4):
                self.ang.append(self._io.read_f4le())

            self.rot_spd = []
            for i in range(4):
                self.rot_spd.append(self._io.read_f4le())

            self.velo_y = self._io.read_f4le()
            self.velo_xz = self._io.read_f4le()
            self.velo_houi = self._io.read_f4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.pos)):
                pass

            for i in range(len(self.ang)):
                pass

            for i in range(len(self.rot_spd)):
                pass



    class LoadBgCommonInfoT(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.LoadBgCommonInfoT, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.glb_crd = self._io.read_s4le()
            self.px = self._io.read_f4le()
            self.pz = self._io.read_f4le()
            self.fcx = self._io.read_f4le()
            self.fcz = self._io.read_f4le()
            self.icx = self._io.read_s4le()
            self.icz = self._io.read_s4le()
            self.minx = self._io.read_s4le()
            self.minz = self._io.read_s4le()
            self.outdoor = self._io.read_s4le()
            self.room_id = self._io.read_s4le()
            self.block_id = []
            for i in range(4):
                self.block_id.append(self._io.read_s4le())

            self.around_id = []
            for i in range(25):
                self.around_id.append(self._io.read_s4le())

            self.unit = self._io.read_s4le()
            self.load = self._io.read_s4le()
            self.need = self._io.read_s4le()
            self.lock = self._io.read_s4le()
            self.miss = self._io.read_s4le()
            self.hide_map = self._io.read_s4le()
            self.hide_map_request = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.block_id)):
                pass

            for i in range(len(self.around_id)):
                pass



    class Matrix4(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Matrix4, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.d = []
            for i in range(16):
                self.d.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.d)):
                pass



    class McCodecData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.McCodecData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.key1 = []
            for i in range(24):
                self.key1.append(self._io.read_u1())

            self.key2 = []
            for i in range(16):
                self.key2.append(self._io.read_u1())

            self.mode = self._io.read_s4le()
            self.step = self._io.read_s4le()
            self.pos = Sh2.Pointer(u"data", self._io, self, self._root)
            self.count = self._io.read_s4le()
            self.zcount = self._io.read_s4le()
            self.csum1 = self._io.read_u4le()
            self.csum2 = self._io.read_u4le()
            self._unnamed9 = self._io.read_bytes(4)
            self.csum4 = self._io.read_u8le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.key1)):
                pass

            for i in range(len(self.key2)):
                pass

            self.pos._fetch_instances()


    class McDirdata(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.McDirdata, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.message = []
            for i in range(28):
                self.message.append(self._io.read_s1())

            self.flag = self._io.read_u4le()
            self.file = []
            for i in range(15):
                self.file.append(Sh2.McFileinfo(self._io, self, self._root))

            self.playing = Sh2.PlayingInfo(self._io, self, self._root)
            self.lastsave = self._io.read_s4le()
            self.id = self._io.read_u4le()
            self.csum = []
            for i in range(4):
                self.csum.append(self._io.read_u4le())

            self.pad = []
            for i in range(130):
                self.pad.append(self._io.read_u4le())

            self.csum_all = self._io.read_u8le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.message)):
                pass

            for i in range(len(self.file)):
                pass
                self.file[i]._fetch_instances()

            self.playing._fetch_instances()
            for i in range(len(self.csum)):
                pass

            for i in range(len(self.pad)):
                pass



    class McFileinfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.McFileinfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.dirid = self._io.read_u1()
            self.fileid = self._io.read_u1()
            self.scene = self._io.read_u1()
            self.b_level = self._io.read_u1()
            self.r_level = self._io.read_u1()
            self.status = self._io.read_u1()
            self.savecount = self._io.read_u2le()
            self.time = self._io.read_f4le()
            self.total_time = self._io.read_f4le()
            self.csum = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class McIconSys(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.McIconSys, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.head = []
            for i in range(4):
                self.head.append(self._io.read_u1())

            self.reserv1 = self._io.read_u2le()
            self.offs_lf = self._io.read_u2le()
            self.reserv2 = self._io.read_u4le()
            self.trans_rate = self._io.read_u4le()
            self.bg_color = []
            for i in range(16):
                self.bg_color.append(self._io.read_s4le())

            self.light_dir = []
            for i in range(12):
                self.light_dir.append(self._io.read_f4le())

            self.light_color = []
            for i in range(12):
                self.light_color.append(self._io.read_f4le())

            self.ambient = []
            for i in range(4):
                self.ambient.append(self._io.read_f4le())

            self.title_name = []
            for i in range(68):
                self.title_name.append(self._io.read_u1())

            self.fname_view = []
            for i in range(64):
                self.fname_view.append(self._io.read_u1())

            self.fname_copy = []
            for i in range(64):
                self.fname_copy.append(self._io.read_u1())

            self.fname_del = []
            for i in range(64):
                self.fname_del.append(self._io.read_u1())

            self.reserve3 = []
            for i in range(512):
                self.reserve3.append(self._io.read_u1())



        def _fetch_instances(self):
            pass
            for i in range(len(self.head)):
                pass

            for i in range(len(self.bg_color)):
                pass

            for i in range(len(self.light_dir)):
                pass

            for i in range(len(self.light_color)):
                pass

            for i in range(len(self.ambient)):
                pass

            for i in range(len(self.title_name)):
                pass

            for i in range(len(self.fname_view)):
                pass

            for i in range(len(self.fname_copy)):
                pass

            for i in range(len(self.fname_del)):
                pass

            for i in range(len(self.reserve3)):
                pass



    class McJobs(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.McJobs, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.job = self._io.read_s1()
            self.port = self._io.read_s1()
            self.data = self._io.read_s2le()


        def _fetch_instances(self):
            pass


    class McSavedata(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.McSavedata, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.csum1 = self._io.read_u4le()
            self.csum2 = self._io.read_u4le()
            self.data = []
            for i in range(8168):
                self.data.append(self._io.read_u1())

            self.csum3 = self._io.read_u4le()
            self.pad = self._io.read_u4le()
            self.csum4 = self._io.read_u8le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.data)):
                pass



    class McWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.McWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.status = self._io.read_u2le()
            self.ls_port = self._io.read_s1()
            self.ls_dir = self._io.read_s1()
            self.ls_file = self._io.read_s1()
            self._unnamed4 = self._io.read_bytes(3)
            self.ls_dir_id = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class McWork2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.McWork2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.dirdata = Sh2.McDirdata(self._io, self, self._root)
            self.savedata = Sh2.McSavedata(self._io, self, self._root)
            self.dirtbl = []
            for i in range(20):
                self.dirtbl.append(Sh2.SceMcTblGetDir(self._io, self, self._root))

            self.tmpinfo = []
            for i in range(75):
                self.tmpinfo.append(Sh2.McFileinfo(self._io, self, self._root))

            self.fileinfo = []
            for i in range(225):
                self.fileinfo.append(Sh2.McFileinfo(self._io, self, self._root))

            self.jobs = []
            for i in range(16):
                self.jobs.append(Sh2.McJobs(self._io, self, self._root))

            self.port = self._io.read_s1()
            self.dirnum = self._io.read_s1()
            self.files = self._io.read_s1()
            self.tbl_files = self._io.read_s1()
            self.job = self._io.read_s1()
            self.job_port = self._io.read_s1()
            self.job_data = self._io.read_s1()
            self.job_step = self._io.read_s1()
            self.job_num = self._io.read_s1()
            self.job_end = self._io.read_s1()
            self._unnamed16 = self._io.read_bytes(2)
            self.result = self._io.read_s4le()
            self.type = []
            for i in range(2):
                self.type.append(self._io.read_s4le())

            self.free = []
            for i in range(2):
                self.free.append(self._io.read_s4le())

            self.format = []
            for i in range(2):
                self.format.append(self._io.read_s4le())

            self.info = []
            for i in range(2):
                self.info.append(self._io.read_s4le())

            self.d_ent = []
            for i in range(2):
                self.d_ent.append(self._io.read_u1())

            self.portstatus = []
            for i in range(3):
                self.portstatus.append(self._io.read_s1())

            self.dirstatus = []
            for i in range(15):
                self.dirstatus.append(self._io.read_s1())

            self.filemax = []
            for i in range(3):
                self.filemax.append(self._io.read_s1())

            self.tmp_status = []
            for i in range(3):
                self.tmp_status.append(self._io.read_s1())

            self._unnamed27 = self._io.read_bytes(2)
            self.type_old = self._io.read_s4le()
            self.retry = self._io.read_s2le()
            self.info_count = self._io.read_s2le()
            self.fd = self._io.read_s4le()
            self.fid = []
            for i in range(2):
                self.fid.append(self._io.read_s4le())

            self.autoload = self._io.read_s2le()
            self.saveload = self._io.read_s1()
            self.menu_step = self._io.read_s1()
            self.menu_sstep = self._io.read_s1()
            self.menu_base = []
            for i in range(3):
                self.menu_base.append(self._io.read_s1())

            self.menu_num = []
            for i in range(3):
                self.menu_num.append(self._io.read_s1())

            self.tmp_num = self._io.read_s1()
            self.menu_info = self._io.read_s1()
            self.menu_infotype = self._io.read_s1()
            self.menu_timer = self._io.read_s1()
            self.menu_port = self._io.read_s1()
            self.menu_yesno = self._io.read_s1()
            self.menu_newdir = self._io.read_s1()
            self.menu_bk = self._io.read_s1()
            self._unnamed47 = self._io.read_bytes(1)
            self.menu_scroll = self._io.read_f4le()
            self.menu_count = self._io.read_f4le()
            self.menu_an_count = self._io.read_f4le()
            self.extra_name = []
            for i in range(8):
                self.extra_name.append(self._io.read_s1())

            self.extra_adr = Sh2.Pointer(u"data", self._io, self, self._root)
            self.extra_size = self._io.read_s4le()
            self.dirid = []
            for i in range(15):
                self.dirid.append(self._io.read_u4le())

            self.dirid_new = self._io.read_u4le()
            self.fname = []
            for i in range(64):
                self.fname.append(self._io.read_s1())

            self.dtime = []
            for i in range(2):
                self.dtime.append(self._io.read_u8le())

            self.loaddata = Sh2.Pointer(u"mc_fileinfo", self._io, self, self._root)
            self._unnamed59 = self._io.read_bytes(4)
            self.cd = Sh2.McCodecData(self._io, self, self._root)
            self._unnamed61 = self._io.read_bytes(24)


        def _fetch_instances(self):
            pass
            self.dirdata._fetch_instances()
            self.savedata._fetch_instances()
            for i in range(len(self.dirtbl)):
                pass
                self.dirtbl[i]._fetch_instances()

            for i in range(len(self.tmpinfo)):
                pass
                self.tmpinfo[i]._fetch_instances()

            for i in range(len(self.fileinfo)):
                pass
                self.fileinfo[i]._fetch_instances()

            for i in range(len(self.jobs)):
                pass
                self.jobs[i]._fetch_instances()

            for i in range(len(self.type)):
                pass

            for i in range(len(self.free)):
                pass

            for i in range(len(self.format)):
                pass

            for i in range(len(self.info)):
                pass

            for i in range(len(self.d_ent)):
                pass

            for i in range(len(self.portstatus)):
                pass

            for i in range(len(self.dirstatus)):
                pass

            for i in range(len(self.filemax)):
                pass

            for i in range(len(self.tmp_status)):
                pass

            for i in range(len(self.fid)):
                pass

            for i in range(len(self.menu_base)):
                pass

            for i in range(len(self.menu_num)):
                pass

            for i in range(len(self.extra_name)):
                pass

            self.extra_adr._fetch_instances()
            for i in range(len(self.dirid)):
                pass

            for i in range(len(self.fname)):
                pass

            for i in range(len(self.dtime)):
                pass

            self.loaddata._fetch_instances()
            self.cd._fetch_instances()


    class MemoryPoolAssociationInfomeation(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.MemoryPoolAssociationInfomeation, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.existent = self._io.read_u4le()
            self._unnamed1 = self._io.read_bytes(12)
            self.data_pool_info = Sh2.ObjectDataPoolInfomeation(self._io, self, self._root)
            self.link_list_max = self._io.read_u4le()
            self.p_link_list = Sh2.Pointer(u"data", self._io, self, self._root)
            self._unnamed5 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            self.data_pool_info._fetch_instances()
            self.p_link_list._fetch_instances()


    class MfontStreamData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.MfontStreamData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x = self._io.read_u2le()
            self.y = self._io.read_u2le()
            self.u = self._io.read_u2le()
            self.v = self._io.read_u2le()


        def _fetch_instances(self):
            pass


    class ModelList(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ModelList, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.kind = self._io.read_s2le()
            self.id = self._io.read_s2le()
            self.flag_off = self._io.read_s2le()
            self.flag_on = self._io.read_s2le()
            self._unnamed4 = self._io.read_bytes(8)
            self.pos = []
            for i in range(4):
                self.pos.append(self._io.read_f4le())

            self.rot = []
            for i in range(4):
                self.rot.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.pos)):
                pass

            for i in range(len(self.rot)):
                pass



    class MovieWrk(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.MovieWrk, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.play_event_no = self._io.read_s4le()
            self.play_event_sta = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class NearSoundData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.NearSoundData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.in_vol = []
            for i in range(7):
                self.in_vol.append(self._io.read_s1())

            self.out_vol = []
            for i in range(7):
                self.out_vol.append(self._io.read_s1())

            self._unnamed2 = self._io.read_bytes(2)
            self.err_code = self._io.read_s4le()
            self.abs_index = self._io.read_s4le()
            self.len = self._io.read_f4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.in_vol)):
                pass

            for i in range(len(self.out_vol)):
                pass



    class ObjectClass(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ObjectClass, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.p_prefix = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_main = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_suffix = Sh2.Pointer(u"data", self._io, self, self._root)
            self.disable = self._io.read_u4le()


        def _fetch_instances(self):
            pass
            self.p_prefix._fetch_instances()
            self.p_main._fetch_instances()
            self.p_suffix._fetch_instances()


    class ObjectClassAssociationInfomeation(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ObjectClassAssociationInfomeation, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.p_class_list = Sh2.Pointer(u"object_class", self._io, self, self._root)
            self.p_data_pool_info = Sh2.Pointer(u"object_data_pool_infomeation", self._io, self, self._root)
            self.p_class_priority_list = Sh2.Pointer(u"data", self._io, self, self._root)
            self.class_max = self._io.read_u4le()


        def _fetch_instances(self):
            pass
            self.p_class_list._fetch_instances()
            self.p_data_pool_info._fetch_instances()
            self.p_class_priority_list._fetch_instances()


    class ObjectDataBlockHeader(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ObjectDataBlockHeader, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.enable = self._io.read_u4le()
            self.p_next = Sh2.Pointer(u"object_data_block_header", self._io, self, self._root)
            self._unnamed2 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            self.p_next._fetch_instances()


    class ObjectDataPoolInfomeation(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ObjectDataPoolInfomeation, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.block_size = self._io.read_u4le()
            self.block_index_max = self._io.read_u4le()
            self.p_block_table = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_free_block_list = Sh2.Pointer(u"object_data_block_header", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.p_block_table._fetch_instances()
            self.p_free_block_list._fetch_instances()


    class ObjectGroupInfomeation(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ObjectGroupInfomeation, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.association_info = Sh2.ObjectClassAssociationInfomeation(self._io, self, self._root)
            self.instance_table_info = Sh2.ObjectInstanceTableInfomeation(self._io, self, self._root)
            self.queue_info = Sh2.ImpactQueueObject(self._io, self, self._root)
            self.enable = self._io.read_u4le()
            self.step = self._io.read_u4le()
            self._unnamed5 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            self.association_info._fetch_instances()
            self.instance_table_info._fetch_instances()
            self.queue_info._fetch_instances()


    class ObjectInstance(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ObjectInstance, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.element = Sh2.ImpactQueueElement(self._io, self, self._root)
            self.enable = self._io.read_u4le()
            self.h_instance = self._io.read_u4le()
            self.p_block = Sh2.Pointer(u"data", self._io, self, self._root)
            self.timer = self._io.read_f4le()
            self.p_prev = Sh2.Pointer(u"object_instance", self._io, self, self._root)
            self.p_next = Sh2.Pointer(u"object_instance", self._io, self, self._root)
            self._unnamed7 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            self.element._fetch_instances()
            self.p_block._fetch_instances()
            self.p_prev._fetch_instances()
            self.p_next._fetch_instances()


    class ObjectInstanceTableInfomeation(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ObjectInstanceTableInfomeation, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.p_instance_table = Sh2.Pointer(u"object_instance", self._io, self, self._root)
            self.instance_max = self._io.read_u4le()
            self.h_instance_history = self._io.read_u4le()
            self.p_hierarchy_table = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_free_table = Sh2.Pointer(u"object_instance", self._io, self, self._root)
            self._unnamed5 = self._io.read_bytes(12)


        def _fetch_instances(self):
            pass
            self.p_instance_table._fetch_instances()
            self.p_hierarchy_table._fetch_instances()
            self.p_free_table._fetch_instances()


    class OpdW(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.OpdW, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.u0 = self._io.read_f4le()
            self.u1 = self._io.read_f4le()
            self.v0 = self._io.read_f4le()
            self.v1 = self._io.read_f4le()
            self.x0 = self._io.read_f4le()
            self.y0 = self._io.read_f4le()
            self.x1 = self._io.read_f4le()
            self.y1 = self._io.read_f4le()
            self.offset_x = self._io.read_f4le()
            self.offset_y = self._io.read_f4le()
            self.scale_x = self._io.read_f4le()
            self.scale_y = self._io.read_f4le()
            self.rgb = self._io.read_u1()
            self.step = self._io.read_u1()
            self.timer = self._io.read_u1()
            self._unnamed15 = self._io.read_bytes(1)


        def _fetch_instances(self):
            pass


    class Pad2d(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Pad2d, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pow = self._io.read_u1()
            self.lower_motion = self._io.read_u1()
            self._unnamed2 = self._io.read_bytes(2)
            self.dir = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class Pad3d(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Pad3d, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.round_way = self._io.read_s1()
            self.reserved1 = self._io.read_u1()
            self.lslide = self._io.read_u1()
            self.rslide = self._io.read_u1()
            self.lturn180 = self._io.read_u1()
            self.rturn180 = self._io.read_u1()


        def _fetch_instances(self):
            pass


    class PadInfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.PadInfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.action = self._io.read_u1()
            self.dash = self._io.read_u1()
            self.attack0 = self._io.read_u1()
            self.attack1 = self._io.read_u1()
            self.attack2 = self._io.read_u1()
            self.menu = self._io.read_u1()
            self.hold = self._io.read_u1()
            self.search = self._io.read_u1()
            self.map = self._io.read_u1()
            self.light_ = self._io.read_bits_int_le(4)
            self.light = self._io.read_bits_int_le(4)
            self.l_button = self._io.read_u1()
            self.r_button = self._io.read_u1()
            self.lstick_x = self._io.read_s1()
            self.lstick_y = self._io.read_s1()
            self.rstick_x = self._io.read_s1()
            self.rstick_y = self._io.read_s1()
            self.forward = self._io.read_u1()
            self.backward = self._io.read_u1()
            self.lround = self._io.read_u1()
            self.rround = self._io.read_u1()
            self.skip = self._io.read_u1()
            self.pause = self._io.read_u1()
            self._unnamed23 = self._io.read_bytes(2)
            self._raw__unnamed24 = self._io.read_bytes(8)
            _io__raw__unnamed24 = KaitaiStream(BytesIO(self._raw__unnamed24))
            self._unnamed24 = Sh2.PadInfoAnon3(_io__raw__unnamed24, self, self._root)


        def _fetch_instances(self):
            pass
            self._unnamed24._fetch_instances()


    class PadInfoAnon3(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.PadInfoAnon3, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._unnamed0 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            _ = self.pad2d
            if hasattr(self, '_m_pad2d'):
                pass
                self._m_pad2d._fetch_instances()

            _ = self.pad3d
            if hasattr(self, '_m_pad3d'):
                pass
                self._m_pad3d._fetch_instances()


        @property
        def pad2d(self):
            if hasattr(self, '_m_pad2d'):
                return self._m_pad2d

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_pad2d = Sh2.Pad2d(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_pad2d', None)

        @property
        def pad3d(self):
            if hasattr(self, '_m_pad3d'):
                return self._m_pad3d

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_pad3d = Sh2.Pad3d(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_pad3d', None)


    class PadKeyConfig(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.PadKeyConfig, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.enter = self._io.read_s4le()
            self.cancel = self._io.read_s4le()
            self.skip = self._io.read_s4le()
            self.front_move = self._io.read_s4le()
            self.back_move = self._io.read_s4le()
            self.right_turn = self._io.read_s4le()
            self.left_turn = self._io.read_s4le()
            self.right_move = self._io.read_s4le()
            self.left_move = self._io.read_s4le()
            self.action = self._io.read_s4le()
            self.attack = self._io.read_s4le()
            self.dash = self._io.read_s4le()
            self.light = self._io.read_s4le()
            self.item = self._io.read_s4le()
            self.search_view = self._io.read_s4le()
            self.ready = self._io.read_s4le()
            self.pause = self._io.read_s4le()
            self.map = self._io.read_s4le()
            self.padding = []
            for i in range(6):
                self.padding.append(self._io.read_s4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.padding)):
                pass



    class PicDrawData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.PicDrawData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.ap = Sh2.Pointer(u"sh2gfw_area_head", self._io, self, self._root)
            self.tex = self._io.read_s4le()
            self.clut = self._io.read_s4le()
            self.x0 = self._io.read_s2le()
            self.y0 = self._io.read_s2le()
            self.x1 = self._io.read_s2le()
            self.y1 = self._io.read_s2le()
            self.x2 = self._io.read_s2le()
            self.y2 = self._io.read_s2le()
            self.x3 = self._io.read_s2le()
            self.y3 = self._io.read_s2le()
            self.us0 = self._io.read_s4le()
            self.vt0 = self._io.read_s4le()
            self.us1 = self._io.read_s4le()
            self.vt1 = self._io.read_s4le()
            self.r = self._io.read_u1()
            self.g = self._io.read_u1()
            self.b = self._io.read_u1()
            self.a = self._io.read_u1()
            self.alpha_a = self._io.read_u1()
            self.alpha_b = self._io.read_u1()
            self.alpha_c = self._io.read_u1()
            self.alpha_d = self._io.read_u1()
            self.alpha_fix = self._io.read_u1()
            self.test_ate = self._io.read_u1()
            self.test_atst = self._io.read_u1()
            self.test_aref = self._io.read_u1()
            self.test_afail = self._io.read_u1()
            self.test_date = self._io.read_u1()
            self.test_datm = self._io.read_u1()
            self.test_zte = self._io.read_u1()
            self.test_ztst = self._io.read_u1()
            self.pad = []
            for i in range(3):
                self.pad.append(self._io.read_u1())

            self.otp = self._io.read_s2le()
            self.status = self._io.read_s2le()


        def _fetch_instances(self):
            pass
            self.ap._fetch_instances()
            for i in range(len(self.pad)):
                pass



    class PlayingInfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.PlayingInfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.stage = self._io.read_u1()
            self.enemy_off = self._io.read_u1()
            self.voice_off = self._io.read_u1()
            self.memo_select = self._io.read_u1()
            self.clear_end_kind = self._io.read_u1()
            self.clear_end_number = self._io.read_u1()
            self.rank = self._io.read_u1()
            self.game_stage = self._io.read_u1()
            self.hidden_item_get = self._io.read_u1()
            self.spray_pow = self._io.read_s1()
            self.savecount = self._io.read_u2le()
            self.clearcount = self._io.read_u2le()
            self.item_get = self._io.read_u2le()
            self.kill_by_shot = self._io.read_u2le()
            self.kill_by_fight = self._io.read_u2le()
            self.time = self._io.read_f4le()
            self.walk_distance = self._io.read_f4le()
            self.run_distance = self._io.read_f4le()
            self.boat_clear_time = self._io.read_f4le()
            self.boat_max_speed = self._io.read_f4le()
            self.jms_damage_total = self._io.read_f4le()
            self.mar_damage_by_enemy = self._io.read_f4le()
            self.mar_damage_by_jms = self._io.read_f4le()
            self.stage_check_point = []
            for i in range(7):
                self.stage_check_point.append(self._io.read_f4le())

            self.stage_score = []
            for i in range(7):
                self.stage_score.append(self._io.read_u4le())

            self.total_score = self._io.read_u4le()
            self.total_time = self._io.read_f4le()
            self.battle_level = self._io.read_u1()
            self.riddle_level = self._io.read_u1()
            self.brightness_level = self._io.read_u1()
            self.screen_position_x = self._io.read_s1()
            self.screen_position_y = self._io.read_s1()
            self.vibration = self._io.read_u1()
            self.auto_load = self._io.read_u1()
            self.sound = self._io.read_u1()
            self.bgm_volume = self._io.read_u1()
            self.se_volume = self._io.read_u1()
            self.weapon_control = self._io.read_u1()
            self.blood_color = self._io.read_u1()
            self.view_control = self._io.read_u1()
            self.retreat_turn = self._io.read_u1()
            self.walk_run_control = self._io.read_u1()
            self.auto_aiming = self._io.read_u1()
            self.view_mode = self._io.read_u1()
            self.bullet_adjust = self._io.read_u1()
            self.language = self._io.read_u1()
            self.subtitles = self._io.read_u1()
            self.control_type = self._io.read_u1()
            self.radar = self._io.read_u1()
            self._unnamed49 = self._io.read_bytes(2)


        def _fetch_instances(self):
            pass
            for i in range(len(self.stage_check_point)):
                pass

            for i in range(len(self.stage_score)):
                pass



    class Pointer(KaitaiStruct):
        def __init__(self, to, _io, _parent=None, _root=None):
            super(Sh2.Pointer, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self.to = to
            self._read()

        def _read(self):
            self.address = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class PssCommonWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.PssCommonWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.mpeg_workp = Sh2.Pointer(u"data", self._io, self, self._root)
            self.read_bufp = Sh2.Pointer(u"read_buf", self._io, self, self._root)
            self.vi_buf_datap = Sh2.Pointer(u"data", self._io, self, self._root)
            self._unnamed3 = self._io.read_bytes(52)
            self.time_stamp = []
            for i in range(512):
                self.time_stamp.append(Sh2.TimeStamp(self._io, self, self._root))

            self.vo_buf_datap = Sh2.Pointer(u"vo_data", self._io, self, self._root)
            self._unnamed6 = self._io.read_bytes(60)
            self.audio_buff = []
            for i in range(49152):
                self.audio_buff.append(self._io.read_u1())

            self.tag_inter_datap = Sh2.Pointer(u"data", self._io, self, self._root)
            self.video_dec_th = self._io.read_s4le()
            self.default_th = self._io.read_s4le()
            self._unnamed11 = self._io.read_bytes(52)
            self.def_stack = []
            for i in range(2048):
                self.def_stack.append(self._io.read_s1())

            self.video_dec_stack = []
            for i in range(16384):
                self.video_dec_stack.append(self._io.read_s1())

            self.db = Sh2.SceGsDbuff(self._io, self, self._root)
            self._unnamed15 = self._io.read_bytes(16)


        def _fetch_instances(self):
            pass
            self.mpeg_workp._fetch_instances()
            self.read_bufp._fetch_instances()
            self.vi_buf_datap._fetch_instances()
            for i in range(len(self.time_stamp)):
                pass
                self.time_stamp[i]._fetch_instances()

            self.vo_buf_datap._fetch_instances()
            for i in range(len(self.audio_buff)):
                pass

            self.tag_inter_datap._fetch_instances()
            for i in range(len(self.def_stack)):
                pass

            for i in range(len(self.video_dec_stack)):
                pass

            self.db._fetch_instances()


    class PssMessageTime(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.PssMessageTime, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.start = self._io.read_u2le()
            self.end = self._io.read_u2le()


        def _fetch_instances(self):
            pass


    class PssSubtitleCtrl(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.PssSubtitleCtrl, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.msg_start = self._io.read_s4le()
            self.msg_no = self._io.read_s4le()
            self.msg_bufp = Sh2.Pointer(u"data", self._io, self, self._root)
            self.adr_msg_time = Sh2.Pointer(u"pss_message_time", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.msg_bufp._fetch_instances()
            self.adr_msg_time._fetch_instances()


    class Q(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Q, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._unnamed0 = self._io.read_bytes(16)


        def _fetch_instances(self):
            pass
            _ = self.fv
            if hasattr(self, '_m_fv'):
                pass
                for i in range(len(self._m_fv)):
                    pass


            _ = self.iv
            if hasattr(self, '_m_iv'):
                pass
                for i in range(len(self._m_iv)):
                    pass


            _ = self.q
            if hasattr(self, '_m_q'):
                pass
                for i in range(len(self._m_q)):
                    pass


            _ = self.s16
            if hasattr(self, '_m_s16'):
                pass
                for i in range(len(self._m_s16)):
                    pass


            _ = self.s32
            if hasattr(self, '_m_s32'):
                pass
                for i in range(len(self._m_s32)):
                    pass


            _ = self.s64
            if hasattr(self, '_m_s64'):
                pass
                for i in range(len(self._m_s64)):
                    pass


            _ = self.s8
            if hasattr(self, '_m_s8'):
                pass
                for i in range(len(self._m_s8)):
                    pass


            _ = self.u128
            if hasattr(self, '_m_u128'):
                pass
                self._m_u128._fetch_instances()

            _ = self.u16
            if hasattr(self, '_m_u16'):
                pass
                for i in range(len(self._m_u16)):
                    pass


            _ = self.u32
            if hasattr(self, '_m_u32'):
                pass
                for i in range(len(self._m_u32)):
                    pass


            _ = self.u64
            if hasattr(self, '_m_u64'):
                pass
                for i in range(len(self._m_u64)):
                    pass


            _ = self.u8
            if hasattr(self, '_m_u8'):
                pass
                for i in range(len(self._m_u8)):
                    pass



        @property
        def fv(self):
            if hasattr(self, '_m_fv'):
                return self._m_fv

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_fv = []
            for i in range(4):
                self._m_fv.append(self._io.read_f4le())

            self._io.seek(_pos)
            return getattr(self, '_m_fv', None)

        @property
        def iv(self):
            if hasattr(self, '_m_iv'):
                return self._m_iv

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_iv = []
            for i in range(4):
                self._m_iv.append(self._io.read_s4le())

            self._io.seek(_pos)
            return getattr(self, '_m_iv', None)

        @property
        def q(self):
            if hasattr(self, '_m_q'):
                return self._m_q

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_q = []
            for i in range(4):
                self._m_q.append(self._io.read_s4le())

            self._io.seek(_pos)
            return getattr(self, '_m_q', None)

        @property
        def s16(self):
            if hasattr(self, '_m_s16'):
                return self._m_s16

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_s16 = []
            for i in range(8):
                self._m_s16.append(self._io.read_s2le())

            self._io.seek(_pos)
            return getattr(self, '_m_s16', None)

        @property
        def s32(self):
            if hasattr(self, '_m_s32'):
                return self._m_s32

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_s32 = []
            for i in range(4):
                self._m_s32.append(self._io.read_s4le())

            self._io.seek(_pos)
            return getattr(self, '_m_s32', None)

        @property
        def s64(self):
            if hasattr(self, '_m_s64'):
                return self._m_s64

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_s64 = []
            for i in range(2):
                self._m_s64.append(self._io.read_s8le())

            self._io.seek(_pos)
            return getattr(self, '_m_s64', None)

        @property
        def s8(self):
            if hasattr(self, '_m_s8'):
                return self._m_s8

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_s8 = []
            for i in range(16):
                self._m_s8.append(self._io.read_s1())

            self._io.seek(_pos)
            return getattr(self, '_m_s8', None)

        @property
        def u128(self):
            if hasattr(self, '_m_u128'):
                return self._m_u128

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_u128 = Sh2.U16(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_u128', None)

        @property
        def u16(self):
            if hasattr(self, '_m_u16'):
                return self._m_u16

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_u16 = []
            for i in range(8):
                self._m_u16.append(self._io.read_u2le())

            self._io.seek(_pos)
            return getattr(self, '_m_u16', None)

        @property
        def u32(self):
            if hasattr(self, '_m_u32'):
                return self._m_u32

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_u32 = []
            for i in range(4):
                self._m_u32.append(self._io.read_u4le())

            self._io.seek(_pos)
            return getattr(self, '_m_u32', None)

        @property
        def u64(self):
            if hasattr(self, '_m_u64'):
                return self._m_u64

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_u64 = []
            for i in range(2):
                self._m_u64.append(self._io.read_u8le())

            self._io.seek(_pos)
            return getattr(self, '_m_u64', None)

        @property
        def u8(self):
            if hasattr(self, '_m_u8'):
                return self._m_u8

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_u8 = []
            for i in range(16):
                self._m_u8.append(self._io.read_u1())

            self._io.seek(_pos)
            return getattr(self, '_m_u8', None)


    class QWorddata(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.QWorddata, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._unnamed0 = self._io.read_bytes(16)


        def _fetch_instances(self):
            pass
            _ = self.fl32
            if hasattr(self, '_m_fl32'):
                pass
                for i in range(len(self._m_fl32)):
                    pass


            _ = self.sc8
            if hasattr(self, '_m_sc8'):
                pass
                for i in range(len(self._m_sc8)):
                    pass


            _ = self.si32
            if hasattr(self, '_m_si32'):
                pass
                for i in range(len(self._m_si32)):
                    pass


            _ = self.ss16
            if hasattr(self, '_m_ss16'):
                pass
                for i in range(len(self._m_ss16)):
                    pass


            _ = self.uc8
            if hasattr(self, '_m_uc8'):
                pass
                for i in range(len(self._m_uc8)):
                    pass


            _ = self.ui32
            if hasattr(self, '_m_ui32'):
                pass
                for i in range(len(self._m_ui32)):
                    pass


            _ = self.ul128
            if hasattr(self, '_m_ul128'):
                pass
                self._m_ul128._fetch_instances()

            _ = self.ul64
            if hasattr(self, '_m_ul64'):
                pass
                for i in range(len(self._m_ul64)):
                    pass


            _ = self.us16
            if hasattr(self, '_m_us16'):
                pass
                for i in range(len(self._m_us16)):
                    pass



        @property
        def fl32(self):
            if hasattr(self, '_m_fl32'):
                return self._m_fl32

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_fl32 = []
            for i in range(4):
                self._m_fl32.append(self._io.read_f4le())

            self._io.seek(_pos)
            return getattr(self, '_m_fl32', None)

        @property
        def sc8(self):
            if hasattr(self, '_m_sc8'):
                return self._m_sc8

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_sc8 = []
            for i in range(16):
                self._m_sc8.append(self._io.read_s1())

            self._io.seek(_pos)
            return getattr(self, '_m_sc8', None)

        @property
        def si32(self):
            if hasattr(self, '_m_si32'):
                return self._m_si32

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_si32 = []
            for i in range(4):
                self._m_si32.append(self._io.read_s4le())

            self._io.seek(_pos)
            return getattr(self, '_m_si32', None)

        @property
        def ss16(self):
            if hasattr(self, '_m_ss16'):
                return self._m_ss16

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_ss16 = []
            for i in range(8):
                self._m_ss16.append(self._io.read_s2le())

            self._io.seek(_pos)
            return getattr(self, '_m_ss16', None)

        @property
        def uc8(self):
            if hasattr(self, '_m_uc8'):
                return self._m_uc8

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_uc8 = []
            for i in range(16):
                self._m_uc8.append(self._io.read_u1())

            self._io.seek(_pos)
            return getattr(self, '_m_uc8', None)

        @property
        def ui32(self):
            if hasattr(self, '_m_ui32'):
                return self._m_ui32

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_ui32 = []
            for i in range(4):
                self._m_ui32.append(self._io.read_u4le())

            self._io.seek(_pos)
            return getattr(self, '_m_ui32', None)

        @property
        def ul128(self):
            if hasattr(self, '_m_ul128'):
                return self._m_ul128

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_ul128 = Sh2.U16(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_ul128', None)

        @property
        def ul64(self):
            if hasattr(self, '_m_ul64'):
                return self._m_ul64

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_ul64 = []
            for i in range(2):
                self._m_ul64.append(self._io.read_u8le())

            self._io.seek(_pos)
            return getattr(self, '_m_ul64', None)

        @property
        def us16(self):
            if hasattr(self, '_m_us16'):
                return self._m_us16

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_us16 = []
            for i in range(8):
                self._m_us16.append(self._io.read_u2le())

            self._io.seek(_pos)
            return getattr(self, '_m_us16', None)


    class Qword(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Qword, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._unnamed0 = self._io.read_bytes(16)


        def _fetch_instances(self):
            pass
            _ = self.c
            if hasattr(self, '_m_c'):
                pass
                for i in range(len(self._m_c)):
                    pass


            _ = self.i
            if hasattr(self, '_m_i'):
                pass
                for i in range(len(self._m_i)):
                    pass


            _ = self.l
            if hasattr(self, '_m_l'):
                pass
                for i in range(len(self._m_l)):
                    pass


            _ = self.q
            if hasattr(self, '_m_q'):
                pass
                self._m_q._fetch_instances()

            _ = self.s
            if hasattr(self, '_m_s'):
                pass
                for i in range(len(self._m_s)):
                    pass



        @property
        def c(self):
            if hasattr(self, '_m_c'):
                return self._m_c

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_c = []
            for i in range(16):
                self._m_c.append(self._io.read_u1())

            self._io.seek(_pos)
            return getattr(self, '_m_c', None)

        @property
        def i(self):
            if hasattr(self, '_m_i'):
                return self._m_i

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_i = []
            for i in range(4):
                self._m_i.append(self._io.read_u4le())

            self._io.seek(_pos)
            return getattr(self, '_m_i', None)

        @property
        def l(self):
            if hasattr(self, '_m_l'):
                return self._m_l

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_l = []
            for i in range(2):
                self._m_l.append(self._io.read_u8le())

            self._io.seek(_pos)
            return getattr(self, '_m_l', None)

        @property
        def q(self):
            if hasattr(self, '_m_q'):
                return self._m_q

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_q = Sh2.U16(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_q', None)

        @property
        def s(self):
            if hasattr(self, '_m_s'):
                return self._m_s

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_s = []
            for i in range(8):
                self._m_s.append(self._io.read_u2le())

            self._io.seek(_pos)
            return getattr(self, '_m_s', None)


    class RadioData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.RadioData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.se_call = self._io.read_s4le()
            self.event = self._io.read_s4le()
            self._unnamed2 = self._io.read_bytes(8)
            self.track = []
            for i in range(4):
                self.track.append(self._io.read_f4le())

            self.pan = []
            for i in range(4):
                self.pan.append(self._io.read_f4le())

            self.volume = self._io.read_f4le()
            self._unnamed6 = self._io.read_bytes(12)
            self.pos = []
            for i in range(4):
                self.pos.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.track)):
                pass

            for i in range(len(self.pan)):
                pass

            for i in range(len(self.pos)):
                pass



    class ReadBuf(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ReadBuf, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.data = []
            for i in range(327680):
                self.data.append(self._io.read_u1())

            self.put = self._io.read_s4le()
            self.count = self._io.read_s4le()
            self.size = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.data)):
                pass



    class SceCdClock(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceCdClock, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.stat = self._io.read_u1()
            self.second = self._io.read_u1()
            self.minute = self._io.read_u1()
            self.hour = self._io.read_u1()
            self.pad = self._io.read_u1()
            self.day = self._io.read_u1()
            self.month = self._io.read_u1()
            self.year = self._io.read_u1()


        def _fetch_instances(self):
            pass


    class SceCdRmode(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceCdRmode, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.trycount = self._io.read_u1()
            self.spindlctrl = self._io.read_u1()
            self.datapattern = self._io.read_u1()
            self.pad = self._io.read_u1()


        def _fetch_instances(self):
            pass


    class SceCdlFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceCdlFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.lsn = self._io.read_u4le()
            self.size = self._io.read_u4le()
            self.name = []
            for i in range(16):
                self.name.append(self._io.read_s1())

            self.date = []
            for i in range(8):
                self.date.append(self._io.read_u1())

            self.flag = self._io.read_u4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.name)):
                pass

            for i in range(len(self.date)):
                pass



    class SceDmaChan(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceDmaChan, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.chcr = Sh2.TDchcr(self._io, self, self._root)
            self.p0 = []
            for i in range(3):
                self.p0.append(self._io.read_u4le())

            self.madr = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p1 = []
            for i in range(3):
                self.p1.append(self._io.read_u4le())

            self.qwc = self._io.read_u4le()
            self.p2 = []
            for i in range(3):
                self.p2.append(self._io.read_u4le())

            self.tadr = Sh2.Pointer(u"sce_dma_tag", self._io, self, self._root)
            self.p3 = []
            for i in range(3):
                self.p3.append(self._io.read_u4le())

            self.as0 = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p4 = []
            for i in range(3):
                self.p4.append(self._io.read_u4le())

            self.as1 = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p5 = []
            for i in range(3):
                self.p5.append(self._io.read_u4le())

            self.p6 = []
            for i in range(4):
                self.p6.append(self._io.read_u4le())

            self.p7 = []
            for i in range(4):
                self.p7.append(self._io.read_u4le())

            self.sadr = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p8 = []
            for i in range(3):
                self.p8.append(self._io.read_u4le())



        def _fetch_instances(self):
            pass
            self.chcr._fetch_instances()
            for i in range(len(self.p0)):
                pass

            self.madr._fetch_instances()
            for i in range(len(self.p1)):
                pass

            for i in range(len(self.p2)):
                pass

            self.tadr._fetch_instances()
            for i in range(len(self.p3)):
                pass

            self.as0._fetch_instances()
            for i in range(len(self.p4)):
                pass

            self.as1._fetch_instances()
            for i in range(len(self.p5)):
                pass

            for i in range(len(self.p6)):
                pass

            for i in range(len(self.p7)):
                pass

            self.sadr._fetch_instances()
            for i in range(len(self.p8)):
                pass



    class SceDmaEnv(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceDmaEnv, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.sts = self._io.read_u1()
            self.std = self._io.read_u1()
            self.mfd = self._io.read_u1()
            self.rcycle = self._io.read_u1()
            self.express = self._io.read_u2le()
            self.notify = self._io.read_u2le()
            self.sqwc = self._io.read_u2le()
            self.tqwc = self._io.read_u2le()
            self.rbadr = Sh2.Pointer(u"data", self._io, self, self._root)
            self.rbmsk = self._io.read_u4le()


        def _fetch_instances(self):
            pass
            self.rbadr._fetch_instances()


    class SceDmaTag(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceDmaTag, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.qwc = self._io.read_u2le()
            self.mark = self._io.read_u1()
            self.id = self._io.read_u1()
            self.next = Sh2.Pointer(u"sce_dma_tag", self._io, self, self._root)
            self.p = []
            for i in range(2):
                self.p.append(self._io.read_u4le())



        def _fetch_instances(self):
            pass
            self.next._fetch_instances()
            for i in range(len(self.p)):
                pass



    class SceGifPackAd(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGifPackAd, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.data = self._io.read_u8le()
            self.addr = self._io.read_u8le()


        def _fetch_instances(self):
            pass


    class SceGifPackFog(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGifPackFog, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pad = []
            for i in range(3):
                self.pad.append(self._io.read_u4le())

            self.f = self._io.read_u4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.pad)):
                pass



    class SceGifPackNop(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGifPackNop, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pad = []
            for i in range(2):
                self.pad.append(self._io.read_u8le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.pad)):
                pass



    class SceGifPackRgbaq(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGifPackRgbaq, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.r = self._io.read_u4le()
            self.g = self._io.read_u4le()
            self.b = self._io.read_u4le()
            self.a = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class SceGifPackSt(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGifPackSt, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.s = self._io.read_f4le()
            self.t = self._io.read_f4le()
            self.q = self._io.read_f4le()
            self.pad96 = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class SceGifPackUv(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGifPackUv, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.u = self._io.read_s4le()
            self.v = self._io.read_s4le()
            self.pad64 = self._io.read_s8le()


        def _fetch_instances(self):
            pass


    class SceGifPackXyz(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGifPackXyz, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x = self._io.read_s4le()
            self.y = self._io.read_s4le()
            self.z = self._io.read_u4le()
            self.pad96 = self._io.read_bits_int_le(15)
            self.adc = self._io.read_bits_int_le(1) != 0
            self.pad112 = Sh2.U16(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.pad112._fetch_instances()


    class SceGifPackXyzf(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGifPackXyzf, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x = self._io.read_s4le()
            self.y = self._io.read_s4le()
            self.z = self._io.read_u4le()
            self.f = self._io.read_bits_int_le(12)
            self.pad108 = self._io.read_bits_int_le(3)
            self.adc = self._io.read_bits_int_le(1) != 0
            self.pad112 = Sh2.U16(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.pad112._fetch_instances()


    class SceGifTag(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGifTag, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.nloop = self._io.read_bits_int_le(15)
            self.eop = self._io.read_bits_int_le(1) != 0
            self.pad16 = Sh2.U16(self._io, self, self._root)
            self.id = self._io.read_bits_int_le(14)
            self.pre = self._io.read_bits_int_le(1) != 0
            self.prim = self._io.read_bits_int_le(11)
            self.flg = self._io.read_bits_int_le(2)
            self.nreg = self._io.read_bits_int_le(4)
            self.regs0 = self._io.read_bits_int_le(4)
            self.regs1 = self._io.read_bits_int_le(4)
            self.regs2 = self._io.read_bits_int_le(4)
            self.regs3 = self._io.read_bits_int_le(4)
            self.regs4 = self._io.read_bits_int_le(4)
            self.regs5 = self._io.read_bits_int_le(4)
            self.regs6 = self._io.read_bits_int_le(4)
            self.regs7 = self._io.read_bits_int_le(4)
            self.regs8 = self._io.read_bits_int_le(4)
            self.regs9 = self._io.read_bits_int_le(4)
            self.regs10 = self._io.read_bits_int_le(4)
            self.regs11 = self._io.read_bits_int_le(4)
            self.regs12 = self._io.read_bits_int_le(4)
            self.regs13 = self._io.read_bits_int_le(4)
            self.regs14 = self._io.read_bits_int_le(4)
            self.regs15 = self._io.read_bits_int_le(4)


        def _fetch_instances(self):
            pass
            self.pad16._fetch_instances()


    class SceGsAlpha(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsAlpha, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.a = self._io.read_bits_int_le(2)
            self.b = self._io.read_bits_int_le(2)
            self.c = self._io.read_bits_int_le(2)
            self.d = self._io.read_bits_int_le(2)
            self.pad8 = self._io.read_bits_int_le(24)
            self.fix = self._io.read_bits_int_le(8)
            self.pad40 = self._io.read_bits_int_le(24)


        def _fetch_instances(self):
            pass


    class SceGsAlphaEnv(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsAlphaEnv, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.alpha1 = Sh2.SceGsAlpha(self._io, self, self._root)
            self.alpha1addr = self._io.read_s8le()
            self.pabe = Sh2.SceGsPabe(self._io, self, self._root)
            self.pabeaddr = self._io.read_s8le()
            self.texa = Sh2.SceGsTexa(self._io, self, self._root)
            self.texaaddr = self._io.read_s8le()
            self.fba1 = Sh2.SceGsFba(self._io, self, self._root)
            self.fba1addr = self._io.read_s8le()


        def _fetch_instances(self):
            pass
            self.alpha1._fetch_instances()
            self.pabe._fetch_instances()
            self.texa._fetch_instances()
            self.fba1._fetch_instances()


    class SceGsAlphaEnv2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsAlphaEnv2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.alpha2 = Sh2.SceGsAlpha(self._io, self, self._root)
            self.alpha2addr = self._io.read_s8le()
            self.pabe = Sh2.SceGsPabe(self._io, self, self._root)
            self.pabeaddr = self._io.read_s8le()
            self.texa = Sh2.SceGsTexa(self._io, self, self._root)
            self.texaaddr = self._io.read_s8le()
            self.fba2 = Sh2.SceGsFba(self._io, self, self._root)
            self.fba2addr = self._io.read_s8le()


        def _fetch_instances(self):
            pass
            self.alpha2._fetch_instances()
            self.pabe._fetch_instances()
            self.texa._fetch_instances()
            self.fba2._fetch_instances()


    class SceGsBitbltbuf(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsBitbltbuf, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.sbp = self._io.read_bits_int_le(14)
            self.pad14 = self._io.read_bits_int_le(2)
            self.sbw = self._io.read_bits_int_le(6)
            self.pad22 = self._io.read_bits_int_le(2)
            self.spsm = self._io.read_bits_int_le(6)
            self.pad30 = self._io.read_bits_int_le(2)
            self.dbp = self._io.read_bits_int_le(14)
            self.pad46 = self._io.read_bits_int_le(2)
            self.dbw = self._io.read_bits_int_le(6)
            self.pad54 = self._io.read_bits_int_le(2)
            self.dpsm = self._io.read_bits_int_le(6)
            self.pad62 = self._io.read_bits_int_le(2)


        def _fetch_instances(self):
            pass


    class SceGsClamp(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsClamp, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.wms = self._io.read_bits_int_le(2)
            self.wmt = self._io.read_bits_int_le(2)
            self.minu = self._io.read_bits_int_le(10)
            self.maxu = self._io.read_bits_int_le(10)
            self.minv = self._io.read_bits_int_le(10)
            self.maxv = self._io.read_bits_int_le(10)
            self.pad44 = self._io.read_bits_int_le(20)


        def _fetch_instances(self):
            pass


    class SceGsClear(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsClear, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.testa = Sh2.SceGsTest(self._io, self, self._root)
            self.testaaddr = self._io.read_s8le()
            self.prim = Sh2.SceGsPrim(self._io, self, self._root)
            self.primaddr = self._io.read_s8le()
            self.rgbaq = Sh2.SceGsRgbaq(self._io, self, self._root)
            self.rgbaqaddr = self._io.read_s8le()
            self.xyz2a = Sh2.SceGsXyz(self._io, self, self._root)
            self.xyz2aaddr = self._io.read_s8le()
            self.xyz2b = Sh2.SceGsXyz(self._io, self, self._root)
            self.xyz2baddr = self._io.read_s8le()
            self.testb = Sh2.SceGsTest(self._io, self, self._root)
            self.testbaddr = self._io.read_s8le()


        def _fetch_instances(self):
            pass
            self.testa._fetch_instances()
            self.prim._fetch_instances()
            self.rgbaq._fetch_instances()
            self.xyz2a._fetch_instances()
            self.xyz2b._fetch_instances()
            self.testb._fetch_instances()


    class SceGsColclamp(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsColclamp, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.clamp = self._io.read_bits_int_le(1) != 0
            self.pad01 = self._io.read_bits_int_le(63)


        def _fetch_instances(self):
            pass


    class SceGsDbuff(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsDbuff, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.disp = []
            for i in range(2):
                self.disp.append(Sh2.SceGsDispEnv(self._io, self, self._root))

            self.giftag0 = Sh2.SceGifTag(self._io, self, self._root)
            self.draw0 = Sh2.SceGsDrawEnv1(self._io, self, self._root)
            self.clear0 = Sh2.SceGsClear(self._io, self, self._root)
            self.giftag1 = Sh2.SceGifTag(self._io, self, self._root)
            self.draw1 = Sh2.SceGsDrawEnv1(self._io, self, self._root)
            self.clear1 = Sh2.SceGsClear(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            for i in range(len(self.disp)):
                pass
                self.disp[i]._fetch_instances()

            self.giftag0._fetch_instances()
            self.draw0._fetch_instances()
            self.clear0._fetch_instances()
            self.giftag1._fetch_instances()
            self.draw1._fetch_instances()
            self.clear1._fetch_instances()


    class SceGsDbuffDc(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsDbuffDc, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.disp = []
            for i in range(2):
                self.disp.append(Sh2.SceGsDispEnv(self._io, self, self._root))

            self.giftag0 = Sh2.SceGifTag(self._io, self, self._root)
            self.draw01 = Sh2.SceGsDrawEnv1(self._io, self, self._root)
            self.draw02 = Sh2.SceGsDrawEnv2(self._io, self, self._root)
            self.clear0 = Sh2.SceGsClear(self._io, self, self._root)
            self.giftag1 = Sh2.SceGifTag(self._io, self, self._root)
            self.draw11 = Sh2.SceGsDrawEnv1(self._io, self, self._root)
            self.draw12 = Sh2.SceGsDrawEnv2(self._io, self, self._root)
            self.clear1 = Sh2.SceGsClear(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            for i in range(len(self.disp)):
                pass
                self.disp[i]._fetch_instances()

            self.giftag0._fetch_instances()
            self.draw01._fetch_instances()
            self.draw02._fetch_instances()
            self.clear0._fetch_instances()
            self.giftag1._fetch_instances()
            self.draw11._fetch_instances()
            self.draw12._fetch_instances()
            self.clear1._fetch_instances()


    class SceGsDimx(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsDimx, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.dimx00 = self._io.read_bits_int_le(3)
            self.pad00 = self._io.read_bits_int_le(1) != 0
            self.dimx01 = self._io.read_bits_int_le(3)
            self.pad01 = self._io.read_bits_int_le(1) != 0
            self.dimx02 = self._io.read_bits_int_le(3)
            self.pad02 = self._io.read_bits_int_le(1) != 0
            self.dimx03 = self._io.read_bits_int_le(3)
            self.pad03 = self._io.read_bits_int_le(1) != 0
            self.dimx10 = self._io.read_bits_int_le(3)
            self.pad10 = self._io.read_bits_int_le(1) != 0
            self.dimx11 = self._io.read_bits_int_le(3)
            self.pad11 = self._io.read_bits_int_le(1) != 0
            self.dimx12 = self._io.read_bits_int_le(3)
            self.pad12 = self._io.read_bits_int_le(1) != 0
            self.dimx13 = self._io.read_bits_int_le(3)
            self.pad13 = self._io.read_bits_int_le(1) != 0
            self.dimx20 = self._io.read_bits_int_le(3)
            self.pad20 = self._io.read_bits_int_le(1) != 0
            self.dimx21 = self._io.read_bits_int_le(3)
            self.pad21 = self._io.read_bits_int_le(1) != 0
            self.dimx22 = self._io.read_bits_int_le(3)
            self.pad22 = self._io.read_bits_int_le(1) != 0
            self.dimx23 = self._io.read_bits_int_le(3)
            self.pad23 = self._io.read_bits_int_le(1) != 0
            self.dimx30 = self._io.read_bits_int_le(3)
            self.pad30 = self._io.read_bits_int_le(1) != 0
            self.dimx31 = self._io.read_bits_int_le(3)
            self.pad31 = self._io.read_bits_int_le(1) != 0
            self.dimx32 = self._io.read_bits_int_le(3)
            self.pad32 = self._io.read_bits_int_le(1) != 0
            self.dimx33 = self._io.read_bits_int_le(3)
            self.pad33 = self._io.read_bits_int_le(1) != 0


        def _fetch_instances(self):
            pass


    class SceGsDispEnv(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsDispEnv, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pmode = Sh2.TGsPmode(self._io, self, self._root)
            self.smode2 = Sh2.TGsSmode2(self._io, self, self._root)
            self.dispfb = Sh2.TGsDispfb2(self._io, self, self._root)
            self.display = Sh2.TGsDisplay2(self._io, self, self._root)
            self.bgcolor = Sh2.TGsBgcolor(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.pmode._fetch_instances()
            self.smode2._fetch_instances()
            self.dispfb._fetch_instances()
            self.display._fetch_instances()
            self.bgcolor._fetch_instances()


    class SceGsDrawEnv1(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsDrawEnv1, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.frame1 = Sh2.SceGsFrame(self._io, self, self._root)
            self.frame1addr = self._io.read_u8le()
            self.zbuf1 = Sh2.SceGsZbuf(self._io, self, self._root)
            self.zbuf1addr = self._io.read_s8le()
            self.xyoffset1 = Sh2.SceGsXyoffset(self._io, self, self._root)
            self.xyoffset1addr = self._io.read_s8le()
            self.scissor1 = Sh2.SceGsScissor(self._io, self, self._root)
            self.scissor1addr = self._io.read_s8le()
            self.prmodecont = Sh2.SceGsPrmodecont(self._io, self, self._root)
            self.prmodecontaddr = self._io.read_s8le()
            self.colclamp = Sh2.SceGsColclamp(self._io, self, self._root)
            self.colclampaddr = self._io.read_s8le()
            self.dthe = Sh2.SceGsDthe(self._io, self, self._root)
            self.dtheaddr = self._io.read_s8le()
            self.test1 = Sh2.SceGsTest(self._io, self, self._root)
            self.test1addr = self._io.read_s8le()


        def _fetch_instances(self):
            pass
            self.frame1._fetch_instances()
            self.zbuf1._fetch_instances()
            self.xyoffset1._fetch_instances()
            self.scissor1._fetch_instances()
            self.prmodecont._fetch_instances()
            self.colclamp._fetch_instances()
            self.dthe._fetch_instances()
            self.test1._fetch_instances()


    class SceGsDrawEnv2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsDrawEnv2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.frame2 = Sh2.SceGsFrame(self._io, self, self._root)
            self.frame2addr = self._io.read_u8le()
            self.zbuf2 = Sh2.SceGsZbuf(self._io, self, self._root)
            self.zbuf2addr = self._io.read_s8le()
            self.xyoffset2 = Sh2.SceGsXyoffset(self._io, self, self._root)
            self.xyoffset2addr = self._io.read_s8le()
            self.scissor2 = Sh2.SceGsScissor(self._io, self, self._root)
            self.scissor2addr = self._io.read_s8le()
            self.prmodecont = Sh2.SceGsPrmodecont(self._io, self, self._root)
            self.prmodecontaddr = self._io.read_s8le()
            self.colclamp = Sh2.SceGsColclamp(self._io, self, self._root)
            self.colclampaddr = self._io.read_s8le()
            self.dthe = Sh2.SceGsDthe(self._io, self, self._root)
            self.dtheaddr = self._io.read_s8le()
            self.test2 = Sh2.SceGsTest(self._io, self, self._root)
            self.test2addr = self._io.read_s8le()


        def _fetch_instances(self):
            pass
            self.frame2._fetch_instances()
            self.zbuf2._fetch_instances()
            self.xyoffset2._fetch_instances()
            self.scissor2._fetch_instances()
            self.prmodecont._fetch_instances()
            self.colclamp._fetch_instances()
            self.dthe._fetch_instances()
            self.test2._fetch_instances()


    class SceGsDthe(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsDthe, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.dthe = self._io.read_bits_int_le(1) != 0
            self.pad01 = self._io.read_bits_int_le(63)


        def _fetch_instances(self):
            pass


    class SceGsFba(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsFba, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.fba = self._io.read_bits_int_le(1) != 0
            self.pad01 = self._io.read_bits_int_le(63)


        def _fetch_instances(self):
            pass


    class SceGsFinish(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsFinish, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pad00 = self._io.read_u8le()


        def _fetch_instances(self):
            pass


    class SceGsFog(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsFog, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pad00 = self._io.read_bits_int_le(56)
            self.f = self._io.read_bits_int_le(8)


        def _fetch_instances(self):
            pass


    class SceGsFogcol(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsFogcol, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.fcr = self._io.read_bits_int_le(8)
            self.fcg = self._io.read_bits_int_le(8)
            self.fcb = self._io.read_bits_int_le(8)
            self.pad24 = self._io.read_bits_int_le(40)


        def _fetch_instances(self):
            pass


    class SceGsFrame(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsFrame, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.fbp = self._io.read_bits_int_le(9)
            self.pad09 = self._io.read_bits_int_le(7)
            self.fbw = self._io.read_bits_int_le(6)
            self.pad22 = self._io.read_bits_int_le(2)
            self.psm = self._io.read_bits_int_le(6)
            self.pad30 = self._io.read_bits_int_le(2)
            self.fbmsk = self._io.read_bits_int_le(32)


        def _fetch_instances(self):
            pass


    class SceGsGparam(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsGparam, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.sce_gs_inter_mode = self._io.read_s2le()
            self.sce_gs_out_mode = self._io.read_s2le()
            self.sce_gs_ff_mode = self._io.read_s2le()
            self.sce_gs_version = self._io.read_s2le()
            self.sce_gs_vs_cfunc = Sh2.Pointer(u"data", self._io, self, self._root)
            self.sce_gs_vs_cid = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.sce_gs_vs_cfunc._fetch_instances()


    class SceGsHwreg(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsHwreg, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.wdata = self._io.read_u8le()


        def _fetch_instances(self):
            pass


    class SceGsLabel(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsLabel, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.id = self._io.read_u4le()
            self.idmsk = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class SceGsLoadImage(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsLoadImage, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.giftag0 = Sh2.SceGifTag(self._io, self, self._root)
            self.bitbltbuf = Sh2.SceGsBitbltbuf(self._io, self, self._root)
            self.bitbltbufaddr = self._io.read_s8le()
            self.trxpos = Sh2.SceGsTrxpos(self._io, self, self._root)
            self.trxposaddr = self._io.read_s8le()
            self.trxreg = Sh2.SceGsTrxreg(self._io, self, self._root)
            self.trxregaddr = self._io.read_s8le()
            self.trxdir = Sh2.SceGsTrxdir(self._io, self, self._root)
            self.trxdiraddr = self._io.read_s8le()
            self.giftag1 = Sh2.SceGifTag(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.giftag0._fetch_instances()
            self.bitbltbuf._fetch_instances()
            self.trxpos._fetch_instances()
            self.trxreg._fetch_instances()
            self.trxdir._fetch_instances()
            self.giftag1._fetch_instances()


    class SceGsMiptbp1(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsMiptbp1, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.tbp1 = self._io.read_bits_int_le(14)
            self.tbw1 = self._io.read_bits_int_le(6)
            self.tbp2 = self._io.read_bits_int_le(14)
            self.tbw2 = self._io.read_bits_int_le(6)
            self.tbp3 = self._io.read_bits_int_le(14)
            self.tbw3 = self._io.read_bits_int_le(6)
            self.pad60 = self._io.read_bits_int_le(4)


        def _fetch_instances(self):
            pass


    class SceGsMiptbp2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsMiptbp2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.tbp4 = self._io.read_bits_int_le(14)
            self.tbw4 = self._io.read_bits_int_le(6)
            self.tbp5 = self._io.read_bits_int_le(14)
            self.tbw5 = self._io.read_bits_int_le(6)
            self.tbp6 = self._io.read_bits_int_le(14)
            self.tbw6 = self._io.read_bits_int_le(6)
            self.pad60 = self._io.read_bits_int_le(4)


        def _fetch_instances(self):
            pass


    class SceGsPabe(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsPabe, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pabe = self._io.read_bits_int_le(1) != 0
            self.pad01 = self._io.read_bits_int_le(63)


        def _fetch_instances(self):
            pass


    class SceGsPrim(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsPrim, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.prim = self._io.read_bits_int_le(3)
            self.iip = self._io.read_bits_int_le(1) != 0
            self.tme = self._io.read_bits_int_le(1) != 0
            self.fge = self._io.read_bits_int_le(1) != 0
            self.abe = self._io.read_bits_int_le(1) != 0
            self.aa1 = self._io.read_bits_int_le(1) != 0
            self.fst = self._io.read_bits_int_le(1) != 0
            self.ctxt = self._io.read_bits_int_le(1) != 0
            self.fix = self._io.read_bits_int_le(1) != 0
            self.pad11 = self._io.read_bits_int_le(53)


        def _fetch_instances(self):
            pass


    class SceGsPrmode(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsPrmode, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pad00 = self._io.read_bits_int_le(3)
            self.iip = self._io.read_bits_int_le(1) != 0
            self.tme = self._io.read_bits_int_le(1) != 0
            self.fge = self._io.read_bits_int_le(1) != 0
            self.abe = self._io.read_bits_int_le(1) != 0
            self.aa1 = self._io.read_bits_int_le(1) != 0
            self.fst = self._io.read_bits_int_le(1) != 0
            self.ctxt = self._io.read_bits_int_le(1) != 0
            self.fix = self._io.read_bits_int_le(1) != 0
            self.pad11 = self._io.read_bits_int_le(53)


        def _fetch_instances(self):
            pass


    class SceGsPrmodecont(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsPrmodecont, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.ac = self._io.read_bits_int_le(1) != 0
            self.pad01 = self._io.read_bits_int_le(63)


        def _fetch_instances(self):
            pass


    class SceGsRgbaq(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsRgbaq, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.r = self._io.read_bits_int_le(8)
            self.g = self._io.read_bits_int_le(8)
            self.b = self._io.read_bits_int_le(8)
            self.a = self._io.read_bits_int_le(8)
            self.q = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class SceGsScanmsk(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsScanmsk, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.msk = self._io.read_bits_int_le(2)
            self.pad02 = self._io.read_bits_int_le(62)


        def _fetch_instances(self):
            pass


    class SceGsScissor(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsScissor, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.scax0 = self._io.read_bits_int_le(11)
            self.pad11 = self._io.read_bits_int_le(5)
            self.scax1 = self._io.read_bits_int_le(11)
            self.pad27 = self._io.read_bits_int_le(5)
            self.scay0 = self._io.read_bits_int_le(11)
            self.pad43 = self._io.read_bits_int_le(5)
            self.scay1 = self._io.read_bits_int_le(11)
            self.pad59 = self._io.read_bits_int_le(5)


        def _fetch_instances(self):
            pass


    class SceGsSignal(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsSignal, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.id = self._io.read_u4le()
            self.idmsk = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class SceGsSt(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsSt, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.s = self._io.read_f4le()
            self.t = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class SceGsStoreImage(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsStoreImage, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.vifcode = []
            for i in range(4):
                self.vifcode.append(self._io.read_u4le())

            self.giftag = Sh2.SceGifTag(self._io, self, self._root)
            self.bitbltbuf = Sh2.SceGsBitbltbuf(self._io, self, self._root)
            self.bitbltbufaddr = self._io.read_s8le()
            self.trxpos = Sh2.SceGsTrxpos(self._io, self, self._root)
            self.trxposaddr = self._io.read_s8le()
            self.trxreg = Sh2.SceGsTrxreg(self._io, self, self._root)
            self.trxregaddr = self._io.read_s8le()
            self.finish = Sh2.SceGsFinish(self._io, self, self._root)
            self.finishaddr = self._io.read_s8le()
            self.trxdir = Sh2.SceGsTrxdir(self._io, self, self._root)
            self.trxdiraddr = self._io.read_s8le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.vifcode)):
                pass

            self.giftag._fetch_instances()
            self.bitbltbuf._fetch_instances()
            self.trxpos._fetch_instances()
            self.trxreg._fetch_instances()
            self.finish._fetch_instances()
            self.trxdir._fetch_instances()


    class SceGsTest(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsTest, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.ate = self._io.read_bits_int_le(1) != 0
            self.atst = self._io.read_bits_int_le(3)
            self.aref = self._io.read_bits_int_le(8)
            self.afail = self._io.read_bits_int_le(2)
            self.date = self._io.read_bits_int_le(1) != 0
            self.datm = self._io.read_bits_int_le(1) != 0
            self.zte = self._io.read_bits_int_le(1) != 0
            self.ztst = self._io.read_bits_int_le(2)
            self.pad19 = self._io.read_bits_int_le(45)


        def _fetch_instances(self):
            pass


    class SceGsTex0(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsTex0, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.tbp0 = self._io.read_bits_int_le(14)
            self.tbw = self._io.read_bits_int_le(6)
            self.psm = self._io.read_bits_int_le(6)
            self.tw = self._io.read_bits_int_le(4)
            self.th = self._io.read_bits_int_le(4)
            self.tcc = self._io.read_bits_int_le(1) != 0
            self.tfx = self._io.read_bits_int_le(2)
            self.cbp = self._io.read_bits_int_le(14)
            self.cpsm = self._io.read_bits_int_le(4)
            self.csm = self._io.read_bits_int_le(1) != 0
            self.csa = self._io.read_bits_int_le(5)
            self.cld = self._io.read_bits_int_le(3)


        def _fetch_instances(self):
            pass


    class SceGsTex1(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsTex1, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.lcm = self._io.read_bits_int_le(1) != 0
            self.pad01 = self._io.read_bits_int_le(1) != 0
            self.mxl = self._io.read_bits_int_le(3)
            self.mmag = self._io.read_bits_int_le(1) != 0
            self.mmin = self._io.read_bits_int_le(3)
            self.mtba = self._io.read_bits_int_le(1) != 0
            self.pad10 = self._io.read_bits_int_le(9)
            self.l = self._io.read_bits_int_le(2)
            self.pad21 = self._io.read_bits_int_le(11)
            self.k = self._io.read_bits_int_le(12)
            self.pad44 = self._io.read_bits_int_le(20)


        def _fetch_instances(self):
            pass


    class SceGsTex2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsTex2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pad00 = self._io.read_bits_int_le(20)
            self.psm = self._io.read_bits_int_le(6)
            self.pad26 = self._io.read_bits_int_le(11)
            self.cbp = self._io.read_bits_int_le(14)
            self.cpsm = self._io.read_bits_int_le(4)
            self.csm = self._io.read_bits_int_le(1) != 0
            self.csa = self._io.read_bits_int_le(5)
            self.cld = self._io.read_bits_int_le(3)


        def _fetch_instances(self):
            pass


    class SceGsTexEnv(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsTexEnv, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.texflush = Sh2.SceGsTexflush(self._io, self, self._root)
            self.texflushaddr = self._io.read_s8le()
            self.tex11 = Sh2.SceGsTex1(self._io, self, self._root)
            self.tex11addr = self._io.read_s8le()
            self.tex01 = Sh2.SceGsTex0(self._io, self, self._root)
            self.tex01addr = self._io.read_s8le()
            self.clamp1 = Sh2.SceGsClamp(self._io, self, self._root)
            self.clamp1addr = self._io.read_s8le()


        def _fetch_instances(self):
            pass
            self.texflush._fetch_instances()
            self.tex11._fetch_instances()
            self.tex01._fetch_instances()
            self.clamp1._fetch_instances()


    class SceGsTexEnv2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsTexEnv2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.texflush = Sh2.SceGsTexflush(self._io, self, self._root)
            self.texflushaddr = self._io.read_s8le()
            self.tex12 = Sh2.SceGsTex1(self._io, self, self._root)
            self.tex12addr = self._io.read_s8le()
            self.tex02 = Sh2.SceGsTex0(self._io, self, self._root)
            self.tex02addr = self._io.read_s8le()
            self.clamp2 = Sh2.SceGsClamp(self._io, self, self._root)
            self.clamp2addr = self._io.read_s8le()


        def _fetch_instances(self):
            pass
            self.texflush._fetch_instances()
            self.tex12._fetch_instances()
            self.tex02._fetch_instances()
            self.clamp2._fetch_instances()


    class SceGsTexa(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsTexa, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.ta0 = self._io.read_bits_int_le(8)
            self.pad08 = self._io.read_bits_int_le(7)
            self.aem = self._io.read_bits_int_le(1) != 0
            self.pad16 = Sh2.U16(self._io, self, self._root)
            self.ta1 = self._io.read_bits_int_le(8)
            self.pad40 = self._io.read_bits_int_le(24)


        def _fetch_instances(self):
            pass
            self.pad16._fetch_instances()


    class SceGsTexclut(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsTexclut, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.cbw = self._io.read_bits_int_le(6)
            self.cou = self._io.read_bits_int_le(6)
            self.cov = self._io.read_bits_int_le(10)
            self.pad22 = self._io.read_bits_int_le(42)


        def _fetch_instances(self):
            pass


    class SceGsTexflush(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsTexflush, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pad00 = self._io.read_u8le()


        def _fetch_instances(self):
            pass


    class SceGsTrxdir(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsTrxdir, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.xdr = self._io.read_bits_int_le(2)
            self.pad02 = self._io.read_bits_int_le(62)


        def _fetch_instances(self):
            pass


    class SceGsTrxpos(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsTrxpos, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.ssax = self._io.read_bits_int_le(11)
            self.pad11 = self._io.read_bits_int_le(5)
            self.ssay = self._io.read_bits_int_le(11)
            self.pad27 = self._io.read_bits_int_le(5)
            self.dsax = self._io.read_bits_int_le(11)
            self.pad43 = self._io.read_bits_int_le(5)
            self.dsay = self._io.read_bits_int_le(11)
            self.dir = self._io.read_bits_int_le(2)
            self.pad61 = self._io.read_bits_int_le(3)


        def _fetch_instances(self):
            pass


    class SceGsTrxreg(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsTrxreg, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.rrw = self._io.read_bits_int_le(12)
            self.pad12 = self._io.read_bits_int_le(20)
            self.rrh = self._io.read_bits_int_le(12)
            self.pad44 = self._io.read_bits_int_le(20)


        def _fetch_instances(self):
            pass


    class SceGsUv(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsUv, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.u = self._io.read_bits_int_le(14)
            self.pad14 = self._io.read_bits_int_le(2)
            self.v = self._io.read_bits_int_le(14)
            self.pad30 = self._io.read_bits_int_le(34)


        def _fetch_instances(self):
            pass


    class SceGsXyoffset(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsXyoffset, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.ofx = Sh2.U16(self._io, self, self._root)
            self.pad16 = Sh2.U16(self._io, self, self._root)
            self.ofy = Sh2.U16(self._io, self, self._root)
            self.pad48 = Sh2.U16(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.ofx._fetch_instances()
            self.pad16._fetch_instances()
            self.ofy._fetch_instances()
            self.pad48._fetch_instances()


    class SceGsXyz(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsXyz, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x = Sh2.U16(self._io, self, self._root)
            self.y = Sh2.U16(self._io, self, self._root)
            self.z = self._io.read_bits_int_le(32)


        def _fetch_instances(self):
            pass
            self.x._fetch_instances()
            self.y._fetch_instances()


    class SceGsXyzf(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsXyzf, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x = Sh2.U16(self._io, self, self._root)
            self.y = Sh2.U16(self._io, self, self._root)
            self.z = self._io.read_bits_int_le(24)
            self.f = self._io.read_bits_int_le(8)


        def _fetch_instances(self):
            pass
            self.x._fetch_instances()
            self.y._fetch_instances()


    class SceGsZbuf(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceGsZbuf, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.zbp = self._io.read_bits_int_le(9)
            self.pad09 = self._io.read_bits_int_le(15)
            self.psm = self._io.read_bits_int_le(4)
            self.pad28 = self._io.read_bits_int_le(4)
            self.zmsk = self._io.read_bits_int_le(1) != 0
            self.pad33 = self._io.read_bits_int_le(31)


        def _fetch_instances(self):
            pass


    class SceIpuDmaEnv(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceIpuDmaEnv, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.d4madr = self._io.read_u4le()
            self.d4tadr = self._io.read_u4le()
            self.d4qwc = self._io.read_u4le()
            self.d4chcr = self._io.read_u4le()
            self.d3madr = self._io.read_u4le()
            self.d3qwc = self._io.read_u4le()
            self.d3chcr = self._io.read_u4le()
            self.ipubp = self._io.read_u4le()
            self.ipuctrl = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class SceIpuRaw8(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceIpuRaw8, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.y = []
            for i in range(256):
                self.y.append(self._io.read_u1())

            self.cb = []
            for i in range(64):
                self.cb.append(self._io.read_u1())

            self.cr = []
            for i in range(64):
                self.cr.append(self._io.read_u1())



        def _fetch_instances(self):
            pass
            for i in range(len(self.y)):
                pass

            for i in range(len(self.cb)):
                pass

            for i in range(len(self.cr)):
                pass



    class SceIpuRgb32(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceIpuRgb32, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pix = []
            for i in range(256):
                self.pix.append(self._io.read_u4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.pix)):
                pass



    class SceMcStDateTime(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceMcStDateTime, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.resv2 = self._io.read_u1()
            self.sec = self._io.read_u1()
            self.min = self._io.read_u1()
            self.hour = self._io.read_u1()
            self.day = self._io.read_u1()
            self.month = self._io.read_u1()
            self.year = self._io.read_u2le()


        def _fetch_instances(self):
            pass


    class SceMcTblGetDir(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceMcTblGetDir, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.create = Sh2.SceMcStDateTime(self._io, self, self._root)
            self.modify = Sh2.SceMcStDateTime(self._io, self, self._root)
            self.file_size_byte = self._io.read_u4le()
            self.attr_file = self._io.read_u2le()
            self.reserve1 = self._io.read_u2le()
            self.reserve2 = self._io.read_u4le()
            self.pda_apl_no = self._io.read_u4le()
            self.entry_name = []
            for i in range(32):
                self.entry_name.append(self._io.read_u1())



        def _fetch_instances(self):
            pass
            self.create._fetch_instances()
            self.modify._fetch_instances()
            for i in range(len(self.entry_name)):
                pass



    class SceMpeg(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceMpeg, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.width = self._io.read_s4le()
            self.height = self._io.read_s4le()
            self.frame_count = self._io.read_s4le()
            self._unnamed3 = self._io.read_bytes(4)
            self.pts = self._io.read_s8le()
            self.dts = self._io.read_s8le()
            self.flags = self._io.read_u8le()
            self.pts2nd = self._io.read_s8le()
            self.dts2nd = self._io.read_s8le()
            self.flags2nd = self._io.read_u8le()
            self.sys = Sh2.Pointer(u"data", self._io, self, self._root)
            self._unnamed11 = self._io.read_bytes(4)


        def _fetch_instances(self):
            pass
            self.sys._fetch_instances()


    class SceMpegCbData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceMpegCbData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._unnamed0 = self._io.read_bytes(32)


        def _fetch_instances(self):
            pass
            _ = self.error
            if hasattr(self, '_m_error'):
                pass
                self._m_error._fetch_instances()

            _ = self.str
            if hasattr(self, '_m_str'):
                pass
                self._m_str._fetch_instances()

            _ = self.ts
            if hasattr(self, '_m_ts'):
                pass
                self._m_ts._fetch_instances()

            _ = self.type
            if hasattr(self, '_m_type'):
                pass


        @property
        def error(self):
            if hasattr(self, '_m_error'):
                return self._m_error

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_error = Sh2.SceMpegCbDataError(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_error', None)

        @property
        def str(self):
            if hasattr(self, '_m_str'):
                return self._m_str

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_str = Sh2.SceMpegCbDataStr(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_str', None)

        @property
        def ts(self):
            if hasattr(self, '_m_ts'):
                return self._m_ts

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_ts = Sh2.SceMpegCbDataTimeStamp(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_ts', None)

        @property
        def type(self):
            if hasattr(self, '_m_type'):
                return self._m_type

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_type = self._io.read_u1()
            self._io.seek(_pos)
            return getattr(self, '_m_type', None)


    class SceMpegCbDataError(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceMpegCbDataError, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_u1()
            self._unnamed1 = self._io.read_bytes(3)
            self.err_message = Sh2.Pointer(u"data", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.err_message._fetch_instances()


    class SceMpegCbDataStr(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceMpegCbDataStr, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_u1()
            self._unnamed1 = self._io.read_bytes(3)
            self.header = Sh2.Pointer(u"data", self._io, self, self._root)
            self.data = Sh2.Pointer(u"data", self._io, self, self._root)
            self.len = self._io.read_u4le()
            self.pts = self._io.read_s8le()
            self.dts = self._io.read_s8le()


        def _fetch_instances(self):
            pass
            self.header._fetch_instances()
            self.data._fetch_instances()


    class SceMpegCbDataTimeStamp(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceMpegCbDataTimeStamp, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_u1()
            self._unnamed1 = self._io.read_bytes(7)
            self.pts = self._io.read_s8le()
            self.dts = self._io.read_s8le()


        def _fetch_instances(self):
            pass


    class SceScfT10kConfig(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceScfT10kConfig, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.time_zone = self._io.read_s2le()
            self.aspect = self._io.read_u1()
            self.date_notation = self._io.read_u1()
            self.language = self._io.read_u1()
            self.spdif = self._io.read_u1()
            self.summer_time = self._io.read_u1()
            self.time_notation = self._io.read_u1()


        def _fetch_instances(self):
            pass


    class SceVif0Packet(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceVif0Packet, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.p_current = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_base = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_dma_tag = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_vif_code = Sh2.Pointer(u"data", self._io, self, self._root)
            self.numlen = self._io.read_u4le()
            self.pad11 = self._io.read_u4le()
            self.pad12 = self._io.read_u4le()
            self.pad13 = self._io.read_u4le()


        def _fetch_instances(self):
            pass
            self.p_current._fetch_instances()
            self.p_base._fetch_instances()
            self.p_dma_tag._fetch_instances()
            self.p_vif_code._fetch_instances()


    class SceVif1Packet(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SceVif1Packet, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.p_current = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_base = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_dma_tag = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_vif_code = Sh2.Pointer(u"data", self._io, self, self._root)
            self.numlen = self._io.read_u4le()
            self.p_gif_tag = Sh2.Pointer(u"data", self._io, self, self._root)
            self.pad12 = self._io.read_u4le()
            self.pad13 = self._io.read_u4le()


        def _fetch_instances(self):
            pass
            self.p_current._fetch_instances()
            self.p_base._fetch_instances()
            self.p_dma_tag._fetch_instances()
            self.p_vif_code._fetch_instances()
            self.p_gif_tag._fetch_instances()


    class ScratchpadFog(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ScratchpadFog, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.unk0 = []
            for i in range(16352):
                self.unk0.append(self._io.read_u1())

            self.wind2 = []
            for i in range(4):
                self.wind2.append(self._io.read_f4le())

            self.wind = []
            for i in range(4):
                self.wind.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.unk0)):
                pass

            for i in range(len(self.wind2)):
                pass

            for i in range(len(self.wind)):
                pass



    class ScreenEffectParameter(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ScreenEffectParameter, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.fade_status = self._io.read_s4le()
            self.fade_type = self._io.read_s4le()
            self.fade_timer_now = self._io.read_f4le()
            self.fade_timer_max = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class Se2dManageData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Se2dManageData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.sd = self._io.read_s4le()
            self._unnamed1 = self._io.read_bytes(12)
            self.pos = []
            for i in range(4):
                self.pos.append(self._io.read_f4le())

            self.vol = self._io.read_f4le()
            self.room = self._io.read_s2le()
            self.pos_on = self._io.read_u1()
            self.pre_dist = self._io.read_u1()
            self.pre_pan = self._io.read_s2le()
            self.status = self._io.read_s2le()
            self.timer = self._io.read_f4le()
            self.base = self._io.read_f4le()
            self._unnamed11 = self._io.read_bytes(12)


        def _fetch_instances(self):
            pass
            for i in range(len(self.pos)):
                pass



    class Se3dChannelData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Se3dChannelData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.sd = self._io.read_s4le()
            self.room = self._io.read_s4le()
            self.status = self._io.read_s4le()
            self._unnamed3 = self._io.read_bytes(4)
            self.pos = []
            for i in range(4):
                self.pos.append(self._io.read_f4le())

            self.vol = self._io.read_f4le()
            self._unnamed6 = self._io.read_bytes(12)


        def _fetch_instances(self):
            pass
            for i in range(len(self.pos)):
                pass



    class SeBgmBuffer(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SeBgmBuffer, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.current = self._io.read_s4le()
            self.next = self._io.read_s4le()
            self.read = self._io.read_s4le()
            self.sdb_no = self._io.read_s4le()
            self.volume = self._io.read_f4le()
            self.track = []
            for i in range(7):
                self.track.append(Sh2.SeTrackBuffer(self._io, self, self._root))



        def _fetch_instances(self):
            pass
            for i in range(len(self.track)):
                pass
                self.track[i]._fetch_instances()



    class SeTrackBuffer(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SeTrackBuffer, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.status = self._io.read_u1()
            self.fade_in_type = self._io.read_u1()
            self.fade_out_type = self._io.read_u1()
            self.pad = self._io.read_u1()
            self.volume = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class SemaParam(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SemaParam, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.current_count = self._io.read_s4le()
            self.max_count = self._io.read_s4le()
            self.init_count = self._io.read_s4le()
            self.num_wait_threads = self._io.read_s4le()
            self.attr = self._io.read_u4le()
            self.option = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class Sh2Sys(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2Sys, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.step = []
            for i in range(8):
                self.step.append(self._io.read_u4le())

            self.pre_playable = self._io.read_u4le()
            self.main_status = self._io.read_s4le()
            self.soft_reset = self._io.read_u4le()
            self.frame_cnt = self._io.read_u4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.step)):
                pass



    class Sh2gfwAllModelDataMan(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwAllModelDataMan, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.n_active_character = self._io.read_s4le()
            self.n_load_character = self._io.read_s4le()
            self.p_mdm = []
            for i in range(32):
                self.p_mdm.append(Sh2.Pointer(u"sh2gfw_model_draw_man", self._io, self, self._root))

            self.file_struct = []
            for i in range(32):
                self.file_struct.append(Sh2.Pointer(u"data", self._io, self, self._root))

            self.fid_model = []
            for i in range(32):
                self.fid_model.append(self._io.read_s4le())

            self.fid_anim = []
            for i in range(32):
                self.fid_anim.append(self._io.read_s4le())

            self.fid_clus = []
            for i in range(32):
                self.fid_clus.append(self._io.read_s4le())

            self.fid_kg1 = []
            for i in range(32):
                self.fid_kg1.append(self._io.read_s4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.p_mdm)):
                pass
                self.p_mdm[i]._fetch_instances()

            for i in range(len(self.file_struct)):
                pass
                self.file_struct[i]._fetch_instances()

            for i in range(len(self.fid_model)):
                pass

            for i in range(len(self.fid_anim)):
                pass

            for i in range(len(self.fid_clus)):
                pass

            for i in range(len(self.fid_kg1)):
                pass



    class Sh2gfwAreaDataMan(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwAreaDataMan, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.areaid = self._io.read_u4le()
            self.use_globalflg = []
            for i in range(7):
                self.use_globalflg.append(self._io.read_u1())

            self.use_transflg = []
            for i in range(7):
                self.use_transflg.append(self._io.read_u1())

            self.block_id = []
            for i in range(7):
                self.block_id.append(self._io.read_u2le())

            self.block_man = []
            for i in range(7):
                self.block_man.append(Sh2.Pointer(u"data", self._io, self, self._root))

            self.p_ah = Sh2.Pointer(u"sh2gfw_area_head", self._io, self, self._root)
            self.global_tex = Sh2.Pointer(u"sh2gfw_tex_head", self._io, self, self._root)
            self.global_clut = Sh2.Pointer(u"sh2gfw_cluts_head", self._io, self, self._root)
            self.global_transtex = Sh2.Pointer(u"sh2gfw_tex_head", self._io, self, self._root)
            self.global_transclut = Sh2.Pointer(u"sh2gfw_cluts_head", self._io, self, self._root)
            self.g_tex_man = Sh2.Pointer(u"sh2gfw_tex_man", self._io, self, self._root)
            self.g_transtex_man = Sh2.Pointer(u"sh2gfw_tex_man", self._io, self, self._root)
            self.gtex_mode = self._io.read_u2le()
            self.gtrans_mode = self._io.read_u2le()
            self.pad1 = self._io.read_u4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.use_globalflg)):
                pass

            for i in range(len(self.use_transflg)):
                pass

            for i in range(len(self.block_id)):
                pass

            for i in range(len(self.block_man)):
                pass
                self.block_man[i]._fetch_instances()

            self.p_ah._fetch_instances()
            self.global_tex._fetch_instances()
            self.global_clut._fetch_instances()
            self.global_transtex._fetch_instances()
            self.global_transclut._fetch_instances()
            self.g_tex_man._fetch_instances()
            self.g_transtex_man._fetch_instances()


    class Sh2gfwAreaHead(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwAreaHead, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.area_id = self._io.read_u4le()
            self.to_global_tex_head = self._io.read_u4le()
            self.to_global_cluts_head = self._io.read_u4le()
            self.date = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class Sh2gfwBlockHead(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwBlockHead, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.block_id = self._io.read_u4le()
            self.to_globaldef = self._io.read_u4le()
            self.to_localdef = self._io.read_u4le()
            self.to_rawblockdata_parms = self._io.read_u4le()
            self.to_local_tex = []
            for i in range(3):
                self.to_local_tex.append(self._io.read_u4le())

            self.to_localcluts = []
            for i in range(3):
                self.to_localcluts.append(self._io.read_u4le())

            self.texnum = self._io.read_u4le()
            self.globaltexnum = self._io.read_u1()
            self.transtexnum = self._io.read_u1()
            self.divflg = self._io.read_u1()
            self.padc = self._io.read_u1()


        def _fetch_instances(self):
            pass
            for i in range(len(self.to_local_tex)):
                pass

            for i in range(len(self.to_localcluts)):
                pass



    class Sh2gfwBlockglobalHead(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwBlockglobalHead, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.gsregsamount = self._io.read_u4le()
            self.transamount = self._io.read_u4le()
            self.gtexnum = self._io.read_u1()
            self.gtransnum = self._io.read_u1()
            self.pads = self._io.read_u2le()
            self.pad2 = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class Sh2gfwBlocklocalHead(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwBlocklocalHead, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.gsregsamount = []
            for i in range(3):
                self.gsregsamount.append(self._io.read_u2le())

            self.transamount = []
            for i in range(3):
                self.transamount.append(self._io.read_u2le())

            self.ltexnum = self._io.read_u2le()
            self.pads = self._io.read_u2le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.gsregsamount)):
                pass

            for i in range(len(self.transamount)):
                pass



    class Sh2gfwClutsHead(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwClutsHead, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.clutssize = self._io.read_u4le()
            self.to_gsregs = self._io.read_u4le()
            self.to_raw_clut = self._io.read_u4le()
            self.clutamount = self._io.read_u1()
            self.transcluts = self._io.read_u1()
            self.clw = self._io.read_u1()
            self.clh = self._io.read_u1()
            self.fmt = []
            for i in range(16):
                self.fmt.append(self._io.read_u1())

            self.transparency = []
            for i in range(16):
                self.transparency.append(self._io.read_u1())



        def _fetch_instances(self):
            pass
            for i in range(len(self.fmt)):
                pass

            for i in range(len(self.transparency)):
                pass



    class Sh2gfwEffectMan(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwEffectMan, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.effectid = self._io.read_u2le()
            self.vifmark = self._io.read_u2le()
            self.valid_id = self._io.read_u2le()
            self.pads = self._io.read_u2le()
            self.thr_cid = self._io.read_s4le()
            self.thr_sid = self._io.read_s4le()
            self.tex0_data = Sh2.U16(self._io, self, self._root)
            self.alpha = Sh2.U16(self._io, self, self._root)
            self.p_tex_man = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_tex_head = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_top = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_pad = Sh2.Pointer(u"data", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.tex0_data._fetch_instances()
            self.alpha._fetch_instances()
            self.p_tex_man._fetch_instances()
            self.p_tex_head._fetch_instances()
            self.p_top._fetch_instances()
            self.p_pad._fetch_instances()


    class Sh2gfwGiftagHead(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwGiftagHead, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.gsregs_amount = self._io.read_u2le()
            self.trans_flg = self._io.read_u1()
            self.eop_flg = self._io.read_u1()
            self.to_next_gifhead = self._io.read_u4le()
            self.id = self._io.read_u2le()
            self.tcc = self._io.read_u1()
            self.tfx = self._io.read_u1()
            self.abe = self._io.read_u1()
            self.pad1 = self._io.read_u1()
            self.pad2 = self._io.read_u1()
            self.pad3 = self._io.read_u1()


        def _fetch_instances(self):
            pass


    class Sh2gfwGsregsHead(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwGsregsHead, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.clutssize = self._io.read_u4le()
            self.to_next_data = self._io.read_u4le()
            self.to_tex_head = self._io.read_u4le()
            self.clutamount = self._io.read_u1()
            self.transamount = self._io.read_u1()
            self.eop_flg = self._io.read_u1()
            self.tr_flg = self._io.read_u1()
            self.fmt = []
            for i in range(16):
                self.fmt.append(self._io.read_u1())

            self.transparency = []
            for i in range(16):
                self.transparency.append(self._io.read_u1())



        def _fetch_instances(self):
            pass
            for i in range(len(self.fmt)):
                pass

            for i in range(len(self.transparency)):
                pass



    class Sh2gfwLoadModelMemman(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwLoadModelMemman, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.index_model = self._io.read_u4le()
            self.index_anime = self._io.read_u4le()
            self.index_clus = self._io.read_u4le()
            self.p_lm_head = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_la_head = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_cl_head = Sh2.Pointer(u"data", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.p_lm_head._fetch_instances()
            self.p_la_head._fetch_instances()
            self.p_cl_head._fetch_instances()


    class Sh2gfwModelDrawMan(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwModelDrawMan, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.chara_id = self._io.read_u4le()
            self.test_sub_char = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.model_head = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_model_header = Sh2.Pointer(u"data", self._io, self, self._root)
            self.sh_model = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_anime = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_cluster = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_kg1_work = Sh2.Pointer(u"data", self._io, self, self._root)
            self.allnum = self._io.read_s2le()
            self.nowtex = self._io.read_s2le()
            self.tb_change_vu1num = self._io.read_u2le()
            self.tb_change_vu1now = self._io.read_u2le()
            self.tb_change_vu1 = []
            for i in range(4):
                self.tb_change_vu1.append(self._io.read_u2le())

            self.tb_index_vu1 = []
            for i in range(4):
                self.tb_index_vu1.append(self._io.read_u2le())

            self.tb_change_vu0num = self._io.read_u2le()
            self.tb_change_vu0now = self._io.read_u2le()
            self.tb_change_vu0 = []
            for i in range(2):
                self.tb_change_vu0.append(self._io.read_u2le())

            self.tb_index_vu0 = []
            for i in range(2):
                self.tb_index_vu0.append(self._io.read_u2le())

            self.chr_slotid = []
            for i in range(6):
                self.chr_slotid.append(self._io.read_s4le())

            self.chr_cid = []
            for i in range(6):
                self.chr_cid.append(self._io.read_s4le())

            self.d1cid = self._io.read_s4le()
            self.d2c1d = self._io.read_s4le()
            self.p_tex_man = []
            for i in range(6):
                self.p_tex_man.append(Sh2.Pointer(u"data", self._io, self, self._root))



        def _fetch_instances(self):
            pass
            self.test_sub_char._fetch_instances()
            self.model_head._fetch_instances()
            self.p_model_header._fetch_instances()
            self.sh_model._fetch_instances()
            self.p_anime._fetch_instances()
            self.p_cluster._fetch_instances()
            self.p_kg1_work._fetch_instances()
            for i in range(len(self.tb_change_vu1)):
                pass

            for i in range(len(self.tb_index_vu1)):
                pass

            for i in range(len(self.tb_change_vu0)):
                pass

            for i in range(len(self.tb_index_vu0)):
                pass

            for i in range(len(self.chr_slotid)):
                pass

            for i in range(len(self.chr_cid)):
                pass

            for i in range(len(self.p_tex_man)):
                pass
                self.p_tex_man[i]._fetch_instances()



    class Sh2gfwModelHeader(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwModelHeader, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.no_texture_id = self._io.read_u1()
            self.padc = []
            for i in range(3):
                self.padc.append(self._io.read_u1())

            self.chara_id = self._io.read_u4le()
            self.texnum = self._io.read_u4le()
            self.to_tex_head_offset = self._io.read_u4le()
            self.to_cluts_head_offset = self._io.read_u4le()
            self.to_model_offset = self._io.read_u4le()
            self.to_kg1_offset = self._io.read_s4le()
            self.padi = self._io.read_s4le()
            self.p_tex_man = []
            for i in range(8):
                self.p_tex_man.append(Sh2.Pointer(u"data", self._io, self, self._root))



        def _fetch_instances(self):
            pass
            for i in range(len(self.padc)):
                pass

            for i in range(len(self.p_tex_man)):
                pass
                self.p_tex_man[i]._fetch_instances()



    class Sh2gfwTexHead(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwTexHead, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.texture_no = self._io.read_u4le()
            self.x = self._io.read_u2le()
            self.y = self._io.read_u2le()
            self.w = self._io.read_u2le()
            self.h = self._io.read_u2le()
            self.color = self._io.read_u1()
            self.padbyte = self._io.read_u1()
            self.importance = self._io.read_u2le()
            self.datasize = self._io.read_u4le()
            self.allsize = self._io.read_u4le()
            self.sendpsm = self._io.read_u1()
            self.drawpsm = self._io.read_u1()
            self.bitshift = self._io.read_u1()
            self.tagpoint = self._io.read_u1()
            self.bitw = self._io.read_u1()
            self.bith = self._io.read_u1()
            self.check = self._io.read_u2le()
            self._raw_giftag = self._io.read_bytes(16)
            _io__raw_giftag = KaitaiStream(BytesIO(self._raw_giftag))
            self.giftag = Sh2.QWorddata(_io__raw_giftag, self, self._root)


        def _fetch_instances(self):
            pass
            self.giftag._fetch_instances()


    class Sh2gfwTransMan(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sh2gfwTransMan, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.blockid = self._io.read_u4le()
            self.p_am = Sh2.Pointer(u"sh2gfw_area_data_man", self._io, self, self._root)
            self.objnum = []
            for i in range(4):
                self.objnum.append(self._io.read_u2le())

            self.trans_clutnum = self._io.read_u4le()
            self.pad2 = self._io.read_u4le()
            self.pad3 = self._io.read_u4le()
            self.pad4 = self._io.read_u4le()
            self.trgehead = []
            for i in range(4):
                self.trgehead.append(Sh2.Pointer(u"data", self._io, self, self._root))

            self.p_tr_global_gif_h = []
            for i in range(64):
                self.p_tr_global_gif_h.append(Sh2.Pointer(u"sh2gfw_giftag_head", self._io, self, self._root))

            self.p_g_tex_head = Sh2.Pointer(u"sh2gfw_tex_head", self._io, self, self._root)
            self.p_g_clut_head = Sh2.Pointer(u"sh2gfw_cluts_head", self._io, self, self._root)
            self.p_g_tex_man = Sh2.Pointer(u"sh2gfw_tex_man", self._io, self, self._root)
            self.used_ggifnum = []
            for i in range(4):
                self.used_ggifnum.append(self._io.read_u1())

            self.p_tr_trans_gif_h = []
            for i in range(64):
                self.p_tr_trans_gif_h.append(Sh2.Pointer(u"sh2gfw_giftag_head", self._io, self, self._root))

            self.p_tr_tex_head = Sh2.Pointer(u"sh2gfw_tex_head", self._io, self, self._root)
            self.p_tr_clut_head = Sh2.Pointer(u"sh2gfw_cluts_head", self._io, self, self._root)
            self.p_tr_tex_man = Sh2.Pointer(u"sh2gfw_tex_man", self._io, self, self._root)
            self.used_t_rgifnum = []
            for i in range(4):
                self.used_t_rgifnum.append(self._io.read_u1())



        def _fetch_instances(self):
            pass
            self.p_am._fetch_instances()
            for i in range(len(self.objnum)):
                pass

            for i in range(len(self.trgehead)):
                pass
                self.trgehead[i]._fetch_instances()

            for i in range(len(self.p_tr_global_gif_h)):
                pass
                self.p_tr_global_gif_h[i]._fetch_instances()

            self.p_g_tex_head._fetch_instances()
            self.p_g_clut_head._fetch_instances()
            self.p_g_tex_man._fetch_instances()
            for i in range(len(self.used_ggifnum)):
                pass

            for i in range(len(self.p_tr_trans_gif_h)):
                pass
                self.p_tr_trans_gif_h[i]._fetch_instances()

            self.p_tr_tex_head._fetch_instances()
            self.p_tr_clut_head._fetch_instances()
            self.p_tr_tex_man._fetch_instances()
            for i in range(len(self.used_t_rgifnum)):
                pass



    class ShAnime3d(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShAnime3d, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.top = Sh2.Pointer(u"sh_skelton", self._io, self, self._root)
            self.anime = Sh2.Pointer(u"data", self._io, self, self._root)
            self.frame_top = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_anime = Sh2.Pointer(u"data", self._io, self, self._root)
            self.p_frame_top = Sh2.Pointer(u"data", self._io, self, self._root)
            self.frame_size = self._io.read_u4le()
            self.total_count = self._io.read_s4le()
            self.c_count = Sh2.Ixy(self._io, self, self._root)
            self.c_speed = Sh2.Sxy(self._io, self, self._root)
            self.total_speed = Sh2.Sxy(self._io, self, self._root)
            self.cur_frame = Sh2.Usxy(self._io, self, self._root)
            self.first_bone_type = self._io.read_s1()
            self.comp_type = self._io.read_s1()
            self._unnamed13 = self._io.read_bytes(2)
            self.anim_a = Sh2.Pointer(u"anime_info", self._io, self, self._root)
            self.anim_b = Sh2.Pointer(u"anime_info", self._io, self, self._root)
            self._unnamed16 = self._io.read_bytes(4)
            self.rot_neck = Sh2.Vector4(self._io, self, self._root)
            self.rot_arms = Sh2.Vector4(self._io, self, self._root)
            self.rot_body_neck = Sh2.Vector4(self._io, self, self._root)
            self.rot_body = Sh2.Vector4(self._io, self, self._root)
            self.scale = self._io.read_f4le()
            self._unnamed22 = self._io.read_bytes(12)


        def _fetch_instances(self):
            pass
            self.top._fetch_instances()
            self.anime._fetch_instances()
            self.frame_top._fetch_instances()
            self.p_anime._fetch_instances()
            self.p_frame_top._fetch_instances()
            self.c_count._fetch_instances()
            self.c_speed._fetch_instances()
            self.total_speed._fetch_instances()
            self.cur_frame._fetch_instances()
            self.anim_a._fetch_instances()
            self.anim_b._fetch_instances()
            self.rot_neck._fetch_instances()
            self.rot_arms._fetch_instances()
            self.rot_body_neck._fetch_instances()
            self.rot_body._fetch_instances()


    class ShAttackInfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShAttackInfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.id = self._io.read_u2le()
            self.kind = self._io.read_u2le()
            self.ap = self._io.read_f4le()
            self.sp = self._io.read_f4le()
            self.min_range = self._io.read_f4le()
            self.max_range = self._io.read_f4le()
            self._raw_hit_check = self._io.read_bytes(12)
            _io__raw_hit_check = KaitaiStream(BytesIO(self._raw_hit_check))
            self.hit_check = Sh2.ShAttackInfoAnon5(_io__raw_hit_check, self, self._root)
            self.atk_start = self._io.read_u1()
            self.atk_end = self._io.read_u1()
            self.sd = self._io.read_u1()
            self.eff = self._io.read_u1()


        def _fetch_instances(self):
            pass
            self.hit_check._fetch_instances()


    class ShAttackInfoAnon5(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShAttackInfoAnon5, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._unnamed0 = self._io.read_bytes(12)


        def _fetch_instances(self):
            pass
            _ = self.fight
            if hasattr(self, '_m_fight'):
                pass
                self._m_fight._fetch_instances()

            _ = self.shot
            if hasattr(self, '_m_shot'):
                pass
                self._m_shot._fetch_instances()


        @property
        def fight(self):
            if hasattr(self, '_m_fight'):
                return self._m_fight

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_fight = Sh2.ShBattleFight(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_fight', None)

        @property
        def shot(self):
            if hasattr(self, '_m_shot'):
                return self._m_shot

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_shot = Sh2.ShBattleShot(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_shot', None)


    class ShAttackQueue(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShAttackQueue, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.rest = self._io.read_s4le()
            self.queue = []
            for i in range(20):
                self.queue.append(Sh2.ShAttackQueueOne(self._io, self, self._root))



        def _fetch_instances(self):
            pass
            for i in range(len(self.queue)):
                pass
                self.queue[i]._fetch_instances()



    class ShAttackQueueOne(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShAttackQueueOne, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.scp = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.wep_no = self._io.read_u1()
            self._unnamed2 = self._io.read_bytes(1)
            self.atk_no = self._io.read_u2le()


        def _fetch_instances(self):
            pass
            self.scp._fetch_instances()


    class ShBattleArea(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShBattleArea, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.center = self._io.read_f4le()
            self.radius = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class ShBattleFight(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShBattleFight, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.test_a = self._io.read_f4le()
            self.test_b = self._io.read_f4le()
            self.test_c = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class ShBattleInfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShBattleInfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pos = []
            for i in range(4):
                self.pos.append(self._io.read_f4le())

            self.vec = []
            for i in range(4):
                self.vec.append(self._io.read_f4le())

            self.id = self._io.read_u2le()
            self.kind = self._io.read_u2le()
            self.dead_timer = self._io.read_f4le()
            self.damage = self._io.read_f4le()
            self.shock = self._io.read_f4le()
            self.atk_result = self._io.read_s4le()
            self._unnamed8 = self._io.read_bytes(12)
            self.prev_atk_pos = Sh2.Vector4(self._io, self, self._root)
            self.target = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.hp = self._io.read_f4le()
            self.hp_max = self._io.read_f4le()
            self.hp_rate = self._io.read_f4le()
            self.status = self._io.read_u4le()
            self.look = Sh2.ShBattleArea(self._io, self, self._root)
            self.feel = Sh2.ShBattleArea(self._io, self, self._root)
            self.se = self._io.read_u1()
            self._unnamed18 = self._io.read_bytes(11)


        def _fetch_instances(self):
            pass
            for i in range(len(self.pos)):
                pass

            for i in range(len(self.vec)):
                pass

            self.prev_atk_pos._fetch_instances()
            self.target._fetch_instances()
            self.look._fetch_instances()
            self.feel._fetch_instances()


    class ShBattleShot(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShBattleShot, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.test_a = self._io.read_f4le()
            self.test_b = self._io.read_f4le()
            self.test_c = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class ShCharaInfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShCharaInfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pos = Sh2.Vector4(self._io, self, self._root)
            self.rot = Sh2.Vector4(self._io, self, self._root)
            self.pos_spd = Sh2.Vector4(self._io, self, self._root)
            self.rot_spd = Sh2.Vector4(self._io, self, self._root)
            self.mat = []
            for i in range(16):
                self.mat.append(self._io.read_f4le())

            self.sk_top = Sh2.Pointer(u"sh_skelton", self._io, self, self._root)
            self._unnamed6 = self._io.read_bytes(12)


        def _fetch_instances(self):
            pass
            self.pos._fetch_instances()
            self.rot._fetch_instances()
            self.pos_spd._fetch_instances()
            self.rot_spd._fetch_instances()
            for i in range(len(self.mat)):
                pass

            self.sk_top._fetch_instances()


    class ShCharacterAll(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShCharacterAll, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.work = []
            for i in range(32):
                self.work.append(Sh2.SubCharacterDisp(self._io, self, self._root))

            self.free = Sh2.Pointer(u"sub_character_disp", self._io, self, self._root)
            self.head = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.player = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.total = self._io.read_s1()
            self._unnamed5 = self._io.read_bytes(3)


        def _fetch_instances(self):
            pass
            for i in range(len(self.work)):
                pass
                self.work[i]._fetch_instances()

            self.free._fetch_instances()
            self.head._fetch_instances()
            self.player._fetch_instances()


    class ShClusterAnime(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShClusterAnime, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.data = Sh2.Pointer(u"data", self._io, self, self._root)
            self.used = self._io.read_u1()
            self.n_clusters = self._io.read_u1()
            self.is_repeat = self._io.read_u1()
            self.frame_updated = self._io.read_u1()
            self.frame_no = self._io.read_s4le()
            self.weights = Sh2.Pointer(u"data", self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.data._fetch_instances()
            self.weights._fetch_instances()


    class ShGameKeyAssign(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShGameKeyAssign, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.type = self._io.read_u2le()
            self.dir_ax = self._io.read_u1()
            self.dir_ay = self._io.read_u1()
            self.dir_bx = self._io.read_u1()
            self.dir_by = self._io.read_u1()
            self.dir_cx = self._io.read_u1()
            self.dir_cy = self._io.read_u1()
            self.drink = self._io.read_u2le()
            self.radio = self._io.read_u2le()
            self.light = self._io.read_u2le()
            self.item = self._io.read_u2le()
            self.map = self._io.read_u2le()
            self.decide = self._io.read_u2le()
            self.cancel = self._io.read_u2le()
            self.skip = self._io.read_u2le()
            self.pause = self._io.read_u2le()
            self.action = self._io.read_u2le()
            self.dash = self._io.read_u2le()
            self.lslide = self._io.read_u2le()
            self.rslide = self._io.read_u2le()
            self.ready = self._io.read_u2le()
            self.view = self._io.read_u2le()


        def _fetch_instances(self):
            pass


    class ShGsAllEnv(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShGsAllEnv, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.loop_counter = self._io.read_u8le()
            self.loop = self._io.read_u4le()
            self.loop3 = self._io.read_u4le()
            self.loop_env = Sh2.ShGsLoopEnv(self._io, self, self._root)
            self.disp_env = []
            for i in range(3):
                self.disp_env.append(Sh2.SceGsDispEnv(self._io, self, self._root))

            self._unnamed5 = self._io.read_bytes(8)
            self.draw_env = []
            for i in range(3):
                self.draw_env.append(Sh2.ShGsDrawEnv(self._io, self, self._root))

            self.stencil_buf = []
            for i in range(3):
                self.stencil_buf.append(Sh2.ShGsStencilDrawEnv(self._io, self, self._root))

            self.stencil_work = []
            for i in range(6):
                self.stencil_work.append(Sh2.ShGsTinyDrawEnv(self._io, self, self._root))

            self.default_env = []
            for i in range(10):
                self.default_env.append(Sh2.QWorddata(self._io, self, self._root))

            self.stencil_env = []
            for i in range(10):
                self.stencil_env.append(Sh2.QWorddata(self._io, self, self._root))

            self.compshadow_env = []
            for i in range(10):
                self.compshadow_env.append(Sh2.QWorddata(self._io, self, self._root))

            self.filter_a = []
            for i in range(10):
                self.filter_a.append(Sh2.QWorddata(self._io, self, self._root))

            self.filter_b = []
            for i in range(10):
                self.filter_b.append(Sh2.QWorddata(self._io, self, self._root))

            self.filter_c = []
            for i in range(10):
                self.filter_c.append(Sh2.QWorddata(self._io, self, self._root))

            self.filter_d = []
            for i in range(10):
                self.filter_d.append(Sh2.QWorddata(self._io, self, self._root))

            self.move_gtex = []
            for i in range(8):
                self.move_gtex.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_alpha_a = []
            for i in range(2):
                self.gs_reg_alpha_a.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_alpha_b = []
            for i in range(2):
                self.gs_reg_alpha_b.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_alpha_c = []
            for i in range(2):
                self.gs_reg_alpha_c.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_alpha_d = []
            for i in range(2):
                self.gs_reg_alpha_d.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_alpha_e = []
            for i in range(2):
                self.gs_reg_alpha_e.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_test_a = []
            for i in range(2):
                self.gs_reg_test_a.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_test_b = []
            for i in range(2):
                self.gs_reg_test_b.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_test_c = []
            for i in range(2):
                self.gs_reg_test_c.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_test_d = []
            for i in range(2):
                self.gs_reg_test_d.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_texa_a = []
            for i in range(2):
                self.gs_reg_texa_a.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_texa_b = []
            for i in range(2):
                self.gs_reg_texa_b.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_zbuf_a = []
            for i in range(2):
                self.gs_reg_zbuf_a.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_zbuf_b = []
            for i in range(2):
                self.gs_reg_zbuf_b.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_pabe_a = []
            for i in range(2):
                self.gs_reg_pabe_a.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_pabe_b = []
            for i in range(2):
                self.gs_reg_pabe_b.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_fba_a = []
            for i in range(2):
                self.gs_reg_fba_a.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_fba_b = []
            for i in range(2):
                self.gs_reg_fba_b.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_prmodecont_a = []
            for i in range(2):
                self.gs_reg_prmodecont_a.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_reg_prmodecont_b = []
            for i in range(2):
                self.gs_reg_prmodecont_b.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_sync_dummy_label = []
            for i in range(2):
                self.gs_sync_dummy_label.append(Sh2.QWorddata(self._io, self, self._root))

            self.gs_sync_dummy_texflush = []
            for i in range(2):
                self.gs_sync_dummy_texflush.append(Sh2.QWorddata(self._io, self, self._root))

            self.now_draw_env = Sh2.ShGsDrawEnv(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.loop_env._fetch_instances()
            for i in range(len(self.disp_env)):
                pass
                self.disp_env[i]._fetch_instances()

            for i in range(len(self.draw_env)):
                pass
                self.draw_env[i]._fetch_instances()

            for i in range(len(self.stencil_buf)):
                pass
                self.stencil_buf[i]._fetch_instances()

            for i in range(len(self.stencil_work)):
                pass
                self.stencil_work[i]._fetch_instances()

            for i in range(len(self.default_env)):
                pass
                self.default_env[i]._fetch_instances()

            for i in range(len(self.stencil_env)):
                pass
                self.stencil_env[i]._fetch_instances()

            for i in range(len(self.compshadow_env)):
                pass
                self.compshadow_env[i]._fetch_instances()

            for i in range(len(self.filter_a)):
                pass
                self.filter_a[i]._fetch_instances()

            for i in range(len(self.filter_b)):
                pass
                self.filter_b[i]._fetch_instances()

            for i in range(len(self.filter_c)):
                pass
                self.filter_c[i]._fetch_instances()

            for i in range(len(self.filter_d)):
                pass
                self.filter_d[i]._fetch_instances()

            for i in range(len(self.move_gtex)):
                pass
                self.move_gtex[i]._fetch_instances()

            for i in range(len(self.gs_reg_alpha_a)):
                pass
                self.gs_reg_alpha_a[i]._fetch_instances()

            for i in range(len(self.gs_reg_alpha_b)):
                pass
                self.gs_reg_alpha_b[i]._fetch_instances()

            for i in range(len(self.gs_reg_alpha_c)):
                pass
                self.gs_reg_alpha_c[i]._fetch_instances()

            for i in range(len(self.gs_reg_alpha_d)):
                pass
                self.gs_reg_alpha_d[i]._fetch_instances()

            for i in range(len(self.gs_reg_alpha_e)):
                pass
                self.gs_reg_alpha_e[i]._fetch_instances()

            for i in range(len(self.gs_reg_test_a)):
                pass
                self.gs_reg_test_a[i]._fetch_instances()

            for i in range(len(self.gs_reg_test_b)):
                pass
                self.gs_reg_test_b[i]._fetch_instances()

            for i in range(len(self.gs_reg_test_c)):
                pass
                self.gs_reg_test_c[i]._fetch_instances()

            for i in range(len(self.gs_reg_test_d)):
                pass
                self.gs_reg_test_d[i]._fetch_instances()

            for i in range(len(self.gs_reg_texa_a)):
                pass
                self.gs_reg_texa_a[i]._fetch_instances()

            for i in range(len(self.gs_reg_texa_b)):
                pass
                self.gs_reg_texa_b[i]._fetch_instances()

            for i in range(len(self.gs_reg_zbuf_a)):
                pass
                self.gs_reg_zbuf_a[i]._fetch_instances()

            for i in range(len(self.gs_reg_zbuf_b)):
                pass
                self.gs_reg_zbuf_b[i]._fetch_instances()

            for i in range(len(self.gs_reg_pabe_a)):
                pass
                self.gs_reg_pabe_a[i]._fetch_instances()

            for i in range(len(self.gs_reg_pabe_b)):
                pass
                self.gs_reg_pabe_b[i]._fetch_instances()

            for i in range(len(self.gs_reg_fba_a)):
                pass
                self.gs_reg_fba_a[i]._fetch_instances()

            for i in range(len(self.gs_reg_fba_b)):
                pass
                self.gs_reg_fba_b[i]._fetch_instances()

            for i in range(len(self.gs_reg_prmodecont_a)):
                pass
                self.gs_reg_prmodecont_a[i]._fetch_instances()

            for i in range(len(self.gs_reg_prmodecont_b)):
                pass
                self.gs_reg_prmodecont_b[i]._fetch_instances()

            for i in range(len(self.gs_sync_dummy_label)):
                pass
                self.gs_sync_dummy_label[i]._fetch_instances()

            for i in range(len(self.gs_sync_dummy_texflush)):
                pass
                self.gs_sync_dummy_texflush[i]._fetch_instances()

            self.now_draw_env._fetch_instances()


    class ShGsDrawEnv(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShGsDrawEnv, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.giftag = Sh2.SceGifTag(self._io, self, self._root)
            self.draw = Sh2.SceGsDrawEnv1(self._io, self, self._root)
            self.drawq2 = []
            for i in range(5):
                self.drawq2.append(Sh2.QWorddata(self._io, self, self._root))

            self.clear = Sh2.SceGsClear(self._io, self, self._root)
            self.giftag_nc = Sh2.SceGifTag(self._io, self, self._root)
            self.draw_nc = Sh2.SceGsDrawEnv1(self._io, self, self._root)
            self.drawq2_nc = []
            for i in range(5):
                self.drawq2_nc.append(Sh2.QWorddata(self._io, self, self._root))

            self._raw_gifad_frame_normal = self._io.read_bytes(16)
            _io__raw_gifad_frame_normal = KaitaiStream(BytesIO(self._raw_gifad_frame_normal))
            self.gifad_frame_normal = Sh2.QWorddata(_io__raw_gifad_frame_normal, self, self._root)
            self._raw_frame_normal = self._io.read_bytes(16)
            _io__raw_frame_normal = KaitaiStream(BytesIO(self._raw_frame_normal))
            self.frame_normal = Sh2.QWorddata(_io__raw_frame_normal, self, self._root)
            self._raw_gifad_frame_mskalpha = self._io.read_bytes(16)
            _io__raw_gifad_frame_mskalpha = KaitaiStream(BytesIO(self._raw_gifad_frame_mskalpha))
            self.gifad_frame_mskalpha = Sh2.QWorddata(_io__raw_gifad_frame_mskalpha, self, self._root)
            self._raw_frame_mskalpha = self._io.read_bytes(16)
            _io__raw_frame_mskalpha = KaitaiStream(BytesIO(self._raw_frame_mskalpha))
            self.frame_mskalpha = Sh2.QWorddata(_io__raw_frame_mskalpha, self, self._root)
            self._raw_gifad_frame_msk_dalpha = self._io.read_bytes(16)
            _io__raw_gifad_frame_msk_dalpha = KaitaiStream(BytesIO(self._raw_gifad_frame_msk_dalpha))
            self.gifad_frame_msk_dalpha = Sh2.QWorddata(_io__raw_gifad_frame_msk_dalpha, self, self._root)
            self._raw_frame_msk_dalpha = self._io.read_bytes(16)
            _io__raw_frame_msk_dalpha = KaitaiStream(BytesIO(self._raw_frame_msk_dalpha))
            self.frame_msk_dalpha = Sh2.QWorddata(_io__raw_frame_msk_dalpha, self, self._root)
            self._raw_gifad_frame_msk_rgb = self._io.read_bytes(16)
            _io__raw_gifad_frame_msk_rgb = KaitaiStream(BytesIO(self._raw_gifad_frame_msk_rgb))
            self.gifad_frame_msk_rgb = Sh2.QWorddata(_io__raw_gifad_frame_msk_rgb, self, self._root)
            self._raw_frame_msk_rgb = self._io.read_bytes(16)
            _io__raw_frame_msk_rgb = KaitaiStream(BytesIO(self._raw_frame_msk_rgb))
            self.frame_msk_rgb = Sh2.QWorddata(_io__raw_frame_msk_rgb, self, self._root)


        def _fetch_instances(self):
            pass
            self.giftag._fetch_instances()
            self.draw._fetch_instances()
            for i in range(len(self.drawq2)):
                pass
                self.drawq2[i]._fetch_instances()

            self.clear._fetch_instances()
            self.giftag_nc._fetch_instances()
            self.draw_nc._fetch_instances()
            for i in range(len(self.drawq2_nc)):
                pass
                self.drawq2_nc[i]._fetch_instances()

            self.gifad_frame_normal._fetch_instances()
            self.frame_normal._fetch_instances()
            self.gifad_frame_mskalpha._fetch_instances()
            self.frame_mskalpha._fetch_instances()
            self.gifad_frame_msk_dalpha._fetch_instances()
            self.frame_msk_dalpha._fetch_instances()
            self.gifad_frame_msk_rgb._fetch_instances()
            self.frame_msk_rgb._fetch_instances()


    class ShGsLoopEnv(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShGsLoopEnv, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.gs_draw_fb_ps = []
            for i in range(3):
                self.gs_draw_fb_ps.append(self._io.read_u4le())

            self.gs_now_disp_fb_ps = []
            for i in range(3):
                self.gs_now_disp_fb_ps.append(self._io.read_u4le())

            self.gs_next_disp_fb_ps = []
            for i in range(3):
                self.gs_next_disp_fb_ps.append(self._io.read_u4le())

            self.gs_tex_tb_ps = []
            for i in range(24):
                self.gs_tex_tb_ps.append(self._io.read_u4le())

            self.gs_shadow_fbp = []
            for i in range(3):
                self.gs_shadow_fbp.append(self._io.read_u4le())

            self.gs_shadow_work_fbp = []
            for i in range(3):
                self.gs_shadow_work_fbp.append(self._io.read_u4le())

            self.clutsize = self._io.read_u2le()
            self.clutamount = self._io.read_u2le()
            self.gs_clut_page = []
            for i in range(8):
                self.gs_clut_page.append(self._io.read_u2le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.gs_draw_fb_ps)):
                pass

            for i in range(len(self.gs_now_disp_fb_ps)):
                pass

            for i in range(len(self.gs_next_disp_fb_ps)):
                pass

            for i in range(len(self.gs_tex_tb_ps)):
                pass

            for i in range(len(self.gs_shadow_fbp)):
                pass

            for i in range(len(self.gs_shadow_work_fbp)):
                pass

            for i in range(len(self.gs_clut_page)):
                pass



    class ShGsStencilDrawEnv(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShGsStencilDrawEnv, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.giftag = Sh2.SceGifTag(self._io, self, self._root)
            self.draw = Sh2.SceGsDrawEnv1(self._io, self, self._root)
            self._raw_alpha1 = self._io.read_bytes(16)
            _io__raw_alpha1 = KaitaiStream(BytesIO(self._raw_alpha1))
            self.alpha1 = Sh2.QWorddata(_io__raw_alpha1, self, self._root)
            self.drawq2 = []
            for i in range(6):
                self.drawq2.append(Sh2.QWorddata(self._io, self, self._root))

            self.clear = Sh2.SceGsClear(self._io, self, self._root)
            self._raw_frame = self._io.read_bytes(16)
            _io__raw_frame = KaitaiStream(BytesIO(self._raw_frame))
            self.frame = Sh2.QWorddata(_io__raw_frame, self, self._root)
            self.giftag_nc = Sh2.SceGifTag(self._io, self, self._root)
            self.draw_nc = Sh2.SceGsDrawEnv1(self._io, self, self._root)
            self._raw_alpha1_nc = self._io.read_bytes(16)
            _io__raw_alpha1_nc = KaitaiStream(BytesIO(self._raw_alpha1_nc))
            self.alpha1_nc = Sh2.QWorddata(_io__raw_alpha1_nc, self, self._root)
            self.drawq2_nc = []
            for i in range(6):
                self.drawq2_nc.append(Sh2.QWorddata(self._io, self, self._root))

            self._raw_gifad_frame_normal = self._io.read_bytes(16)
            _io__raw_gifad_frame_normal = KaitaiStream(BytesIO(self._raw_gifad_frame_normal))
            self.gifad_frame_normal = Sh2.QWorddata(_io__raw_gifad_frame_normal, self, self._root)
            self._raw_frame_normal = self._io.read_bytes(16)
            _io__raw_frame_normal = KaitaiStream(BytesIO(self._raw_frame_normal))
            self.frame_normal = Sh2.QWorddata(_io__raw_frame_normal, self, self._root)
            self._raw_gifad_frame_mskalpha = self._io.read_bytes(16)
            _io__raw_gifad_frame_mskalpha = KaitaiStream(BytesIO(self._raw_gifad_frame_mskalpha))
            self.gifad_frame_mskalpha = Sh2.QWorddata(_io__raw_gifad_frame_mskalpha, self, self._root)
            self._raw_frame_mskalpha = self._io.read_bytes(16)
            _io__raw_frame_mskalpha = KaitaiStream(BytesIO(self._raw_frame_mskalpha))
            self.frame_mskalpha = Sh2.QWorddata(_io__raw_frame_mskalpha, self, self._root)
            self._raw_gifad_frame_msk_dalpha = self._io.read_bytes(16)
            _io__raw_gifad_frame_msk_dalpha = KaitaiStream(BytesIO(self._raw_gifad_frame_msk_dalpha))
            self.gifad_frame_msk_dalpha = Sh2.QWorddata(_io__raw_gifad_frame_msk_dalpha, self, self._root)
            self._raw_frame_msk_dalpha = self._io.read_bytes(16)
            _io__raw_frame_msk_dalpha = KaitaiStream(BytesIO(self._raw_frame_msk_dalpha))
            self.frame_msk_dalpha = Sh2.QWorddata(_io__raw_frame_msk_dalpha, self, self._root)


        def _fetch_instances(self):
            pass
            self.giftag._fetch_instances()
            self.draw._fetch_instances()
            self.alpha1._fetch_instances()
            for i in range(len(self.drawq2)):
                pass
                self.drawq2[i]._fetch_instances()

            self.clear._fetch_instances()
            self.frame._fetch_instances()
            self.giftag_nc._fetch_instances()
            self.draw_nc._fetch_instances()
            self.alpha1_nc._fetch_instances()
            for i in range(len(self.drawq2_nc)):
                pass
                self.drawq2_nc[i]._fetch_instances()

            self.gifad_frame_normal._fetch_instances()
            self.frame_normal._fetch_instances()
            self.gifad_frame_mskalpha._fetch_instances()
            self.frame_mskalpha._fetch_instances()
            self.gifad_frame_msk_dalpha._fetch_instances()
            self.frame_msk_dalpha._fetch_instances()


    class ShGsTinyDrawEnv(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShGsTinyDrawEnv, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._raw_giftag = self._io.read_bytes(16)
            _io__raw_giftag = KaitaiStream(BytesIO(self._raw_giftag))
            self.giftag = Sh2.QWorddata(_io__raw_giftag, self, self._root)
            self._raw_frame = self._io.read_bytes(16)
            _io__raw_frame = KaitaiStream(BytesIO(self._raw_frame))
            self.frame = Sh2.QWorddata(_io__raw_frame, self, self._root)
            self._raw_scissor = self._io.read_bytes(16)
            _io__raw_scissor = KaitaiStream(BytesIO(self._raw_scissor))
            self.scissor = Sh2.QWorddata(_io__raw_scissor, self, self._root)
            self._raw_xyoffset = self._io.read_bytes(16)
            _io__raw_xyoffset = KaitaiStream(BytesIO(self._raw_xyoffset))
            self.xyoffset = Sh2.QWorddata(_io__raw_xyoffset, self, self._root)
            self._raw_zbuf = self._io.read_bytes(16)
            _io__raw_zbuf = KaitaiStream(BytesIO(self._raw_zbuf))
            self.zbuf = Sh2.QWorddata(_io__raw_zbuf, self, self._root)
            self._raw_test = self._io.read_bytes(16)
            _io__raw_test = KaitaiStream(BytesIO(self._raw_test))
            self.test = Sh2.QWorddata(_io__raw_test, self, self._root)
            self._raw_gifad_normal = self._io.read_bytes(16)
            _io__raw_gifad_normal = KaitaiStream(BytesIO(self._raw_gifad_normal))
            self.gifad_normal = Sh2.QWorddata(_io__raw_gifad_normal, self, self._root)
            self._raw_frame_normal = self._io.read_bytes(16)
            _io__raw_frame_normal = KaitaiStream(BytesIO(self._raw_frame_normal))
            self.frame_normal = Sh2.QWorddata(_io__raw_frame_normal, self, self._root)
            self._raw_gifad_mskalpha = self._io.read_bytes(16)
            _io__raw_gifad_mskalpha = KaitaiStream(BytesIO(self._raw_gifad_mskalpha))
            self.gifad_mskalpha = Sh2.QWorddata(_io__raw_gifad_mskalpha, self, self._root)
            self._raw_frame_mskalpha = self._io.read_bytes(16)
            _io__raw_frame_mskalpha = KaitaiStream(BytesIO(self._raw_frame_mskalpha))
            self.frame_mskalpha = Sh2.QWorddata(_io__raw_frame_mskalpha, self, self._root)
            self._raw_gifad_msk_dalpha = self._io.read_bytes(16)
            _io__raw_gifad_msk_dalpha = KaitaiStream(BytesIO(self._raw_gifad_msk_dalpha))
            self.gifad_msk_dalpha = Sh2.QWorddata(_io__raw_gifad_msk_dalpha, self, self._root)
            self._raw_frame_msk_dalpha = self._io.read_bytes(16)
            _io__raw_frame_msk_dalpha = KaitaiStream(BytesIO(self._raw_frame_msk_dalpha))
            self.frame_msk_dalpha = Sh2.QWorddata(_io__raw_frame_msk_dalpha, self, self._root)


        def _fetch_instances(self):
            pass
            self.giftag._fetch_instances()
            self.frame._fetch_instances()
            self.scissor._fetch_instances()
            self.xyoffset._fetch_instances()
            self.zbuf._fetch_instances()
            self.test._fetch_instances()
            self.gifad_normal._fetch_instances()
            self.frame_normal._fetch_instances()
            self.gifad_mskalpha._fetch_instances()
            self.frame_mskalpha._fetch_instances()
            self.gifad_msk_dalpha._fetch_instances()
            self.frame_msk_dalpha._fetch_instances()


    class ShInArea(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShInArea, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.look_on = self._io.read_bits_int_le(2)
            self.feel_on = self._io.read_bits_int_le(2)
            self.light_on = self._io.read_bits_int_le(4)


        def _fetch_instances(self):
            pass


    class ShInAreaTgtInfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShInAreaTgtInfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._raw_adr = self._io.read_bytes(4)
            _io__raw_adr = KaitaiStream(BytesIO(self._raw_adr))
            self.adr = Sh2.ShInAreaTgtInfoAnon4(_io__raw_adr, self, self._root)
            self.distance = self._io.read_f4le()
            self.in_area = Sh2.ShInArea(self._io, self, self._root)
            self._unnamed3 = self._io.read_bytes(3)


        def _fetch_instances(self):
            pass
            self.adr._fetch_instances()
            self.in_area._fetch_instances()


    class ShInAreaTgtInfoAnon4(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShInAreaTgtInfoAnon4, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._unnamed0 = self._io.read_bytes(4)


        def _fetch_instances(self):
            pass
            _ = self.scp
            if hasattr(self, '_m_scp'):
                pass
                self._m_scp._fetch_instances()


        @property
        def scp(self):
            if hasattr(self, '_m_scp'):
                return self._m_scp

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_scp = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_scp', None)


    class ShItemScreenObjectSettingData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShItemScreenObjectSettingData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.chara_id = self._io.read_s4le()
            self.scale = self._io.read_f4le()
            self._unnamed2 = self._io.read_bytes(8)
            self.rot = Sh2.Vector4(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.rot._fetch_instances()


    class ShMariaWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShMariaWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.mar_p = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self._unnamed1 = self._io.read_bytes(12)
            self.dist_rot = Sh2.Vector4(self._io, self, self._root)
            self.dist_pos = Sh2.Vector4(self._io, self, self._root)
            self.pos = Sh2.Vector4(self._io, self, self._root)
            self.rot = Sh2.Vector4(self._io, self, self._root)
            self.to_target = self._io.read_f4le()
            self._unnamed7 = self._io.read_bytes(12)
            self.tgt_pos = []
            for i in range(20):
                self.tgt_pos.append(self._io.read_f4le())

            self.tgt_pointer = self._io.read_s4le()
            self.pushed_dir = self._io.read_s4le()
            self.main_status_now = self._io.read_u1()
            self.main_status_prev = self._io.read_u1()
            self.sub_status_now = self._io.read_u1()
            self.sub_status_prev = self._io.read_u1()
            self.sub_st_flg = self._io.read_u4le()
            self.anime_st_flg = self._io.read_u4le()
            self.anime_pause = self._io.read_u4le()
            self._unnamed18 = self._io.read_bytes(8)
            self.r_forward = Sh2.ClVhitResult(self._io, self, self._root)
            self.l_forward = Sh2.ClVhitResult(self._io, self, self._root)
            self.forward = Sh2.ClVhitResult(self._io, self, self._root)
            self.ft_floor = Sh2.ClVhitResult(self._io, self, self._root)
            self.r_foot = Sh2.ClVhitResult(self._io, self, self._root)
            self.l_foot = Sh2.ClVhitResult(self._io, self, self._root)
            self.column_mov = Sh2.ClHitpolyColumn(self._io, self, self._root)
            self.column_atk = Sh2.ClHitpolyColumn(self._io, self, self._root)
            self.col_mov_z_hosei = self._io.read_f4le()
            self.col_atk_z_hosei = self._io.read_f4le()
            self.se_upper = []
            for i in range(4):
                self.se_upper.append(self._io.read_u1())

            self.se_foot = []
            for i in range(4):
                self.se_foot.append(self._io.read_u1())

            self.tgt_neck_angle = Sh2.Vector4(self._io, self, self._root)
            self.look_tgt = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.look_obj = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.dist_to_jms = self._io.read_f4le()
            self.hp_recover = self._io.read_f4le()
            self.stand_time = self._io.read_f4le()
            self.move_time = self._io.read_f4le()
            self.muteki_time = self._io.read_f4le()
            self.relax_time = self._io.read_f4le()
            self.afraid_time = self._io.read_f4le()
            self.hp = self._io.read_f4le()
            self.hp_max = self._io.read_f4le()
            self.tired = self._io.read_s4le()
            self.tired_max = self._io.read_s4le()
            self.relax_flag = self._io.read_u1()
            self.no_damage = self._io.read_u1()
            self.dead = self._io.read_u1()
            self._unnamed48 = self._io.read_bytes(1)
            self.damage_no = self._io.read_u2le()
            self.enemy_around = self._io.read_u1()
            self.enemy_atk_area = self._io.read_u1()
            self.look_jms = self._io.read_u1()
            self.random_status = self._io.read_u1()
            self.active_type = self._io.read_u1()
            self._unnamed55 = self._io.read_bytes(1)


        def _fetch_instances(self):
            pass
            self.mar_p._fetch_instances()
            self.dist_rot._fetch_instances()
            self.dist_pos._fetch_instances()
            self.pos._fetch_instances()
            self.rot._fetch_instances()
            for i in range(len(self.tgt_pos)):
                pass

            self.r_forward._fetch_instances()
            self.l_forward._fetch_instances()
            self.forward._fetch_instances()
            self.ft_floor._fetch_instances()
            self.r_foot._fetch_instances()
            self.l_foot._fetch_instances()
            self.column_mov._fetch_instances()
            self.column_atk._fetch_instances()
            for i in range(len(self.se_upper)):
                pass

            for i in range(len(self.se_foot)):
                pass

            self.tgt_neck_angle._fetch_instances()
            self.look_tgt._fetch_instances()
            self.look_obj._fetch_instances()


    class ShPlayerWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShPlayerWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.player = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self._unnamed1 = self._io.read_bytes(12)
            self.dist_rot = Sh2.Vector4(self._io, self, self._root)
            self.dist_pos = Sh2.Vector4(self._io, self, self._root)
            self.pos = Sh2.Vector4(self._io, self, self._root)
            self.rot = Sh2.Vector4(self._io, self, self._root)
            self.rot_y = self._io.read_f4le()
            self.inner_to_wall = self._io.read_f4le()
            self.dist_to_wall = self._io.read_f4le()
            self.dir_tgt_2d = self._io.read_f4le()
            self.dir_now_2d = self._io.read_f4le()
            self.map_mode = self._io.read_u1()
            self.reserve0 = self._io.read_u1()
            self.step = self._io.read_u1()
            self.sub_step = self._io.read_u1()
            self.timer = self._io.read_u2le()
            self.timer2 = self._io.read_u2le()
            self.allbody_now = self._io.read_u4le()
            self.upper_now = self._io.read_u1()
            self.lower_now = self._io.read_u1()
            self._unnamed20 = self._io.read_bytes(2)
            self.allbody_prev = self._io.read_u4le()
            self.upper_prev = self._io.read_u1()
            self.lower_prev = self._io.read_u1()
            self.event_status_now = self._io.read_u1()
            self.event_status_prev = self._io.read_u1()
            self.event_move_mode = self._io.read_u1()
            self.reserve1 = self._io.read_u1()
            self._unnamed28 = self._io.read_bytes(2)
            self.upper_st_flg = self._io.read_u4le()
            self.lower_st_flg = self._io.read_u4le()
            self.u_anime_st_flg = self._io.read_u4le()
            self.l_anime_st_flg = self._io.read_u4le()
            self.anime_pause = self._io.read_u4le()
            self.act_with_wep = self._io.read_u4le()
            self.light_vec_inner_rate = self._io.read_f4le()
            self._unnamed36 = self._io.read_bytes(4)
            self.light_pos_revise = []
            for i in range(4):
                self.light_pos_revise.append(self._io.read_f4le())

            self.light_vec_revise = []
            for i in range(4):
                self.light_vec_revise.append(self._io.read_f4le())

            self.light_pos = []
            for i in range(4):
                self.light_pos.append(self._io.read_f4le())

            self.light_vec = []
            for i in range(4):
                self.light_vec.append(self._io.read_f4le())

            self.light_pos_revise_reverse = []
            for i in range(4):
                self.light_pos_revise_reverse.append(self._io.read_f4le())

            self.light_vec_revise_reverse = []
            for i in range(4):
                self.light_vec_revise_reverse.append(self._io.read_f4le())

            self.light_pos_reverse = []
            for i in range(4):
                self.light_pos_reverse.append(self._io.read_f4le())

            self.light_vec_reverse = []
            for i in range(4):
                self.light_vec_reverse.append(self._io.read_f4le())

            self.light_vec_neck = []
            for i in range(4):
                self.light_vec_neck.append(self._io.read_f4le())

            self.room_name_prev = self._io.read_s4le()
            self.room_name_now = self._io.read_s4le()
            self._unnamed48 = self._io.read_bytes(8)
            self.r_side = Sh2.ClVhitResult(self._io, self, self._root)
            self.l_side = Sh2.ClVhitResult(self._io, self, self._root)
            self.foot = Sh2.ClVhitResult(self._io, self, self._root)
            self.ft_floor = Sh2.ClVhitResult(self._io, self, self._root)
            self.r_foot = Sh2.ClVhitResult(self._io, self, self._root)
            self.l_foot = Sh2.ClVhitResult(self._io, self, self._root)
            self.column_mov = Sh2.ClHitpolyColumn(self._io, self, self._root)
            self.column_atk = Sh2.ClHitpolyColumn(self._io, self, self._root)
            self.col_mov_z_hosei = self._io.read_f4le()
            self.col_atk_z_hosei = self._io.read_f4le()
            self.wep_no_hit_floor = self._io.read_u1()
            self.efct_upper = self._io.read_u1()
            self.light_reverse = self._io.read_u1()
            self.water_road = self._io.read_u1()
            self.pad = []
            for i in range(10):
                self.pad.append(Sh2.PadInfo(self._io, self, self._root))

            self.rstick_x = self._io.read_f4le()
            self.rstick_y = self._io.read_f4le()
            self.lstick_x = self._io.read_f4le()
            self.lstick_y = self._io.read_f4le()
            self.lstick_p = self._io.read_f4le()
            self.cam_rot_y = []
            for i in range(2):
                self.cam_rot_y.append(self._io.read_f4le())

            self.now_cam_no = self._io.read_u1()
            self.cam_chg_flg = self._io.read_u1()
            self.ctrl_unit = self._io.read_u1()
            self.ctrl_inputing = self._io.read_u1()
            self.se_upper = []
            for i in range(4):
                self.se_upper.append(self._io.read_u1())

            self.se_foot = []
            for i in range(4):
                self.se_foot.append(self._io.read_u1())

            self.csaw_se_vol = self._io.read_f4le()
            self.csaw_se_flg = self._io.read_u1()
            self.d_shock = self._io.read_u1()
            self.reserve2 = self._io.read_u1()
            self.strike_splash_flg = self._io.read_u1()
            self.event_anime = self._io.read_s4le()
            self.tgt_body_angle = Sh2.Vector4(self._io, self, self._root)
            self.tgt_neck_angle = Sh2.Vector4(self._io, self, self._root)
            self.tgt_arms_angle = Sh2.Vector4(self._io, self, self._root)
            self.hold_chg = []
            for i in range(2):
                self.hold_chg.append(self._io.read_u1())

            self.hold_loop = []
            for i in range(2):
                self.hold_loop.append(self._io.read_u1())

            self.motion_no = self._io.read_u1()
            self.shotgun_dir = self._io.read_u1()
            self.shotgun_prev = self._io.read_u1()
            self.guard_check = self._io.read_u1()
            self.parts_light = self._io.read_s4le()
            self.parts_rhand = self._io.read_s4le()
            self.parts_lhand = self._io.read_s4le()
            self.target = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.look_tgt = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.non_input = self._io.read_f4le()
            self.hugging_gauge = self._io.read_f4le()
            self.running_time = self._io.read_f4le()
            self.muteki_time = self._io.read_f4le()
            self.hp = self._io.read_f4le()
            self.hp_max = self._io.read_f4le()
            self.hp_recover = self._io.read_f4le()
            self.shock = self._io.read_f4le()
            self.spray_time = self._io.read_f4le()
            self.tired = self._io.read_s4le()
            self.tired_max = self._io.read_s4le()
            self.spirit = self._io.read_s4le()
            self.enemy_liedown = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.enemy_around = self._io.read_u1()
            self.enemy_atk_area = self._io.read_u1()
            self.enemy_near = self._io.read_u1()
            self.lock_on = self._io.read_u1()
            self.running = self._io.read_u1()
            self.cannot_run = self._io.read_u1()
            self.fall_type = self._io.read_u1()
            self.reload = self._io.read_u1()
            self.weapon = self._io.read_u1()
            self.shoot_val = self._io.read_u1()
            self.reload_val = self._io.read_u1()
            self.atk_type = self._io.read_u1()
            self.atk_reserve = []
            for i in range(2):
                self.atk_reserve.append(self._io.read_u1())

            self.attack_ok = self._io.read_u1()
            self.hold_type = self._io.read_s1()
            self.dead = self._io.read_u1()
            self.no_damage = self._io.read_u1()
            self.atk_count = self._io.read_u1()
            self.hug_status = self._io.read_u1()
            self.hug_dir = self._io.read_u1()
            self.se_on = self._io.read_u1()
            self.spray_set = self._io.read_u1()
            self.spray_pow = self._io.read_s1()
            self.damage_no = self._io.read_u2le()
            self.attack_no = self._io.read_u2le()
            self._unnamed134 = self._io.read_bytes(4)


        def _fetch_instances(self):
            pass
            self.player._fetch_instances()
            self.dist_rot._fetch_instances()
            self.dist_pos._fetch_instances()
            self.pos._fetch_instances()
            self.rot._fetch_instances()
            for i in range(len(self.light_pos_revise)):
                pass

            for i in range(len(self.light_vec_revise)):
                pass

            for i in range(len(self.light_pos)):
                pass

            for i in range(len(self.light_vec)):
                pass

            for i in range(len(self.light_pos_revise_reverse)):
                pass

            for i in range(len(self.light_vec_revise_reverse)):
                pass

            for i in range(len(self.light_pos_reverse)):
                pass

            for i in range(len(self.light_vec_reverse)):
                pass

            for i in range(len(self.light_vec_neck)):
                pass

            self.r_side._fetch_instances()
            self.l_side._fetch_instances()
            self.foot._fetch_instances()
            self.ft_floor._fetch_instances()
            self.r_foot._fetch_instances()
            self.l_foot._fetch_instances()
            self.column_mov._fetch_instances()
            self.column_atk._fetch_instances()
            for i in range(len(self.pad)):
                pass
                self.pad[i]._fetch_instances()

            for i in range(len(self.cam_rot_y)):
                pass

            for i in range(len(self.se_upper)):
                pass

            for i in range(len(self.se_foot)):
                pass

            self.tgt_body_angle._fetch_instances()
            self.tgt_neck_angle._fetch_instances()
            self.tgt_arms_angle._fetch_instances()
            for i in range(len(self.hold_chg)):
                pass

            for i in range(len(self.hold_loop)):
                pass

            self.target._fetch_instances()
            self.look_tgt._fetch_instances()
            self.enemy_liedown._fetch_instances()
            for i in range(len(self.atk_reserve)):
                pass



    class ShSkelton(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShSkelton, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.next = Sh2.Pointer(u"sh_skelton", self._io, self, self._root)
            self.parent = Sh2.Pointer(u"sh_skelton", self._io, self, self._root)
            self._unnamed2 = self._io.read_bytes(8)
            self.src_m = Sh2.Matrix4(self._io, self, self._root)
            self.src_t = Sh2.Vector4(self._io, self, self._root)
            self.des_m = Sh2.Matrix4(self._io, self, self._root)
            self.des_t = Sh2.Vector4(self._io, self, self._root)
            self.axis = Sh2.Vector4(self._io, self, self._root)
            self.theta = self._io.read_f4le()
            self.xx = self._io.read_f4le()
            self.yy = self._io.read_f4le()
            self.zz = self._io.read_f4le()
            self.xy = self._io.read_f4le()
            self.yz = self._io.read_f4le()
            self.zx = self._io.read_f4le()
            self.c_count = self._io.read_u2le()
            self.c_speed = self._io.read_u2le()
            self.change = self._io.read_s1()
            self.reserved = self._io.read_s1()
            self.is_key = self._io.read_s1()
            self.pad = self._io.read_s1()
            self.untouchable = Sh2.Pointer(u"data", self._io, self, self._root)
            self._unnamed22 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            self.next._fetch_instances()
            self.parent._fetch_instances()
            self.src_m._fetch_instances()
            self.src_t._fetch_instances()
            self.des_m._fetch_instances()
            self.des_t._fetch_instances()
            self.axis._fetch_instances()
            self.untouchable._fetch_instances()


    class ShSkeltonWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ShSkeltonWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.work = []
            for i in range(400):
                self.work.append(Sh2.ShSkelton(self._io, self, self._root))

            self.free = Sh2.Pointer(u"sh_skelton", self._io, self, self._root)
            self.last = self._io.read_s4le()
            self._unnamed3 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            for i in range(len(self.work)):
                pass
                self.work[i]._fetch_instances()

            self.free._fetch_instances()


    class SndRoadArea(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SndRoadArea, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x0 = self._io.read_f4le()
            self.z0 = self._io.read_f4le()
            self.x1 = self._io.read_f4le()
            self.z1 = self._io.read_f4le()
            self.x2 = self._io.read_f4le()
            self.z2 = self._io.read_f4le()
            self.min_hy = self._io.read_f4le()
            self.max_hy = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class SoundData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SoundData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.lim_sw = Sh2.SndRoadArea(self._io, self, self._root)
            self.flags = self._io.read_s4le()
            self.chanstat = []
            for i in range(7):
                self.chanstat.append(self._io.read_s4le())



        def _fetch_instances(self):
            pass
            self.lim_sw._fetch_instances()
            for i in range(len(self.chanstat)):
                pass



    class SoundWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SoundWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.sound_ary = Sh2.Pointer(u"sound_data", self._io, self, self._root)
            self._unnamed1 = self._io.read_bytes(12)
            self.chara_pos = []
            for i in range(4):
                self.chara_pos.append(self._io.read_f4le())

            self.half_w = self._io.read_f4le()
            self.page = self._io.read_s4le()
            self.near_sound_num = self._io.read_s4le()
            self.near_sound_ary = []
            for i in range(8):
                self.near_sound_ary.append(Sh2.NearSoundData(self._io, self, self._root))

            self.on_num = self._io.read_s4le()
            self.on_chan = []
            for i in range(7):
                self.on_chan.append(self._io.read_s1())

            self._unnamed9 = self._io.read_bytes(1)
            self.abs_num = self._io.read_s4le()
            self.nearindex = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.sound_ary._fetch_instances()
            for i in range(len(self.chara_pos)):
                pass

            for i in range(len(self.near_sound_ary)):
                pass
                self.near_sound_ary[i]._fetch_instances()

            for i in range(len(self.on_chan)):
                pass



    class SpuStreamBody(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SpuStreamBody, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.id = []
            for i in range(4):
                self.id.append(self._io.read_s1())

            self.size = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.id)):
                pass



    class SpuStreamHeader(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SpuStreamHeader, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.id = []
            for i in range(4):
                self.id.append(self._io.read_s1())

            self.size = self._io.read_s4le()
            self.type = self._io.read_s4le()
            self.rate = self._io.read_s4le()
            self.ch = self._io.read_s4le()
            self.inter_size = self._io.read_s4le()
            self.loop_start = self._io.read_s4le()
            self.loop_end = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.id)):
                pass



    class StageData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.StageData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.ev_list = Sh2.Pointer(u"event_list", self._io, self, self._root)
            self.ev_pos = Sh2.Pointer(u"data", self._io, self, self._root)
            self.ev_prog = Sh2.Pointer(u"data", self._io, self, self._root)
            self.gi_list = Sh2.Pointer(u"item_list", self._io, self, self._root)
            self.mdl_list = Sh2.Pointer(u"model_list", self._io, self, self._root)
            self.en_list = Sh2.Pointer(u"enemy_list", self._io, self, self._root)
            self.stage_init = Sh2.Pointer(u"data", self._io, self, self._root)
            self.room_init = Sh2.Pointer(u"data", self._io, self, self._root)
            self.alltime_func = Sh2.Pointer(u"data", self._io, self, self._root)
            self.glb_crd = self._io.read_s4le()
            self.pc_model = self._io.read_s4le()
            self.stg_anim_info = Sh2.Pointer(u"anime_info", self._io, self, self._root)
            self.bgm_control = Sh2.Pointer(u"data", self._io, self, self._root)
            self.gfw_func = Sh2.Pointer(u"gfw_func", self._io, self, self._root)
            self.chara_data_clear = Sh2.Pointer(u"data", self._io, self, self._root)
            self.sound_call_after_load = Sh2.Pointer(u"data", self._io, self, self._root)
            self.reserve_11 = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.ev_list._fetch_instances()
            self.ev_pos._fetch_instances()
            self.ev_prog._fetch_instances()
            self.gi_list._fetch_instances()
            self.mdl_list._fetch_instances()
            self.en_list._fetch_instances()
            self.stage_init._fetch_instances()
            self.room_init._fetch_instances()
            self.alltime_func._fetch_instances()
            self.stg_anim_info._fetch_instances()
            self.bgm_control._fetch_instances()
            self.gfw_func._fetch_instances()
            self.chara_data_clear._fetch_instances()
            self.sound_call_after_load._fetch_instances()


    class StrFile(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.StrFile, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.is_on_cd = self._io.read_s4le()
            self.size = self._io.read_s4le()
            self.fp = Sh2.SceCdlFile(self._io, self, self._root)
            self.iop_buf = Sh2.Pointer(u"data", self._io, self, self._root)
            self.fd = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.fp._fetch_instances()
            self.iop_buf._fetch_instances()


    class SubCharacter(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SubCharacter, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.index = self._io.read_s4le()
            self.status = self._io.read_u4le()
            self.sub_status = self._io.read_u4le()
            self.sub_st = self._io.read_u4le()
            self.kind = self._io.read_s2le()
            self.id = self._io.read_s2le()
            self.step = self._io.read_u4le()
            self.model_type = self._io.read_u4le()
            self._unnamed8 = self._io.read_bytes(4)
            self.pos = Sh2.Vector4(self._io, self, self._root)
            self.rot = Sh2.Vector4(self._io, self, self._root)
            self.pos_spd = Sh2.Vector4(self._io, self, self._root)
            self.rot_spd = Sh2.Vector4(self._io, self, self._root)
            self.mat = []
            for i in range(16):
                self.mat.append(self._io.read_f4le())

            self.sk_top = Sh2.Pointer(u"sh_skelton", self._io, self, self._root)
            self.eye_y = self._io.read_f4le()
            self.center_y = self._io.read_f4le()
            self.spd = self._io.read_f4le()
            self.spd_org = self._io.read_f4le()
            self.spd_y = self._io.read_f4le()
            self.spd_roty = self._io.read_f4le()
            self._unnamed21 = self._io.read_bytes(4)
            self.grnd_normal = []
            for i in range(4):
                self.grnd_normal.append(self._io.read_f4le())

            self.grnd_height = self._io.read_f4le()
            self._unnamed24 = self._io.read_bytes(12)
            self.b_pos = Sh2.Vector4(self._io, self, self._root)
            self.b_rot = Sh2.Vector4(self._io, self, self._root)
            self.en_first_status = self._io.read_s4le()
            self.colis_fall_timer = self._io.read_s4le()
            self._unnamed29 = self._io.read_bytes(8)
            self.battle = Sh2.ShBattleInfo(self._io, self, self._root)
            self.eye = Sh2.ClVhitResult(self._io, self, self._root)
            self.function = Sh2.Pointer(u"data", self._io, self, self._root)
            self.effecter_function = Sh2.Pointer(u"data", self._io, self, self._root)
            self.pre = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.next = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.work = []
            for i in range(4):
                self.work.append(self._io.read_u1())

            self.enemy_p = Sh2.Pointer(u"data", self._io, self, self._root)
            self._unnamed38 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            self.pos._fetch_instances()
            self.rot._fetch_instances()
            self.pos_spd._fetch_instances()
            self.rot_spd._fetch_instances()
            for i in range(len(self.mat)):
                pass

            self.sk_top._fetch_instances()
            for i in range(len(self.grnd_normal)):
                pass

            self.b_pos._fetch_instances()
            self.b_rot._fetch_instances()
            self.battle._fetch_instances()
            self.eye._fetch_instances()
            self.function._fetch_instances()
            self.effecter_function._fetch_instances()
            self.pre._fetch_instances()
            self.next._fetch_instances()
            for i in range(len(self.work)):
                pass

            self.enemy_p._fetch_instances()


    class SubCharacterDisp(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SubCharacterDisp, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.sc = Sh2.SubCharacter(self._io, self, self._root)
            self.anime2 = Sh2.ShAnime3d(self._io, self, self._root)
            self.anime = Sh2.ShAnime3d(self._io, self, self._root)
            self.cluster_anime = Sh2.Pointer(u"sh_cluster_anime", self._io, self, self._root)
            self.models = []
            for i in range(3):
                self.models.append(Sh2.Pointer(u"data", self._io, self, self._root))

            self.work = Sh2.Pointer(u"data", self._io, self, self._root)
            self.data = Sh2.Pointer(u"data", self._io, self, self._root)
            self.model_adr = self._io.read_u4le()
            self.anime_adr = self._io.read_u4le()
            self.clani_adr = self._io.read_u4le()
            self.anime_list = Sh2.Pointer(u"data", self._io, self, self._root)
            self.clani_list = Sh2.Pointer(u"data", self._io, self, self._root)
            self._unnamed12 = self._io.read_bytes(4)


        def _fetch_instances(self):
            pass
            self.sc._fetch_instances()
            self.anime2._fetch_instances()
            self.anime._fetch_instances()
            self.cluster_anime._fetch_instances()
            for i in range(len(self.models)):
                pass
                self.models[i]._fetch_instances()

            self.work._fetch_instances()
            self.data._fetch_instances()
            self.anime_list._fetch_instances()
            self.clani_list._fetch_instances()


    class Sxy(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Sxy, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x = self._io.read_s2le()
            self.y = self._io.read_s2le()


        def _fetch_instances(self):
            pass


    class SysW(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.SysW, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.cam_ang_y = self._io.read_f4le()
            self.cam_ang_z = self._io.read_f4le()
            self.cam_r_xz = self._io.read_f4le()
            self.cam_y = self._io.read_f4le()
            self.hero = Sh2.Kanri(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.hero._fetch_instances()


    class TDasr0(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDasr0, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.addr = self._io.read_bits_int_le(31)
            self.spr = self._io.read_bits_int_le(1) != 0


        def _fetch_instances(self):
            pass


    class TDasr1(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDasr1, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.addr = self._io.read_bits_int_le(31)
            self.spr = self._io.read_bits_int_le(1) != 0


        def _fetch_instances(self):
            pass


    class TDchcr(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDchcr, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.dir = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(1) != 0
            self.mod = self._io.read_bits_int_le(2)
            self.asp = self._io.read_bits_int_le(2)
            self.tte = self._io.read_bits_int_le(1) != 0
            self.tie = self._io.read_bits_int_le(1) != 0
            self.str = self._io.read_bits_int_le(1) != 0
            self.p1 = self._io.read_bits_int_le(7)
            self.tag = Sh2.U16(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.tag._fetch_instances()


    class TDctrl(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDctrl, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.dmae = self._io.read_bits_int_le(1) != 0
            self.rele = self._io.read_bits_int_le(1) != 0
            self.mfd = self._io.read_bits_int_le(2)
            self.sts = self._io.read_bits_int_le(2)
            self.std = self._io.read_bits_int_le(2)
            self.rcyc = self._io.read_bits_int_le(3)
            self.p0 = self._io.read_bits_int_le(21)


        def _fetch_instances(self):
            pass


    class TDenabler(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDenabler, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.p0 = Sh2.U16(self._io, self, self._root)
            self.cpnd = self._io.read_bits_int_le(1) != 0
            self.p1 = self._io.read_bits_int_le(15)


        def _fetch_instances(self):
            pass
            self.p0._fetch_instances()


    class TDenablew(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDenablew, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.p0 = Sh2.U16(self._io, self, self._root)
            self.cpnd = self._io.read_bits_int_le(1) != 0
            self.p1 = self._io.read_bits_int_le(15)


        def _fetch_instances(self):
            pass
            self.p0._fetch_instances()


    class TDmadr(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDmadr, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.addr = self._io.read_bits_int_le(31)
            self.spr = self._io.read_bits_int_le(1) != 0


        def _fetch_instances(self):
            pass


    class TDpcr(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDpcr, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.cpc0 = self._io.read_bits_int_le(1) != 0
            self.cpc1 = self._io.read_bits_int_le(1) != 0
            self.cpc2 = self._io.read_bits_int_le(1) != 0
            self.cpc3 = self._io.read_bits_int_le(1) != 0
            self.cpc4 = self._io.read_bits_int_le(1) != 0
            self.cpc5 = self._io.read_bits_int_le(1) != 0
            self.cpc6 = self._io.read_bits_int_le(1) != 0
            self.cpc7 = self._io.read_bits_int_le(1) != 0
            self.cpc8 = self._io.read_bits_int_le(1) != 0
            self.cpc9 = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(6)
            self.cde0 = self._io.read_bits_int_le(1) != 0
            self.cde1 = self._io.read_bits_int_le(1) != 0
            self.cde2 = self._io.read_bits_int_le(1) != 0
            self.cde3 = self._io.read_bits_int_le(1) != 0
            self.cde4 = self._io.read_bits_int_le(1) != 0
            self.cde5 = self._io.read_bits_int_le(1) != 0
            self.cde6 = self._io.read_bits_int_le(1) != 0
            self.cde7 = self._io.read_bits_int_le(1) != 0
            self.cde8 = self._io.read_bits_int_le(1) != 0
            self.cde9 = self._io.read_bits_int_le(1) != 0
            self.p1 = self._io.read_bits_int_le(5)
            self.pce = self._io.read_bits_int_le(1) != 0


        def _fetch_instances(self):
            pass


    class TDqwc(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDqwc, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.qwc = Sh2.U16(self._io, self, self._root)
            self.p0 = Sh2.U16(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.qwc._fetch_instances()
            self.p0._fetch_instances()


    class TDrbor(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDrbor, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.addr = self._io.read_bits_int_le(31)
            self.p0 = self._io.read_bits_int_le(1) != 0


        def _fetch_instances(self):
            pass


    class TDrbsr(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDrbsr, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.rmsk = self._io.read_bits_int_le(31)
            self.p0 = self._io.read_bits_int_le(1) != 0


        def _fetch_instances(self):
            pass


    class TDsadr(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDsadr, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.addr = self._io.read_bits_int_le(14)
            self.p0 = self._io.read_bits_int_le(18)


        def _fetch_instances(self):
            pass


    class TDsqwc(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDsqwc, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.sqwc = self._io.read_bits_int_le(8)
            self.p0 = self._io.read_bits_int_le(8)
            self.tqwc = self._io.read_bits_int_le(8)
            self.p1 = self._io.read_bits_int_le(8)


        def _fetch_instances(self):
            pass


    class TDstadr(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDstadr, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.addr = self._io.read_bits_int_le(31)
            self.p0 = self._io.read_bits_int_le(1) != 0


        def _fetch_instances(self):
            pass


    class TDstat(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDstat, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.cis0 = self._io.read_bits_int_le(1) != 0
            self.cis1 = self._io.read_bits_int_le(1) != 0
            self.cis2 = self._io.read_bits_int_le(1) != 0
            self.cis3 = self._io.read_bits_int_le(1) != 0
            self.cis4 = self._io.read_bits_int_le(1) != 0
            self.cis5 = self._io.read_bits_int_le(1) != 0
            self.cis6 = self._io.read_bits_int_le(1) != 0
            self.cis7 = self._io.read_bits_int_le(1) != 0
            self.cis8 = self._io.read_bits_int_le(1) != 0
            self.cis9 = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(3)
            self.sis = self._io.read_bits_int_le(1) != 0
            self.meis = self._io.read_bits_int_le(1) != 0
            self.beis = self._io.read_bits_int_le(1) != 0
            self.cim0 = self._io.read_bits_int_le(1) != 0
            self.cim1 = self._io.read_bits_int_le(1) != 0
            self.cim2 = self._io.read_bits_int_le(1) != 0
            self.cim3 = self._io.read_bits_int_le(1) != 0
            self.cim4 = self._io.read_bits_int_le(1) != 0
            self.cim5 = self._io.read_bits_int_le(1) != 0
            self.cim6 = self._io.read_bits_int_le(1) != 0
            self.cim7 = self._io.read_bits_int_le(1) != 0
            self.cim8 = self._io.read_bits_int_le(1) != 0
            self.cim9 = self._io.read_bits_int_le(1) != 0
            self.p1 = self._io.read_bits_int_le(3)
            self.sim = self._io.read_bits_int_le(1) != 0
            self.meim = self._io.read_bits_int_le(1) != 0
            self.p2 = self._io.read_bits_int_le(1) != 0


        def _fetch_instances(self):
            pass


    class TDtadr(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TDtadr, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.addr = self._io.read_bits_int_le(31)
            self.spr = self._io.read_bits_int_le(1) != 0


        def _fetch_instances(self):
            pass


    class TGifCnt(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGifCnt, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.loopcnt = self._io.read_bits_int_le(15)
            self.p0 = self._io.read_bits_int_le(1) != 0
            self.regcnt = self._io.read_bits_int_le(4)
            self.vuaddr = self._io.read_bits_int_le(10)
            self.p1 = self._io.read_bits_int_le(2)


        def _fetch_instances(self):
            pass


    class TGifCtrl(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGifCtrl, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.rst = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(2)
            self.pse = self._io.read_bits_int_le(1) != 0
            self.p1 = self._io.read_bits_int_le(28)


        def _fetch_instances(self):
            pass


    class TGifMode(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGifMode, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.m3r = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(1) != 0
            self.imt = self._io.read_bits_int_le(1) != 0
            self.p1 = self._io.read_bits_int_le(29)


        def _fetch_instances(self):
            pass


    class TGifP3cnt(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGifP3cnt, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.p3cnt = self._io.read_bits_int_le(15)
            self.p0 = self._io.read_bits_int_le(17)


        def _fetch_instances(self):
            pass


    class TGifP3tag(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGifP3tag, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.loopcnt = self._io.read_bits_int_le(15)
            self.eop = self._io.read_bits_int_le(1) != 0
            self.p0 = Sh2.U16(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.p0._fetch_instances()


    class TGifStat(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGifStat, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.m3r = self._io.read_bits_int_le(1) != 0
            self.m3p = self._io.read_bits_int_le(1) != 0
            self.imt = self._io.read_bits_int_le(1) != 0
            self.pse = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(1) != 0
            self.ip3 = self._io.read_bits_int_le(1) != 0
            self.p3q = self._io.read_bits_int_le(1) != 0
            self.p2q = self._io.read_bits_int_le(1) != 0
            self.p1q = self._io.read_bits_int_le(1) != 0
            self.oph = self._io.read_bits_int_le(1) != 0
            self.apath = self._io.read_bits_int_le(2)
            self.dir = self._io.read_bits_int_le(1) != 0
            self.p1 = self._io.read_bits_int_le(11)
            self.fqc = self._io.read_bits_int_le(5)
            self.p2 = self._io.read_bits_int_le(3)


        def _fetch_instances(self):
            pass


    class TGifTag0(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGifTag0, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.nloop = self._io.read_bits_int_le(15)
            self.eop = self._io.read_bits_int_le(1) != 0
            self.tag = Sh2.U16(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.tag._fetch_instances()


    class TGifTag1(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGifTag1, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.tag = self._io.read_bits_int_le(14)
            self.pre = self._io.read_bits_int_le(1) != 0
            self.prim = self._io.read_bits_int_le(11)
            self.flg = self._io.read_bits_int_le(2)
            self.nreg = self._io.read_bits_int_le(4)


        def _fetch_instances(self):
            pass


    class TGifTag2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGifTag2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.tag = self._io.read_bits_int_le(32)


        def _fetch_instances(self):
            pass


    class TGifTag3(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGifTag3, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.tag = self._io.read_bits_int_le(32)


        def _fetch_instances(self):
            pass


    class TGsBgcolor(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGsBgcolor, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.r = self._io.read_bits_int_le(8)
            self.g = self._io.read_bits_int_le(8)
            self.b = self._io.read_bits_int_le(8)
            self.p0 = self._io.read_bits_int_le(8)
            self.p1 = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class TGsBusdir(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGsBusdir, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.dir = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(31)
            self.p1 = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class TGsCsr(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGsCsr, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.signal = self._io.read_bits_int_le(1) != 0
            self.finish = self._io.read_bits_int_le(1) != 0
            self.hsint = self._io.read_bits_int_le(1) != 0
            self.vsint = self._io.read_bits_int_le(1) != 0
            self.edwint = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(3)
            self.flush = self._io.read_bits_int_le(1) != 0
            self.reset = self._io.read_bits_int_le(1) != 0
            self.p1 = self._io.read_bits_int_le(2)
            self.nfield = self._io.read_bits_int_le(1) != 0
            self.field = self._io.read_bits_int_le(1) != 0
            self.fifo = self._io.read_bits_int_le(2)
            self.rev = self._io.read_bits_int_le(8)
            self.id = self._io.read_bits_int_le(8)
            self.p2 = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class TGsDispfb1(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGsDispfb1, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.fbp = self._io.read_bits_int_le(9)
            self.fbw = self._io.read_bits_int_le(6)
            self.psm = self._io.read_bits_int_le(5)
            self.p0 = self._io.read_bits_int_le(12)
            self.dbx = self._io.read_bits_int_le(11)
            self.dby = self._io.read_bits_int_le(11)
            self.p1 = self._io.read_bits_int_le(10)


        def _fetch_instances(self):
            pass


    class TGsDispfb2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGsDispfb2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.fbp = self._io.read_bits_int_le(9)
            self.fbw = self._io.read_bits_int_le(6)
            self.psm = self._io.read_bits_int_le(5)
            self.p0 = self._io.read_bits_int_le(12)
            self.dbx = self._io.read_bits_int_le(11)
            self.dby = self._io.read_bits_int_le(11)
            self.p1 = self._io.read_bits_int_le(10)


        def _fetch_instances(self):
            pass


    class TGsDisplay1(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGsDisplay1, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.dx = self._io.read_bits_int_le(12)
            self.dy = self._io.read_bits_int_le(11)
            self.magh = self._io.read_bits_int_le(4)
            self.magv = self._io.read_bits_int_le(2)
            self.p0 = self._io.read_bits_int_le(3)
            self.dw = self._io.read_bits_int_le(12)
            self.dh = self._io.read_bits_int_le(11)
            self.p1 = self._io.read_bits_int_le(9)


        def _fetch_instances(self):
            pass


    class TGsDisplay2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGsDisplay2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.dx = self._io.read_bits_int_le(12)
            self.dy = self._io.read_bits_int_le(11)
            self.magh = self._io.read_bits_int_le(4)
            self.magv = self._io.read_bits_int_le(2)
            self.p0 = self._io.read_bits_int_le(3)
            self.dw = self._io.read_bits_int_le(12)
            self.dh = self._io.read_bits_int_le(11)
            self.p1 = self._io.read_bits_int_le(9)


        def _fetch_instances(self):
            pass


    class TGsExtbuf(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGsExtbuf, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.exbp = self._io.read_bits_int_le(14)
            self.exbw = self._io.read_bits_int_le(6)
            self.fbin = self._io.read_bits_int_le(2)
            self.wffmd = self._io.read_bits_int_le(1) != 0
            self.emoda = self._io.read_bits_int_le(2)
            self.emodc = self._io.read_bits_int_le(2)
            self.p0 = self._io.read_bits_int_le(5)
            self.wdx = self._io.read_bits_int_le(11)
            self.wdy = self._io.read_bits_int_le(11)
            self.p1 = self._io.read_bits_int_le(10)


        def _fetch_instances(self):
            pass


    class TGsExtdata(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGsExtdata, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.sx = self._io.read_bits_int_le(12)
            self.sy = self._io.read_bits_int_le(11)
            self.smph = self._io.read_bits_int_le(4)
            self.smpv = self._io.read_bits_int_le(2)
            self.p0 = self._io.read_bits_int_le(3)
            self.ww = self._io.read_bits_int_le(12)
            self.wh = self._io.read_bits_int_le(11)
            self.p1 = self._io.read_bits_int_le(9)


        def _fetch_instances(self):
            pass


    class TGsExtwrite(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGsExtwrite, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.write = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(31)
            self.p1 = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class TGsImr(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGsImr, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.p0 = self._io.read_bits_int_le(8)
            self.sigmsk = self._io.read_bits_int_le(1) != 0
            self.finishmsk = self._io.read_bits_int_le(1) != 0
            self.hsmsk = self._io.read_bits_int_le(1) != 0
            self.vsmsk = self._io.read_bits_int_le(1) != 0
            self.edwmsk = self._io.read_bits_int_le(1) != 0
            self.p1 = self._io.read_bits_int_le(19)
            self.p2 = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class TGsPmode(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGsPmode, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.en1 = self._io.read_bits_int_le(1) != 0
            self.en2 = self._io.read_bits_int_le(1) != 0
            self.crtmd = self._io.read_bits_int_le(3)
            self.mmod = self._io.read_bits_int_le(1) != 0
            self.amod = self._io.read_bits_int_le(1) != 0
            self.slbg = self._io.read_bits_int_le(1) != 0
            self.alp = self._io.read_bits_int_le(8)
            self.p0 = Sh2.U16(self._io, self, self._root)
            self.p1 = self._io.read_u4le()


        def _fetch_instances(self):
            pass
            self.p0._fetch_instances()


    class TGsSiglblid(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGsSiglblid, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.sigid = self._io.read_bits_int_le(32)
            self.lblid = self._io.read_bits_int_le(32)


        def _fetch_instances(self):
            pass


    class TGsSmode2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TGsSmode2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.int = self._io.read_bits_int_le(1) != 0
            self.ffmd = self._io.read_bits_int_le(1) != 0
            self.dpms = self._io.read_bits_int_le(2)
            self.p0 = self._io.read_bits_int_le(28)
            self.p1 = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class TIpuBp(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TIpuBp, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.bp = self._io.read_bits_int_le(7)
            self.p0 = self._io.read_bits_int_le(1) != 0
            self.ifc = self._io.read_bits_int_le(4)
            self.p1 = self._io.read_bits_int_le(4)
            self.fp = self._io.read_bits_int_le(2)
            self.p2 = self._io.read_bits_int_le(14)


        def _fetch_instances(self):
            pass


    class TIpuCmdRead(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TIpuCmdRead, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.data = self._io.read_bits_int_le(32)
            self.p0 = self._io.read_bits_int_le(31)
            self.busy = self._io.read_bits_int_le(1) != 0


        def _fetch_instances(self):
            pass


    class TIpuCmdWrite(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TIpuCmdWrite, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.option = self._io.read_bits_int_le(28)
            self.code = self._io.read_bits_int_le(4)


        def _fetch_instances(self):
            pass


    class TIpuCtrl(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TIpuCtrl, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.ifc = self._io.read_bits_int_le(4)
            self.ofc = self._io.read_bits_int_le(4)
            self.cbp = self._io.read_bits_int_le(6)
            self.ecd = self._io.read_bits_int_le(1) != 0
            self.scd = self._io.read_bits_int_le(1) != 0
            self.idp = self._io.read_bits_int_le(2)
            self.p0 = self._io.read_bits_int_le(2)
            self.as_ = self._io.read_bits_int_le(1) != 0
            self.ivf = self._io.read_bits_int_le(1) != 0
            self.qst = self._io.read_bits_int_le(1) != 0
            self.mp1 = self._io.read_bits_int_le(1) != 0
            self.pct = self._io.read_bits_int_le(3)
            self.p1 = self._io.read_bits_int_le(3)
            self.rst = self._io.read_bits_int_le(1) != 0
            self.busy = self._io.read_bits_int_le(1) != 0


        def _fetch_instances(self):
            pass


    class TIpuTop(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TIpuTop, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.bstop = self._io.read_bits_int_le(32)
            self.p0 = self._io.read_bits_int_le(31)
            self.busy = self._io.read_bits_int_le(1) != 0


        def _fetch_instances(self):
            pass


    class TTcomp(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TTcomp, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.comp = Sh2.U16(self._io, self, self._root)
            self.p0 = Sh2.U16(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.comp._fetch_instances()
            self.p0._fetch_instances()


    class TTcount(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TTcount, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.count = Sh2.U16(self._io, self, self._root)
            self.p0 = Sh2.U16(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.count._fetch_instances()
            self.p0._fetch_instances()


    class TThold(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TThold, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.hold = Sh2.U16(self._io, self, self._root)
            self.p0 = Sh2.U16(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.hold._fetch_instances()
            self.p0._fetch_instances()


    class TTmode(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TTmode, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.clks = self._io.read_bits_int_le(2)
            self.gate = self._io.read_bits_int_le(1) != 0
            self.gats = self._io.read_bits_int_le(1) != 0
            self.gatm = self._io.read_bits_int_le(2)
            self.zret = self._io.read_bits_int_le(1) != 0
            self.cue = self._io.read_bits_int_le(1) != 0
            self.cmpe = self._io.read_bits_int_le(1) != 0
            self.ovfe = self._io.read_bits_int_le(1) != 0
            self.equf = self._io.read_bits_int_le(1) != 0
            self.ovff = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(20)


        def _fetch_instances(self):
            pass


    class TVif0Err(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVif0Err, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.mii = self._io.read_bits_int_le(1) != 0
            self.me0 = self._io.read_bits_int_le(1) != 0
            self.me1 = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(29)


        def _fetch_instances(self):
            pass


    class TVif0Fbrst(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVif0Fbrst, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.rst = self._io.read_bits_int_le(1) != 0
            self.fbk = self._io.read_bits_int_le(1) != 0
            self.stp = self._io.read_bits_int_le(1) != 0
            self.stc = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(28)


        def _fetch_instances(self):
            pass


    class TVif0Num(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVif0Num, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.num = self._io.read_bits_int_le(8)
            self.p0 = self._io.read_bits_int_le(24)


        def _fetch_instances(self):
            pass


    class TVif0Stat(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVif0Stat, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.vps = self._io.read_bits_int_le(2)
            self.vew = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(3)
            self.mrk = self._io.read_bits_int_le(1) != 0
            self.p1 = self._io.read_bits_int_le(1) != 0
            self.vss = self._io.read_bits_int_le(1) != 0
            self.vfs = self._io.read_bits_int_le(1) != 0
            self.vis = self._io.read_bits_int_le(1) != 0
            self.int = self._io.read_bits_int_le(1) != 0
            self.ero = self._io.read_bits_int_le(1) != 0
            self.er1 = self._io.read_bits_int_le(1) != 0
            self.p2 = self._io.read_bits_int_le(10)
            self.fqc = self._io.read_bits_int_le(4)
            self.p3 = self._io.read_bits_int_le(4)


        def _fetch_instances(self):
            pass


    class TVif1Base(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVif1Base, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.base = self._io.read_bits_int_le(10)
            self.p0 = self._io.read_bits_int_le(22)


        def _fetch_instances(self):
            pass


    class TVif1Err(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVif1Err, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.mii = self._io.read_bits_int_le(1) != 0
            self.me0 = self._io.read_bits_int_le(1) != 0
            self.me1 = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(29)


        def _fetch_instances(self):
            pass


    class TVif1Fbrst(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVif1Fbrst, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.rst = self._io.read_bits_int_le(1) != 0
            self.fbk = self._io.read_bits_int_le(1) != 0
            self.stp = self._io.read_bits_int_le(1) != 0
            self.stc = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(28)


        def _fetch_instances(self):
            pass


    class TVif1Num(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVif1Num, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.num = self._io.read_bits_int_le(8)
            self.p0 = self._io.read_bits_int_le(24)


        def _fetch_instances(self):
            pass


    class TVif1Ofst(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVif1Ofst, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.offset = self._io.read_bits_int_le(10)
            self.p0 = self._io.read_bits_int_le(22)


        def _fetch_instances(self):
            pass


    class TVif1Stat(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVif1Stat, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.vps = self._io.read_bits_int_le(2)
            self.vew = self._io.read_bits_int_le(1) != 0
            self.vgw = self._io.read_bits_int_le(1) != 0
            self.p0 = self._io.read_bits_int_le(2)
            self.mrk = self._io.read_bits_int_le(1) != 0
            self.dbf = self._io.read_bits_int_le(1) != 0
            self.vss = self._io.read_bits_int_le(1) != 0
            self.vfs = self._io.read_bits_int_le(1) != 0
            self.vis = self._io.read_bits_int_le(1) != 0
            self.int = self._io.read_bits_int_le(1) != 0
            self.ero = self._io.read_bits_int_le(1) != 0
            self.er1 = self._io.read_bits_int_le(1) != 0
            self.p1 = self._io.read_bits_int_le(9)
            self.fdr = self._io.read_bits_int_le(1) != 0
            self.fqc = self._io.read_bits_int_le(5)
            self.p2 = self._io.read_bits_int_le(3)


        def _fetch_instances(self):
            pass


    class TVif1Top(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVif1Top, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.top = self._io.read_bits_int_le(10)
            self.p0 = self._io.read_bits_int_le(22)


        def _fetch_instances(self):
            pass


    class TVif1Tops(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVif1Tops, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.tops = self._io.read_bits_int_le(10)
            self.p0 = self._io.read_bits_int_le(22)


        def _fetch_instances(self):
            pass


    class TVifC0(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifC0, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.c0 = self._io.read_bits_int_le(32)


        def _fetch_instances(self):
            pass


    class TVifC1(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifC1, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.c1 = self._io.read_bits_int_le(32)


        def _fetch_instances(self):
            pass


    class TVifC2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifC2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.c2 = self._io.read_bits_int_le(32)


        def _fetch_instances(self):
            pass


    class TVifC3(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifC3, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.c3 = self._io.read_bits_int_le(32)


        def _fetch_instances(self):
            pass


    class TVifCode(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifCode, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.immediate = Sh2.U16(self._io, self, self._root)
            self.num = self._io.read_bits_int_le(8)
            self.cmd = self._io.read_bits_int_le(8)


        def _fetch_instances(self):
            pass
            self.immediate._fetch_instances()


    class TVifCycle(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifCycle, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.cl = self._io.read_bits_int_le(8)
            self.wl = self._io.read_bits_int_le(8)
            self.p0 = Sh2.U16(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.p0._fetch_instances()


    class TVifItop(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifItop, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.itop = self._io.read_bits_int_le(10)
            self.p0 = self._io.read_bits_int_le(22)


        def _fetch_instances(self):
            pass


    class TVifItops(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifItops, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.itops = self._io.read_bits_int_le(10)
            self.p0 = self._io.read_bits_int_le(22)


        def _fetch_instances(self):
            pass


    class TVifMark(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifMark, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.mark = Sh2.U16(self._io, self, self._root)
            self.p0 = Sh2.U16(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.mark._fetch_instances()
            self.p0._fetch_instances()


    class TVifMask(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifMask, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.m0 = self._io.read_bits_int_le(2)
            self.m1 = self._io.read_bits_int_le(2)
            self.m2 = self._io.read_bits_int_le(2)
            self.m3 = self._io.read_bits_int_le(2)
            self.m4 = self._io.read_bits_int_le(2)
            self.m5 = self._io.read_bits_int_le(2)
            self.m6 = self._io.read_bits_int_le(2)
            self.m7 = self._io.read_bits_int_le(2)
            self.m8 = self._io.read_bits_int_le(2)
            self.m9 = self._io.read_bits_int_le(2)
            self.m10 = self._io.read_bits_int_le(2)
            self.m11 = self._io.read_bits_int_le(2)
            self.m12 = self._io.read_bits_int_le(2)
            self.m13 = self._io.read_bits_int_le(2)
            self.m14 = self._io.read_bits_int_le(2)
            self.m15 = self._io.read_bits_int_le(2)


        def _fetch_instances(self):
            pass


    class TVifMode(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifMode, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.mod = self._io.read_bits_int_le(2)
            self.p0 = self._io.read_bits_int_le(30)


        def _fetch_instances(self):
            pass


    class TVifR0(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifR0, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.r0 = self._io.read_bits_int_le(32)


        def _fetch_instances(self):
            pass


    class TVifR1(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifR1, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.r1 = self._io.read_bits_int_le(32)


        def _fetch_instances(self):
            pass


    class TVifR2(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifR2, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.r2 = self._io.read_bits_int_le(32)


        def _fetch_instances(self):
            pass


    class TVifR3(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TVifR3, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.r3 = self._io.read_bits_int_le(32)


        def _fetch_instances(self):
            pass


    class TextPos(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TextPos, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.block_index = self._io.read_u4le()
            self.texture_no = self._io.read_u4le()


        def _fetch_instances(self):
            pass


    class ThreadParam(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ThreadParam, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.status = self._io.read_s4le()
            self.entry = Sh2.Pointer(u"data", self._io, self, self._root)
            self.stack = Sh2.Pointer(u"data", self._io, self, self._root)
            self.stack_size = self._io.read_s4le()
            self.gp_reg = Sh2.Pointer(u"data", self._io, self, self._root)
            self.init_priority = self._io.read_s4le()
            self.current_priority = self._io.read_s4le()
            self.attr = self._io.read_u4le()
            self.option = self._io.read_u4le()
            self.wait_type = self._io.read_s4le()
            self.wait_id = self._io.read_s4le()
            self.wakeup_count = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.entry._fetch_instances()
            self.stack._fetch_instances()
            self.gp_reg._fetch_instances()


    class TimeStamp(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TimeStamp, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pts = self._io.read_s8le()
            self.dts = self._io.read_s8le()
            self.pos = self._io.read_s4le()
            self.len = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class TitleDataWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TitleDataWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.memcard = self._io.read_s4le()
            self.mode = self._io.read_s4le()
            self.sel = self._io.read_s4le()
            self.timer = self._io.read_f4le()
            self.alpha = self._io.read_s4le()
            self.alphar = self._io.read_f4le()
            self.menu = []
            for i in range(10):
                self.menu.append(self._io.read_u4le())

            self.pic0 = Sh2.PicDrawData(self._io, self, self._root)
            self.pload0 = Sh2.Pointer(u"data", self._io, self, self._root)
            self.pload1 = Sh2.Pointer(u"data", self._io, self, self._root)
            self.texadr = self._io.read_s4le()
            self.clutadr = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.menu)):
                pass

            self.pic0._fetch_instances()
            self.pload0._fetch_instances()
            self.pload1._fetch_instances()


    class TitlePointList(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TitlePointList, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.pos_x = self._io.read_f4le()
            self.pos_y = self._io.read_f4le()
            self.pos_z = self._io.read_f4le()
            self.rot = self._io.read_f4le()
            self.stg = self._io.read_s4le()
            self.jump_nemu_id = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class TitleSprChgColorWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TitleSprChgColorWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.start_rgba = []
            for i in range(4):
                self.start_rgba.append(self._io.read_s4le())

            self.end_rgba = []
            for i in range(4):
                self.end_rgba.append(self._io.read_s4le())

            self.cycle = self._io.read_f4le()
            self.timer = self._io.read_f4le()
            self._unnamed4 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            for i in range(len(self.start_rgba)):
                pass

            for i in range(len(self.end_rgba)):
                pass



    class TitleSprWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.TitleSprWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.u0 = self._io.read_s2le()
            self.v0 = self._io.read_s2le()
            self.u1 = self._io.read_s2le()
            self.v1 = self._io.read_s2le()
            self.w = self._io.read_s2le()
            self.h = self._io.read_s2le()
            self._unnamed6 = self._io.read_bytes(4)
            self.rgba = []
            for i in range(4):
                self.rgba.append(self._io.read_s4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.rgba)):
                pass



    class U16(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.U16, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.bytes = self._io.read_bytes(16)


        def _fetch_instances(self):
            pass


    class Usxy(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Usxy, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x = self._io.read_u2le()
            self.y = self._io.read_u2le()


        def _fetch_instances(self):
            pass


    class VbCoordinate(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VbCoordinate, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.flg = self._io.read_u4le()
            self._unnamed1 = self._io.read_bytes(12)
            self.coord = []
            for i in range(16):
                self.coord.append(self._io.read_f4le())

            self.work = []
            for i in range(16):
                self.work.append(self._io.read_f4le())

            self.param = Sh2.Pointer(u"data", self._io, self, self._root)
            self.super = Sh2.Pointer(u"vb_coordinate", self._io, self, self._root)
            self.sub = Sh2.Pointer(u"vb_coordinate", self._io, self, self._root)
            self.r = Sh2.VbCoordinateAnon13(self._io, self, self._root)
            self._unnamed8 = self._io.read_bytes(12)
            self.lw = []
            for i in range(16):
                self.lw.append(self._io.read_f4le())

            self.ls = []
            for i in range(16):
                self.ls.append(self._io.read_f4le())

            self.rot = []
            for i in range(4):
                self.rot.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.coord)):
                pass

            for i in range(len(self.work)):
                pass

            self.param._fetch_instances()
            self.super._fetch_instances()
            self.sub._fetch_instances()
            self.r._fetch_instances()
            for i in range(len(self.lw)):
                pass

            for i in range(len(self.ls)):
                pass

            for i in range(len(self.rot)):
                pass



    class VbCoordinateAnon13(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VbCoordinateAnon13, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.vx = self._io.read_s2le()
            self.vy = self._io.read_s2le()
            self.vz = self._io.read_s2le()
            self.pad = self._io.read_s2le()


        def _fetch_instances(self):
            pass


    class VbRview(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VbRview, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.vp = []
            for i in range(4):
                self.vp.append(self._io.read_f4le())

            self.vr = []
            for i in range(4):
                self.vr.append(self._io.read_f4le())

            self.rz = self._io.read_f4le()
            self.super = Sh2.Pointer(u"vb_coordinate", self._io, self, self._root)
            self._unnamed4 = self._io.read_bytes(8)


        def _fetch_instances(self):
            pass
            for i in range(len(self.vp)):
                pass

            for i in range(len(self.vr)):
                pass

            self.super._fetch_instances()


    class VbScreeninfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VbScreeninfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.scr_z = self._io.read_f4le()
            self.sx = self._io.read_f4le()
            self.sy = self._io.read_f4le()
            self.cx = self._io.read_f4le()
            self.cy = self._io.read_f4le()
            self.zmin = self._io.read_f4le()
            self.zmax = self._io.read_f4le()
            self.nearz = self._io.read_f4le()
            self.farz = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class VbWvsmatrix(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VbWvsmatrix, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.wvm = []
            for i in range(16):
                self.wvm.append(self._io.read_f4le())

            self.vsm = []
            for i in range(16):
                self.vsm.append(self._io.read_f4le())

            self.wsm = []
            for i in range(16):
                self.wsm.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.wvm)):
                pass

            for i in range(len(self.vsm)):
                pass

            for i in range(len(self.wsm)):
                pass



    class VcCamMvParam(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcCamMvParam, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.accel_xz = self._io.read_f4le()
            self.accel_y = self._io.read_f4le()
            self.max_spd_xz = self._io.read_f4le()
            self.max_spd_y = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class VcCameraIntinfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcCameraIntinfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.mode = self._io.read_s4le()
            self.mv_smooth = self._io.read_s4le()
            self.ev_cam_rate = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class VcChaseCamParam(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcChaseCamParam, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.ofs_hy = self._io.read_f4le()
            self.ratio_r_xz = self._io.read_f4le()
            self.lr_lim_ang_y = self._io.read_f4le()
            self.rr_lim_ang_y = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class VcCirCamManager(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcCirCamManager, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.origin = []
            for i in range(4):
                self.origin.append(self._io.read_f4le())

            self.sw_l = []
            for i in range(4):
                self.sw_l.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            for i in range(len(self.origin)):
                pass

            for i in range(len(self.sw_l)):
                pass



    class VcFixAngCamParam(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcFixAngCamParam, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.ang_x = self._io.read_f4le()
            self.ang_y = self._io.read_f4le()
            self.ofs_hy = self._io.read_f4le()
            self.cam2wth_dist = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class VcFixCamManager(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcFixCamManager, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.exception_f = self._io.read_s4le()
            self.add_ang_y = self._io.read_f4le()
            self.add_rd_x = self._io.read_f4le()
            self.add_rd_z = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class VcLimitArea(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcLimitArea, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.min_hx = self._io.read_f4le()
            self.max_hx = self._io.read_f4le()
            self.min_hz = self._io.read_f4le()
            self.max_hz = self._io.read_f4le()
            self.min_hy = self._io.read_f4le()
            self.max_hy = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class VcLocusCircleCamParam(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcLocusCircleCamParam, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.origin_x = self._io.read_f4le()
            self.origin_z = self._io.read_f4le()
            self.ang_y = self._io.read_f4le()
            self.radius = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class VcNearRoadData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcNearRoadData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.road_p = Sh2.Pointer(u"vc_road_data", self._io, self, self._root)
            self.rd_dir_type = self._io.read_s4le()
            self.use_priority = self._io.read_s4le()
            self.chara2road_sum_dist = self._io.read_f4le()
            self.chara2road_vec_x = self._io.read_f4le()
            self.chara2road_vec_z = self._io.read_f4le()
            self.rd = Sh2.VcLimitArea(self._io, self, self._root)
            self.sw = Sh2.VcLimitArea(self._io, self, self._root)
            self._unnamed8 = self._io.read_bytes(8)
            self.rd_rzm = []
            for i in range(16):
                self.rd_rzm.append(self._io.read_f4le())

            self.rd_rim = []
            for i in range(16):
                self.rd_rim.append(self._io.read_f4le())

            self.sw_rzm = []
            for i in range(16):
                self.sw_rzm.append(self._io.read_f4le())

            self.sw_rim = []
            for i in range(16):
                self.sw_rim.append(self._io.read_f4le())



        def _fetch_instances(self):
            pass
            self.road_p._fetch_instances()
            self.rd._fetch_instances()
            self.sw._fetch_instances()
            for i in range(len(self.rd_rzm)):
                pass

            for i in range(len(self.rd_rim)):
                pass

            for i in range(len(self.sw_rzm)):
                pass

            for i in range(len(self.sw_rim)):
                pass



    class VcPreInfo(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcPreInfo, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.hero_neck_wm = []
            for i in range(16):
                self.hero_neck_wm.append(self._io.read_f4le())

            self.hero_neck_lm = []
            for i in range(16):
                self.hero_neck_lm.append(self._io.read_f4le())

            self.hero_neck_lwm = []
            for i in range(16):
                self.hero_neck_lwm.append(self._io.read_f4le())

            self.hero_head_ang_x = self._io.read_f4le()
            self.hero_head_ang_y = self._io.read_f4le()
            self.hero_eye_y = self._io.read_f4le()


        def _fetch_instances(self):
            pass
            for i in range(len(self.hero_neck_wm)):
                pass

            for i in range(len(self.hero_neck_lm)):
                pass

            for i in range(len(self.hero_neck_lwm)):
                pass



    class VcProjectionParams(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcProjectionParams, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.new = self._io.read_f4le()
            self.old = self._io.read_f4le()
            self.delta = self._io.read_f4le()
            self.flg = self._io.read_s4le()


        def _fetch_instances(self):
            pass


    class VcRoadArea(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcRoadArea, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x0 = self._io.read_f4le()
            self.z0 = self._io.read_f4le()
            self.x1 = self._io.read_f4le()
            self.z1 = self._io.read_f4le()
            self.x2 = self._io.read_f4le()
            self.z2 = self._io.read_f4le()
            self.min_hy = self._io.read_f4le()
            self.max_hy = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class VcRoadData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcRoadData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.lim_sw = Sh2.VcRoadArea(self._io, self, self._root)
            self.lim_rd = Sh2.VcRoadArea(self._io, self, self._root)
            self.kind_id = self._io.read_s4le()
            self.flags = self._io.read_s4le()
            self.area_size_type = self._io.read_s4le()
            self.rd_type = self._io.read_s4le()
            self.mv_y_type = self._io.read_s4le()
            self.ofs_watch_hy = self._io.read_f4le()
            self.trace_btm_hy = self._io.read_f4le()
            self.rd_dir_type = self._io.read_s4le()
            self.projection = self._io.read_f4le()
            self.proj_volume = self._io.read_f4le()
            self.proj_sec = self._io.read_f4le()
            self.cam_mv_type = self._io.read_s4le()
            self._raw_tmp = self._io.read_bytes(16)
            _io__raw_tmp = KaitaiStream(BytesIO(self._raw_tmp))
            self.tmp = Sh2.VcRoadDataAnon14(_io__raw_tmp, self, self._root)


        def _fetch_instances(self):
            pass
            self.lim_sw._fetch_instances()
            self.lim_rd._fetch_instances()
            self.tmp._fetch_instances()


    class VcRoadDataAnon14(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcRoadDataAnon14, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self._unnamed0 = self._io.read_bytes(16)


        def _fetch_instances(self):
            pass
            _ = self.chs
            if hasattr(self, '_m_chs'):
                pass
                self._m_chs._fetch_instances()

            _ = self.cir
            if hasattr(self, '_m_cir'):
                pass
                self._m_cir._fetch_instances()

            _ = self.data
            if hasattr(self, '_m_data'):
                pass
                for i in range(len(self._m_data)):
                    pass


            _ = self.fix
            if hasattr(self, '_m_fix'):
                pass
                self._m_fix._fetch_instances()

            _ = self.stl
            if hasattr(self, '_m_stl'):
                pass
                self._m_stl._fetch_instances()


        @property
        def chs(self):
            if hasattr(self, '_m_chs'):
                return self._m_chs

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_chs = Sh2.VcChaseCamParam(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_chs', None)

        @property
        def cir(self):
            if hasattr(self, '_m_cir'):
                return self._m_cir

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_cir = Sh2.VcLocusCircleCamParam(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_cir', None)

        @property
        def data(self):
            if hasattr(self, '_m_data'):
                return self._m_data

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_data = []
            for i in range(16):
                self._m_data.append(self._io.read_u1())

            self._io.seek(_pos)
            return getattr(self, '_m_data', None)

        @property
        def fix(self):
            if hasattr(self, '_m_fix'):
                return self._m_fix

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_fix = Sh2.VcFixAngCamParam(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_fix', None)

        @property
        def stl(self):
            if hasattr(self, '_m_stl'):
                return self._m_stl

            _pos = self._io.pos()
            self._io.seek(0)
            self._m_stl = Sh2.VcSettleCamParam(self._io, self, self._root)
            self._io.seek(_pos)
            return getattr(self, '_m_stl', None)


    class VcSettleCamParam(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcSettleCamParam, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.sta_base_ang_y = self._io.read_f4le()
            self.end_base_ang_y = self._io.read_f4le()
            self.lr_lim_ang_y = self._io.read_f4le()
            self.rr_lim_ang_y = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class VcThroughDoorCamParam(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcThroughDoorCamParam, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.active_f = self._io.read_s4le()
            self.timer = self._io.read_f4le()
            self.rail_ang_y = self._io.read_f4le()
            self._unnamed3 = self._io.read_bytes(4)
            self.rail_sta_pos = []
            for i in range(4):
                self.rail_sta_pos.append(self._io.read_f4le())

            self.rail_sta_to_chara_dist = self._io.read_f4le()
            self._unnamed6 = self._io.read_bytes(12)


        def _fetch_instances(self):
            pass
            for i in range(len(self.rail_sta_pos)):
                pass



    class VcWatchMvParam(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcWatchMvParam, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.ang_accel_x = self._io.read_f4le()
            self.ang_accel_y = self._io.read_f4le()
            self.max_ang_spd_x = self._io.read_f4le()
            self.max_ang_spd_y = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class VcWork(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VcWork, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.view_cam_active_f = self._io.read_s4le()
            self.vc_road_ary_list = Sh2.Pointer(u"data", self._io, self, self._root)
            self.flags = self._io.read_u2le()
            self._unnamed3 = self._io.read_bytes(2)
            self.through_door_activate_init_f = self._io.read_s4le()
            self.through_door = Sh2.VcThroughDoorCamParam(self._io, self, self._root)
            self.scr_half_ang_wy = self._io.read_f4le()
            self.scr_half_ang_wx = self._io.read_f4le()
            self.user_cam_mv_prm = Sh2.VcCamMvParam(self._io, self, self._root)
            self._unnamed9 = self._io.read_bytes(8)
            self.cam_tgt_pos = []
            for i in range(4):
                self.cam_tgt_pos.append(self._io.read_f4le())

            self.cam_pos = []
            for i in range(4):
                self.cam_pos.append(self._io.read_f4le())

            self.cam_mv_ang_y = self._io.read_f4le()
            self._unnamed13 = self._io.read_bytes(12)
            self.cam_velo = []
            for i in range(4):
                self.cam_velo.append(self._io.read_f4le())

            self.old_cam_excl_area_r = self._io.read_f4le()
            self.ideal_cam_pos_h = self._io.read_f4le()
            self.user_watch_mv_prm = Sh2.VcWatchMvParam(self._io, self, self._root)
            self._unnamed18 = self._io.read_bytes(8)
            self.watch_tgt_pos = []
            for i in range(4):
                self.watch_tgt_pos.append(self._io.read_f4le())

            self.watch_tgt_max_y = self._io.read_f4le()
            self.watch_tgt_ang_z = self._io.read_f4le()
            self._unnamed22 = self._io.read_bytes(8)
            self.cam_mat_ang = []
            for i in range(4):
                self.cam_mat_ang.append(self._io.read_f4le())

            self.cam_mat = []
            for i in range(16):
                self.cam_mat.append(self._io.read_f4le())

            self.ofs_cam_ang = []
            for i in range(4):
                self.ofs_cam_ang.append(self._io.read_f4le())

            self.ofs_cam_ang_spd = []
            for i in range(4):
                self.ofs_cam_ang_spd.append(self._io.read_f4le())

            self.base_cam_ang = []
            for i in range(4):
                self.base_cam_ang.append(self._io.read_f4le())

            self.old_base_cam_ang = []
            for i in range(4):
                self.old_base_cam_ang.append(self._io.read_f4le())

            self.cam_chara2ideal_ang_y = self._io.read_f4le()
            self._unnamed30 = self._io.read_bytes(12)
            self.cam_tgt_velo = []
            for i in range(4):
                self.cam_tgt_velo.append(self._io.read_f4le())

            self.cam_tgt_mv_ang_y = self._io.read_f4le()
            self.cam_tgt_spd = self._io.read_f4le()
            self._unnamed34 = self._io.read_bytes(8)
            self.chara_pos = []
            for i in range(4):
                self.chara_pos.append(self._io.read_f4le())

            self.chara_bottom_y = self._io.read_f4le()
            self.chara_top_y = self._io.read_f4le()
            self.chara_center_y = self._io.read_f4le()
            self.chara_grnd_y = self._io.read_f4le()
            self.chara_head_pos = []
            for i in range(4):
                self.chara_head_pos.append(self._io.read_f4le())

            self.chara_mv_spd = self._io.read_f4le()
            self.chara_mv_ang_y = self._io.read_f4le()
            self.chara_ang_spd_y = self._io.read_f4le()
            self.chara_eye_ang_y = self._io.read_f4le()
            self.chara_eye_ang_wy = self._io.read_f4le()
            self.chara_watch_xz_r = self._io.read_f4le()
            self.fix_man = Sh2.VcFixCamManager(self._io, self, self._root)
            self._unnamed48 = self._io.read_bytes(8)
            self.cir_man = Sh2.VcCirCamManager(self._io, self, self._root)
            self.near_road_ary = []
            for i in range(128):
                self.near_road_ary.append(Sh2.VcNearRoadData(self._io, self, self._root))

            self.near_road_suu = self._io.read_s4le()
            self._unnamed52 = self._io.read_bytes(12)
            self.cur_near_road = Sh2.VcNearRoadData(self._io, self, self._root)
            self.nearest_enemy_p = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.nearest_enemy_xz_dist = self._io.read_f4le()
            self.enemy_input_watch_y = self._io.read_f4le()
            self.nearest_item_p = Sh2.Pointer(u"sub_character", self._io, self, self._root)
            self.nearest_item_xz_dist = self._io.read_f4le()
            self._unnamed59 = self._io.read_bytes(12)


        def _fetch_instances(self):
            pass
            self.vc_road_ary_list._fetch_instances()
            self.through_door._fetch_instances()
            self.user_cam_mv_prm._fetch_instances()
            for i in range(len(self.cam_tgt_pos)):
                pass

            for i in range(len(self.cam_pos)):
                pass

            for i in range(len(self.cam_velo)):
                pass

            self.user_watch_mv_prm._fetch_instances()
            for i in range(len(self.watch_tgt_pos)):
                pass

            for i in range(len(self.cam_mat_ang)):
                pass

            for i in range(len(self.cam_mat)):
                pass

            for i in range(len(self.ofs_cam_ang)):
                pass

            for i in range(len(self.ofs_cam_ang_spd)):
                pass

            for i in range(len(self.base_cam_ang)):
                pass

            for i in range(len(self.old_base_cam_ang)):
                pass

            for i in range(len(self.cam_tgt_velo)):
                pass

            for i in range(len(self.chara_pos)):
                pass

            for i in range(len(self.chara_head_pos)):
                pass

            self.fix_man._fetch_instances()
            self.cir_man._fetch_instances()
            for i in range(len(self.near_road_ary)):
                pass
                self.near_road_ary[i]._fetch_instances()

            self.cur_near_road._fetch_instances()
            self.nearest_enemy_p._fetch_instances()
            self.nearest_item_p._fetch_instances()


    class Vector4(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.Vector4, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x = self._io.read_f4le()
            self.y = self._io.read_f4le()
            self.z = self._io.read_f4le()
            self.w = self._io.read_f4le()


        def _fetch_instances(self):
            pass


    class ViBuf(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.ViBuf, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.data = Sh2.Pointer(u"data", self._io, self, self._root)
            self.tag = Sh2.Pointer(u"data", self._io, self, self._root)
            self.n = self._io.read_s4le()
            self.dma_start = self._io.read_s4le()
            self.dma_n = self._io.read_s4le()
            self.read_bytes = self._io.read_s4le()
            self.buff_size = self._io.read_s4le()
            self.env = Sh2.SceIpuDmaEnv(self._io, self, self._root)
            self.sema = self._io.read_s4le()
            self.is_active = self._io.read_s4le()
            self.total_bytes = self._io.read_s8le()
            self.ts = Sh2.Pointer(u"time_stamp", self._io, self, self._root)
            self.n_ts = self._io.read_s4le()
            self.count_ts = self._io.read_s4le()
            self.wt_ts = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.data._fetch_instances()
            self.tag._fetch_instances()
            self.env._fetch_instances()
            self.ts._fetch_instances()


    class VideoDec(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VideoDec, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.vibuf = Sh2.ViBuf(self._io, self, self._root)
            self.state = self._io.read_s4le()
            self.sema = self._io.read_s4le()
            self.hid_endimage = self._io.read_s4le()
            self.hid_vblank = self._io.read_s4le()
            self.cscvu1 = Sh2.CscVu1(self._io, self, self._root)


        def _fetch_instances(self):
            pass
            self.vibuf._fetch_instances()
            self.cscvu1._fetch_instances()


    class VoBuf(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VoBuf, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.data = Sh2.Pointer(u"vo_data", self._io, self, self._root)
            self.tag_inter = Sh2.Pointer(u"vo_tag", self._io, self, self._root)
            self.tag = Sh2.Pointer(u"vo_tag", self._io, self, self._root)
            self.write = self._io.read_s4le()
            self.count = self._io.read_s4le()
            self.size = self._io.read_s4le()


        def _fetch_instances(self):
            pass
            self.data._fetch_instances()
            self.tag_inter._fetch_instances()
            self.tag._fetch_instances()


    class VoData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VoData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.v = []
            for i in range(393216):
                self.v.append(self._io.read_u1())



        def _fetch_instances(self):
            pass
            for i in range(len(self.v)):
                pass



    class VoTag(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.VoTag, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.status = self._io.read_s4le()
            self.v = Sh2.Pointer(u"data", self._io, self, self._root)
            self.dummy = []
            for i in range(14):
                self.dummy.append(self._io.read_s4le())



        def _fetch_instances(self):
            pass
            self.v._fetch_instances()
            for i in range(len(self.dummy)):
                pass



    class WfontStreamData(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            super(Sh2.WfontStreamData, self).__init__(_io)
            self._parent = _parent
            self._root = _root
            self._read()

        def _read(self):
            self.x = self._io.read_u2le()
            self.y = self._io.read_u2le()
            self.vw = self._io.read_u2le()
            self.vh = self._io.read_u2le()
            self.u = self._io.read_u2le()
            self.v = self._io.read_u2le()
            self.rgb_u = self._io.read_u4le()
            self.rgb_d = self._io.read_u4le()
            self.w = self._io.read_u2le()
            self.h = self._io.read_u2le()


        def _fetch_instances(self):
            pass



