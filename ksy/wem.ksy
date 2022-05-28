meta:
  id: wem
  file-extension: wem
  endian: le

seq:
  - id: riff_header
    type: riff_header
  - id: chunks
    type: chunk
    repeat: eos

types:
  riff_header:
    seq:
      - id: magic
        contents: 'RIFF'
      - id: chunk_size
        type: u4
      - id: wav_id
        type: u4
  riff_chunk:
    seq:
      - id: dummy
        size: _io.pos % 2 # add dummy byte if chunk doesn't start on even
      - id: type
        # No longer using a string because the type can have some non-standard chars
        #type: str
        size: 4
        #encoding: UTF-8
      - id: size
        type: u4
  fmt_chunk:
    seq:
      - id: compression_code
        type: u2
      - id: channels
        type: u2
      - id: samples_per_sec
        type: u4
      - id: avg_bytes_per_sec
        type: u4
      - id: block_align
        type: u2
      - id: bits_per_sample
        type: u2
      - id: extra_byte_count
        type: u2
      - id: valid_bits_per_sample
        type: u2
      - id: channel_mask
        type: u4
      - id: guid
        type: str
        size: 42
        encoding: utf-8
  cue_chunk:
    seq:
      - id: cue_point_count
        type: u4
      - id: cue_points
        type: cue_point_subchunk
        repeat: expr
        repeat-expr: cue_point_count
  cue_point_subchunk:
    seq:
      - id: id
        type: u4
      - id: position
        type: u4
      - id: data_chunk_id
        type: u4
      - id: chunk_start
        type: u4
      - id: block_start
        type: u4
      - id: sample_start
        type: u4
  list_chunk:
    params:
      - id: size
        type: u4
    seq:
      - id: adtl
        contents: 'adtl'
      - id: labl
        type: list_labl_subchunk
      #- id: data
      #  size: size - 4
  list_labl_subchunk:
    seq:
      - id: magic
        contents: 'labl'
      - id: size
        type: u4
      - id: cue_point_id
        type: u4
      - id: data
        type: str
        size: size - 4 # size without cue point ID
        encoding: utf-8
  junk_chunk:
    seq:
      - id: junk
        type: str
        size: 26
        encoding: utf-8
  data_chunk:
    params:
      - id: size
        type: u4
    seq:
      - id: data
        type: str
        size: size
        encoding: utf-8
  random_blank_bytes:
    seq:
      - id: dummy
        type: u1
        repeat: until
        repeat-until: _ != 0 or _io.eof
  chunk:
    seq:
      - id: riff_chunk
        type: riff_chunk
      - id: data
        type:
          switch-on: riff_chunk.type
          cases:
            '[0x66, 0x6d, 0x74, 0x20]': fmt_chunk
            '[0x4a, 0x55, 0x4e, 0x4b]': junk_chunk
            '[0x63, 0x75, 0x65, 0x20]': cue_chunk
            '[0x4c, 0x49, 0x53, 0x54]': list_chunk(riff_chunk.size)
            '[0x64, 0x61, 0x74, 0x61]': data_chunk(riff_chunk.size)
            '[0x00, 0x00, 0x00, 0x00]': random_blank_bytes

