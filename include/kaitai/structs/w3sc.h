#ifndef W3SC_H_
#define W3SC_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class w3sc_t : public kaitai::kstruct {

public:
    class file_info_t;

    w3sc_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, w3sc_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~w3sc_t();

    class file_info_t : public kaitai::kstruct {

    public:

        file_info_t(kaitai::kstream* p__io, w3sc_t* p__parent = 0, w3sc_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~file_info_t();

    private:
        bool f_data;
        std::string m_data;

    public:
        std::string data();

    private:
        bool f_name;
        std::string m_name;

    public:
        std::string name();

    private:
        uint64_t m_name_offset;
        uint64_t m_offset;
        uint64_t m_size;
        w3sc_t* m__root;
        w3sc_t* m__parent;

    public:
        uint64_t name_offset() const { return m_name_offset; }
        uint64_t offset() const { return m_offset; }
        uint64_t size() const { return m_size; }
        w3sc_t* _root() const { return m__root; }
        w3sc_t* _parent() const { return m__parent; }
    };

private:
    bool f_file_infos;
    std::vector<file_info_t*>* m_file_infos;

public:
    std::vector<file_info_t*>* file_infos();

private:
    std::string m_magic;
    uint32_t m_version;
    uint64_t m_dummy;
    uint64_t m_info_offset;
    uint64_t m_files;
    uint64_t m_names_offset;
    uint64_t m_names_size;
    w3sc_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::string magic() const { return m_magic; }
    uint32_t version() const { return m_version; }
    uint64_t dummy() const { return m_dummy; }
    uint64_t info_offset() const { return m_info_offset; }
    uint64_t files() const { return m_files; }
    uint64_t names_offset() const { return m_names_offset; }
    uint64_t names_size() const { return m_names_size; }
    w3sc_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // W3SC_H_
