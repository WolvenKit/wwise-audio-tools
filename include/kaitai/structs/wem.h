#ifndef WEM_H_
#define WEM_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 11000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.11 or later is required"
#endif

class wem_t : public kaitai::kstruct {

public:
    class chunk_t;
    class fmt_chunk_t;
    class junk_chunk_t;
    class list_labl_subchunk_t;
    class riff_header_t;
    class list_chunk_t;
    class data_chunk_t;
    class cue_chunk_t;
    class riff_chunk_t;
    class cue_point_subchunk_t;
    class random_blank_bytes_t;

    wem_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, wem_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~wem_t();

    class chunk_t : public kaitai::kstruct {

    public:

        chunk_t(kaitai::kstream* p__io, wem_t* p__parent = 0, wem_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~chunk_t();

    private:
        riff_chunk_t* m_riff_chunk;
        kaitai::kstruct* m_data;
        bool n_data;

    public:
        bool _is_null_data() { data(); return n_data; };

    private:
        wem_t* m__root;
        wem_t* m__parent;

    public:
        riff_chunk_t* riff_chunk() const { return m_riff_chunk; }
        kaitai::kstruct* data() const { return m_data; }
        wem_t* _root() const { return m__root; }
        wem_t* _parent() const { return m__parent; }
    };

    class fmt_chunk_t : public kaitai::kstruct {

    public:

        fmt_chunk_t(kaitai::kstream* p__io, wem_t::chunk_t* p__parent = 0, wem_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~fmt_chunk_t();

    private:
        uint16_t m_compression_code;
        uint16_t m_channels;
        uint32_t m_samples_per_sec;
        uint32_t m_avg_bytes_per_sec;
        uint16_t m_block_align;
        uint16_t m_bits_per_sample;
        uint16_t m_extra_byte_count;
        uint16_t m_valid_bits_per_sample;
        uint32_t m_channel_mask;
        std::string m_guid;
        wem_t* m__root;
        wem_t::chunk_t* m__parent;

    public:
        uint16_t compression_code() const { return m_compression_code; }
        uint16_t channels() const { return m_channels; }
        uint32_t samples_per_sec() const { return m_samples_per_sec; }
        uint32_t avg_bytes_per_sec() const { return m_avg_bytes_per_sec; }
        uint16_t block_align() const { return m_block_align; }
        uint16_t bits_per_sample() const { return m_bits_per_sample; }
        uint16_t extra_byte_count() const { return m_extra_byte_count; }
        uint16_t valid_bits_per_sample() const { return m_valid_bits_per_sample; }
        uint32_t channel_mask() const { return m_channel_mask; }
        std::string guid() const { return m_guid; }
        wem_t* _root() const { return m__root; }
        wem_t::chunk_t* _parent() const { return m__parent; }
    };

    class junk_chunk_t : public kaitai::kstruct {

    public:

        junk_chunk_t(kaitai::kstream* p__io, wem_t::chunk_t* p__parent = 0, wem_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~junk_chunk_t();

    private:
        std::string m_junk;
        wem_t* m__root;
        wem_t::chunk_t* m__parent;

    public:
        std::string junk() const { return m_junk; }
        wem_t* _root() const { return m__root; }
        wem_t::chunk_t* _parent() const { return m__parent; }
    };

    class list_labl_subchunk_t : public kaitai::kstruct {

    public:

        list_labl_subchunk_t(kaitai::kstream* p__io, wem_t::list_chunk_t* p__parent = 0, wem_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~list_labl_subchunk_t();

    private:
        std::string m_magic;
        uint32_t m_size;
        uint32_t m_cue_point_id;
        std::string m_data;
        wem_t* m__root;
        wem_t::list_chunk_t* m__parent;

    public:
        std::string magic() const { return m_magic; }
        uint32_t size() const { return m_size; }
        uint32_t cue_point_id() const { return m_cue_point_id; }
        std::string data() const { return m_data; }
        wem_t* _root() const { return m__root; }
        wem_t::list_chunk_t* _parent() const { return m__parent; }
    };

    class riff_header_t : public kaitai::kstruct {

    public:

        riff_header_t(kaitai::kstream* p__io, wem_t* p__parent = 0, wem_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~riff_header_t();

    private:
        std::string m_magic;
        uint32_t m_chunk_size;
        uint32_t m_wav_id;
        wem_t* m__root;
        wem_t* m__parent;

    public:
        std::string magic() const { return m_magic; }
        uint32_t chunk_size() const { return m_chunk_size; }
        uint32_t wav_id() const { return m_wav_id; }
        wem_t* _root() const { return m__root; }
        wem_t* _parent() const { return m__parent; }
    };

    class list_chunk_t : public kaitai::kstruct {

    public:

        list_chunk_t(uint32_t p_size, kaitai::kstream* p__io, wem_t::chunk_t* p__parent = 0, wem_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~list_chunk_t();

    private:
        std::string m_adtl;
        list_labl_subchunk_t* m_labl;
        uint32_t m_size;
        wem_t* m__root;
        wem_t::chunk_t* m__parent;

    public:
        std::string adtl() const { return m_adtl; }
        list_labl_subchunk_t* labl() const { return m_labl; }
        uint32_t size() const { return m_size; }
        wem_t* _root() const { return m__root; }
        wem_t::chunk_t* _parent() const { return m__parent; }
    };

    class data_chunk_t : public kaitai::kstruct {

    public:

        data_chunk_t(uint32_t p_size, kaitai::kstream* p__io, wem_t::chunk_t* p__parent = 0, wem_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~data_chunk_t();

    private:
        std::string m_data;
        uint32_t m_size;
        wem_t* m__root;
        wem_t::chunk_t* m__parent;

    public:
        std::string data() const { return m_data; }
        uint32_t size() const { return m_size; }
        wem_t* _root() const { return m__root; }
        wem_t::chunk_t* _parent() const { return m__parent; }
    };

    class cue_chunk_t : public kaitai::kstruct {

    public:

        cue_chunk_t(kaitai::kstream* p__io, wem_t::chunk_t* p__parent = 0, wem_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~cue_chunk_t();

    private:
        uint32_t m_cue_point_count;
        std::vector<cue_point_subchunk_t*>* m_cue_points;
        wem_t* m__root;
        wem_t::chunk_t* m__parent;

    public:
        uint32_t cue_point_count() const { return m_cue_point_count; }
        std::vector<cue_point_subchunk_t*>* cue_points() const { return m_cue_points; }
        wem_t* _root() const { return m__root; }
        wem_t::chunk_t* _parent() const { return m__parent; }
    };

    class riff_chunk_t : public kaitai::kstruct {

    public:

        riff_chunk_t(kaitai::kstream* p__io, wem_t::chunk_t* p__parent = 0, wem_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~riff_chunk_t();

    private:
        std::string m_dummy;
        std::string m_type;
        uint32_t m_size;
        wem_t* m__root;
        wem_t::chunk_t* m__parent;

    public:
        std::string dummy() const { return m_dummy; }
        std::string type() const { return m_type; }
        uint32_t size() const { return m_size; }
        wem_t* _root() const { return m__root; }
        wem_t::chunk_t* _parent() const { return m__parent; }
    };

    class cue_point_subchunk_t : public kaitai::kstruct {

    public:

        cue_point_subchunk_t(kaitai::kstream* p__io, wem_t::cue_chunk_t* p__parent = 0, wem_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~cue_point_subchunk_t();

    private:
        uint32_t m_id;
        uint32_t m_position;
        uint32_t m_data_chunk_id;
        uint32_t m_chunk_start;
        uint32_t m_block_start;
        uint32_t m_sample_start;
        wem_t* m__root;
        wem_t::cue_chunk_t* m__parent;

    public:
        uint32_t id() const { return m_id; }
        uint32_t position() const { return m_position; }
        uint32_t data_chunk_id() const { return m_data_chunk_id; }
        uint32_t chunk_start() const { return m_chunk_start; }
        uint32_t block_start() const { return m_block_start; }
        uint32_t sample_start() const { return m_sample_start; }
        wem_t* _root() const { return m__root; }
        wem_t::cue_chunk_t* _parent() const { return m__parent; }
    };

    class random_blank_bytes_t : public kaitai::kstruct {

    public:

        random_blank_bytes_t(kaitai::kstream* p__io, wem_t::chunk_t* p__parent = 0, wem_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~random_blank_bytes_t();

    private:
        std::vector<uint8_t>* m_dummy;
        wem_t* m__root;
        wem_t::chunk_t* m__parent;

    public:
        std::vector<uint8_t>* dummy() const { return m_dummy; }
        wem_t* _root() const { return m__root; }
        wem_t::chunk_t* _parent() const { return m__parent; }
    };

private:
    riff_header_t* m_riff_header;
    std::vector<chunk_t*>* m_chunks;
    wem_t* m__root;
    kaitai::kstruct* m__parent;

public:
    riff_header_t* riff_header() const { return m_riff_header; }
    std::vector<chunk_t*>* chunks() const { return m_chunks; }
    wem_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // WEM_H_
