/**
 * @file wwtools.hpp
 * @author Abheek Dhawan (abheekd at protonmail dot com)
 * @brief helper functions for other Wwise file actions
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022 RED Modding Tools
 *
 */

#ifndef WWTOOLS_WWTOOLS_HPP
#define WWTOOLS_WWTOOLS_HPP

#include <string>

#include "export.h"

/**
 * @namespace wwtools
 * @brief parent namespace for specific file type helper functions
 *
 */
namespace wwtools {
/**
 * @brief get OGG file data from WEM file data
 *
 * @param indata WEM file data
 * @return OGG file data
 */
std::string wem_to_ogg(const std::string &indata);

#if WWTOOLS_LIBRARY
extern "C" {
WWTOOLS_EXPORT uint64_t get_wem_to_ogg_size(const uint8_t *indata, uint64_t insize);

WWTOOLS_EXPORT void wem_to_ogg(const uint8_t *indata, uint64_t insize, uint8_t *outdata);
}
#endif
} // namespace wwtools

#endif // WWTOOLS_WWTOOLS_HPP
