#include <string>
#include <vector>

#include "kaitai/structs/w3sc.h"
#include "kaitai/kaitaistream.h"
#include "wwtools/w3sc.hpp"

namespace wwtools::w3sc {
std::string get_info(const std::string &indata) {
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
}
