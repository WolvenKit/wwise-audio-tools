#define __STDC_CONSTANT_MACROS
#include <iostream>
#include <string>

#include "ww2ogg/errors.h"
#include "ww2ogg/packed_codebooks.h"
#include "ww2ogg/wwriff.h"

namespace ww2ogg {
bool ww2ogg(const std::string &indata, std::ostream &outdata,
            unsigned char codebooks_data[], bool inline_codebooks,
            bool full_setup, ForcePacketFormat force_packet_format) {
  try {
    std::string codebooks_data_s = std::string(
        reinterpret_cast<char *>(codebooks_data), packed_codebooks_bin_len);
    Wwise_RIFF_Vorbis ww(indata, codebooks_data_s, inline_codebooks, full_setup,
                         force_packet_format);

    ww.generate_ogg(outdata);
  } catch (const file_open_error &fe) {
    return false;
  } catch (const parse_error &pe) {
    return false;
  }
  return true;
}

std::string wem_info(const std::string &indata, unsigned char codebooks_data[],
                     bool inline_codebooks, bool full_setup,
                     ForcePacketFormat force_packet_format) {

  std::string codebooks_data_s = std::string(
      reinterpret_cast<char *>(codebooks_data), packed_codebooks_bin_len);
  Wwise_RIFF_Vorbis ww(indata, codebooks_data_s, inline_codebooks, full_setup,
                       force_packet_format);
  return ww.get_info();
}
} // namespace ww2ogg
