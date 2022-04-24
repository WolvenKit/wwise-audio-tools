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
      - id: type
        # No longer using a string because the type can have some non-standard chars
        #type: str
        size: 4
        #encoding: UTF-8
      - id: size
        type: u4
  fmt_chunk:
    seq:
      - id: format_tag
        type: u2
      - id: channels
        type: u2
      - id: samples_per_sec
        type: u4
      - id: avg_bytes_per_sec
        type: u4
      - id: blockalign
        type: u2
      - id: bits_per_sample
        type: u2
      - id: size
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
      - id: cue_count
        type: u4
  list_chunk:
    params:
      - id: size
        type: u4
    seq:
      - id: list
        size: size
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