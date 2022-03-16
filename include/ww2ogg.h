#include <string>
#include <sstream>

#include "wwriff.h"
#include "packed_codebooks.h"

extern "C" bool
ww2ogg(std::string indata, std::ostream &outdata, unsigned char codebooks_data[] = packed_codebooks_bin,
           bool inline_codebooks = false, bool full_setup = false,
           ForcePacketFormat force_packet_format = kNoForcePacketFormat);
