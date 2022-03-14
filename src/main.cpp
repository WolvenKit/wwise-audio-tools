#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "ww2ogg.h"
#include "revorb.h"
#include "wwriff.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Missing file!" << std::endl;
        return 1;
    }

    auto infile = std::string(argv[1]);
    std::ofstream fout(infile.substr(0, infile.find_last_of(".")) + ".ogg");
    std::ifstream fin(infile);

    std::stringstream indata;
    indata << fin.rdbuf();
    std::string outdata = wem_to_ogg(infile, indata.str(), "packed_codebooks.bin");
    if (outdata == "") {
        std::cerr << "An error occurred." << std::endl;
        return 1;
    }

    fout << outdata;
}
