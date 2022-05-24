#ifndef WWTOOLS_BNK_HPP
#define WWTOOLS_BNK_HPP

#include <string>
#include <vector>

#include "kaitai/structs/bnk.h"
#include "kaitai/kaitaistream.h"

namespace wwtools::bnk {
void extract(const std::string &indata, std::vector<std::string> &outdata);
std::string get_info(const std::string &indata);
} // namespace wwtools::bnk

#endif // WWTOOLS_BNK_HPP
