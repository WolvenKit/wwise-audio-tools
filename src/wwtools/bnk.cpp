#include <map>
#include <string>
#include <vector>

#include "kaitai/kaitaistream.h"
#include "kaitai/structs/bnk.h"
#include "wwtools/bnk.hpp"

// not in namespace, only used to keep
// trace of events and corresponding
// SFX for get_event_id_info
struct EventSFX {
  bnk_t::action_type_t action_type;
  bnk_t::sound_effect_or_voice_t *sfx;
  bool is_child;
};

namespace wwtools::bnk {
void extract(const std::string &indata, std::vector<std::string> &outdata) {
  // create a Kaitai stream with the input data
  kaitai::kstream ks(indata);

  // create a BNK object from the stream
  bnk_t bnk(&ks);

  // loop through each section to find the DATA section
  for (const auto &section : *bnk.data()) {
    if (section->type() == "DATA") {
      // cast the section to a DATA section
      auto *data_section = (bnk_t::data_data_t *)(section->section_data());
      // reserve the necessary amount
      outdata.reserve(data_section->didx_data()->num_files());
      // loop through each data object in the section
      for (const auto &file_data : *data_section->data_obj_section()->data()) {
        // append the file vector with the file data
        outdata.push_back(file_data->file());
      }
    }
  }
}

std::string get_info(const std::string &indata) {
  // create a Kaitai stream with the input data
  kaitai::kstream ks(indata);

  // create a BNK object from the stream
  bnk_t bnk(&ks);

  // add data from header
  std::stringstream data_ss;

  // loop through each section to find the BKHD (Bank Header) section
  for (const auto &section : *bnk.data()) {
    if (section->type() == "BKHD") {
      bnk_t::bkhd_data_t *bkhd_section =
          (bnk_t::bkhd_data_t *)(section->section_data());
      auto version = bkhd_section->version();
      auto id = bkhd_section->id();
      data_ss << "Version: " << version << '\n';
      data_ss << "Soundbank ID: " << id << '\n';
    }
  }

  // loop through each section to find the DIDX (Data Index) section
  for (const auto &section : *bnk.data()) {
    if (section->type() == "DIDX") {
      auto *didx_section = (bnk_t::didx_data_t *)(section->section_data());
      data_ss << didx_section->num_files() << " embedded WEM files:\n";
      for (auto index : *didx_section->objs()) {
        data_ss << '\t' << index->id() << '\n';
      }
    }
  }

  return data_ss.str();
}

std::string get_event_id_info(const std::string &indata,
                              const std::string &in_event_id) {
  kaitai::kstream ks(indata);
  bnk_t bnk(&ks);

  std::stringstream data_ss;
  // loop through each section to get to HIRC and find event ID
  for (const auto &section : *bnk.data()) {
    int num_events = 0;
    // read HIRC
    if (section->type() == "HIRC") {
      // cast section to HIRC data
      bnk_t::hirc_data_t *hirc_data =
          (bnk_t::hirc_data_t *)(section->section_data());
      // create a map between events and the corresponding event actions
      std::map<uint32_t /* event */,
               std::vector<
                   bnk_t::event_action_t *> /* event action (with gobj id) */>
          event_to_event_actions;
      // loop through all HIRC objects
      for (const auto &obj_i : *hirc_data->objs()) {
        if (obj_i->type() == bnk_t::OBJECT_TYPE_EVENT) { // get event
          num_events++; // increment the number of events
          bnk_t::event_t *event =
              (bnk_t::event_t *)(obj_i->object_data()); // cast to event
          bool all_event_ids = false;
          if (in_event_id.empty())
            all_event_ids = true;
          // compare ID to command line input ID
          if (std::to_string(obj_i->id()) == in_event_id) {
            // get all event action IDs for this event
            for (const auto &event_action_id : *event->event_actions()) {
              // loop to get corresponding event actions from IDs
              for (const auto &obj_j : *hirc_data->objs()) {
                // check if it's an event actions, and if it is, check if it
                // matches up with an event_action_id corresponding to the
                // inputted event
                if (obj_j->type() == bnk_t::OBJECT_TYPE_EVENT_ACTION) {
                  bnk_t::event_action_t *event_action =
                      (bnk_t::event_action_t *)(obj_j->object_data());
                  if (obj_j->id() == event_action_id) {
                    // if it points to a game object (sound or container)
                    if (event_action->game_object_id() != 0) {
                      // add it to the vector in the map corresponding to the
                      // event ID
                      event_to_event_actions[obj_i->id()].push_back(
                          event_action);
                    }
                  }
                }
              }
            }
          } else if (all_event_ids) {
            // get all event action IDs for this event
            for (const auto &event_action_id : *event->event_actions()) {
              // loop to get corresponding event actions from IDs
              for (const auto &obj_j : *hirc_data->objs()) {
                // check if it's an event actions, and if it is, check if it
                // matches up with an event_action_id corresponding to the
                // inputted event
                if (obj_j->type() == bnk_t::OBJECT_TYPE_EVENT_ACTION) {
                  bnk_t::event_action_t *event_action =
                      (bnk_t::event_action_t *)(obj_j->object_data());
                  if (obj_j->id() == event_action_id) {
                    // if it points to a game object (sound or container)
                    if (event_action->game_object_id() != 0) {
                      // add it to the vector in the map corresponding to the
                      // event ID
                      event_to_event_actions[obj_i->id()].push_back(
                          event_action);
                    }
                  }
                }
              }
            }
          }
        }
      }

      std::map<uint32_t /* event ID */, std::vector<EventSFX>>
          event_to_event_sfxs;
      // loop through all objects again, this time looking for SFX
      for (const auto &obj : *hirc_data->objs()) {
        if (obj->type() == bnk_t::OBJECT_TYPE_SOUND_EFFECT_OR_VOICE) {
          bnk_t::sound_effect_or_voice_t *sound_effect_or_voice =
              (bnk_t::sound_effect_or_voice_t *)(obj->object_data());

          // get parent ID since it can also be used to check if this is a child
          // of an object that is manipulated by the event
          uint32_t parent_id_offset = 6;
          uint8_t num_effects = sound_effect_or_voice->sound_structure().at(1);
          if (num_effects > 0) {
            parent_id_offset++; // bit mask for bypassed effects
            parent_id_offset += num_effects * 7; // 7 bytes for each effect
          }
          uint32_t parent_id = 0;
          std::stringstream ss;
          ss.write(sound_effect_or_voice->sound_structure().c_str(),
                   sound_effect_or_voice->sound_structure().size());
          ss.seekg(parent_id_offset);
          ss.read(reinterpret_cast<char *>(&parent_id), 4);

          // loop through each event ID and its corresponding event actions
          for (const auto &[event, event_actions] : event_to_event_actions) {
            for (const auto &event_action : event_actions) {
              if (event_action->game_object_id() == obj->id() ||
                  event_action->game_object_id() == parent_id) {
                EventSFX current_event_sfx{};
                current_event_sfx.action_type = event_action->type();
                current_event_sfx.sfx = sound_effect_or_voice;
                if (event_action->game_object_id() == parent_id)
                  current_event_sfx.is_child = true;
                else
                  current_event_sfx.is_child = false;
                event_to_event_sfxs[event].push_back(current_event_sfx);
              }
            }
          }
        }
      }
      data_ss << "Found " << num_events << " event(s)\n";
      data_ss << event_to_event_sfxs.size() << " of them point to files in this BNK\n\n";
      for (const auto &[event_id, event_sfxs] : event_to_event_sfxs) {
        data_ss << event_id << '\n';
        for (const auto &event_sfx : event_sfxs) {
          data_ss << '\t'
                  << wwtools::bnk::get_event_action_type(event_sfx.action_type)
                  << ' ' << event_sfx.sfx->audio_file_id();
          if (event_sfx.is_child)
            data_ss << " (child)\n";
          else
            data_ss << '\n';
        }
        data_ss << std::endl; // newline + flush
      }
    }
  }

  return data_ss.str();
}

std::string get_wem_id_at_index(const std::string &indata, const int &index) {
  // create a Kaitai stream with the input data
  kaitai::kstream ks(indata);

  // create a BNK object from the stream
  bnk_t bnk(&ks);

  // add data from header
  std::stringstream data_ss;

  // loop through each section to find the DIDX (Data Index) section
  for (const auto &section : *bnk.data()) {
    if (section->type() == "DIDX") {
      auto *didx_section = (bnk_t::didx_data_t *)(section->section_data());
      return std::to_string(didx_section->objs()->at(index)->id());
    }
  }

  return "";
}

std::string get_event_action_type(bnk_t::action_type_t action_type) {
  std::string ret;
  switch (action_type) {
  case bnk_t::ACTION_TYPE_PLAY:
    ret = "play";
    break;
  case bnk_t::ACTION_TYPE_PAUSE:
    ret = "pause";
    break;
  case bnk_t::ACTION_TYPE_STOP:
    ret = "stop";
    break;
  case bnk_t::ACTION_TYPE_RESUME:
      ret = "resume";
      break;
  default:
    ret = std::to_string(action_type);
    break;
  }
  return ret;
}
} // namespace wwtools::bnk
