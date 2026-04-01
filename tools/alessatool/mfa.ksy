meta:
  id: mfa
  file-extension: mfa
  encoding: ascii
  endian: le

seq:
  - id: commmand
    type: strz
    size: 0xE0
  
  - id: file_info
    type: info
    repeat: until
    repeat-until: _.file_ofs == 0x20202020
  
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

instances:
  num_files:
    value: _root.file_info.size - 1 
 
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
