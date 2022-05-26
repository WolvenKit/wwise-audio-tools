/**
 * @file w3sc.hpp
 * @author Abheek Dhawan (abheekd at protonmail dot com)
 * @brief works with sound cache files from The Witcher 3
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022 RED Modding Tools
 * 
 */

#ifndef WWTOOLS_W3SC_HPP
#define WWTOOLS_W3SC_HPP

#include <string>
#include <vector>

#include "kaitai/structs/w3sc.h"
#include "kaitai/kaitaistream.h"

/**
 * @namespace wwtools::w3sc
 * @brief contains helper functions for The Witcher 3 sound cache files
 * 
 */
namespace wwtools::w3sc {
/**
 * @brief get the info string
 * 
 * @param indata std::string with the file data
 * @return a printable info string
 */
std::string get_info(const std::string &indata);
} // namespace wwtools::w3sc

#endif // WWTOOLS_W3SC_HPP
