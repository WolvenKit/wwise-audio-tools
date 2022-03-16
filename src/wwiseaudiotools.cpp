#include <sstream>
#include <string>

#include "revorb.h"
#include "ww2ogg.h"

extern "C" std::string wem_to_ogg(std::string indata) {
  std::stringstream indata_ss(indata);
  std::stringstream wem_out;
  std::stringstream revorb_out;

  if (!ww2ogg(indata_ss.str(), wem_out))
    return "";

  if (!revorb(wem_out, revorb_out)) {
    return "";
  }

  return revorb_out.str();
}
