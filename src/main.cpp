#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "revorb.h"
#include "ww2ogg.h"
#include "wwriff.h"

#include "packed_codebooks.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Missing file!" << std::endl;
    return 1;
  }

  auto infile = std::string(argv[1]);
  std::ofstream fout(infile.substr(0, infile.find_last_of(".")) + ".ogg");
  std::ifstream filein(infile);

  std::stringstream indata;
  indata << filein.rdbuf();
  std::string codebooks(reinterpret_cast<char *>(packed_codebooks_bin),
                        packed_codebooks_bin_len);

  std::string outdata = wem_to_ogg(infile, indata.str(), codebooks);
  if (outdata == "") {
    std::cerr << "An error occurred." << std::endl;
    return 1;
  }

  fout << outdata;
}
