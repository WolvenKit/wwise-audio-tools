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

/**
 * @brief get WEMs correlating to a BNK and an optional event ID
 *
 * @param indata std::string with the file data
 * @param in_event_id the input event ID
 * @return a printable info string
 */
std::string get_event_id_info(const std::string &indata,
                              const std::string &in_event_id);

/**
 * @brief get the ID of a WEM at an index
 *
 * @param indata std::string with the file data
 * @param index the index to get the ID from
 * @return the ID as a string
 */
std::string get_wem_id_at_index(const std::string &indata, const int &index);

std::string get_event_name_from_id(const std::uint32_t &event_id);

/**
 * @brief get a string with the action type from the enum
 * @param action_type an action type to be converted to string
 * @return the string name of the action type
 */
std::string get_event_action_type(bnk_t::action_type_t action_type);
} // namespace wwtools::bnk

#endif // WWTOOLS_BNK_HPP
