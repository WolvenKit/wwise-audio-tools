#include <string>
#include <vector>

#include "kaitai/kaitaistream.h"
#include "kaitai/structs/bnk.h"
#include "wwtools/bnk.hpp"

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
          bnk_t::bkhd_data_t *bkhd_section = (bnk_t::bkhd_data_t *)(section->section_data());
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

std::string get_event_action_type(bnk_t::action_type_t action_type) {
    std::string ret;
    switch(action_type) {
        case bnk_t::ACTION_TYPE_PLAY:
            ret = "play";
            break;
        case bnk_t::ACTION_TYPE_PAUSE:
            ret = "pause";
            break;
        case bnk_t::ACTION_TYPE_STOP:
            ret = "stop";
            break;
        default:
            ret = std::to_string(action_type);
            break;
    }
    return ret;
}
} // namespace wwtools::bnk
