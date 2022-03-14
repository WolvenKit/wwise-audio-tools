#include <string>

#include "wwriff.h"

std::string
wem_to_ogg(std::string infile, std::string indata, std::string codebooks_file,
           bool inline_codebooks = false, bool full_setup = false,
           ForcePacketFormat force_packet_format = kNoForcePacketFormat);
