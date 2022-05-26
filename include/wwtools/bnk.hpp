#ifndef WWTOOLS_BNK_HPP
#define WWTOOLS_BNK_HPP

#include <string>
#include <vector>

#include "kaitai/structs/bnk.h"
#include "kaitai/kaitaistream.h"

namespace wwtools::bnk {
/**
 * @brief Extract BNK to array of WEMS
 * 
 * @param indata std::string with the BNK content
 * @param outdata vector of std::string that has all the embedded WEM files
 */
void extract(const std::string &indata, std::vector<std::string> &outdata);

/**
 * @brief get the info string
 * 
 * @param indata std::string with the file data
 * @return a printable info string
 */
std::string get_info(const std::string &indata);
} // namespace wwtools::bnk

#endif // WWTOOLS_BNK_HPP
