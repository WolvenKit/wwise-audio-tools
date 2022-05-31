/**
 * @file bnk.hpp
 * @author Abheek Dhawan (abheekd at protonmail dot com)
 * @brief works with Wwise Soundbank files
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022 RED Modding Tools
 *
 */

#ifndef WWTOOLS_BNK_HPP
#define WWTOOLS_BNK_HPP

#include <string>
#include <vector>

#include "kaitai/kaitaistream.h"
#include "kaitai/structs/bnk.h"

/**
 * @namespace wwtools::bnk
 * @brief contains helper functions for Wwise Soundbank files
 *
 */
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

std::string get_event_id_info(const std::string &indata, const std::string& in_event_id);

std::string get_wem_id_at_index(const std::string &indata, const int &index);

std::string get_event_action_type(bnk_t::action_type_t action_type);
} // namespace wwtools::bnk

#endif // WWTOOLS_BNK_HPP
