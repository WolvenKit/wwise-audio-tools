meta:
  id: w3sc
  file-extension: cache
  endian: le
seq:
  - id: magic
    contents: 'CS3W'
  - id: version
    type: u4
  - id: dummy
    type: u8
  # The size of this changes based on the version declared previously
  # See the witcher3.bms QuickBMS script for more info
  - id: info_offset
    type: u4
  - id: files
    type: u4
  - id: names_offset
    type: u4
  - id: names_size
    type: u4
instances:
  file_infos:
    pos: info_offset
    type: file_info
    repeat: expr
    repeat-expr: files
types:
  file_info:
    seq:
      - id: name_offset
        type: u4
      - id: offset
        type: u4
      - id: size
        type: u4
    instances:
      data:
        pos: offset
        size: size
      name:
        pos: _parent.names_offset + name_offset
        type: strz
        encoding: UTF-8