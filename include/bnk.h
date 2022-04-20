#ifndef BNK_H_
#define BNK_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class bnk_t : public kaitai::kstruct {

public:
    class data_index_t;
    class indices_t;
    class data_t;
    class bank_header_t;
    class audio_section_t;
    class audio_sections_t;
    class index_t;

    bnk_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, bnk_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~bnk_t();

    /**
     * The DIDX (Data Index) section contains the references to the .wem files embedded in the SoundBank.
     */

    class data_index_t : public kaitai::kstruct {

    public:

        data_index_t(kaitai::kstream* p__io, bnk_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~data_index_t();

    private:
        std::string m_magic;
        uint32_t m_length;
        indices_t* m_data;
        bnk_t* m__root;
        bnk_t* m__parent;
        std::string m__raw_data;
        kaitai::kstream* m__io__raw_data;

    public:
        std::string magic() const { return m_magic; }
        uint32_t length() const { return m_length; }
        indices_t* data() const { return m_data; }
        bnk_t* _root() const { return m__root; }
        bnk_t* _parent() const { return m__parent; }
        std::string _raw_data() const { return m__raw_data; }
        kaitai::kstream* _io__raw_data() const { return m__io__raw_data; }
    };

    class indices_t : public kaitai::kstruct {

    public:

        indices_t(kaitai::kstream* p__io, bnk_t::data_index_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~indices_t();

    private:
        std::vector<index_t*>* m_indices;
        bnk_t* m__root;
        bnk_t::data_index_t* m__parent;

    public:
        std::vector<index_t*>* indices() const { return m_indices; }
        bnk_t* _root() const { return m__root; }
        bnk_t::data_index_t* _parent() const { return m__parent; }
    };

    class data_t : public kaitai::kstruct {

    public:

        data_t(kaitai::kstream* p__io, bnk_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~data_t();

    private:
        std::string m_magic;
        uint32_t m_length;
        audio_sections_t* m_data;
        bnk_t* m__root;
        bnk_t* m__parent;
        std::string m__raw_data;
        kaitai::kstream* m__io__raw_data;

    public:
        std::string magic() const { return m_magic; }
        uint32_t length() const { return m_length; }
        audio_sections_t* data() const { return m_data; }
        bnk_t* _root() const { return m__root; }
        bnk_t* _parent() const { return m__parent; }
        std::string _raw_data() const { return m__raw_data; }
        kaitai::kstream* _io__raw_data() const { return m__io__raw_data; }
    };

    /**
     * The BKHD section (Bank Header) contains the version number and the SoundBank id.
     */

    class bank_header_t : public kaitai::kstruct {

    public:

        bank_header_t(kaitai::kstream* p__io, bnk_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~bank_header_t();

    private:
        std::string m_magic;
        uint32_t m_length;
        uint32_t m_version;
        uint32_t m_id;
        std::string m_data;
        bnk_t* m__root;
        bnk_t* m__parent;

    public:
        std::string magic() const { return m_magic; }
        uint32_t length() const { return m_length; }
        uint32_t version() const { return m_version; }
        uint32_t id() const { return m_id; }
        std::string data() const { return m_data; }
        bnk_t* _root() const { return m__root; }
        bnk_t* _parent() const { return m__parent; }
    };

    class audio_section_t : public kaitai::kstruct {

    public:

        audio_section_t(uint32_t p_index, kaitai::kstream* p__io, bnk_t::audio_sections_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~audio_section_t();

    private:
        bool f_data;
        std::string m_data;

    public:
        std::string data();

    private:
        uint32_t m_index;
        bnk_t* m__root;
        bnk_t::audio_sections_t* m__parent;

    public:
        uint32_t index() const { return m_index; }
        bnk_t* _root() const { return m__root; }
        bnk_t::audio_sections_t* _parent() const { return m__parent; }
    };

    class audio_sections_t : public kaitai::kstruct {

    public:

        audio_sections_t(kaitai::kstream* p__io, bnk_t::data_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~audio_sections_t();

    private:
        std::vector<audio_section_t*>* m_audio_sections;
        bnk_t* m__root;
        bnk_t::data_t* m__parent;

    public:
        std::vector<audio_section_t*>* audio_sections() const { return m_audio_sections; }
        bnk_t* _root() const { return m__root; }
        bnk_t::data_t* _parent() const { return m__parent; }
    };

    class index_t : public kaitai::kstruct {

    public:

        index_t(kaitai::kstream* p__io, bnk_t::indices_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~index_t();

    private:
        uint32_t m_id;
        uint32_t m_offset;
        uint32_t m_length;
        bnk_t* m__root;
        bnk_t::indices_t* m__parent;

    public:
        uint32_t id() const { return m_id; }
        uint32_t offset() const { return m_offset; }
        uint32_t length() const { return m_length; }
        bnk_t* _root() const { return m__root; }
        bnk_t::indices_t* _parent() const { return m__parent; }
    };

private:
    bank_header_t* m_bank_header;
    data_index_t* m_data_index;
    data_t* m_data;
    bnk_t* m__root;
    kaitai::kstruct* m__parent;

public:
    bank_header_t* bank_header() const { return m_bank_header; }
    data_index_t* data_index() const { return m_data_index; }
    data_t* data() const { return m_data; }
    bnk_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // BNK_H_
