meta:
  id: bnk
  file-extension: bnk
  endian: le

seq:
  - id: data
    type: section
    repeat: eos

# BNK
types:
  section:
    seq:
      - id: type
        type: str
        size: 4
        encoding: utf-8
      - id: length
        type: u4
      - id: section_data
        type:
          switch-on: type
          cases:
            '"BKHD"': bkhd_data(length)
            '"DIDX"': didx_data(length)
            '"HIRC"': hirc_data(length)
            '"STID"': stid_data
            '"DATA"': data_data(length)
            _: rand(length)

  rand:
    params:
      - id: length
        type: u4
    seq:
      - id: data
        size: length

# BKHD BEGIN
  bkhd_data:
    params:
      - id: length
        type: u4
    seq:
      - id: version
        type: u4
      - id: id
        type: u4
      - id: blank1
        contents: [00, 00, 00, 00]
      - id: blank2
        contents: [00, 00, 00, 00]
      - id: random
        size: length - 16
# BKHD END

# DIDX BEGIN
  didx_data:
    params:
      - id: length
        type: u4
    seq:
      - id: objs
        type: didx_obj
        repeat: expr
        repeat-expr: num_files
    instances:
      num_files:
        value: length / 12
  didx_obj:
    seq:
      - id: id
        type: u4
      - id: offset
        type: u4
      - id: length
        type: u4
    instances:
      embedded_file_data:
        pos: offset
        size: length
# DIDX END

# DATA BEGIN
  data_data:
    params:
      - id: length
        type: u4
    seq:
      - id: data_obj_section
        type: data_obj_section(length)
        size: length
    instances:
      didx_data:
        value: _parent._parent.data[1].section_data.as<didx_data>
  data_obj_section:
    params:
      - id: length
        type: u4
    seq:
      - id: data
        type: data_obj(_parent.didx_data.objs[_index].offset, _parent.didx_data.objs[_index].length)
        repeat: expr
        repeat-expr: _parent.didx_data.num_files
  data_obj:
    params:
      - id: offset
        type: u4
      - id: length
        type: u4
    instances:
      file:
        pos: offset
        size: length
# DATA END

# STID BEGIN
  stid_data:
    seq:
      - id: unk1
        contents: [01, 00, 00, 00]
      - id: num_soundbanks
        type: u4
      - id: objs
        type: stid_obj
        repeat: expr
        repeat-expr: num_soundbanks
  stid_obj:
    seq:
      - id: id
        type: u4
      - id: name_len
        type: u1
      - id: name
        type: str
        size: name_len
        encoding: utf-8
# STID END
        
# HIRC BEGIN
  hirc_data:
    params:
      - id: length
        type: u4
    seq:
      - id: num_objects
        type: u4
      - id: objs
        type: hirc_obj
        repeat: expr
        repeat-expr: num_objects
  hirc_obj:
    seq:
      - id: type
        type: s1
        enum: object_type
      - id: length
        type: u4
      - id: id
        type: u4
      #- id: additional_bytes
      #  size: length - (1 * 4)
      - id: object_data
        type:
          switch-on: type
          cases:
            object_type::settings: settings
            object_type::sound_effect_or_voice: sound_effect_or_voice
            #object_type::music_segment: music_segment
            object_type::event_action: event_action
            object_type::event: event
            _: random_bytes(length - 4)

  settings:
    seq:
      - id: settings_count
        type: s1
      - id: setting_type
        size: 1
        repeat: expr
        repeat-expr: settings_count
      - id: setting_val
        type: f4
        repeat: expr
        repeat-expr: settings_count
  sound_effect_or_voice:
    seq:
      - id: unknown
        size: 4
      - id: included_or_streamed
        type: u4
      - id: audio_file_id
        type: u4
      - id: source_id
        type: u4
      - id: wem_offset
        type: u4
        if: included_or_streamed == 0
      - id: wem_length
        type: u4
        if: included_or_streamed == 0
      - id: sound_object_type
        type: s1
      - id: sound_structure
        size: _parent.as<hirc_obj>.length - (4 * 5) - (1 * 1) - (8 * (included_or_streamed == 0 ? 1 : 0))
        #type: sound_structure
    instances:
      wem_data:
        pos: wem_offset
        size: wem_length
        if: included_or_streamed == 0
  event_action:
    seq:
      - id: scope
        type: s1
        enum: action_scope
      - id: type
        type: s1
        enum: action_type
      - id: game_object_id
        type: u4
      - id: blank1
        contents: [00]
      - id: parameter_count
        type: s1
      - id: parameter_type
        size: 1
        repeat: expr
        repeat-expr: parameter_count
      - id: parameter_value
        type:
          switch-on: parameter_type[_index]
          cases:
            '[0x0e]': u4
            '[0x0f]': u4
            '[0x10]': f4
        repeat: expr
        repeat-expr: parameter_count
      - id: blank2
        contents: [00]
      - id: state_group_id
        type: u4
        if: type == action_type::set_state
      - id: state_id
        type: u4
        if: type == action_type::set_state
      - id: switch_group_id
        type: u4
        if: type == action_type::set_switch
      - id: switch_id
        type: u4
        if: type == action_type::set_switch
      - id: extra
        type: random_bytes(_parent.length - 4 - 1 - 1 - 4 - 1 - 1 - (1 * parameter_count) - (4 * parameter_count) - 1 - (8 * (type == action_type::set_state ? 1 : 0)) - (8 * (type == action_type::set_switch ? 1 : 0)))
  event:
    seq:
      - id: event_action_count
        type: u4
      - id: event_actions
        type: u4
        repeat: expr
        repeat-expr: event_action_count
  audio_bus:
    seq:
      - id: parent_audio_bus_id
        type: u4
      - id: additional_parameter_count
        type: s1
      - id: parameter_type
        type: s1
        enum: audio_bus_parameter_type
        repeat: expr
        repeat-expr: additional_parameter_count
      - id: parameter_value
        type: f4
        repeat: expr
        repeat-expr: additional_parameter_count
      - id: action_when_priority_equal
        type: s1
      - id: action_when_limit_reached
        type: s1
      - id: sound_instances_limit
        type: u2
      - id: override_parent_playback_limit
        type: b1
      - id: unknown
        size: 4
        #contents: [0x3f, 0x00, 0x00, 0x00]
      - id: auto_ducking_recover_time
        type: u4
      - id: auto_ducking_max_volume
        type: f4
      - id: auto_ducking_num_busses
        type: u4
      # incomplete!
  music_segment:
    seq:
      - id: sound_structure
        type: sound_structure
      - id: child_obj_count
        type: u4
      - id: child_obj
        type: u4
        repeat: expr
        repeat-expr: child_obj_count
      - id: unk
        size: 100
      
  sound_structure:
    seq:
      - id: override_parent_settings_for_effects
        type: b1
      - id: effects_count
        type: s1
      - id: bypassed_effects
        size: 1
        if: effects_count > 0
      - id: effect
        type: ss_effect
        repeat: expr
        repeat-expr: effects_count
        if: effects_count > 0
      - id: output_bus_id
        type: u4
      - id: parent_id
        type: u4
      - id: override_parent_settings_playback_priority
        type: b1
      - id: offset_priority_enabled
        type: b1
      - id: additional_parameter_count
        type: s1
      - id: parameter_type
        type: s1
        repeat: expr
        repeat-expr: additional_parameter_count
      - id: parameter_value
        type:
          switch-on: parameter_type[_index]
          cases:
            7: u4
            _: f4
        repeat: expr
        repeat-expr: additional_parameter_count
      - id: blank1
        #contents: [00]
        size: 1
      - id: positioning_section_included
        type: b1
      - id: positioning_dimension
        type: s1
        if: positioning_section_included
      - id: pos_inc_2d
        type: ss_pos_inc_2d
        if: positioning_section_included and positioning_dimension == 0
      - id: pos_inc_3d
        type: ss_pos_inc_3d
        if: positioning_section_included and positioning_dimension == 0
      - id: override_parent_game_aux_settings
        type: b1
      - id: use_game_aux_sends
        type: b1
      - id: user_aux_sends_exist
        type: b1
      - id: aux_busses
        type: u4
        repeat: expr
        repeat-expr: 4
        if: user_aux_sends_exist
      - id: unk_limit_param_playback
        type: b1
      - id: when_priority_is_equal
        type: s1
        if: unk_limit_param_playback
      - id: when_limit_is_reached
        type: s1
        if: unk_limit_param_playback
      - id: sound_instance_limit
        type: u2
        if: unk_limit_param_playback
      - id: sound_instance_limiting_behavior
        type: s1
      - id: virt_voice_behavior
        type: s1
      - id: parent_playback_settings_override
        type: b1
      - id: parent_virt_voice_settings_override
        type: b1
      - id: state_group_count
        type: u4
      - id: state_group
        type: ss_state_group
        repeat: expr
        repeat-expr: state_group_count
      - id: rtpc_count
        type: u2
      
      
  ss_effect:
    seq:
      - id: index
        type: s1
      - id: id
        type: u4
      - id: blank
        #contents: [00, 00]
        size: 2
  ss_pos_inc_2d:
    seq:
      - id: panner_enabled
        type: b1
  ss_pos_inc_3d:
    seq:
      - id: source_type
        type: u4
      - id: attenuation_id
        type: u4
      - id: spatialization_enabled
        type: b1
      - id: play_type
        type: u4
        enum: play_type
        if: source_type == 2
      - id: looping_enabled
        type: b1
        if: source_type == 2
      - id: trainsition_time
        type: u4
        if: source_type == 2
      - id: follow_listener_orientation
        type: b1
        if: source_type == 2
      - id: update_at_each_frame
        type: b1
        if: source_type == 3
  ss_state_group:
    seq:
      - id: id
        type: u4
      - id: change_occurs_at
        type: s1
      - id: settings_vary_from_default
        type: u2
      - id: state_obj
        type: ss_state_obj
        repeat: expr
        repeat-expr: settings_vary_from_default
  ss_state_obj:
    seq:
      - id: id
        type: u4
      - id: settings_obj_id
        type: u4
  ss_rtpc:
    seq:
      - id: game_param_x_axis_id
        type: u4
      - id: y_axis_type
        type: u4 # TODO: add enum
      - id: unk_id_1
        type: u4
      - id: unk_1
        size: 1
      - id: num_points
        type: s1
      - id: unk_2
        size: 1
      - id: point
        type: ss_rtpc_point
        repeat: expr
        repeat-expr: num_points
  ss_rtpc_point:
    seq:
      - id: x_coord
        type: f4
      - id: y_coord
        type: f4
      - id: curve_shape
        type: u4
        
  random_bytes:
    params:
      - id: size
        type: u4
    seq:
      - id: data
        size: size
        
enums:
  object_type:
    1: settings
    2: sound_effect_or_voice
    3: event_action
    4: event
    5: random_or_sequence_container
    5: switch_container
    7: actor_mixer
    8: audio_bus
    9: blend_container
    10: music_segment
    11: music_track
    12: music_switch_container
    13: music_playlist_container
    14: attenuation
    15: dialogue_event
    16: motion_bus
    17: motion_fx
    18: effect
    19: unknown
    20: auxiliary_bus
  action_scope:
    1: game_object_switch_or_trigger
    2: global
    3: game_object
    4: game_object_state
    5: all
    9: all_except
  action_type:
    1: stop
    2: pause
    3: resume
    4: play
    5: trigger
    6: mute
    7: unmute
    8: set_voice_pitch
    9: reset_voice_pitch
    10: set_voice_volume
    11: reset_voice_volume
    12: set_bus_volume
    13: reset_bus_volume
    14: set_voice_low_pass_filter
    15: reset_voice_low_pass_filter
    16: enable_state
    17: disable_state
    18: set_state
    19: set_game_parameter
    20: reset_game_parameter
    21: set_switch
    22: enable_bypass_or_disable_bypass
    23: reset_bypass_effect
    24: break
    25: seek
  audio_bus_parameter_type:
    0: voice_volume
    2: voice_pitch
    3: voice_low_pass_filter
    4: bus_volume
  play_type:
    0: sequence_step
    1: random_step
    2: sequence_continuous
    3: random_continuous
    4: sequence_step_new_path
    5: random_step_new_path
# HIRC END
