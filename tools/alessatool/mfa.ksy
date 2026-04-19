meta:
  id: mfa
  file-extension: mfa
  encoding: shift-jis
  endian: le

params:
  - id: skip_command_prelude
    type: bool
    doc: |
      If set to true, will skip parsing the command line string at the start of
      the file.

seq:
  - id: command_prelude
    type: command_prelude
    if: not skip_command_prelude
  
  - id: num_files
    type: u4
  
  - id: archive_size
    type: u4
  
  - id: file_info
    type: info
    repeat: expr
    repeat-expr: num_files
  
  - id: filenames
    type: strz
    repeat: expr 
    repeat-expr: num_files
    
  - id: pad
    type: u1
    valid: 0xA
  
  - id: files
    type: file(_io.pos, _index)
    repeat: expr
    repeat-expr: num_files

types:
  file:
    params:
      - id: base
        type: u4
      - id: index
        type: u4
    instances:
      data:
        pos: data_ofs
        size: len_data
      data_ofs:
        value: base + _root.file_info[index].file_ofs
      len_data:
        value: _root.file_info[index].file_size
      filename:
        value: _root.filenames[_root.num_files - index - 1]

  info:
    seq:
      - type: u4
      - id: file_ofs
        type: u4
      - type: u4
      - id: file_size
        type: u4

  command_prelude:
    seq:
      - id: commmand
        type: str
        terminator: 0xC # form feed
    
      - id: line_feed
        type: u1
        valid: 0xA # line feed
    
      - id: spaces
        type: u1
        repeat: until
        repeat-until: _io.pos % 0x10 == 0x8
