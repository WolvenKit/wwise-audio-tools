#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "bnk.h"
#include "kaitai/kaitaistream.h"
#include "revorb.h"
#include "ww2ogg.h"
#include "wwiseaudiotools.h"
#include "wwriff.h"

namespace fs = std::filesystem;

bool convert(std::string indata, std::string outpath) {
		std::string outdata = wem_to_ogg(indata);
		if (outdata == "") {
			return false;
		}

		std::ofstream fout(outpath);
		fout << outdata;
		return true;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
		// If there is no input file, convert all WEM files in the current directory
		for (const auto& file : fs::directory_iterator(fs::current_path())) {
			if (file.path().extension() == ".wem") {
				std::cout << "Coverting " << file.path() << "..." << std::endl;
				std::string outpath = file.path().string().substr(0, file.path().string().find_last_of(".")) + ".ogg";
				auto success = convert(file.path().string(), outpath);
				if (!success) {
					std::cerr << "Failed to convert " << file.path() << std::endl;
					return 1;
				}
			}
		}		
  } else {
		if (argc < 3) {
			std::cout << "Missing arguments!" << std::endl;
		} else {	
			std::cout << argv[1] << std::endl;
			if (strcmp(argv[1], "wem") == 0) {
				auto path = std::string(argv[2]);
				
				std::ifstream filein(path);
				std::stringstream indata;
				indata << filein.rdbuf();
				std::string outpath = path.substr(0, path.find_last_of(".")) + ".ogg";

				auto success = convert(indata.str(), outpath);
				if (!success) {
					std::cerr << "Failed to convert " << path << std::endl;
					return 1;
				}
			} else if (strcmp(argv[1], "bnk") == 0) {
				auto path = std::string(argv[2]);

				std::ifstream ifs(path, std::ifstream::binary);
				if (!ifs) {
					std::cout << "File does not exist!" << std::endl;
					return 1;
				}

				kaitai::kstream ks(&ifs);
				
				bnk_t bnk(&ks);
				const auto data = bnk.data();

				// Create directory with name of bnk file, no extension
				fs::create_directory(path.substr(0, path.find_last_of(".")));
				int idx = 0;
				for (auto audio_section : *data->data()->audio_sections()) {
					std::string indata = audio_section->data();
					fs::path outdir(path.substr(0, path.find_last_of(".")));
					std::stringstream ss;
					ss << bnk.data_index()->data()->indices()->at(idx)->id();
					fs::path filename(ss.str() + ".ogg");
					fs::path outpath = outdir / filename;
					auto success = convert(indata, outpath.string());
					if (!success) {
						std::cerr << "Failed to convert " << outpath.string() << std::endl;
						// Don't return error because the rest may succeed
					}
					idx++;
				}
			} else {
				std::cout <<
				"Please use the command in one of the following ways:\n" <<
				"  ./wwise-audio-converter wem [input.wem]\n" <<
				"  ./wwise-audio-converter bnk [input.bnk]\n" <<
				"Or run it without arguments to find and convert all WEMs in the current directory." << std::endl;
			}
		}
	}
}
