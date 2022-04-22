#include <string>

#include "revorb.h"
#include "ww2ogg.h"
#include "wwt_bnk.hpp"

extern "C" std::string wem_to_ogg(const std::string& indata) {
  std::stringstream wem_out;
  std::stringstream revorb_out;

  if (!ww2ogg(indata, wem_out))
    return "";

  if (!revorb(wem_out, revorb_out)) {
    return "";
  }

  return revorb_out.str();
}
