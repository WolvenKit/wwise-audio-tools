#include <string>
#include <vector>

#include "kaitai/structs/bnk.h"
#include "kaitai/kaitaistream.h"

namespace wwtools::bnk {
void extract(const std::string &indata, std::vector<std::string> &outdata);
std::string get_info(const std::string &indata);
}
