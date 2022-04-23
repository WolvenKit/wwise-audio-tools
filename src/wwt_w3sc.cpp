#include <string>
#include <vector>

#include "w3sc.h"
#include "kaitai/kaitaistream.h"

/*extern "C" void bnk_extract(const std::string &indata, std::vector<std::string> &outdata) {
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
    outdata.push_back(audio_section->data());
    idx++;
  }
}*/

std::string get_w3sc_info(const std::string &indata) {
  // Create a Kaitai stream with the input data
  kaitai::kstream ks(indata);

  // Create a BNK object from the stream
	w3sc_t cache(&ks);

  // Add data from header
  std::stringstream data_ss;
  data_ss << "Cache Version: " << cache.version() << std::endl;

  // Add WEM indexes and count
  data_ss << cache.files() << " embedded files:" << std::endl;
  for (auto file_info : *cache.file_infos()) {
    data_ss << "  " << file_info->name() << std::endl; 
  }

  return data_ss.str();
}
