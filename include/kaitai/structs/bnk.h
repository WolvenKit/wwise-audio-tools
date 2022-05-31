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
    class data_obj_t;
    class data_data_t;
    class data_obj_section_t;
    class didx_obj_t;
    class hirc_data_t;
    class bkhd_data_t;
    class event_t;
    class ss_state_group_t;
    class sound_structure_t;
    class stid_obj_t;
    class didx_data_t;
    class ss_rtpc_t;
    class sound_effect_or_voice_t;
    class hirc_obj_t;
    class section_t;
    class audio_bus_t;
    class stid_data_t;
    class ss_effect_t;
    class rand_t;
    class music_segment_t;
    class ss_pos_inc_3d_t;
    class event_action_t;
    class random_bytes_t;
    class ss_pos_inc_2d_t;
    class ss_rtpc_point_t;
    class settings_t;
    class ss_state_obj_t;

    enum action_scope_t {
        ACTION_SCOPE_GAME_OBJECT_SWITCH_OR_TRIGGER = 1,
        ACTION_SCOPE_GLOBAL = 2,
        ACTION_SCOPE_GAME_OBJECT = 3,
        ACTION_SCOPE_GAME_OBJECT_STATE = 4,
        ACTION_SCOPE_ALL = 5,
        ACTION_SCOPE_ALL_EXCEPT = 9
    };

    enum object_type_t {
        OBJECT_TYPE_SETTINGS = 1,
        OBJECT_TYPE_SOUND_EFFECT_OR_VOICE = 2,
        OBJECT_TYPE_EVENT_ACTION = 3,
        OBJECT_TYPE_EVENT = 4,
        OBJECT_TYPE_RANDOM_OR_SEQUENCE_CONTAINER = 5,
        OBJECT_TYPE_ACTOR_MIXER = 7,
        OBJECT_TYPE_AUDIO_BUS = 8,
        OBJECT_TYPE_BLEND_CONTAINER = 9,
        OBJECT_TYPE_MUSIC_SEGMENT = 10,
        OBJECT_TYPE_MUSIC_TRACK = 11,
        OBJECT_TYPE_MUSIC_SWITCH_CONTAINER = 12,
        OBJECT_TYPE_MUSIC_PLAYLIST_CONTAINER = 13,
        OBJECT_TYPE_ATTENUATION = 14,
        OBJECT_TYPE_DIALOGUE_EVENT = 15,
        OBJECT_TYPE_MOTION_BUS = 16,
        OBJECT_TYPE_MOTION_FX = 17,
        OBJECT_TYPE_EFFECT = 18,
        OBJECT_TYPE_UNKNOWN = 19,
        OBJECT_TYPE_AUXILIARY_BUS = 20
    };

    enum play_type_t {
        PLAY_TYPE_SEQUENCE_STEP = 0,
        PLAY_TYPE_RANDOM_STEP = 1,
        PLAY_TYPE_SEQUENCE_CONTINUOUS = 2,
        PLAY_TYPE_RANDOM_CONTINUOUS = 3,
        PLAY_TYPE_SEQUENCE_STEP_NEW_PATH = 4,
        PLAY_TYPE_RANDOM_STEP_NEW_PATH = 5
    };

    enum audio_bus_parameter_type_t {
        AUDIO_BUS_PARAMETER_TYPE_VOICE_VOLUME = 0,
        AUDIO_BUS_PARAMETER_TYPE_VOICE_PITCH = 2,
        AUDIO_BUS_PARAMETER_TYPE_VOICE_LOW_PASS_FILTER = 3,
        AUDIO_BUS_PARAMETER_TYPE_BUS_VOLUME = 4
    };

    enum action_type_t {
        ACTION_TYPE_STOP = 1,
        ACTION_TYPE_PAUSE = 2,
        ACTION_TYPE_RESUME = 3,
        ACTION_TYPE_PLAY = 4,
        ACTION_TYPE_TRIGGER = 5,
        ACTION_TYPE_MUTE = 6,
        ACTION_TYPE_UNMUTE = 7,
        ACTION_TYPE_SET_VOICE_PITCH = 8,
        ACTION_TYPE_RESET_VOICE_PITCH = 9,
        ACTION_TYPE_SET_VOICE_VOLUME = 10,
        ACTION_TYPE_RESET_VOICE_VOLUME = 11,
        ACTION_TYPE_SET_BUS_VOLUME = 12,
        ACTION_TYPE_RESET_BUS_VOLUME = 13,
        ACTION_TYPE_SET_VOICE_LOW_PASS_FILTER = 14,
        ACTION_TYPE_RESET_VOICE_LOW_PASS_FILTER = 15,
        ACTION_TYPE_ENABLE_STATE = 16,
        ACTION_TYPE_DISABLE_STATE = 17,
        ACTION_TYPE_SET_STATE = 18,
        ACTION_TYPE_SET_GAME_PARAMETER = 19,
        ACTION_TYPE_RESET_GAME_PARAMETER = 20,
        ACTION_TYPE_SET_SWITCH = 21,
        ACTION_TYPE_ENABLE_BYPASS_OR_DISABLE_BYPASS = 22,
        ACTION_TYPE_RESET_BYPASS_EFFECT = 23,
        ACTION_TYPE_BREAK = 24,
        ACTION_TYPE_SEEK = 25
    };

    bnk_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, bnk_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~bnk_t();

    class data_obj_t : public kaitai::kstruct {

    public:

        data_obj_t(uint32_t p_offset, uint32_t p_length, kaitai::kstream* p__io, bnk_t::data_obj_section_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~data_obj_t();

    private:
        bool f_file;
        std::string m_file;

    public:
        std::string file();

    private:
        uint32_t m_offset;
        uint32_t m_length;
        bnk_t* m__root;
        bnk_t::data_obj_section_t* m__parent;

    public:
        uint32_t offset() const { return m_offset; }
        uint32_t length() const { return m_length; }
        bnk_t* _root() const { return m__root; }
        bnk_t::data_obj_section_t* _parent() const { return m__parent; }
    };

    class data_data_t : public kaitai::kstruct {

    public:

        data_data_t(uint32_t p_length, kaitai::kstream* p__io, bnk_t::section_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~data_data_t();

    private:
        bool f_didx_data;
        bnk_t::didx_data_t* m_didx_data;

    public:
        bnk_t::didx_data_t* didx_data();

    private:
        data_obj_section_t* m_data_obj_section;
        uint32_t m_length;
        bnk_t* m__root;
        bnk_t::section_t* m__parent;
        std::string m__raw_data_obj_section;
        kaitai::kstream* m__io__raw_data_obj_section;

    public:
        data_obj_section_t* data_obj_section() const { return m_data_obj_section; }
        uint32_t length() const { return m_length; }
        bnk_t* _root() const { return m__root; }
        bnk_t::section_t* _parent() const { return m__parent; }
        std::string _raw_data_obj_section() const { return m__raw_data_obj_section; }
        kaitai::kstream* _io__raw_data_obj_section() const { return m__io__raw_data_obj_section; }
    };

    class data_obj_section_t : public kaitai::kstruct {

    public:

        data_obj_section_t(uint32_t p_length, kaitai::kstream* p__io, bnk_t::data_data_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~data_obj_section_t();

    private:
        std::vector<data_obj_t*>* m_data;
        uint32_t m_length;
        bnk_t* m__root;
        bnk_t::data_data_t* m__parent;

    public:
        std::vector<data_obj_t*>* data() const { return m_data; }
        uint32_t length() const { return m_length; }
        bnk_t* _root() const { return m__root; }
        bnk_t::data_data_t* _parent() const { return m__parent; }
    };

    class didx_obj_t : public kaitai::kstruct {

    public:

        didx_obj_t(kaitai::kstream* p__io, bnk_t::didx_data_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~didx_obj_t();

    private:
        uint32_t m_id;
        uint32_t m_offset;
        uint32_t m_length;
        bnk_t* m__root;
        bnk_t::didx_data_t* m__parent;

    public:
        uint32_t id() const { return m_id; }
        uint32_t offset() const { return m_offset; }
        uint32_t length() const { return m_length; }
        bnk_t* _root() const { return m__root; }
        bnk_t::didx_data_t* _parent() const { return m__parent; }
    };

    class hirc_data_t : public kaitai::kstruct {

    public:

        hirc_data_t(uint32_t p_length, kaitai::kstream* p__io, bnk_t::section_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~hirc_data_t();

    private:
        uint32_t m_num_objects;
        std::vector<hirc_obj_t*>* m_objs;
        uint32_t m_length;
        bnk_t* m__root;
        bnk_t::section_t* m__parent;

    public:
        uint32_t num_objects() const { return m_num_objects; }
        std::vector<hirc_obj_t*>* objs() const { return m_objs; }
        uint32_t length() const { return m_length; }
        bnk_t* _root() const { return m__root; }
        bnk_t::section_t* _parent() const { return m__parent; }
    };

    class bkhd_data_t : public kaitai::kstruct {

    public:

        bkhd_data_t(uint32_t p_length, kaitai::kstream* p__io, bnk_t::section_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~bkhd_data_t();

    private:
        uint32_t m_version;
        uint32_t m_id;
        std::string m_blank1;
        std::string m_blank2;
        std::string m_random;
        uint32_t m_length;
        bnk_t* m__root;
        bnk_t::section_t* m__parent;

    public:
        [[nodiscard]] uint32_t version() const;
        uint32_t id() const { return m_id; }
        std::string blank1() const { return m_blank1; }
        std::string blank2() const { return m_blank2; }
        std::string random() const { return m_random; }
        uint32_t length() const { return m_length; }
        bnk_t* _root() const { return m__root; }
        bnk_t::section_t* _parent() const { return m__parent; }
    };

    class event_t : public kaitai::kstruct {

    public:

        event_t(kaitai::kstream* p__io, bnk_t::hirc_obj_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~event_t();

    private:
        uint32_t m_event_action_count;
        std::vector<uint32_t>* m_event_actions;
        bnk_t* m__root;
        bnk_t::hirc_obj_t* m__parent;

    public:
        uint32_t event_action_count() const { return m_event_action_count; }
        std::vector<uint32_t>* event_actions() const { return m_event_actions; }
        bnk_t* _root() const { return m__root; }
        bnk_t::hirc_obj_t* _parent() const { return m__parent; }
    };

    class ss_state_group_t : public kaitai::kstruct {

    public:

        ss_state_group_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~ss_state_group_t();

    private:
        uint32_t m_id;
        int8_t m_change_occurs_at;
        uint16_t m_settings_vary_from_default;
        std::vector<ss_state_obj_t*>* m_state_obj;
        bnk_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint32_t id() const { return m_id; }
        int8_t change_occurs_at() const { return m_change_occurs_at; }
        uint16_t settings_vary_from_default() const { return m_settings_vary_from_default; }
        std::vector<ss_state_obj_t*>* state_obj() const { return m_state_obj; }
        bnk_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class sound_structure_t : public kaitai::kstruct {

    public:

        sound_structure_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~sound_structure_t();

    private:
        bool m_override_parent_settings_for_effects;
        int8_t m_effects_count;
        std::string m_bypassed_effects;
        bool n_bypassed_effects;

    public:
        bool _is_null_bypassed_effects() { bypassed_effects(); return n_bypassed_effects; };

    private:
        std::vector<ss_effect_t*>* m_effect;
        bool n_effect;

    public:
        bool _is_null_effect() { effect(); return n_effect; };

    private:
        uint32_t m_output_bus_id;
        uint32_t m_parent_id;
        bool m_override_parent_settings_playback_priority;
        bool m_offset_priority_enabled;
        int8_t m_additional_parameter_count;
        std::vector<int8_t>* m_parameter_type;
        std::vector<double>* m_parameter_value;
        std::string m_blank1;
        bool m_positioning_section_included;
        int8_t m_positioning_dimension;
        bool n_positioning_dimension;

    public:
        bool _is_null_positioning_dimension() { positioning_dimension(); return n_positioning_dimension; };

    private:
        ss_pos_inc_2d_t* m_pos_inc_2d;
        bool n_pos_inc_2d;

    public:
        bool _is_null_pos_inc_2d() { pos_inc_2d(); return n_pos_inc_2d; };

    private:
        ss_pos_inc_3d_t* m_pos_inc_3d;
        bool n_pos_inc_3d;

    public:
        bool _is_null_pos_inc_3d() { pos_inc_3d(); return n_pos_inc_3d; };

    private:
        bool m_override_parent_game_aux_settings;
        bool m_use_game_aux_sends;
        bool m_user_aux_sends_exist;
        std::vector<uint32_t>* m_aux_busses;
        bool n_aux_busses;

    public:
        bool _is_null_aux_busses() { aux_busses(); return n_aux_busses; };

    private:
        bool m_unk_limit_param_playback;
        int8_t m_when_priority_is_equal;
        bool n_when_priority_is_equal;

    public:
        bool _is_null_when_priority_is_equal() { when_priority_is_equal(); return n_when_priority_is_equal; };

    private:
        int8_t m_when_limit_is_reached;
        bool n_when_limit_is_reached;

    public:
        bool _is_null_when_limit_is_reached() { when_limit_is_reached(); return n_when_limit_is_reached; };

    private:
        uint16_t m_sound_instance_limit;
        bool n_sound_instance_limit;

    public:
        bool _is_null_sound_instance_limit() { sound_instance_limit(); return n_sound_instance_limit; };

    private:
        int8_t m_sound_instance_limiting_behavior;
        int8_t m_virt_voice_behavior;
        bool m_parent_playback_settings_override;
        bool m_parent_virt_voice_settings_override;
        uint32_t m_state_group_count;
        std::vector<ss_state_group_t*>* m_state_group;
        uint16_t m_rtpc_count;
        bnk_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        bool override_parent_settings_for_effects() const { return m_override_parent_settings_for_effects; }
        int8_t effects_count() const { return m_effects_count; }
        std::string bypassed_effects() const { return m_bypassed_effects; }
        std::vector<ss_effect_t*>* effect() const { return m_effect; }
        uint32_t output_bus_id() const { return m_output_bus_id; }
        uint32_t parent_id() const { return m_parent_id; }
        bool override_parent_settings_playback_priority() const { return m_override_parent_settings_playback_priority; }
        bool offset_priority_enabled() const { return m_offset_priority_enabled; }
        int8_t additional_parameter_count() const { return m_additional_parameter_count; }
        std::vector<int8_t>* parameter_type() const { return m_parameter_type; }
        std::vector<double>* parameter_value() const { return m_parameter_value; }
        std::string blank1() const { return m_blank1; }
        bool positioning_section_included() const { return m_positioning_section_included; }
        int8_t positioning_dimension() const { return m_positioning_dimension; }
        ss_pos_inc_2d_t* pos_inc_2d() const { return m_pos_inc_2d; }
        ss_pos_inc_3d_t* pos_inc_3d() const { return m_pos_inc_3d; }
        bool override_parent_game_aux_settings() const { return m_override_parent_game_aux_settings; }
        bool use_game_aux_sends() const { return m_use_game_aux_sends; }
        bool user_aux_sends_exist() const { return m_user_aux_sends_exist; }
        std::vector<uint32_t>* aux_busses() const { return m_aux_busses; }
        bool unk_limit_param_playback() const { return m_unk_limit_param_playback; }
        int8_t when_priority_is_equal() const { return m_when_priority_is_equal; }
        int8_t when_limit_is_reached() const { return m_when_limit_is_reached; }
        uint16_t sound_instance_limit() const { return m_sound_instance_limit; }
        int8_t sound_instance_limiting_behavior() const { return m_sound_instance_limiting_behavior; }
        int8_t virt_voice_behavior() const { return m_virt_voice_behavior; }
        bool parent_playback_settings_override() const { return m_parent_playback_settings_override; }
        bool parent_virt_voice_settings_override() const { return m_parent_virt_voice_settings_override; }
        uint32_t state_group_count() const { return m_state_group_count; }
        std::vector<ss_state_group_t*>* state_group() const { return m_state_group; }
        uint16_t rtpc_count() const { return m_rtpc_count; }
        bnk_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class stid_obj_t : public kaitai::kstruct {

    public:

        stid_obj_t(kaitai::kstream* p__io, bnk_t::stid_data_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~stid_obj_t();

    private:
        uint32_t m_id;
        uint8_t m_name_len;
        std::string m_name;
        bnk_t* m__root;
        bnk_t::stid_data_t* m__parent;

    public:
        uint32_t id() const { return m_id; }
        uint8_t name_len() const { return m_name_len; }
        std::string name() const { return m_name; }
        bnk_t* _root() const { return m__root; }
        bnk_t::stid_data_t* _parent() const { return m__parent; }
    };

    class didx_data_t : public kaitai::kstruct {

    public:

        didx_data_t(uint32_t p_length, kaitai::kstream* p__io, bnk_t::section_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~didx_data_t();

    private:
        bool f_num_files;
        int32_t m_num_files;

    public:
        int32_t num_files();

    private:
        std::vector<didx_obj_t*>* m_objs;
        uint32_t m_length;
        bnk_t* m__root;
        bnk_t::section_t* m__parent;

    public:
        std::vector<didx_obj_t*>* objs() const { return m_objs; }
        uint32_t length() const { return m_length; }
        bnk_t* _root() const { return m__root; }
        bnk_t::section_t* _parent() const { return m__parent; }
    };

    class ss_rtpc_t : public kaitai::kstruct {

    public:

        ss_rtpc_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~ss_rtpc_t();

    private:
        uint32_t m_game_param_x_axis_id;
        uint32_t m_y_axis_type;
        uint32_t m_unk_id_1;
        std::string m_unk_1;
        int8_t m_num_points;
        std::string m_unk_2;
        std::vector<ss_rtpc_point_t*>* m_point;
        bnk_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint32_t game_param_x_axis_id() const { return m_game_param_x_axis_id; }
        uint32_t y_axis_type() const { return m_y_axis_type; }
        uint32_t unk_id_1() const { return m_unk_id_1; }
        std::string unk_1() const { return m_unk_1; }
        int8_t num_points() const { return m_num_points; }
        std::string unk_2() const { return m_unk_2; }
        std::vector<ss_rtpc_point_t*>* point() const { return m_point; }
        bnk_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class sound_effect_or_voice_t : public kaitai::kstruct {

    public:

        sound_effect_or_voice_t(kaitai::kstream* p__io, bnk_t::hirc_obj_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~sound_effect_or_voice_t();

    private:
        bool f_wem_data;
        std::string m_wem_data;
        bool n_wem_data;

    public:
        bool _is_null_wem_data() { wem_data(); return n_wem_data; };

    private:

    public:
        std::string wem_data();

    private:
        std::string m_unknown;
        uint32_t m_included_or_streamed;
        uint32_t m_audio_file_id;
        uint32_t m_source_id;
        uint32_t m_wem_offset;
        bool n_wem_offset;

    public:
        bool _is_null_wem_offset() { wem_offset(); return n_wem_offset; };

    private:
        uint32_t m_wem_length;
        bool n_wem_length;

    public:
        bool _is_null_wem_length() { wem_length(); return n_wem_length; };

    private:
        int8_t m_sound_object_type;
        std::string m_sound_structure;
        bnk_t* m__root;
        bnk_t::hirc_obj_t* m__parent;

    public:
        std::string unknown() const { return m_unknown; }
        uint32_t included_or_streamed() const { return m_included_or_streamed; }
        uint32_t audio_file_id() const { return m_audio_file_id; }
        uint32_t source_id() const { return m_source_id; }
        uint32_t wem_offset() const { return m_wem_offset; }
        uint32_t wem_length() const { return m_wem_length; }
        int8_t sound_object_type() const { return m_sound_object_type; }
        std::string sound_structure() const { return m_sound_structure; }
        bnk_t* _root() const { return m__root; }
        bnk_t::hirc_obj_t* _parent() const { return m__parent; }
    };

    class hirc_obj_t : public kaitai::kstruct {

    public:

        hirc_obj_t(kaitai::kstream* p__io, bnk_t::hirc_data_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~hirc_obj_t();

    private:
        object_type_t m_type;
        uint32_t m_length;
        uint32_t m_id;
        kaitai::kstruct* m_object_data;
        bnk_t* m__root;
        bnk_t::hirc_data_t* m__parent;

    public:
        object_type_t type() const { return m_type; }
        uint32_t length() const { return m_length; }
        uint32_t id() const { return m_id; }
        kaitai::kstruct* object_data() const { return m_object_data; }
        bnk_t* _root() const { return m__root; }
        bnk_t::hirc_data_t* _parent() const { return m__parent; }
    };

    class section_t : public kaitai::kstruct {

    public:

        section_t(kaitai::kstream* p__io, bnk_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~section_t();

    private:
        std::string m_type;
        uint32_t m_length;
        kaitai::kstruct* m_section_data;
        bnk_t* m__root;
        bnk_t* m__parent;

    public:
        std::string type() const { return m_type; }
        uint32_t length() const { return m_length; }
        kaitai::kstruct* section_data() const { return m_section_data; }
        bnk_t* _root() const { return m__root; }
        bnk_t* _parent() const { return m__parent; }
    };

    class audio_bus_t : public kaitai::kstruct {

    public:

        audio_bus_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~audio_bus_t();

    private:
        uint32_t m_parent_audio_bus_id;
        int8_t m_additional_parameter_count;
        std::vector<audio_bus_parameter_type_t>* m_parameter_type;
        std::vector<float>* m_parameter_value;
        int8_t m_action_when_priority_equal;
        int8_t m_action_when_limit_reached;
        uint16_t m_sound_instances_limit;
        bool m_override_parent_playback_limit;
        std::string m_unknown;
        uint32_t m_auto_ducking_recover_time;
        float m_auto_ducking_max_volume;
        uint32_t m_auto_ducking_num_busses;
        bnk_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint32_t parent_audio_bus_id() const { return m_parent_audio_bus_id; }
        int8_t additional_parameter_count() const { return m_additional_parameter_count; }
        std::vector<audio_bus_parameter_type_t>* parameter_type() const { return m_parameter_type; }
        std::vector<float>* parameter_value() const { return m_parameter_value; }
        int8_t action_when_priority_equal() const { return m_action_when_priority_equal; }
        int8_t action_when_limit_reached() const { return m_action_when_limit_reached; }
        uint16_t sound_instances_limit() const { return m_sound_instances_limit; }
        bool override_parent_playback_limit() const { return m_override_parent_playback_limit; }
        std::string unknown() const { return m_unknown; }
        uint32_t auto_ducking_recover_time() const { return m_auto_ducking_recover_time; }
        float auto_ducking_max_volume() const { return m_auto_ducking_max_volume; }
        uint32_t auto_ducking_num_busses() const { return m_auto_ducking_num_busses; }
        bnk_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class stid_data_t : public kaitai::kstruct {

    public:

        stid_data_t(kaitai::kstream* p__io, bnk_t::section_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~stid_data_t();

    private:
        std::string m_unk1;
        uint32_t m_num_soundbanks;
        std::vector<stid_obj_t*>* m_objs;
        bnk_t* m__root;
        bnk_t::section_t* m__parent;

    public:
        std::string unk1() const { return m_unk1; }
        uint32_t num_soundbanks() const { return m_num_soundbanks; }
        std::vector<stid_obj_t*>* objs() const { return m_objs; }
        bnk_t* _root() const { return m__root; }
        bnk_t::section_t* _parent() const { return m__parent; }
    };

    class ss_effect_t : public kaitai::kstruct {

    public:

        ss_effect_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~ss_effect_t();

    private:
        int8_t m_index;
        uint32_t m_id;
        std::string m_blank;
        bnk_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        int8_t index() const { return m_index; }
        uint32_t id() const { return m_id; }
        std::string blank() const { return m_blank; }
        bnk_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class rand_t : public kaitai::kstruct {

    public:

        rand_t(uint32_t p_length, kaitai::kstream* p__io, bnk_t::section_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~rand_t();

    private:
        std::string m_data;
        uint32_t m_length;
        bnk_t* m__root;
        bnk_t::section_t* m__parent;

    public:
        std::string data() const { return m_data; }
        uint32_t length() const { return m_length; }
        bnk_t* _root() const { return m__root; }
        bnk_t::section_t* _parent() const { return m__parent; }
    };

    class music_segment_t : public kaitai::kstruct {

    public:

        music_segment_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~music_segment_t();

    private:
        sound_structure_t* m_sound_structure;
        uint32_t m_child_obj_count;
        std::vector<uint32_t>* m_child_obj;
        std::string m_unk;
        bnk_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        sound_structure_t* sound_structure() const { return m_sound_structure; }
        uint32_t child_obj_count() const { return m_child_obj_count; }
        std::vector<uint32_t>* child_obj() const { return m_child_obj; }
        std::string unk() const { return m_unk; }
        bnk_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class ss_pos_inc_3d_t : public kaitai::kstruct {

    public:

        ss_pos_inc_3d_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~ss_pos_inc_3d_t();

    private:
        uint32_t m_source_type;
        uint32_t m_attenuation_id;
        bool m_spatialization_enabled;
        play_type_t m_play_type;
        bool n_play_type;

    public:
        bool _is_null_play_type() { play_type(); return n_play_type; };

    private:
        bool m_looping_enabled;
        bool n_looping_enabled;

    public:
        bool _is_null_looping_enabled() { looping_enabled(); return n_looping_enabled; };

    private:
        uint32_t m_trainsition_time;
        bool n_trainsition_time;

    public:
        bool _is_null_trainsition_time() { trainsition_time(); return n_trainsition_time; };

    private:
        bool m_follow_listener_orientation;
        bool n_follow_listener_orientation;

    public:
        bool _is_null_follow_listener_orientation() { follow_listener_orientation(); return n_follow_listener_orientation; };

    private:
        bool m_update_at_each_frame;
        bool n_update_at_each_frame;

    public:
        bool _is_null_update_at_each_frame() { update_at_each_frame(); return n_update_at_each_frame; };

    private:
        bnk_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint32_t source_type() const { return m_source_type; }
        uint32_t attenuation_id() const { return m_attenuation_id; }
        bool spatialization_enabled() const { return m_spatialization_enabled; }
        play_type_t play_type() const { return m_play_type; }
        bool looping_enabled() const { return m_looping_enabled; }
        uint32_t trainsition_time() const { return m_trainsition_time; }
        bool follow_listener_orientation() const { return m_follow_listener_orientation; }
        bool update_at_each_frame() const { return m_update_at_each_frame; }
        bnk_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class event_action_t : public kaitai::kstruct {

    public:

        event_action_t(kaitai::kstream* p__io, bnk_t::hirc_obj_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~event_action_t();

    private:
        action_scope_t m_scope;
        action_type_t m_type;
        uint32_t m_game_object_id;
        std::string m_blank1;
        int8_t m_parameter_count;
        std::vector<std::string>* m_parameter_type;
        std::vector<double>* m_parameter_value;
        std::string m_blank2;
        uint32_t m_state_group_id;
        bool n_state_group_id;

    public:
        bool _is_null_state_group_id() { state_group_id(); return n_state_group_id; };

    private:
        uint32_t m_state_id;
        bool n_state_id;

    public:
        bool _is_null_state_id() { state_id(); return n_state_id; };

    private:
        uint32_t m_switch_group_id;
        bool n_switch_group_id;

    public:
        bool _is_null_switch_group_id() { switch_group_id(); return n_switch_group_id; };

    private:
        uint32_t m_switch_id;
        bool n_switch_id;

    public:
        bool _is_null_switch_id() { switch_id(); return n_switch_id; };

    private:
        random_bytes_t* m_extra;
        bnk_t* m__root;
        bnk_t::hirc_obj_t* m__parent;

    public:
        action_scope_t scope() const { return m_scope; }
        action_type_t type() const { return m_type; }
        uint32_t game_object_id() const { return m_game_object_id; }
        std::string blank1() const { return m_blank1; }
        int8_t parameter_count() const { return m_parameter_count; }
        std::vector<std::string>* parameter_type() const { return m_parameter_type; }
        std::vector<double>* parameter_value() const { return m_parameter_value; }
        std::string blank2() const { return m_blank2; }
        uint32_t state_group_id() const { return m_state_group_id; }
        uint32_t state_id() const { return m_state_id; }
        uint32_t switch_group_id() const { return m_switch_group_id; }
        uint32_t switch_id() const { return m_switch_id; }
        random_bytes_t* extra() const { return m_extra; }
        bnk_t* _root() const { return m__root; }
        bnk_t::hirc_obj_t* _parent() const { return m__parent; }
    };

    class random_bytes_t : public kaitai::kstruct {

    public:

        random_bytes_t(uint32_t p_size, kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~random_bytes_t();

    private:
        std::string m_data;
        uint32_t m_size;
        bnk_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        std::string data() const { return m_data; }
        uint32_t size() const { return m_size; }
        bnk_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class ss_pos_inc_2d_t : public kaitai::kstruct {

    public:

        ss_pos_inc_2d_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~ss_pos_inc_2d_t();

    private:
        bool m_panner_enabled;
        bnk_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        bool panner_enabled() const { return m_panner_enabled; }
        bnk_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class ss_rtpc_point_t : public kaitai::kstruct {

    public:

        ss_rtpc_point_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~ss_rtpc_point_t();

    private:
        float m_x_coord;
        float m_y_coord;
        uint32_t m_curve_shape;
        bnk_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        float x_coord() const { return m_x_coord; }
        float y_coord() const { return m_y_coord; }
        uint32_t curve_shape() const { return m_curve_shape; }
        bnk_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class settings_t : public kaitai::kstruct {

    public:

        settings_t(kaitai::kstream* p__io, bnk_t::hirc_obj_t* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~settings_t();

    private:
        int8_t m_settings_count;
        std::vector<std::string>* m_setting_type;
        std::vector<float>* m_setting_val;
        bnk_t* m__root;
        bnk_t::hirc_obj_t* m__parent;

    public:
        int8_t settings_count() const { return m_settings_count; }
        std::vector<std::string>* setting_type() const { return m_setting_type; }
        std::vector<float>* setting_val() const { return m_setting_val; }
        bnk_t* _root() const { return m__root; }
        bnk_t::hirc_obj_t* _parent() const { return m__parent; }
    };

    class ss_state_obj_t : public kaitai::kstruct {

    public:

        ss_state_obj_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, bnk_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~ss_state_obj_t();

    private:
        uint32_t m_id;
        uint32_t m_settings_obj_id;
        bnk_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint32_t id() const { return m_id; }
        uint32_t settings_obj_id() const { return m_settings_obj_id; }
        bnk_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

private:
    std::vector<section_t*>* m_data;
    bnk_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::vector<section_t*>* data() const { return m_data; }
    bnk_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // BNK_H_
