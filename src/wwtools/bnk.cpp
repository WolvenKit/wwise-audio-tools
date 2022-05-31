#include <string>
#include <vector>

#include "kaitai/kaitaistream.h"
#include "kaitai/structs/bnk.h"
#include "wwtools/bnk.hpp"

namespace wwtools::bnk {
void extract(const std::string &indata, std::vector<std::string> &outdata) {
  // Create a Kaitai stream with the input data
  kaitai::kstream ks(indata);

  // Create a BNK object from the stream
  bnk_t bnk(&ks);
  const auto data = bnk.data();

  // Reserve the length of the audio sections
  //outdata.reserve(data->data()->audio_sections()->size());
  int idx = 0;
  // Loop through the audio sections and save the data to outdata
  //for (auto audio_section : *data->data()->audio_sections()) {
  //  outdata.push_back(audio_section->data());
  //  idx++;
  //}
}

std::string get_info(const std::string &indata) {
  // Create a Kaitai stream with the input data
  kaitai::kstream ks(indata);

  // Create a BNK object from the stream
  bnk_t bnk(&ks);

  // Add data from header
  std::stringstream data_ss;
  //data_ss << "Version: " << bnk.bank_header()->version() << std::endl;
  //data_ss << "Soundbank ID: " << bnk.bank_header()->id() << std::endl;

  // Add WEM indexes and count
  //data_ss << bnk.data_index()->data()->indices()->size()
  //        << " embedded WEM files:" << std::endl;
  //for (auto index : *bnk.data_index()->data()->indices()) {
  //  data_ss << "  " << index->id() << std::endl;
  //}

  //return data_ss.str();
  return "";
}

std::string get_event_action_type(bnk_t::action_type_t action_type) {
    switch(action_type) {
        case bnk_t::ACTION_TYPE_PLAY:
            return "play";
            break;
        case bnk_t::ACTION_TYPE_PAUSE:
            return "pause";
            break;
        case bnk_t::ACTION_TYPE_STOP:
            return "stop";
            break;
        default:
            return std::to_string(action_type);
            break;
    }
}
} // namespace wwtools::bnk
