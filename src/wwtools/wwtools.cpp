#include <cstring>
#include <string>

#include "revorb/revorb.hpp"
#include "ww2ogg/ww2ogg.h"
#include "wwtools/bnk.hpp"
#include "wwtools/wwtools.hpp"

namespace wwtools {
EXPORT size_t wem_to_ogg(const uint8_t *in_data, size_t in_size,
                             uint8_t **out_data) {
  std::string ret_s =
      wem_to_ogg(std::string(reinterpret_cast<const char *>(in_data), in_size));
  memcpy(*out_data, ret_s.c_str(), ret_s.size());
  return ret_s.size();
}

std::string wem_to_ogg(const std::string &in_data) {
  std::stringstream wem_out;
  std::stringstream revorb_out;

  if (!ww2ogg::ww2ogg(in_data, wem_out))
    return "";

  if (!revorb::revorb(wem_out, revorb_out)) {
    return "";
  }

  return revorb_out.str();
}
} // namespace wwtools
