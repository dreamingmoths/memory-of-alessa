meta:
  id: mw_overlay_header
  endian: le
  file-extension: mwovl
  encoding: ascii

seq:
  - id: identifier
    size: 3

  - id: version
    type: u1

  - id: id
    type: u4

  - id: address
    type: u4

  - id: sz_text
    type: u4

  - id: sz_data
    type: u4

  - id: sz_bss
    type: u4

  - id: static_init
    type: u4

  - id: static_init_end
    type: u4

  - id: name
    type: strz
    size: 32
