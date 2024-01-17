// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/structs/wem.h"
#include "kaitai/exceptions.h"

wem_t::wem_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, wem_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_riff_header = 0;
    m_chunks = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void wem_t::_read() {
    m_riff_header = new riff_header_t(m__io, this, m__root);
    m_chunks = new std::vector<chunk_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_chunks->push_back(new chunk_t(m__io, this, m__root));
            i++;
        }
    }
}

wem_t::~wem_t() {
    _clean_up();
}

void wem_t::_clean_up() {
    if (m_riff_header) {
        delete m_riff_header; m_riff_header = 0;
    }
    if (m_chunks) {
        for (std::vector<chunk_t*>::iterator it = m_chunks->begin(); it != m_chunks->end(); ++it) {
            delete *it;
        }
        delete m_chunks; m_chunks = 0;
    }
}

wem_t::chunk_t::chunk_t(kaitai::kstream* p__io, wem_t* p__parent, wem_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_riff_chunk = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void wem_t::chunk_t::_read() {
    m_riff_chunk = new riff_chunk_t(m__io, this, m__root);
    n_data = true;
    {
        std::string on = riff_chunk()->type();
        if (on == std::string("\x64\x61\x74\x61", 4)) {
            n_data = false;
            m_data = new data_chunk_t(riff_chunk()->size(), m__io, this, m__root);
        }
        else if (on == std::string("\x00\x00\x00\x00", 4)) {
            n_data = false;
            m_data = new random_blank_bytes_t(m__io, this, m__root);
        }
        else if (on == std::string("\x4C\x49\x53\x54", 4)) {
            n_data = false;
            m_data = new list_chunk_t(riff_chunk()->size(), m__io, this, m__root);
        }
        else if (on == std::string("\x4A\x55\x4E\x4B", 4)) {
            n_data = false;
            m_data = new junk_chunk_t(m__io, this, m__root);
        }
        else if (on == std::string("\x63\x75\x65\x20", 4)) {
            n_data = false;
            m_data = new cue_chunk_t(m__io, this, m__root);
        }
        else if (on == std::string("\x66\x6D\x74\x20", 4)) {
            n_data = false;
            m_data = new fmt_chunk_t(m__io, this, m__root);
        }
    }
}

wem_t::chunk_t::~chunk_t() {
    _clean_up();
}

void wem_t::chunk_t::_clean_up() {
    if (m_riff_chunk) {
        delete m_riff_chunk; m_riff_chunk = 0;
    }
    if (!n_data) {
        if (m_data) {
            delete m_data; m_data = 0;
        }
    }
}

wem_t::fmt_chunk_t::fmt_chunk_t(kaitai::kstream* p__io, wem_t::chunk_t* p__parent, wem_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void wem_t::fmt_chunk_t::_read() {
    m_compression_code = m__io->read_u2le();
    m_channels = m__io->read_u2le();
    m_samples_per_sec = m__io->read_u4le();
    m_avg_bytes_per_sec = m__io->read_u4le();
    m_block_align = m__io->read_u2le();
    m_bits_per_sample = m__io->read_u2le();
    m_extra_byte_count = m__io->read_u2le();
    m_valid_bits_per_sample = m__io->read_u2le();
    m_channel_mask = m__io->read_u4le();
    m_guid = kaitai::kstream::bytes_to_str(m__io->read_bytes(42), "UTF-8");
}

wem_t::fmt_chunk_t::~fmt_chunk_t() {
    _clean_up();
}

void wem_t::fmt_chunk_t::_clean_up() {
}

wem_t::junk_chunk_t::junk_chunk_t(kaitai::kstream* p__io, wem_t::chunk_t* p__parent, wem_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void wem_t::junk_chunk_t::_read() {
    m_junk = kaitai::kstream::bytes_to_str(m__io->read_bytes(26), "UTF-8");
}

wem_t::junk_chunk_t::~junk_chunk_t() {
    _clean_up();
}

void wem_t::junk_chunk_t::_clean_up() {
}

wem_t::list_labl_subchunk_t::list_labl_subchunk_t(kaitai::kstream* p__io, wem_t::list_chunk_t* p__parent, wem_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void wem_t::list_labl_subchunk_t::_read() {
    m_magic = m__io->read_bytes(4);
    if (!(magic() == std::string("\x6C\x61\x62\x6C", 4))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x6C\x61\x62\x6C", 4), magic(), _io(), std::string("/types/list_labl_subchunk/seq/0"));
    }
    m_size = m__io->read_u4le();
    m_cue_point_id = m__io->read_u4le();
    m_data = kaitai::kstream::bytes_to_str(m__io->read_bytes((size() - 4)), "UTF-8");
}

wem_t::list_labl_subchunk_t::~list_labl_subchunk_t() {
    _clean_up();
}

void wem_t::list_labl_subchunk_t::_clean_up() {
}

wem_t::riff_header_t::riff_header_t(kaitai::kstream* p__io, wem_t* p__parent, wem_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void wem_t::riff_header_t::_read() {
    m_magic = m__io->read_bytes(4);
    if (!(magic() == std::string("\x52\x49\x46\x46", 4))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x52\x49\x46\x46", 4), magic(), _io(), std::string("/types/riff_header/seq/0"));
    }
    m_chunk_size = m__io->read_u4le();
    m_wav_id = m__io->read_u4le();
}

wem_t::riff_header_t::~riff_header_t() {
    _clean_up();
}

void wem_t::riff_header_t::_clean_up() {
}

wem_t::list_chunk_t::list_chunk_t(uint32_t p_size, kaitai::kstream* p__io, wem_t::chunk_t* p__parent, wem_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_size = p_size;
    m_labl = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void wem_t::list_chunk_t::_read() {
    m_adtl = m__io->read_bytes(4);
    if (!(adtl() == std::string("\x61\x64\x74\x6C", 4))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x61\x64\x74\x6C", 4), adtl(), _io(), std::string("/types/list_chunk/seq/0"));
    }
    m_labl = new list_labl_subchunk_t(m__io, this, m__root);
}

wem_t::list_chunk_t::~list_chunk_t() {
    _clean_up();
}

void wem_t::list_chunk_t::_clean_up() {
    if (m_labl) {
        delete m_labl; m_labl = 0;
    }
}

wem_t::data_chunk_t::data_chunk_t(uint32_t p_size, kaitai::kstream* p__io, wem_t::chunk_t* p__parent, wem_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_size = p_size;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void wem_t::data_chunk_t::_read() {
    m_data = kaitai::kstream::bytes_to_str(m__io->read_bytes(size()), "UTF-8");
}

wem_t::data_chunk_t::~data_chunk_t() {
    _clean_up();
}

void wem_t::data_chunk_t::_clean_up() {
}

wem_t::cue_chunk_t::cue_chunk_t(kaitai::kstream* p__io, wem_t::chunk_t* p__parent, wem_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_cue_points = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void wem_t::cue_chunk_t::_read() {
    m_cue_point_count = m__io->read_u4le();
    m_cue_points = new std::vector<cue_point_subchunk_t*>();
    const int l_cue_points = cue_point_count();
    for (int i = 0; i < l_cue_points; i++) {
        m_cue_points->push_back(new cue_point_subchunk_t(m__io, this, m__root));
    }
}

wem_t::cue_chunk_t::~cue_chunk_t() {
    _clean_up();
}

void wem_t::cue_chunk_t::_clean_up() {
    if (m_cue_points) {
        for (std::vector<cue_point_subchunk_t*>::iterator it = m_cue_points->begin(); it != m_cue_points->end(); ++it) {
            delete *it;
        }
        delete m_cue_points; m_cue_points = 0;
    }
}

wem_t::riff_chunk_t::riff_chunk_t(kaitai::kstream* p__io, wem_t::chunk_t* p__parent, wem_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void wem_t::riff_chunk_t::_read() {
    m_dummy = m__io->read_bytes(kaitai::kstream::mod(_io()->pos(), 2));
    m_type = m__io->read_bytes(4);
    m_size = m__io->read_u4le();
}

wem_t::riff_chunk_t::~riff_chunk_t() {
    _clean_up();
}

void wem_t::riff_chunk_t::_clean_up() {
}

wem_t::cue_point_subchunk_t::cue_point_subchunk_t(kaitai::kstream* p__io, wem_t::cue_chunk_t* p__parent, wem_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void wem_t::cue_point_subchunk_t::_read() {
    m_id = m__io->read_u4le();
    m_position = m__io->read_u4le();
    m_data_chunk_id = m__io->read_u4le();
    m_chunk_start = m__io->read_u4le();
    m_block_start = m__io->read_u4le();
    m_sample_start = m__io->read_u4le();
}

wem_t::cue_point_subchunk_t::~cue_point_subchunk_t() {
    _clean_up();
}

void wem_t::cue_point_subchunk_t::_clean_up() {
}

wem_t::random_blank_bytes_t::random_blank_bytes_t(kaitai::kstream* p__io, wem_t::chunk_t* p__parent, wem_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_dummy = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void wem_t::random_blank_bytes_t::_read() {
    m_dummy = new std::vector<uint8_t>();
    {
        int i = 0;
        uint8_t _;
        do {
            _ = m__io->read_u1();
            m_dummy->push_back(_);
            i++;
        } while (!( ((_ != 0) || (_io()->is_eof())) ));
    }
}

wem_t::random_blank_bytes_t::~random_blank_bytes_t() {
    _clean_up();
}

void wem_t::random_blank_bytes_t::_clean_up() {
    if (m_dummy) {
        delete m_dummy; m_dummy = 0;
    }
}
