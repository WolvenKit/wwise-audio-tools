meta:
  id: bundle
  file-extension: bundle
  endian: le

seq:
  - id: magic
    contents: 'POTATO70'
  - id: bundle_size
    type: u4
  - id: dummy_size
    type: u4
  - id: data_offset
    type: u4
  - id: buffer_for_info_off
    size: 32 - 8 - (4 * 3)
  - id: files
    type: embedded_file
    repeat: until
    repeat-until: _io.pos >= data_offset

types:
  embedded_file:
    seq:
      - id: name
        type: str
        size: 0x100
        encoding: utf-8
      - id: hash
        #type: str
        size: 0x10
        #encoding: utf-8
      - id: zero1
        contents: [00, 00, 00, 00]
      - id: size
        type: u4
      - id: compressed_size
        type: u4
      - id: offset
        type: u4
      - id: timestamp
        type: u8
      - id: zero2
        contents: [00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00]
      - id: dummy
        type: u4
      - id: compression_type
        type: u4
        enum: compression_type
    instances:
      data:
        pos: offset
        size: compressed_size

enums:
  compression_type:
    0: none
    1: zlib
    2: snappy
    3: doboz
    4: lz4 # 4 and 5
    5: lz4