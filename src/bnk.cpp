// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "bnk.h"
#include "kaitai/exceptions.h"

bnk_t::bnk_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_bank_header = 0;
    m_data_index = 0;
    m_data = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::_read() {
    m_bank_header = new bank_header_t(m__io, this, m__root);
    m_data_index = new data_index_t(m__io, this, m__root);
    m_data = new data_t(m__io, this, m__root);
}

bnk_t::~bnk_t() {
    _clean_up();
}

void bnk_t::_clean_up() {
    if (m_bank_header) {
        delete m_bank_header; m_bank_header = 0;
    }
    if (m_data_index) {
        delete m_data_index; m_data_index = 0;
    }
    if (m_data) {
        delete m_data; m_data = 0;
    }
}

bnk_t::data_index_t::data_index_t(kaitai::kstream* p__io, bnk_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_data = 0;
    m__io__raw_data = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::data_index_t::_read() {
    m_magic = m__io->read_bytes(4);
    if (!(magic() == std::string("\x44\x49\x44\x58", 4))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x44\x49\x44\x58", 4), magic(), _io(), std::string("/types/data_index/seq/0"));
    }
    m_length = m__io->read_u4le();
    m__raw_data = m__io->read_bytes(length());
    m__io__raw_data = new kaitai::kstream(m__raw_data);
    m_data = new indices_t(m__io__raw_data, this, m__root);
}

bnk_t::data_index_t::~data_index_t() {
    _clean_up();
}

void bnk_t::data_index_t::_clean_up() {
    if (m__io__raw_data) {
        delete m__io__raw_data; m__io__raw_data = 0;
    }
    if (m_data) {
        delete m_data; m_data = 0;
    }
}

bnk_t::indices_t::indices_t(kaitai::kstream* p__io, bnk_t::data_index_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_indices = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::indices_t::_read() {
    m_indices = new std::vector<index_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_indices->push_back(new index_t(m__io, this, m__root));
            i++;
        }
    }
}

bnk_t::indices_t::~indices_t() {
    _clean_up();
}

void bnk_t::indices_t::_clean_up() {
    if (m_indices) {
        for (std::vector<index_t*>::iterator it = m_indices->begin(); it != m_indices->end(); ++it) {
            delete *it;
        }
        delete m_indices; m_indices = 0;
    }
}

bnk_t::data_t::data_t(kaitai::kstream* p__io, bnk_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_data = 0;
    m__io__raw_data = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::data_t::_read() {
    m_magic = m__io->read_bytes(4);
    if (!(magic() == std::string("\x44\x41\x54\x41", 4))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x44\x41\x54\x41", 4), magic(), _io(), std::string("/types/data/seq/0"));
    }
    m_length = m__io->read_u4le();
    m__raw_data = m__io->read_bytes(length());
    m__io__raw_data = new kaitai::kstream(m__raw_data);
    m_data = new audio_sections_t(m__io__raw_data, this, m__root);
}

bnk_t::data_t::~data_t() {
    _clean_up();
}

void bnk_t::data_t::_clean_up() {
    if (m__io__raw_data) {
        delete m__io__raw_data; m__io__raw_data = 0;
    }
    if (m_data) {
        delete m_data; m_data = 0;
    }
}

bnk_t::bank_header_t::bank_header_t(kaitai::kstream* p__io, bnk_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::bank_header_t::_read() {
    m_magic = m__io->read_bytes(4);
    if (!(magic() == std::string("\x42\x4B\x48\x44", 4))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x42\x4B\x48\x44", 4), magic(), _io(), std::string("/types/bank_header/seq/0"));
    }
    m_length = m__io->read_u4le();
    m_version = m__io->read_u4le();
    m_id = m__io->read_u4le();
    m_data = m__io->read_bytes((length() - (2 * 4)));
}

bnk_t::bank_header_t::~bank_header_t() {
    _clean_up();
}

void bnk_t::bank_header_t::_clean_up() {
}

bnk_t::audio_section_t::audio_section_t(uint32_t p_index, kaitai::kstream* p__io, bnk_t::audio_sections_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_index = p_index;
    f_data = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::audio_section_t::_read() {
}

bnk_t::audio_section_t::~audio_section_t() {
    _clean_up();
}

void bnk_t::audio_section_t::_clean_up() {
    if (f_data) {
    }
}

std::string bnk_t::audio_section_t::data() {
    if (f_data)
        return m_data;
    std::streampos _pos = m__io->pos();
    m__io->seek(_parent()->_parent()->_parent()->data_index()->data()->indices()->at(index())->offset());
    m_data = m__io->read_bytes(_parent()->_parent()->_parent()->data_index()->data()->indices()->at(index())->length());
    m__io->seek(_pos);
    f_data = true;
    return m_data;
}

bnk_t::audio_sections_t::audio_sections_t(kaitai::kstream* p__io, bnk_t::data_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_audio_sections = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::audio_sections_t::_read() {
    int l_audio_sections = _parent()->_parent()->data_index()->data()->indices()->size();
    m_audio_sections = new std::vector<audio_section_t*>();
    m_audio_sections->reserve(l_audio_sections);
    for (int i = 0; i < l_audio_sections; i++) {
        m_audio_sections->push_back(new audio_section_t(i, m__io, this, m__root));
    }
}

bnk_t::audio_sections_t::~audio_sections_t() {
    _clean_up();
}

void bnk_t::audio_sections_t::_clean_up() {
    if (m_audio_sections) {
        for (std::vector<audio_section_t*>::iterator it = m_audio_sections->begin(); it != m_audio_sections->end(); ++it) {
            delete *it;
        }
        delete m_audio_sections; m_audio_sections = 0;
    }
}

bnk_t::index_t::index_t(kaitai::kstream* p__io, bnk_t::indices_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::index_t::_read() {
    m_id = m__io->read_u4le();
    m_offset = m__io->read_u4le();
    m_length = m__io->read_u4le();
}

bnk_t::index_t::~index_t() {
    _clean_up();
}

void bnk_t::index_t::_clean_up() {
}
