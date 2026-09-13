meta:
  id: filesystem
  endian: le

types:
  fs_mgc_file:
    seq:
      - id: type
        type: b8
      - id: padding
        type: b24
      - id: parent
        type: u4
        doc: pointer to fsFile
      - id: start
        type: u4
        doc: char*
      - id: end
        type: u4
        doc: char*

  fs_cd_file:
    seq:
      - id: type
        type: b8
      - id: number
        type: b24
      - id: name
        type: u4
        doc: char*
      - id: lsn
        type: s4
      - id: size
        type: s4

  fs_hd_file:
    seq:
      - id: type
        type: b8
      - id: padding
        type: b24
      - id: name
        type: u4
        doc: char*
      - id: offset
        type: s4
      - id: size
        type: s4

  fs_mgp_file:
    seq:
      - id: type
        type: b8
      - id: padding
        type: b24
      - id: file
        type: u4
        doc: pointer to fsFile
      - id: start
        type: u4
        doc: pointer to fsMgcFile
      - id: end
        type: u4
        doc: pointer to fsMgcFile

  fs_mgf_file:
    seq:
      - id: type
        type: b8
      - id: padding
        type: b24
      - id: parent
        type: u4
        doc: pointer to fsFile
      - id: offset
        type: s4
      - id: size
        type: s4

  fs_file_check:
    seq:
      - id: type
        type: b8
      - id: number
        type: b24
      - id: pad0
        type: s4
      - id: pad1
        type: s4
      - id: pad2
        type: s4

  fs_file:
    seq:
      - id: pack
        type: u_long128

    instances:
        check:
          type: fs_file_check
        cd:
          type: fs_cd_file
        hd:
          type: fs_hd_file
        mgc:
          type: fs_mgc_file
        mgf:
          type: fs_mgf_file
        mgp:
          type: fs_mgp_file

  fs_file_index_index:
    seq:
      - id: fp
        type: u4
        doc: pointer to fsFile
      - id: name
        type: u4

  fs_file_index:
    seq:
      - id: index
        type: fs_file_index_index
    instances:
      pack:
        type: u8

  u_long128:
    seq:
      - id: value
        size: 16
