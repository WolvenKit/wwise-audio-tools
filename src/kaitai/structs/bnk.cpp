// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/structs/bnk.h"
#include "kaitai/exceptions.h"

bnk_t::bnk_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_data = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::_read() {
    m_data = new std::vector<section_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_data->push_back(new section_t(m__io, this, m__root));
            i++;
        }
    }
}

bnk_t::~bnk_t() {
    _clean_up();
}

void bnk_t::_clean_up() {
    if (m_data) {
        for (std::vector<section_t*>::iterator it = m_data->begin(); it != m_data->end(); ++it) {
            delete *it;
        }
        delete m_data; m_data = 0;
    }
}

bnk_t::data_obj_t::data_obj_t(uint32_t p_offset, uint32_t p_length, kaitai::kstream* p__io, bnk_t::data_obj_section_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_offset = p_offset;
    m_length = p_length;
    f_file = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::data_obj_t::_read() {
}

bnk_t::data_obj_t::~data_obj_t() {
    _clean_up();
}

void bnk_t::data_obj_t::_clean_up() {
    if (f_file) {
    }
}

std::string bnk_t::data_obj_t::file() {
    if (f_file)
        return m_file;
    std::streampos _pos = m__io->pos();
    m__io->seek(offset());
    m_file = m__io->read_bytes(length());
    m__io->seek(_pos);
    f_file = true;
    return m_file;
}

bnk_t::data_data_t::data_data_t(uint32_t p_length, kaitai::kstream* p__io, bnk_t::section_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_length = p_length;
    m_data_obj_section = 0;
    m__io__raw_data_obj_section = 0;
    f_didx_data = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::data_data_t::_read() {
    m__raw_data_obj_section = m__io->read_bytes(length());
    m__io__raw_data_obj_section = new kaitai::kstream(m__raw_data_obj_section);
    m_data_obj_section = new data_obj_section_t(length(), m__io__raw_data_obj_section, this, m__root);
}

bnk_t::data_data_t::~data_data_t() {
    _clean_up();
}

void bnk_t::data_data_t::_clean_up() {
    if (m__io__raw_data_obj_section) {
        delete m__io__raw_data_obj_section; m__io__raw_data_obj_section = 0;
    }
    if (m_data_obj_section) {
        delete m_data_obj_section; m_data_obj_section = 0;
    }
}

bnk_t::didx_data_t* bnk_t::data_data_t::didx_data() {
    if (f_didx_data)
        return m_didx_data;
    m_didx_data = static_cast<bnk_t::didx_data_t*>(_parent()->_parent()->data()->at(1)->section_data());
    f_didx_data = true;
    return m_didx_data;
}

bnk_t::data_obj_section_t::data_obj_section_t(uint32_t p_length, kaitai::kstream* p__io, bnk_t::data_data_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_length = p_length;
    m_data = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::data_obj_section_t::_read() {
    m_data = new std::vector<data_obj_t*>();
    const int l_data = _parent()->didx_data()->num_files();
    for (int i = 0; i < l_data; i++) {
        m_data->push_back(new data_obj_t(_parent()->didx_data()->objs()->at(i)->offset(), _parent()->didx_data()->objs()->at(i)->length(), m__io, this, m__root));
    }
}

bnk_t::data_obj_section_t::~data_obj_section_t() {
    _clean_up();
}

void bnk_t::data_obj_section_t::_clean_up() {
    if (m_data) {
        for (std::vector<data_obj_t*>::iterator it = m_data->begin(); it != m_data->end(); ++it) {
            delete *it;
        }
        delete m_data; m_data = 0;
    }
}

bnk_t::didx_obj_t::didx_obj_t(kaitai::kstream* p__io, bnk_t::didx_data_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::didx_obj_t::_read() {
    m_id = m__io->read_u4le();
    m_offset = m__io->read_u4le();
    m_length = m__io->read_u4le();
}

bnk_t::didx_obj_t::~didx_obj_t() {
    _clean_up();
}

void bnk_t::didx_obj_t::_clean_up() {
}

bnk_t::hirc_data_t::hirc_data_t(uint32_t p_length, kaitai::kstream* p__io, bnk_t::section_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_length = p_length;
    m_objs = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::hirc_data_t::_read() {
    m_num_objects = m__io->read_u4le();
    m_objs = new std::vector<hirc_obj_t*>();
    const int l_objs = num_objects();
    for (int i = 0; i < l_objs; i++) {
        m_objs->push_back(new hirc_obj_t(m__io, this, m__root));
    }
}

bnk_t::hirc_data_t::~hirc_data_t() {
    _clean_up();
}

void bnk_t::hirc_data_t::_clean_up() {
    if (m_objs) {
        for (std::vector<hirc_obj_t*>::iterator it = m_objs->begin(); it != m_objs->end(); ++it) {
            delete *it;
        }
        delete m_objs; m_objs = 0;
    }
}

bnk_t::bkhd_data_t::bkhd_data_t(uint32_t p_length, kaitai::kstream* p__io, bnk_t::section_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_length = p_length;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::bkhd_data_t::_read() {
    m_version = m__io->read_u4le();
    m_id = m__io->read_u4le();
    m_random = m__io->read_bytes((length() - 8));
}

bnk_t::bkhd_data_t::~bkhd_data_t() {
    _clean_up();
}

void bnk_t::bkhd_data_t::_clean_up() {
}

bnk_t::event_t::event_t(kaitai::kstream* p__io, bnk_t::hirc_obj_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_event_action_count_new = 0;
    m_event_actions = 0;
    f_version = false;
    f_event_action_count_value = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::event_t::_read() {
    n_event_action_count_new = true;
    if (version() >= 123) {
        n_event_action_count_new = false;
        m_event_action_count_new = new vlq_t(m__io);
    }
    n_event_action_count_old = true;
    if (version() < 123) {
        n_event_action_count_old = false;
        m_event_action_count_old = m__io->read_u4le();
    }
    m_event_actions = new std::vector<uint32_t>();
    const int l_event_actions = event_action_count_value();
    for (int i = 0; i < l_event_actions; i++) {
        m_event_actions->push_back(m__io->read_u4le());
    }
}

bnk_t::event_t::~event_t() {
    _clean_up();
}

void bnk_t::event_t::_clean_up() {
    if (!n_event_action_count_new) {
        if (m_event_action_count_new) {
            delete m_event_action_count_new; m_event_action_count_new = 0;
        }
    }
    if (!n_event_action_count_old) {
    }
    if (m_event_actions) {
        delete m_event_actions; m_event_actions = 0;
    }
}

uint32_t bnk_t::event_t::version() {
    if (f_version)
        return m_version;
    m_version = static_cast<bnk_t::bkhd_data_t*>(_root()->data()->at(0)->section_data())->version();
    f_version = true;
    return m_version;
}

int32_t bnk_t::event_t::event_action_count_value() {
    if (f_event_action_count_value)
        return m_event_action_count_value;
    m_event_action_count_value = ((version() >= 123) ? (static_cast<vlq_t*>(event_action_count_new())->value()) : (static_cast<uint32_t>(event_action_count_old())));
    f_event_action_count_value = true;
    return m_event_action_count_value;
}

bnk_t::ss_state_group_t::ss_state_group_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_state_obj = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::ss_state_group_t::_read() {
    m_id = m__io->read_u4le();
    m_change_occurs_at = m__io->read_s1();
    m_settings_vary_from_default = m__io->read_u2le();
    m_state_obj = new std::vector<ss_state_obj_t*>();
    const int l_state_obj = settings_vary_from_default();
    for (int i = 0; i < l_state_obj; i++) {
        m_state_obj->push_back(new ss_state_obj_t(m__io, this, m__root));
    }
}

bnk_t::ss_state_group_t::~ss_state_group_t() {
    _clean_up();
}

void bnk_t::ss_state_group_t::_clean_up() {
    if (m_state_obj) {
        for (std::vector<ss_state_obj_t*>::iterator it = m_state_obj->begin(); it != m_state_obj->end(); ++it) {
            delete *it;
        }
        delete m_state_obj; m_state_obj = 0;
    }
}

bnk_t::sound_structure_t::sound_structure_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_effect = 0;
    m_parameter_type = 0;
    m_parameter_value = 0;
    m_pos_inc_2d = 0;
    m_pos_inc_3d = 0;
    m_aux_busses = 0;
    m_state_group = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::sound_structure_t::_read() {
    m_override_parent_settings_for_effects = m__io->read_bits_int_be(1);
    m__io->align_to_byte();
    m_effects_count = m__io->read_s1();
    n_bypassed_effects = true;
    if (effects_count() > 0) {
        n_bypassed_effects = false;
        m_bypassed_effects = m__io->read_bytes(1);
    }
    n_effect = true;
    if (effects_count() > 0) {
        n_effect = false;
        m_effect = new std::vector<ss_effect_t*>();
        const int l_effect = effects_count();
        for (int i = 0; i < l_effect; i++) {
            m_effect->push_back(new ss_effect_t(m__io, this, m__root));
        }
    }
    m_output_bus_id = m__io->read_u4le();
    m_parent_id = m__io->read_u4le();
    m_override_parent_settings_playback_priority = m__io->read_bits_int_be(1);
    m_offset_priority_enabled = m__io->read_bits_int_be(1);
    m__io->align_to_byte();
    m_additional_parameter_count = m__io->read_s1();
    m_parameter_type = new std::vector<int8_t>();
    const int l_parameter_type = additional_parameter_count();
    for (int i = 0; i < l_parameter_type; i++) {
        m_parameter_type->push_back(m__io->read_s1());
    }
    m_parameter_value = new std::vector<double>();
    const int l_parameter_value = additional_parameter_count();
    for (int i = 0; i < l_parameter_value; i++) {
        switch (parameter_type()->at(i)) {
        case 7: {
            m_parameter_value->push_back(m__io->read_u4le());
            break;
        }
        default: {
            m_parameter_value->push_back(m__io->read_f4le());
            break;
        }
        }
    }
    m_blank1 = m__io->read_bytes(1);
    m_positioning_section_included = m__io->read_bits_int_be(1);
    m__io->align_to_byte();
    n_positioning_dimension = true;
    if (positioning_section_included()) {
        n_positioning_dimension = false;
        m_positioning_dimension = m__io->read_s1();
    }
    n_pos_inc_2d = true;
    if ( ((positioning_section_included()) && (positioning_dimension() == 0)) ) {
        n_pos_inc_2d = false;
        m_pos_inc_2d = new ss_pos_inc_2d_t(m__io, this, m__root);
    }
    n_pos_inc_3d = true;
    if ( ((positioning_section_included()) && (positioning_dimension() == 0)) ) {
        n_pos_inc_3d = false;
        m_pos_inc_3d = new ss_pos_inc_3d_t(m__io, this, m__root);
    }
    m_override_parent_game_aux_settings = m__io->read_bits_int_be(1);
    m_use_game_aux_sends = m__io->read_bits_int_be(1);
    m_user_aux_sends_exist = m__io->read_bits_int_be(1);
    m__io->align_to_byte();
    n_aux_busses = true;
    if (user_aux_sends_exist()) {
        n_aux_busses = false;
        m_aux_busses = new std::vector<uint32_t>();
        const int l_aux_busses = 4;
        for (int i = 0; i < l_aux_busses; i++) {
            m_aux_busses->push_back(m__io->read_u4le());
        }
    }
    m_unk_limit_param_playback = m__io->read_bits_int_be(1);
    m__io->align_to_byte();
    n_when_priority_is_equal = true;
    if (unk_limit_param_playback()) {
        n_when_priority_is_equal = false;
        m_when_priority_is_equal = m__io->read_s1();
    }
    n_when_limit_is_reached = true;
    if (unk_limit_param_playback()) {
        n_when_limit_is_reached = false;
        m_when_limit_is_reached = m__io->read_s1();
    }
    n_sound_instance_limit = true;
    if (unk_limit_param_playback()) {
        n_sound_instance_limit = false;
        m_sound_instance_limit = m__io->read_u2le();
    }
    m_sound_instance_limiting_behavior = m__io->read_s1();
    m_virt_voice_behavior = m__io->read_s1();
    m_parent_playback_settings_override = m__io->read_bits_int_be(1);
    m_parent_virt_voice_settings_override = m__io->read_bits_int_be(1);
    m__io->align_to_byte();
    m_state_group_count = m__io->read_u4le();
    m_state_group = new std::vector<ss_state_group_t*>();
    const int l_state_group = state_group_count();
    for (int i = 0; i < l_state_group; i++) {
        m_state_group->push_back(new ss_state_group_t(m__io, this, m__root));
    }
    m_rtpc_count = m__io->read_u2le();
}

bnk_t::sound_structure_t::~sound_structure_t() {
    _clean_up();
}

void bnk_t::sound_structure_t::_clean_up() {
    if (!n_bypassed_effects) {
    }
    if (!n_effect) {
        if (m_effect) {
            for (std::vector<ss_effect_t*>::iterator it = m_effect->begin(); it != m_effect->end(); ++it) {
                delete *it;
            }
            delete m_effect; m_effect = 0;
        }
    }
    if (m_parameter_type) {
        delete m_parameter_type; m_parameter_type = 0;
    }
    if (m_parameter_value) {
        delete m_parameter_value; m_parameter_value = 0;
    }
    if (!n_positioning_dimension) {
    }
    if (!n_pos_inc_2d) {
        if (m_pos_inc_2d) {
            delete m_pos_inc_2d; m_pos_inc_2d = 0;
        }
    }
    if (!n_pos_inc_3d) {
        if (m_pos_inc_3d) {
            delete m_pos_inc_3d; m_pos_inc_3d = 0;
        }
    }
    if (!n_aux_busses) {
        if (m_aux_busses) {
            delete m_aux_busses; m_aux_busses = 0;
        }
    }
    if (!n_when_priority_is_equal) {
    }
    if (!n_when_limit_is_reached) {
    }
    if (!n_sound_instance_limit) {
    }
    if (m_state_group) {
        for (std::vector<ss_state_group_t*>::iterator it = m_state_group->begin(); it != m_state_group->end(); ++it) {
            delete *it;
        }
        delete m_state_group; m_state_group = 0;
    }
}

bnk_t::stid_obj_t::stid_obj_t(kaitai::kstream* p__io, bnk_t::stid_data_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::stid_obj_t::_read() {
    m_id = m__io->read_u4le();
    m_name_len = m__io->read_u1();
    m_name = kaitai::kstream::bytes_to_str(m__io->read_bytes(name_len()), "UTF-8");
}

bnk_t::stid_obj_t::~stid_obj_t() {
    _clean_up();
}

void bnk_t::stid_obj_t::_clean_up() {
}

bnk_t::didx_data_t::didx_data_t(uint32_t p_length, kaitai::kstream* p__io, bnk_t::section_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_length = p_length;
    m_objs = 0;
    f_num_files = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::didx_data_t::_read() {
    m_objs = new std::vector<didx_obj_t*>();
    const int l_objs = num_files();
    for (int i = 0; i < l_objs; i++) {
        m_objs->push_back(new didx_obj_t(m__io, this, m__root));
    }
}

bnk_t::didx_data_t::~didx_data_t() {
    _clean_up();
}

void bnk_t::didx_data_t::_clean_up() {
    if (m_objs) {
        for (std::vector<didx_obj_t*>::iterator it = m_objs->begin(); it != m_objs->end(); ++it) {
            delete *it;
        }
        delete m_objs; m_objs = 0;
    }
}

int32_t bnk_t::didx_data_t::num_files() {
    if (f_num_files)
        return m_num_files;
    m_num_files = (length() / 12);
    f_num_files = true;
    return m_num_files;
}

bnk_t::ss_rtpc_t::ss_rtpc_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_point = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::ss_rtpc_t::_read() {
    m_game_param_x_axis_id = m__io->read_u4le();
    m_y_axis_type = m__io->read_u4le();
    m_unk_id_1 = m__io->read_u4le();
    m_unk_1 = m__io->read_bytes(1);
    m_num_points = m__io->read_s1();
    m_unk_2 = m__io->read_bytes(1);
    m_point = new std::vector<ss_rtpc_point_t*>();
    const int l_point = num_points();
    for (int i = 0; i < l_point; i++) {
        m_point->push_back(new ss_rtpc_point_t(m__io, this, m__root));
    }
}

bnk_t::ss_rtpc_t::~ss_rtpc_t() {
    _clean_up();
}

void bnk_t::ss_rtpc_t::_clean_up() {
    if (m_point) {
        for (std::vector<ss_rtpc_point_t*>::iterator it = m_point->begin(); it != m_point->end(); ++it) {
            delete *it;
        }
        delete m_point; m_point = 0;
    }
}

bnk_t::sound_effect_or_voice_t::sound_effect_or_voice_t(kaitai::kstream* p__io, bnk_t::hirc_obj_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_wem_data = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::sound_effect_or_voice_t::_read() {
    m_unknown = m__io->read_bytes(4);
    m_included_or_streamed = m__io->read_u4le();
    m_audio_file_id = m__io->read_u4le();
    m_source_id = m__io->read_u4le();
    n_wem_offset = true;
    if (included_or_streamed() == 0) {
        n_wem_offset = false;
        m_wem_offset = m__io->read_u4le();
    }
    n_wem_length = true;
    if (included_or_streamed() == 0) {
        n_wem_length = false;
        m_wem_length = m__io->read_u4le();
    }
    m_sound_object_type = m__io->read_s1();
    m_sound_structure = m__io->read_bytes((((static_cast<bnk_t::hirc_obj_t*>(_parent())->length() - (4 * 5)) - (1 * 1)) - (8 * ((included_or_streamed() == 0) ? (1) : (0)))));
}

bnk_t::sound_effect_or_voice_t::~sound_effect_or_voice_t() {
    _clean_up();
}

void bnk_t::sound_effect_or_voice_t::_clean_up() {
    if (!n_wem_offset) {
    }
    if (!n_wem_length) {
    }
    if (f_wem_data && !n_wem_data) {
    }
}

std::string bnk_t::sound_effect_or_voice_t::wem_data() {
    if (f_wem_data)
        return m_wem_data;
    n_wem_data = true;
    if (included_or_streamed() == 0) {
        n_wem_data = false;
        std::streampos _pos = m__io->pos();
        m__io->seek(wem_offset());
        m_wem_data = m__io->read_bytes(wem_length());
        m__io->seek(_pos);
        f_wem_data = true;
    }
    return m_wem_data;
}

bnk_t::hirc_obj_t::hirc_obj_t(kaitai::kstream* p__io, bnk_t::hirc_data_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::hirc_obj_t::_read() {
    m_type = static_cast<bnk_t::object_type_t>(m__io->read_s1());
    m_length = m__io->read_u4le();
    m_id = m__io->read_u4le();
    switch (type()) {
    case bnk_t::OBJECT_TYPE_SOUND_EFFECT_OR_VOICE: {
        m_object_data = new sound_effect_or_voice_t(m__io, this, m__root);
        break;
    }
    case bnk_t::OBJECT_TYPE_EVENT_ACTION: {
        m_object_data = new event_action_t(m__io, this, m__root);
        break;
    }
    case bnk_t::OBJECT_TYPE_EVENT: {
        m_object_data = new event_t(m__io, this, m__root);
        break;
    }
    case bnk_t::OBJECT_TYPE_SETTINGS: {
        m_object_data = new settings_t(m__io, this, m__root);
        break;
    }
    default: {
        m_object_data = new random_bytes_t((length() - 4), m__io, this, m__root);
        break;
    }
    }
}

bnk_t::hirc_obj_t::~hirc_obj_t() {
    _clean_up();
}

void bnk_t::hirc_obj_t::_clean_up() {
    if (m_object_data) {
        delete m_object_data; m_object_data = 0;
    }
}

bnk_t::section_t::section_t(kaitai::kstream* p__io, bnk_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::section_t::_read() {
    m_type = kaitai::kstream::bytes_to_str(m__io->read_bytes(4), "UTF-8");
    m_length = m__io->read_u4le();
    {
        std::string on = type();
        if (on == std::string("HIRC")) {
            m_section_data = new hirc_data_t(length(), m__io, this, m__root);
        }
        else if (on == std::string("DATA")) {
            m_section_data = new data_data_t(length(), m__io, this, m__root);
        }
        else if (on == std::string("STID")) {
            m_section_data = new stid_data_t(m__io, this, m__root);
        }
        else if (on == std::string("DIDX")) {
            m_section_data = new didx_data_t(length(), m__io, this, m__root);
        }
        else if (on == std::string("BKHD")) {
            m_section_data = new bkhd_data_t(length(), m__io, this, m__root);
        }
        else {
            m_section_data = new rand_t(length(), m__io, this, m__root);
        }
    }
}

bnk_t::section_t::~section_t() {
    _clean_up();
}

void bnk_t::section_t::_clean_up() {
    if (m_section_data) {
        delete m_section_data; m_section_data = 0;
    }
}

bnk_t::audio_bus_t::audio_bus_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_parameter_type = 0;
    m_parameter_value = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::audio_bus_t::_read() {
    m_parent_audio_bus_id = m__io->read_u4le();
    m_additional_parameter_count = m__io->read_s1();
    m_parameter_type = new std::vector<audio_bus_parameter_type_t>();
    const int l_parameter_type = additional_parameter_count();
    for (int i = 0; i < l_parameter_type; i++) {
        m_parameter_type->push_back(static_cast<bnk_t::audio_bus_parameter_type_t>(m__io->read_s1()));
    }
    m_parameter_value = new std::vector<float>();
    const int l_parameter_value = additional_parameter_count();
    for (int i = 0; i < l_parameter_value; i++) {
        m_parameter_value->push_back(m__io->read_f4le());
    }
    m_action_when_priority_equal = m__io->read_s1();
    m_action_when_limit_reached = m__io->read_s1();
    m_sound_instances_limit = m__io->read_u2le();
    m_override_parent_playback_limit = m__io->read_bits_int_be(1);
    m__io->align_to_byte();
    m_unknown = m__io->read_bytes(4);
    m_auto_ducking_recover_time = m__io->read_u4le();
    m_auto_ducking_max_volume = m__io->read_f4le();
    m_auto_ducking_num_busses = m__io->read_u4le();
}

bnk_t::audio_bus_t::~audio_bus_t() {
    _clean_up();
}

void bnk_t::audio_bus_t::_clean_up() {
    if (m_parameter_type) {
        delete m_parameter_type; m_parameter_type = 0;
    }
    if (m_parameter_value) {
        delete m_parameter_value; m_parameter_value = 0;
    }
}

bnk_t::stid_data_t::stid_data_t(kaitai::kstream* p__io, bnk_t::section_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_objs = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::stid_data_t::_read() {
    m_unk1 = m__io->read_bytes(4);
    if (!(unk1() == std::string("\x01\x00\x00\x00", 4))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x01\x00\x00\x00", 4), unk1(), _io(), std::string("/types/stid_data/seq/0"));
    }
    m_num_soundbanks = m__io->read_u4le();
    m_objs = new std::vector<stid_obj_t*>();
    const int l_objs = num_soundbanks();
    for (int i = 0; i < l_objs; i++) {
        m_objs->push_back(new stid_obj_t(m__io, this, m__root));
    }
}

bnk_t::stid_data_t::~stid_data_t() {
    _clean_up();
}

void bnk_t::stid_data_t::_clean_up() {
    if (m_objs) {
        for (std::vector<stid_obj_t*>::iterator it = m_objs->begin(); it != m_objs->end(); ++it) {
            delete *it;
        }
        delete m_objs; m_objs = 0;
    }
}

bnk_t::ss_effect_t::ss_effect_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::ss_effect_t::_read() {
    m_index = m__io->read_s1();
    m_id = m__io->read_u4le();
    m_blank = m__io->read_bytes(2);
}

bnk_t::ss_effect_t::~ss_effect_t() {
    _clean_up();
}

void bnk_t::ss_effect_t::_clean_up() {
}

bnk_t::rand_t::rand_t(uint32_t p_length, kaitai::kstream* p__io, bnk_t::section_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_length = p_length;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::rand_t::_read() {
    m_data = m__io->read_bytes(length());
}

bnk_t::rand_t::~rand_t() {
    _clean_up();
}

void bnk_t::rand_t::_clean_up() {
}

bnk_t::music_segment_t::music_segment_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_sound_structure = 0;
    m_child_obj = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::music_segment_t::_read() {
    m_sound_structure = new sound_structure_t(m__io, this, m__root);
    m_child_obj_count = m__io->read_u4le();
    m_child_obj = new std::vector<uint32_t>();
    const int l_child_obj = child_obj_count();
    for (int i = 0; i < l_child_obj; i++) {
        m_child_obj->push_back(m__io->read_u4le());
    }
    m_unk = m__io->read_bytes(100);
}

bnk_t::music_segment_t::~music_segment_t() {
    _clean_up();
}

void bnk_t::music_segment_t::_clean_up() {
    if (m_sound_structure) {
        delete m_sound_structure; m_sound_structure = 0;
    }
    if (m_child_obj) {
        delete m_child_obj; m_child_obj = 0;
    }
}

bnk_t::ss_pos_inc_3d_t::ss_pos_inc_3d_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::ss_pos_inc_3d_t::_read() {
    m_source_type = m__io->read_u4le();
    m_attenuation_id = m__io->read_u4le();
    m_spatialization_enabled = m__io->read_bits_int_be(1);
    m__io->align_to_byte();
    n_play_type = true;
    if (source_type() == 2) {
        n_play_type = false;
        m_play_type = static_cast<bnk_t::play_type_t>(m__io->read_u4le());
    }
    n_looping_enabled = true;
    if (source_type() == 2) {
        n_looping_enabled = false;
        m_looping_enabled = m__io->read_bits_int_be(1);
    }
    m__io->align_to_byte();
    n_trainsition_time = true;
    if (source_type() == 2) {
        n_trainsition_time = false;
        m_trainsition_time = m__io->read_u4le();
    }
    n_follow_listener_orientation = true;
    if (source_type() == 2) {
        n_follow_listener_orientation = false;
        m_follow_listener_orientation = m__io->read_bits_int_be(1);
    }
    n_update_at_each_frame = true;
    if (source_type() == 3) {
        n_update_at_each_frame = false;
        m_update_at_each_frame = m__io->read_bits_int_be(1);
    }
}

bnk_t::ss_pos_inc_3d_t::~ss_pos_inc_3d_t() {
    _clean_up();
}

void bnk_t::ss_pos_inc_3d_t::_clean_up() {
    if (!n_play_type) {
    }
    if (!n_looping_enabled) {
    }
    if (!n_trainsition_time) {
    }
    if (!n_follow_listener_orientation) {
    }
    if (!n_update_at_each_frame) {
    }
}

bnk_t::event_action_t::event_action_t(kaitai::kstream* p__io, bnk_t::hirc_obj_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_parameter_type = 0;
    m_parameter_value = 0;
    m_extra = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::event_action_t::_read() {
    m_scope = static_cast<bnk_t::action_scope_t>(m__io->read_s1());
    m_type = static_cast<bnk_t::action_type_t>(m__io->read_s1());
    m_game_object_id = m__io->read_u4le();
    m_blank1 = m__io->read_bytes(1);
    if (!(blank1() == std::string("\x00", 1))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x00", 1), blank1(), _io(), std::string("/types/event_action/seq/3"));
    }
    m_parameter_count = m__io->read_s1();
    m_parameter_type = new std::vector<std::string>();
    const int l_parameter_type = parameter_count();
    for (int i = 0; i < l_parameter_type; i++) {
        m_parameter_type->push_back(m__io->read_bytes(1));
    }
    m_parameter_value = new std::vector<double>();
    const int l_parameter_value = parameter_count();
    for (int i = 0; i < l_parameter_value; i++) {
        {
            std::string on = parameter_type()->at(i);
            if (on == std::string("\x0E", 1)) {
                m_parameter_value->push_back(m__io->read_u4le());
            }
            else if (on == std::string("\x0F", 1)) {
                m_parameter_value->push_back(m__io->read_u4le());
            }
            else if (on == std::string("\x10", 1)) {
                m_parameter_value->push_back(m__io->read_f4le());
            }
        }
    }
    m_blank2 = m__io->read_bytes(1);
    if (!(blank2() == std::string("\x00", 1))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x00", 1), blank2(), _io(), std::string("/types/event_action/seq/7"));
    }
    n_state_group_id = true;
    if (type() == bnk_t::ACTION_TYPE_SET_STATE) {
        n_state_group_id = false;
        m_state_group_id = m__io->read_u4le();
    }
    n_state_id = true;
    if (type() == bnk_t::ACTION_TYPE_SET_STATE) {
        n_state_id = false;
        m_state_id = m__io->read_u4le();
    }
    n_switch_group_id = true;
    if (type() == bnk_t::ACTION_TYPE_SET_SWITCH) {
        n_switch_group_id = false;
        m_switch_group_id = m__io->read_u4le();
    }
    n_switch_id = true;
    if (type() == bnk_t::ACTION_TYPE_SET_SWITCH) {
        n_switch_id = false;
        m_switch_id = m__io->read_u4le();
    }
    m_extra = new random_bytes_t((((((((((((_parent()->length() - 4) - 1) - 1) - 4) - 1) - 1) - (1 * parameter_count())) - (4 * parameter_count())) - 1) - (8 * ((type() == bnk_t::ACTION_TYPE_SET_STATE) ? (1) : (0)))) - (8 * ((type() == bnk_t::ACTION_TYPE_SET_SWITCH) ? (1) : (0)))), m__io, this, m__root);
}

bnk_t::event_action_t::~event_action_t() {
    _clean_up();
}

void bnk_t::event_action_t::_clean_up() {
    if (m_parameter_type) {
        delete m_parameter_type; m_parameter_type = 0;
    }
    if (m_parameter_value) {
        delete m_parameter_value; m_parameter_value = 0;
    }
    if (!n_state_group_id) {
    }
    if (!n_state_id) {
    }
    if (!n_switch_group_id) {
    }
    if (!n_switch_id) {
    }
    if (m_extra) {
        delete m_extra; m_extra = 0;
    }
}

bnk_t::random_bytes_t::random_bytes_t(uint32_t p_size, kaitai::kstream* p__io, kaitai::kstruct* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
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

void bnk_t::random_bytes_t::_read() {
    m_data = m__io->read_bytes(size());
}

bnk_t::random_bytes_t::~random_bytes_t() {
    _clean_up();
}

void bnk_t::random_bytes_t::_clean_up() {
}

bnk_t::ss_pos_inc_2d_t::ss_pos_inc_2d_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::ss_pos_inc_2d_t::_read() {
    m_panner_enabled = m__io->read_bits_int_be(1);
}

bnk_t::ss_pos_inc_2d_t::~ss_pos_inc_2d_t() {
    _clean_up();
}

void bnk_t::ss_pos_inc_2d_t::_clean_up() {
}

bnk_t::ss_rtpc_point_t::ss_rtpc_point_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::ss_rtpc_point_t::_read() {
    m_x_coord = m__io->read_f4le();
    m_y_coord = m__io->read_f4le();
    m_curve_shape = m__io->read_u4le();
}

bnk_t::ss_rtpc_point_t::~ss_rtpc_point_t() {
    _clean_up();
}

void bnk_t::ss_rtpc_point_t::_clean_up() {
}

bnk_t::settings_t::settings_t(kaitai::kstream* p__io, bnk_t::hirc_obj_t* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_setting_type = 0;
    m_setting_val = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::settings_t::_read() {
    m_settings_count = m__io->read_s1();
    m_setting_type = new std::vector<std::string>();
    const int l_setting_type = settings_count();
    for (int i = 0; i < l_setting_type; i++) {
        m_setting_type->push_back(m__io->read_bytes(1));
    }
    m_setting_val = new std::vector<float>();
    const int l_setting_val = settings_count();
    for (int i = 0; i < l_setting_val; i++) {
        m_setting_val->push_back(m__io->read_f4le());
    }
}

bnk_t::settings_t::~settings_t() {
    _clean_up();
}

void bnk_t::settings_t::_clean_up() {
    if (m_setting_type) {
        delete m_setting_type; m_setting_type = 0;
    }
    if (m_setting_val) {
        delete m_setting_val; m_setting_val = 0;
    }
}

bnk_t::ss_state_obj_t::ss_state_obj_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, bnk_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void bnk_t::ss_state_obj_t::_read() {
    m_id = m__io->read_u4le();
    m_settings_obj_id = m__io->read_u4le();
}

bnk_t::ss_state_obj_t::~ss_state_obj_t() {
    _clean_up();
}

void bnk_t::ss_state_obj_t::_clean_up() {
}
