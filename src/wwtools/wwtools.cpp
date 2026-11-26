#include <algorithm>
#include <string>

#include "revorb/revorb.hpp"
#include "ww2ogg/ww2ogg.h"
#include "wwtools/bnk.hpp"
#include "wwtools/wwtools.hpp"

namespace wwtools {
std::string wem_to_ogg(const std::string &indata) {
  std::stringstream wem_out;
  std::stringstream revorb_out;

  if (!ww2ogg::ww2ogg(indata, wem_out))
    return "";

  if (!revorb::revorb(wem_out, revorb_out)) {
    return "";
  }

  return revorb_out.str();
}

uint64_t get_wem_to_ogg_size(const uint8_t* indata, uint64_t insize) {
  const auto wem = std::string(reinterpret_cast<const char*>(indata), insize);
  const std::string ogg = wem_to_ogg(wem);
  return ogg.size();
}

void wem_to_ogg(const uint8_t *indata, uint64_t insize, uint8_t *outdata) {
  const auto wem = std::string(reinterpret_cast<const char*>(indata), insize);
  const std::string ogg = wem_to_ogg(wem);
  std::copy_n(reinterpret_cast<const uint8_t*>(ogg.data()), ogg.size(), outdata);
}

} // namespace wwtools
