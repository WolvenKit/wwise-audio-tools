#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdint.h>
#include <string>
#include <utility>
#include <vector>

#include "kaitai/kaitaistream.h"
#include "kaitai/structs/bnk.h"
#include "kaitai/structs/w3sc.h"
#include "revorb/revorb.hpp"
#include "util/rang.hpp"
#include "ww2ogg/ww2ogg.h"
#include "ww2ogg/wwriff.h"
#include "wwtools/bnk.hpp"
#include "wwtools/util/write.hpp"
#include "wwtools/w3sc.hpp"
#include "wwtools/wwtools.hpp"

namespace fs = std::filesystem;
bool convert(std::string indata, std::string outpath) {
  std::string outdata = wwtools::wem_to_ogg(indata);
  if (outdata == "") {
    return false;
  }

  std::ofstream fout(outpath);
  fout << outdata;
  return true;
}

void print_help(std::string extra_message = "",
                std::string filename = "wwtools") {
  if (!extra_message.empty()) {
    std::cout << rang::fg::red << extra_message << rang::fg::reset << std::endl
              << std::endl;
  }
  std::cout << "Please use the command in one of the following ways:\n"
            << "  " << filename << " wem [input.wem] (--info)\n"
            << "  " << filename << " bnk [event|extract] [input.bnk] (event ID) (--info) (--no-convert)\n"
            << "  " << filename
            << " cache [read|write] [file/directory name] (--info) "
               "(--no-convert-wem) (--no-convert-bnk)\n"
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
        print_help("Please place all flags after other args!", argv[0]);
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
  // TODO: Add more descriptive comments regarding as much as possible
  std::pair<std::vector<std::string>, bool> flags_raw = get_flags(argc, argv);
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
        // TODO: Add function for changing extension
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
      print_help("No WEM files found in the current directory!", argv[0]);
    }
  } else {
    if (argc < 3) {
      print_help("Missing arguments!", argv[0]);
      return 1;
    } else {
#pragma region WEM
      if (strcmp(argv[1], "wem") == 0) {
        auto path = std::string(argv[2]);

        std::ifstream filein(path, std::ios::binary);
        std::stringstream indata;
        indata << filein.rdbuf();
        if (has_flag(flags, "info")) {
          std::cout << ww2ogg::wem_info(indata.str());
          return 0;
        }
        std::string outpath = path.substr(0, path.find_last_of(".")) + ".ogg";

        std::cout << "Extracting " << outpath << "..." << std::endl;
        auto success = convert(indata.str(), outpath);
        if (!success) {
          std::cerr << "Failed to convert " << path << std::endl;
          return 1;
        }
#pragma endregion WEM
#pragma region BNK
      } else if (strcmp(argv[1], "bnk") == 0) {
        if (argc < 4) {
          print_help(
              "You must specify whether to extract or find an event as well as the input!",
              argv[0]);
          return EXIT_FAILURE;
        }

        if (strcmp(argv[2], "event") != 0 && strcmp(argv[2], "extract") != 0) {
          print_help("Incorrect value for read or write!", argv[0]);
          return EXIT_FAILURE;
        }

        auto bnk_path = std::string(argv[3]);

        if (strcmp(argv[2], "event") == 0) {
          if (argc < 5) {
            print_help("Not enough arguments for finding an event!");
            return EXIT_FAILURE;
          }

          // get paths for all sound cache files
          // std::vector<std::string> cache_paths;
          // cache_paths.resize(argc - 4);
          // for (int i = 4; i < argc; i++)
          //  cache_paths.push_back(argv[i]);

          std::cout << bnk_path << std::endl;
          std::ifstream bnk_in(bnk_path, std::ios::binary);
          kaitai::kstream ks(&bnk_in);
          bnk_t bnk(&ks);

          // loop through each section to get to HIRC and find event ID
          for (const auto &section : *bnk.data()) {
            if (section->type() == "HIRC") {
              bnk_t::hirc_data_t *hirc_data = (bnk_t::hirc_data_t *)(section->section_data());
              std::map<uint32_t /* event */, std::vector<bnk_t::event_action_t *> /* event action (with gobj id) */> event_to_event_actions;
              for (const auto &obj : *hirc_data->objs()) {
                if (obj->type() == bnk_t::OBJECT_TYPE_EVENT) {
                  bnk_t::event_t *event = (bnk_t::event_t *)(obj->object_data());
                  if (std::to_string(obj->id()) == argv[4]) {
                    for (const auto& event_action_id : *event->event_actions()) {
                      for (const auto &obj2 : *hirc_data->objs()) {
                        if (obj2->type() == bnk_t::OBJECT_TYPE_EVENT_ACTION) {
                          bnk_t::event_action_t *event_action = (bnk_t::event_action_t *)(obj2->object_data());
                          if (obj2->id() == event_action_id) {
                              if (event_action->scope() == bnk_t::ACTION_SCOPE_GAME_OBJECT) {
                                  event_to_event_actions[obj->id()].push_back(event_action);
                              }
                          }
                        }
                      }
                    }
                  }
                }
              }

              /* std::cout << event_to_event_actions.size() << std::endl;
              for (const auto &[thing1, thing2] : event_to_event_actions) {
                  std::cout << thing1 << std::endl;
                  for (const auto &thing3 : thing2)
                      std::cout << '\t' << thing3->game_object_id() << std::endl;
              } */

                bool printed_event_id = false;
              for (const auto& obj : *hirc_data->objs()) {
                if (obj->type() == bnk_t::OBJECT_TYPE_SOUND_EFFECT_OR_VOICE) {
                  bnk_t::sound_effect_or_voice_t *sound_effect_or_voice = (bnk_t::sound_effect_or_voice_t *)(obj->object_data());
                  uint32_t parent_id_offset = 6;
                  uint8_t num_effects = sound_effect_or_voice->sound_structure().at(1);
                  if (num_effects > 0) {
                    parent_id_offset++; // bit mask for bypassed effects
                    parent_id_offset += num_effects * 7; // 7 bytes for each effect
                  }
                  uint32_t parent_id = 0;
                  std::stringstream ss;
                  ss.write(sound_effect_or_voice->sound_structure().c_str(), sound_effect_or_voice->sound_structure().size());
                  ss.seekg(parent_id_offset);
                  ss.read(reinterpret_cast<char *>(&parent_id), 4);

                  for (const auto &[event, event_actions] : event_to_event_actions) {
                      if (!printed_event_id)
                        std::cout << event;
                      printed_event_id = true;
                      for (const auto &event_action : event_actions) {
                          if (event_action->game_object_id() == obj->id() || event_action->game_object_id() == parent_id) {
                              std::cout << '\n' << '\t' << wwtools::bnk::get_event_action_type(event_action->type()) << ' ' << sound_effect_or_voice->audio_file_id();
                              if (event_action->game_object_id() == parent_id)
                                  std::cout << " (child)";
                          }
                      }
                      std::cout << std::flush;
                  }
                }
              }
            }
          }
        }
/*      } else if (strcmp(argv[1], "bnk") == 0) {
        auto path = std::string(argv[2]);

        std::ifstream filein(path, std::ios::binary);
        std::stringstream indata;
        indata << filein.rdbuf();
        if (has_flag(flags, "info")) {
          std::cout << wwtools::bnk::get_info(indata.str());
          return 0;
        }

        kaitai::kstream ks(indata.str());

        bnk_t bnk(&ks);

        std::vector<std::string> wems;
        // Populate WEMs vector with data
        wwtools::bnk::extract(indata.str(), wems);
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
          std::cout << rang::fg::cyan << "[" << idx + 1 << "/" << wems.size()
                    << "] " << rang::fg::reset << "Extracting "
                    << outpath.string() + file_extension << "..." << std::endl;
          if (noconvert) {
            std::ofstream of(outpath.string() + file_extension);
            of << wem;
            of.close();
            idx++;
            continue;
          }
          auto success = convert(wem, outpath.string() + file_extension);
          if (!success) {
            std::cout << "Failed to convert "
                      << outpath.string() + file_extension << std::endl;
            // Don't return error because the rest may succeed
          }
          idx++;
        }*/
#pragma endregion BNK
#pragma region CACHE      
      } else if (strcmp(argv[1], "cache") == 0) {
        if (argc < 4) {
          print_help(
              "You must specify whether to read or write as well as the input!",
              argv[0]);
          return EXIT_FAILURE;
        }

        if (strcmp(argv[2], "read") != 0 && strcmp(argv[2], "write") != 0) {
          print_help("Incorrect value for read or write!", argv[0]);
          return EXIT_FAILURE;
        }

        auto path = std::string(argv[3]);

        if (strcmp(argv[2], "read") == 0) {
          std::ifstream filein(path, std::ios::binary);
          std::stringstream indata;
          indata << filein.rdbuf();
          if (has_flag(flags, "info")) {
            std::cout << wwtools::w3sc::get_info(indata.str());
            return 0;
          }

          kaitai::kstream ks(indata.str());

          w3sc_t cache(&ks);

          int file_index = 0;
          int file_count = cache.file_infos()->size();
          for (auto file : *cache.file_infos()) {
            file_index++;
            if (file->name().substr(file->name().find_last_of(".")) == ".bnk") {
              std::cout << rang::fg::cyan << "[" << file_index << "/"
                        << file_count << "] " << rang::fg::reset
                        << "Extracting " << file->name() << "..." << std::endl;
              // Currently unable to read music files
              if (file->name().find("music_") != std::string::npos ||
                  file->name().find("vo_") != std::string::npos ||
                  file->name().find("qu_") != std::string::npos ||
                  file->name().find("mutations_") != std::string::npos) {
                continue;
              }

              kaitai::kstream bnk_ks(file->data());
              bnk_t bnk(&bnk_ks);
              std::vector<std::string> wems;
              // Populate WEMs vector with data
              wwtools::bnk::extract(file->data(), wems);
              // Create directory with name of bnk file, no extension
              fs::create_directory(
                  file->name().substr(0, file->name().find_last_of(".")));
              int idx = 0;
              for (auto wem : wems) {
                fs::path outdir(
                    file->name().substr(0, file->name().find_last_of(".")));
                std::stringstream ss;
                // ss << bnk.data_index()->data()->indices()->at(idx)->id();
                bool noconvert = has_flag(flags, "no-convert-bnk");
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
                auto success = convert(wem, outpath.string() + file_extension);
                if (!success) {
                  std::cout
                      << rang::fg::yellow << "Failed to convert "
                      << outpath.string() + file_extension
                      << " (Likely a metadata-only file. This WEM will likely "
                         "be found in the cache itself and not the soundbank.)"
                      << rang::fg::reset << std::endl;
                  // Don't return error because the rest may succeed
                }
                idx++;
              }
            } else if (file->name().substr(file->name().find_last_of(".")) ==
                       ".wem") {
              bool noconvert = has_flag(flags, "no-convert-wem");
              if (noconvert) {
                std::cout << rang::fg::cyan << "[" << file_index << "/"
                          << file_count << "] " << rang::fg::reset
                          << "Extracting " << file->name() << "..."
                          << rang::fg::reset << std::endl;
                std::ofstream fout(file->name());
                fout << file->data();
                continue;
              }
              std::string outpath =
                  file->name().substr(0, file->name().find_last_of(".")) +
                  ".ogg";
              std::cout << rang::fg::cyan << "[" << file_index << "/"
                        << file_count << "] " << rang::fg::reset
                        << "Extracting "
                        << file->name().substr(0,
                                               file->name().find_last_of(".")) +
                               ".ogg"
                        << rang::fg::reset << std::endl;
              auto success = convert(file->data(), outpath);
              if (!success) {
                // TODO: Add more rang usage
                std::cout << "Failed to convert " << path << std::endl;
              }
            }
          }
        } else { // write cache file
          std::ofstream of("soundspc.cache", std::ios::binary);
          std::vector<std::pair<std::string, std::string>> v;
          for (const auto &file : fs::directory_iterator(path)) {
            std::ifstream ifs(file.path().string(), std::ios::binary);
            std::stringstream ss;
            ss << ifs.rdbuf();
            v.push_back({file.path().filename().string(), ss.str()});
          }
          wwtools::w3sc::create(v, of);
        }
#pragma endregion CACHE      
      } else {
        print_help(argv[0]);
        return 1;
      }
    }
  }
}
