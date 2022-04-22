#include <sstream>
#include <string>
#include <vector>

#include "bnk.h"
#include "kaitai/kaitaistream.h"
#include "wwt_bnk.hpp"

extern "C" void bnk_extract(const std::string &indata, std::vector<std::string> &outdata) {
  // Create a Kaitai stream with the input data
  kaitai::kstream ks(indata);

  // Create a BNK object from the stream
  bnk_t bnk(&ks);
  const auto data = bnk.data();

  // Reserve the length of the audio sections
  outdata.reserve(data->data()->audio_sections()->size());
  int idx = 0;
  // Loop through the audio sections and save the data to outdata
  for (auto audio_section : *data->data()->audio_sections()) {
    std::stringstream ss;
    ss << bnk.data_index()->data()->indices()->at(idx)->id();
    outdata.push_back(ss.str());
    idx++;
  }
}

extern "C" std::string get_bnk_info(const std::string &indata) {
  // Create a Kaitai stream with the input data
  kaitai::kstream ks(indata);

  // Create a BNK object from the stream
  bnk_t bnk(&ks);
  const auto data = bnk.data();

  // Add data from header
  std::stringstream data_ss;
  data_ss << "Version: " << bnk.bank_header()->version() << std::endl;
  data_ss << "Soundbank ID: " << bnk.bank_header()->id() << std::endl;

  // Add WEM indexes and count
  data_ss << bnk.data_index()->data()->indices()->size() << " embedded WEM files:" << std::endl;
  for (auto index : *bnk.data_index()->data()->indices()) {
    data_ss << "  " << index->id() << std::endl; 
  }

  return data_ss.str();
}
