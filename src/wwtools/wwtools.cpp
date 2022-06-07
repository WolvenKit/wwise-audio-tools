#include <string>

#include "revorb/revorb.hpp"
#include "ww2ogg/ww2ogg.h"
#include "wwtools/bnk.hpp"
#include "wwtools/wwtools.hpp"

namespace wwtools {
extern "C" const char *wem_to_ogg(const char *in_data) {
    std::string ret_s = wem_to_ogg(std::string(in_data));
    char *ret = new char[ret_s.length() + 1];
    return strncpy(ret, ret_s.c_str(), ret_s.size() + 1);
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
