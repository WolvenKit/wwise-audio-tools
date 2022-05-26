#ifndef WWTOOLS_WWTOOLS_HPP
#define WWTOOLS_WWTOOLS_HPP

#include <string>

namespace wwtools {
/**
 * @brief get OGG file data from WEM file data
 * 
 * @param indata WEM file data
 * @return OGG file data
 */
std::string wem_to_ogg(const std::string& indata);
} // namespace wwtools

#endif // WWTOOLS_WWTOOLS_HPP
