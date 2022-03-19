#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "revorb.h"
#include "ww2ogg.h"
#include "wwiseaudiotools.h"
#include "wwriff.h"

namespace fs = std::filesystem;

bool convert(std::string path) {
		std::ofstream fout(path.substr(0, path.find_last_of(".")) + ".ogg");
		std::ifstream filein(path);

		std::stringstream indata;
		indata << filein.rdbuf();

		std::string outdata = wem_to_ogg(indata.str());
		if (outdata == "") {
			return false;
		}

		fout << outdata;
		return true;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
		// If there is no input file, convert all WEM files in the current directory
		for (const auto& file : fs::directory_iterator(fs::current_path())) {
			if (file.path().extension() == ".wem") {
				std::cout << "Coverting " << file.path() << "..." << std::endl;
				auto success = convert(file.path());
				if (!success) {
					std::cerr << "Failed to convert " << file.path() << std::endl;
					return 1;
				}
			}
		}		
  } else {
		auto path = std::string(argv[1]);
		auto success = convert(path);
		if (!success) {
			std::cerr << "Failed to convert " << path << std::endl;
			return 1;
		}
	}
}
