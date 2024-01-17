// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/structs/vlq.h"

vlq_t::vlq_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, vlq_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_groups = 0;
    f_len = false;
    f_value = false;
    f_sign_bit = false;
    f_value_signed = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void vlq_t::_read() {
    m_groups = new std::vector<group_t*>();
    {
        int i = 0;
        group_t* _;
        do {
            _ = new group_t(m__io, this, m__root);
            m_groups->push_back(_);
            i++;
        } while (!(!(_->has_next())));
    }
}

vlq_t::~vlq_t() {
    _clean_up();
}

void vlq_t::_clean_up() {
    if (m_groups) {
        for (std::vector<group_t*>::iterator it = m_groups->begin(); it != m_groups->end(); ++it) {
            delete *it;
        }
        delete m_groups; m_groups = 0;
    }
}

vlq_t::group_t::group_t(kaitai::kstream* p__io, vlq_t* p__parent, vlq_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_has_next = false;
    f_value = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void vlq_t::group_t::_read() {
    m_b = m__io->read_u1();
}

vlq_t::group_t::~group_t() {
    _clean_up();
}

void vlq_t::group_t::_clean_up() {
}

bool vlq_t::group_t::has_next() {
    if (f_has_next)
        return m_has_next;
    m_has_next = (b() & 128) != 0;
    f_has_next = true;
    return m_has_next;
}

int32_t vlq_t::group_t::value() {
    if (f_value)
        return m_value;
    m_value = (b() & 127);
    f_value = true;
    return m_value;
}

int32_t vlq_t::len() {
    if (f_len)
        return m_len;
    m_len = groups()->size();
    f_len = true;
    return m_len;
}

int32_t vlq_t::value() {
    if (f_value)
        return m_value;
    m_value = (((((((groups()->at(0)->value() + ((len() >= 2) ? ((groups()->at(1)->value() << 7)) : (0))) + ((len() >= 3) ? ((groups()->at(2)->value() << 14)) : (0))) + ((len() >= 4) ? ((groups()->at(3)->value() << 21)) : (0))) + ((len() >= 5) ? ((groups()->at(4)->value() << 28)) : (0))) + ((len() >= 6) ? ((groups()->at(5)->value() << 35)) : (0))) + ((len() >= 7) ? ((groups()->at(6)->value() << 42)) : (0))) + ((len() >= 8) ? ((groups()->at(7)->value() << 49)) : (0)));
    f_value = true;
    return m_value;
}

int32_t vlq_t::sign_bit() {
    if (f_sign_bit)
        return m_sign_bit;
    m_sign_bit = (1 << ((7 * len()) - 1));
    f_sign_bit = true;
    return m_sign_bit;
}

int32_t vlq_t::value_signed() {
    if (f_value_signed)
        return m_value_signed;
    m_value_signed = ((value() ^ sign_bit()) - sign_bit());
    f_value_signed = true;
    return m_value_signed;
}
