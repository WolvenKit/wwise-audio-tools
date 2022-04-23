// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "w3sc.h"
#include "kaitai/exceptions.h"

w3sc_t::w3sc_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, w3sc_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_file_infos = 0;
    f_file_infos = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void w3sc_t::_read() {
    m_magic = m__io->read_bytes(4);
    if (!(magic() == std::string("\x43\x53\x33\x57", 4))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x43\x53\x33\x57", 4), magic(), _io(), std::string("/seq/0"));
    }
    m_version = m__io->read_u4le();
    m_dummy = m__io->read_u8le();
    switch (version()) {
    case 1: {
        m_info_offset = m__io->read_u4le();
        break;
    }
    default: {
        m_info_offset = m__io->read_u8le();
        break;
    }
    }
    switch (version()) {
    case 1: {
        m_files = m__io->read_u4le();
        break;
    }
    default: {
        m_files = m__io->read_u8le();
        break;
    }
    }
    switch (version()) {
    case 1: {
        m_names_offset = m__io->read_u4le();
        break;
    }
    default: {
        m_names_offset = m__io->read_u8le();
        break;
    }
    }
    switch (version()) {
    case 1: {
        m_names_size = m__io->read_u4le();
        break;
    }
    default: {
        m_names_size = m__io->read_u8le();
        break;
    }
    }
}

w3sc_t::~w3sc_t() {
    _clean_up();
}

void w3sc_t::_clean_up() {
    if (f_file_infos) {
        if (m_file_infos) {
            for (std::vector<file_info_t*>::iterator it = m_file_infos->begin(); it != m_file_infos->end(); ++it) {
                delete *it;
            }
            delete m_file_infos; m_file_infos = 0;
        }
    }
}

w3sc_t::file_info_t::file_info_t(kaitai::kstream* p__io, w3sc_t* p__parent, w3sc_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_data = false;
    f_name = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void w3sc_t::file_info_t::_read() {
    switch (_parent()->version()) {
    case 1: {
        m_name_offset = m__io->read_u4le();
        break;
    }
    default: {
        m_name_offset = m__io->read_u8le();
        break;
    }
    }
    switch (_parent()->version()) {
    case 1: {
        m_offset = m__io->read_u4le();
        break;
    }
    default: {
        m_offset = m__io->read_u8le();
        break;
    }
    }
    switch (_parent()->version()) {
    case 1: {
        m_size = m__io->read_u4le();
        break;
    }
    default: {
        m_size = m__io->read_u8le();
        break;
    }
    }
}

w3sc_t::file_info_t::~file_info_t() {
    _clean_up();
}

void w3sc_t::file_info_t::_clean_up() {
    if (f_data) {
    }
    if (f_name) {
    }
}

std::string w3sc_t::file_info_t::data() {
    if (f_data)
        return m_data;
    std::streampos _pos = m__io->pos();
    m__io->seek(offset());
    m_data = m__io->read_bytes(size());
    m__io->seek(_pos);
    f_data = true;
    return m_data;
}

std::string w3sc_t::file_info_t::name() {
    if (f_name)
        return m_name;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->names_offset() + name_offset()));
    m_name = kaitai::kstream::bytes_to_str(m__io->read_bytes_term(0, false, true, true), std::string("UTF-8"));
    m__io->seek(_pos);
    f_name = true;
    return m_name;
}

std::vector<w3sc_t::file_info_t*>* w3sc_t::file_infos() {
    if (f_file_infos)
        return m_file_infos;
    std::streampos _pos = m__io->pos();
    m__io->seek(info_offset());
    int l_file_infos = files();
    m_file_infos = new std::vector<file_info_t*>();
    m_file_infos->reserve(l_file_infos);
    for (int i = 0; i < l_file_infos; i++) {
        m_file_infos->push_back(new file_info_t(m__io, this, m__root));
    }
    m__io->seek(_pos);
    f_file_infos = true;
    return m_file_infos;
}
