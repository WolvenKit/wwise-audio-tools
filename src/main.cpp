#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "bnk.h"
#include "kaitai/kaitaistream.h"
#include "revorb.h"
#include "ww2ogg.h"
#include "wwiseaudiotools.h"
#include "wwriff.h"
#include "wwt_bnk.hpp"

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

void print_help(std::string filename = "wwise-audio-tools") {
  std::cout << "Please use the command in one of the following ways:\n"
            << "  " << filename << " wem [input.wem]\n"
            << "  " << filename << " bnk [input.bnk]\n"
            << "Or run it without arguments to find and convert all WEMs in "
               "the current directory."
            << std::endl;
}

std::pair<std::vector<std::string>, bool> get_flags(int argc, char *argv[]) {
  std::vector<std::string> flags;
  flags.reserve(argc);
  bool flag_found = false;
  for (int i = 0; i < argc; i++) {
    std::string arg(argv[i]);
    // TODO: Change to starts_with with C++20
    if (arg.rfind("--", 0) == 0 && arg.length() > 2) {
      flag_found = true;
      flags.push_back(arg.substr(2, arg.npos));
    } else {
      // If current arg is not a flag but comes after a flag...
      if (flag_found) {
        std::cerr << "Please place all flags after other args!" << std::endl;
        print_help(argv[0]);
        return {{}, true};
      }
    }
  }
  return {flags, false};
}

bool has_flag(std::vector<std::string> flags, std::string wanted_flag) {
  for (auto flag : flags) {
    if (flag == wanted_flag) {
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  pair<std::vector<std::string>, bool> flags_raw = get_flags(argc, argv);
  if (flags_raw.second) { // If there's an error...
    return 1;
  }
  std::vector<std::string> flags = flags_raw.first;
  if (has_flag(flags, "help")) {
    print_help();
    return 0;
  }
  if (argc < 2) {
    // If there is no input file, convert all WEM files in the current directory
    bool wemExists = false;
    for (const auto &file : fs::directory_iterator(fs::current_path())) {
      if (file.path().extension() == ".wem") {
        wemExists = true;
        std::cout << "Coverting " << file.path() << "..." << std::endl;
        std::string outpath = file.path().string().substr(
                                  0, file.path().string().find_last_of(".")) +
                              ".ogg";
        auto success = convert(file.path().string(), outpath);
        if (!success) {
          std::cerr << "Failed to convert " << file.path() << std::endl;
          return 1;
        }
      }
    }
    if (!wemExists) {
      std::cout << "No WEM files found in the current directory!" << std::endl;
      print_help(argv[0]);
    }
  } else {
    if (argc < 3) {
      std::cout << "Missing arguments!" << std::endl;
      print_help(argv[0]);
      return 1;
    } else {
      if (strcmp(argv[1], "wem") == 0) {
        auto path = std::string(argv[2]);

        std::ifstream filein(path, std::ios::binary);
        std::stringstream indata;
        indata << filein.rdbuf();
        if (has_flag(flags, "info")) {
          std::cout << wem_info(indata.str());
          return 0;
        }
        std::string outpath = path.substr(0, path.find_last_of(".")) + ".ogg";

        auto success = convert(indata.str(), outpath);
        if (!success) {
          std::cerr << "Failed to convert " << path << std::endl;
          return 1;
        }
      } else if (strcmp(argv[1], "bnk") == 0) {
        auto path = std::string(argv[2]);

        std::ifstream filein(path, std::ios::binary);
        std::stringstream indata;
        indata << filein.rdbuf();
        if (has_flag(flags, "info")) {
          std::cout << get_bnk_info(indata.str());
          return 0;
        }

        kaitai::kstream ks(indata.str());

        bnk_t bnk(&ks);
        const auto data = bnk.data();

        std::vector<std::string> wems;
        // Populate WEMs vector with data
        bnk_extract(indata.str(), wems);
        // Create directory with name of bnk file, no extension
        fs::create_directory(path.substr(0, path.find_last_of(".")));
        int idx = 0;
        for (auto wem : wems) {
          fs::path outdir(path.substr(0, path.find_last_of(".")));
          std::stringstream ss;
          ss << bnk.data_index()->data()->indices()->at(idx)->id();
          bool noconvert = has_flag(flags, "no-convert");
          fs::path filename(ss.str());
          fs::path outpath = outdir / filename;
          std::string file_extension = noconvert ? ".wem" : ".ogg";
          if (noconvert) {
            std::ofstream of(outpath.string() + file_extension);
            of << wem;
            of.close();
            idx++;
            continue;
          }
          auto success = convert(wem, outpath.string());
          if (!success) {
            std::cerr << "Failed to convert " << outpath.string() << std::endl;
            // Don't return error because the rest may succeed
          }
          idx++;
        }
      } else {
        print_help(argv[0]);
        return 1;
      }
    }
  }
}
