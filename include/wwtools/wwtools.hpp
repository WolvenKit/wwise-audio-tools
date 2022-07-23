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

#if defined(_MSC_VER)
//  Microsoft
#define EXPORT extern "C" __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
//  GCC
#define EXPORT extern "C" __attribute__((visibility("default")))
#define IMPORT
#else
//  do nothing and hope for the best?
#define EXPORT
#define IMPORT
#pragma warning Unknown dynamic link import/export semantics.
#endif


#include <string>

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
std::string wem_to_ogg(const std::string &in_data);
EXPORT size_t wem_to_ogg(const uint8_t *in_data, size_t in_size, uint8_t **out_data);
} // namespace wwtools

#endif // WWTOOLS_WWTOOLS_HPP
