#ifndef VLQ_H_
#define VLQ_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 11000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.11 or later is required"
#endif

/**
 * A variable-length unsigned/signed integer using base128 encoding. 1-byte groups
 * consist of 1-bit flag of continuation and 7-bit value chunk, and are ordered
 * "least significant group first", i.e. in "little-endian" manner.
 * 
 * This particular encoding is specified and used in:
 * 
 * * DWARF debug file format, where it's dubbed "unsigned LEB128" or "ULEB128".
 *   http://dwarfstd.org/doc/dwarf-2.0.0.pdf - page 139
 * * Google Protocol Buffers, where it's called "Base 128 Varints".
 *   https://developers.google.com/protocol-buffers/docs/encoding?csw=1#varints
 * * Apache Lucene, where it's called "VInt"
 *   https://lucene.apache.org/core/3_5_0/fileformats.html#VInt
 * * Apache Avro uses this as a basis for integer encoding, adding ZigZag on
 *   top of it for signed ints
 *   https://avro.apache.org/docs/current/spec.html#binary_encode_primitive
 * 
 * More information on this encoding is available at https://en.wikipedia.org/wiki/LEB128
 * 
 * This particular implementation supports serialized values to up 8 bytes long.
 */

class vlq_t : public kaitai::kstruct {

public:
    class group_t;

    vlq_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, vlq_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~vlq_t();

    /**
     * One byte group, clearly divided into 7-bit "value" chunk and 1-bit "continuation" flag.
     */

    class group_t : public kaitai::kstruct {

    public:

        group_t(kaitai::kstream* p__io, vlq_t* p__parent = 0, vlq_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~group_t();

    private:
        bool f_has_next;
        bool m_has_next;

    public:

        /**
         * If true, then we have more bytes to read
         */
        bool has_next();

    private:
        bool f_value;
        int32_t m_value;

    public:

        /**
         * The 7-bit (base128) numeric value chunk of this group
         */
        int32_t value();

    private:
        uint8_t m_b;
        vlq_t* m__root;
        vlq_t* m__parent;

    public:
        uint8_t b() const { return m_b; }
        vlq_t* _root() const { return m__root; }
        vlq_t* _parent() const { return m__parent; }
    };

private:
    bool f_len;
    int32_t m_len;

public:
    int32_t len();

private:
    bool f_value;
    int32_t m_value;

public:

    /**
     * Resulting unsigned value as normal integer
     */
    int32_t value();

private:
    bool f_sign_bit;
    int32_t m_sign_bit;

public:
    int32_t sign_bit();

private:
    bool f_value_signed;
    int32_t m_value_signed;

public:

    /**
     * \sa https://graphics.stanford.edu/~seander/bithacks.html#VariableSignExtend Source
     */
    int32_t value_signed();

private:
    std::vector<group_t*>* m_groups;
    vlq_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::vector<group_t*>* groups() const { return m_groups; }
    vlq_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // VLQ_H_
