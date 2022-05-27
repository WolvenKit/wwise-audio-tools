#include <cstdint>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "kaitai/kaitaistream.h"
#include "kaitai/structs/w3sc.h"
#include "wwtools/util/write.hpp"
#include "wwtools/w3sc.hpp"

const uint8_t HEADER_LENGTH = 48;
const uint16_t CACHE_BUFFER_SIZE = 4096;
int get_names_offset(
    const std::vector<std::pair<std::string, std::string>> &files) {
  uint32_t ret = 0;
  for (const auto &file : files) {
    const std::string file_contents = file.second;
    ret += file_contents.size();
  }
  ret += HEADER_LENGTH;
  return ret;
}

int get_info_offset(
    const std::vector<std::pair<std::string, std::string>> &files) {
  uint32_t ret = get_names_offset(files);
  for (const auto &file : files) {
    const std::string file_name = file.first;
    ret += file_name.size() + 1; // add 1 for '\0' char
  }
  return ret;
}

std::string get_footer_names(
    const std::vector<std::pair<std::string, std::string>> &files) {
  std::string ret;
  for (const auto &file : files)
    ret += file.first + '\0';
  return ret;
}

std::string get_footer_infos(
    const std::vector<std::pair<std::string, std::string>> &files) {
  std::stringstream ss;
  std::vector<uint32_t> data_offsets;
  data_offsets.resize(files.size(),
                      HEADER_LENGTH); // offset starts after header
  for (size_t i = 0; i < files.size(); i++) {
    if (i == 0)
      continue;
    data_offsets[i] = data_offsets[i - 1] + files[i].second.size();
  }
  // names
  std::vector<uint32_t> name_offsets;
  name_offsets.resize(files.size(), 0);
  // uint32_t name_offsets[static_cast<int>(files.size())];
  for (size_t i = 0; i < files.size(); i++) {
    if (i == 0)
      continue; // only populate name_offsets starting at index 1
    name_offsets[i] = name_offsets[i - 1] + files[i].first.size() + 1;
  }
  for (size_t i = 0; i < files.size(); i++) {
    wwtools::util::write::little_endian<uint32_t>(name_offsets[i], ss);
    wwtools::util::write::little_endian<uint32_t>(data_offsets[i], ss);
    wwtools::util::write::little_endian<uint32_t>(files[i].second.size(), ss);
  }

  return ss.str();
}

// https://github.com/ADawesomeguy/witcher-3-sound-editing-tools/blob/82365dc8c7721ce6cc47cd57fabf065d805a5f74/create_sounds_cache.py#L19-L26
uint64_t calculate_checksum(std::string data) {
  const uint64_t FNV_64_PRIME = 0x100000001b3;
  const uint64_t FNV1_64_INIT = 0xcbf29ce484222325;

  uint64_t ret = FNV1_64_INIT;
  for (const uint8_t &byte : data) {
    ret ^= byte;
    ret *= FNV_64_PRIME;
  }

  return ret;
}

uint64_t calculate_buffer_size(
    const std::vector<std::pair<std::string, std::string>> &files) {
  uint64_t ret = 0;
  for (int i = 0; i < files.size(); i++) {
    uint64_t file_size = files.at(i).second.size();
    ret = std::max(ret, file_size);
  }

  // round up to nearest multiple of cache buffer size
  ret += CACHE_BUFFER_SIZE - (ret % CACHE_BUFFER_SIZE);
  return ret;
}

namespace wwtools::w3sc {
const char MAGIC[4] = {'W', '3', 'S', 'C'};
const uint32_t VERSION = 1; // TODO: stuff changes from
                            // 32-bit to 64-bit based on version
const uint64_t DUMMY = 0;

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

// TODO: change vector string pair weird stuff to a class
// also i think i have little endian/big endian mixed up and stuff
void create(const std::vector<std::pair<std::string, std::string>> &files,
            std::ostream &os) {
  wwtools::util::write::big_endian<uint32_t>(MAGIC, os);
  wwtools::util::write::little_endian<uint32_t>(VERSION, os);
  wwtools::util::write::little_endian<uint64_t>(DUMMY, os);
  wwtools::util::write::little_endian<uint32_t>(
      static_cast<uint32_t>(get_info_offset(files)), os);
  wwtools::util::write::little_endian<uint32_t>(
      static_cast<uint32_t>(files.size()), os);
  wwtools::util::write::little_endian<uint32_t>(
      static_cast<uint32_t>(get_names_offset(files)), os);
  wwtools::util::write::little_endian<uint32_t>(
      (get_info_offset(files) - get_names_offset(files)), os); // names size

  // weird 8 bytes (buffer size?)
  wwtools::util::write::little_endian<uint64_t>(DUMMY, os);
  // next weird 8 bytes (checksum?)
  wwtools::util::write::little_endian<uint64_t>(DUMMY, os);
  // all data
  std::vector<uint32_t> data_offsets;
  data_offsets.resize(files.size(), 48);
  for (size_t i = 0; i < files.size(); i++) {
    os.write(files[i].second.c_str(), files[i].second.size());
    if (i == 0)
      continue;
    data_offsets[i] = data_offsets[i - 1] + files[i].second.size();
  }
  // names
  std::vector<uint32_t> name_offsets;
  name_offsets.resize(files.size(), 0);
  // uint32_t name_offsets[static_cast<int>(files.size())];
  for (size_t i = 0; i < files.size(); i++) {
    os.write(files[i].first.c_str(),
             files[i].first.size() + 1 /* include \0 */);
    if (i == 0)
      continue; // only populate name_offsets starting at index 1
    name_offsets[i] = name_offsets[i - 1] + files[i].first.size();
  }
  // info
  for (size_t i = 0; i < files.size(); i++) {
    wwtools::util::write::little_endian<uint32_t>(name_offsets[i], os);
    wwtools::util::write::little_endian<uint32_t>(data_offsets[i], os);
    wwtools::util::write::little_endian<uint32_t>(files[i].second.size(), os);
  }

  // buffer size
  os.seekp(32);
  wwtools::util::write::little_endian<uint64_t>(calculate_buffer_size(files),
                                                os);
  // checksum and stuff
  os.seekp(40);
  wwtools::util::write::little_endian<uint64_t>(
      calculate_checksum(get_footer_names(files) + get_footer_infos(files)),
      os);
}
} // namespace wwtools::w3sc
