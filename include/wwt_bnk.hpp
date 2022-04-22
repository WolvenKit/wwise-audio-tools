#include <string>
#include <vector>

#include "bnk.h"
#include "kaitai/kaitaistream.h"

extern "C" void bnk_extract(const std::string &indata, std::vector<std::string> &outdata);
extern "C" std::string get_bnk_info(const std::string &indata);
