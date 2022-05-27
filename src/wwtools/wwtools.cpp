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
} // namespace wwtools
