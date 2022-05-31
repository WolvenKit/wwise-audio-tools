#include <sstream>
#include <string>

#include "packed_codebooks.h"
#ifndef WW2OGG_WW2OGG_H
#define WW2OGG_WW2OGG_H

#include "wwriff.h"

namespace ww2ogg {
bool ww2ogg(const std::string &indata, std::ostream &outdata,
            unsigned char codebooks_data[] = packed_codebooks_bin,
            bool inline_codebooks = false, bool full_setup = false,
            ForcePacketFormat force_packet_format = kNoForcePacketFormat);

std::string
wem_info(const std::string &indata,
         unsigned char codebooks_data[] = packed_codebooks_bin,
         bool inline_codebooks = false, bool full_setup = false,
         ForcePacketFormat force_packet_format = kNoForcePacketFormat);
} // namespace ww2ogg

#endif // WW2OGG_WW2OGG_H
