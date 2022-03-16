#define __STDC_CONSTANT_MACROS
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "errors.h"
#include "revorb.h"
#include "stdint.h"
#include "wwriff.h"
#include "packed_codebooks.h"

extern "C" __attribute__((visibility("default"))) bool 
ww2ogg(std::string indata, std::ostream &outdata, unsigned char codebooks_data[],
           bool inline_codebooks, bool full_setup,
           ForcePacketFormat force_packet_format) {
  try {
    std::string codebooks_data_s = string(reinterpret_cast<char*>(codebooks_data), packed_codebooks_bin_len);
    Wwise_RIFF_Vorbis ww(indata, codebooks_data_s, inline_codebooks,
                         full_setup, force_packet_format);

    ww.print_info();

    ww.generate_ogg(outdata);
  } catch (const File_open_error &fe) {
    return false;
  } catch (const Parse_error &pe) {
    return false;
  }
  return true;
}
