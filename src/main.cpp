#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "cxxopts/cxxopts.hpp"
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

std::string normalize_path(const std::string &x)
{
    fs::path path(x);
    auto canonical = fs::weakly_canonical(path);
    return canonical.make_preferred().string();
}

bool is_filepath(std::string x)
{
    auto npath = fs::path(normalize_path(x));

    return !npath.extension().empty();
}

bool is_directorypath(std::string x)
{
    auto npath = fs::path(normalize_path(x));

    return npath.extension().empty();
}

void setup_options(cxxopts::Options &options)
{
    options.add_options()("ops", "Operation Positional", cxxopts::value<std::string>())("info", "", cxxopts::value<bool>()->default_value("false"))("ipath", "Input Path Positional", cxxopts::value<std::string>()->default_value(fs::current_path().string()))("opath", "Output Path Positional", cxxopts::value<std::string>()->default_value(""))("h,help", "Print usage");

    options.positional_help("<wem|bnk|cache> [input file/directory] [output file/directory]");

    options.add_options("bnk")("event", "", cxxopts::value<bool>()->default_value("false"))("extract", "", cxxopts::value<bool>()->default_value("false"))("no-convert", "", cxxopts::value<bool>()->default_value("false"));

    options.add_options("cache")("read", "", cxxopts::value<bool>()->default_value("false"))("write", "", cxxopts::value<bool>()->default_value("false"))("no-convert-wem", "", cxxopts::value<bool>()->default_value("false"))("no-convert-bnk", "", cxxopts::value<bool>()->default_value("false"));

    options.parse_positional({"ops", "ipath", "opath"});
}

bool is_allowed_op(std::string &ops)
{
    std::unordered_set<std::string> allowed_ops = {
        "wem", "bnk", "cache"};

    return allowed_ops.find(ops) != allowed_ops.end();
}

bool convert_wem_to_ogg(const std::string &indata, const std::string &outpath)
{

    std::string outdata = wwtools::wem_to_ogg(indata);
    if (outdata.empty())
    {
        return false;
    }

    std::ofstream fout(outpath, std::ios::binary);
    fout << outdata;

    return true;
}

std::tuple<std::string, std::string> ensure_in_out_filepaths(std::string ipath, std::string opath)
{
    if (!is_filepath(ipath))
    {
        throw std::invalid_argument("ipath needs to be a filepath");
    }

    if (opath.empty())
    {
        auto outpath = fs::path(ipath).replace_extension("ogg").string();

        // .\fu.wem, .\fu.ogg
        return std::make_tuple(ipath, outpath);
    }

    if (is_filepath(opath))
    {
        // .\fu.wem .\b\ar.ogg
        return std::make_tuple(ipath, opath);
    }

    if (is_directorypath(opath))
    {
        if (!fs::is_directory(opath))
        {
            throw std::invalid_argument("opath not an existing directory");
        }

        auto outpath = (fs::path(opath) / fs::path(ipath).replace_extension("ogg").filename()).string();

        // .\fu.wem .\b\fu.ogg
        return std::make_tuple(ipath, outpath);
    }

    throw std::invalid_argument("opath malformed");
}

int main(int argc, char *argv[])
{
    cxxopts::Options options("wwtools", "a simple command line tool used to convert Wwise WEM files to OGG files");

    setup_options(options);
    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    auto ops = result["ops"].as<std::string>();

    if (!is_allowed_op(ops))
    {
        std::cout << ops << " is not a supported operation. Try wem, bnk, or cache." << std::endl;
        return 1;
    }

    auto ipath = result["ipath"].as<std::string>();
    auto opath = result["opath"].as<std::string>();

    //  Combinations:
    // - No In or Out
    //   _defaults to all matching files in current directory_
    // - File to File
    // - File to Directory
    // - Directory to Directory
    //   _same as first_

    auto inputIsFile = is_filepath(ipath);
    auto inputIsDirectory = is_directorypath(ipath);

    auto success = FALSE;

#pragma region WEM
    if (strcasecmp(ops.c_str(), "wem") == 0)
    {
        std::map<std::string, std::string> queuedFiles;

        if (inputIsFile)
        {
            auto ct = ensure_in_out_filepaths(ipath, opath);

            queuedFiles[std::get<0>(ct)] = std::get<1>(ct);
        }
        else if (inputIsDirectory)
        {
            for (const auto &file : fs::directory_iterator(ipath))
            {

                if (strcasecmp(file.path().extension().string().c_str(), ".wem") == 0)
                {
                    auto ct = ensure_in_out_filepaths(file.path().string(), opath);

                    queuedFiles[std::get<0>(ct)] = std::get<1>(ct);
                }
            }
        }
        else
        {
            // input is garbage
        }

        // for (const auto &ct : queuedFiles) {
        std::map<std::string, std::string>::iterator qfi = queuedFiles.begin();

        while (qfi != queuedFiles.end())
        {
            try
            {
                std::ifstream filein(qfi->first, std::ios::binary);
                std::stringstream indata;
                indata << filein.rdbuf();

                success = convert_wem_to_ogg(indata.str(), qfi->second);

                if (!success)
                {
                    std::cerr << "Failed to convert " << qfi->first << std::endl;
                }
                else
                {
                    std::cout << "Converted " << qfi->first << " to " << qfi->second << std::endl;
                }

                ++qfi;
            }
            catch (std::invalid_argument &e)
            {
                std::cerr << e.what() << std::endl;

                return EXIT_FAILURE;
            }
        }
    }
#pragma endregion WEM

#pragma region BNK

#pragma endregion BNK

#pragma region CACHE
#pragma endregion CACHE
    // for (const auto &file : fs::directory_iterator(fs::path(result["ipath"].as<std::string>()))) {
    //     std::cout << file.path() << std::endl;
    // }

    return EXIT_SUCCESS;

    //   // TODO: Add more descriptive comments regarding as much as possible
    //   std::pair<std::vector<std::string>, bool> flags_raw = get_flags(argc, argv);
    //   if (flags_raw.second) { // If there's an error...
    //     return 1;
    //   }
    //   std::vector<std::string> flags = flags_raw.first;
    //   if (has_flag(flags, "help")) {
    //     print_help();
    //     return 0;
    //   }
    //   if (argc < 2) {
    //     // If there is no input file, convert all WEM files in the current directory
    //     bool wemExists = false;
    //     for (const auto &file : fs::directory_iterator(fs::current_path())) {
    //       if (file.path().extension() == ".wem") {
    //         wemExists = true;
    //         std::cout << "Converting " << file.path() << "..." << std::endl;

    //         std::ifstream filein(file.path().string(), std::ios::binary);
    //         std::stringstream indata;
    //         indata << filein.rdbuf();

    //         // TODO: Add function for changing extension
    //         std::string outpath = file.path().string().substr(
    //                                   0, file.path().string().find_last_of(".")) +
    //                               ".ogg";

    //         auto success = convert(indata.str(), outpath);
    //         if (!success) {
    //           std::cerr << "Failed to convert " << file.path() << std::endl;
    //           return 1;
    //         }
    //       }
    //     }
    //     if (!wemExists) {
    //       print_help("No WEM files found in the current directory!", argv[0]);
    //     }
    //   } else {
    //     if (argc < 3) {
    //       print_help("Missing arguments!", argv[0]);
    //       return 1;
    //     } else {
    // #pragma region WEM
    //       if (strcmp(argv[1], "wem") == 0) {
    //         auto path = std::string(argv[2]);

    //         std::ifstream filein(path, std::ios::binary);
    //         std::stringstream indata;
    //         indata << filein.rdbuf();
    //         if (has_flag(flags, "info")) {
    //           std::cout << ww2ogg::wem_info(indata.str());
    //           return 0;
    //         }
    //         std::string outpath = path.substr(0, path.find_last_of(".")) + ".ogg";

    //         std::cout << "Extracting " << outpath << "..." << std::endl;
    //         auto success = convert(indata.str(), outpath);
    //         if (!success) {
    //           std::cerr << "Failed to convert " << path << std::endl;
    //           return 1;
    //         }
    // #pragma endregion WEM
    // #pragma region BNK
    //       } else if (strcmp(argv[1], "bnk") == 0) {
    //         auto path = std::string(argv[3]);

    //         std::ifstream filein(path, std::ios::binary);
    //         std::stringstream indata;
    //         indata << filein.rdbuf();

    //         if (has_flag(flags, "info")) {
    //           std::cout << wwtools::bnk::get_info(indata.str());
    //           return EXIT_SUCCESS;
    //         }

    //         if (argc < 4) {
    //           print_help("You must specify whether to extract or find an event as "
    //                      "well as the input!",
    //                      argv[0]);
    //           return EXIT_FAILURE;
    //         }

    //         if (strcmp(argv[2], "event") != 0 && strcmp(argv[2], "extract") != 0) {
    //           print_help("Incorrect value for read or write!", argv[0]);
    //           return EXIT_FAILURE;
    //         }

    //         auto bnk_path = std::string(argv[3]);

    //         if (strcmp(argv[2], "event") == 0) {
    //           if (argc < 4) {
    //             print_help("Not enough arguments for finding an event!");
    //             return EXIT_FAILURE;
    //           }

    //           std::string in_event_id;
    //           if (argc >= 5)
    //             in_event_id = argv[4];

    //           std::ifstream bnk_in(bnk_path, std::ios::binary);
    //           std::stringstream indata;
    //           indata << bnk_in.rdbuf();

    //           std::cout << wwtools::bnk::get_event_id_info(indata.str(),
    //                                                        in_event_id);
    //         } else if (strcmp(argv[2], "extract") == 0) {
    //           std::vector<std::string> wems;
    //           // populate WEMs vector with data
    //           wwtools::bnk::extract(indata.str(), wems);
    //           kaitai::kstream ks(indata.str());
    //           bnk_t bnk(&ks);
    //           // create directory with name of bnk file, no extension
    //           fs::create_directory(path.substr(0, path.find_last_of(".")));
    //           int idx = 0;
    //           for (auto wem : wems) {
    //             fs::path outdir(path.substr(0, path.find_last_of(".")));
    //             std::ifstream bnk_in(bnk_path, std::ios::binary);
    //             std::stringstream indata;
    //             indata << bnk_in.rdbuf();
    //             bool noconvert = has_flag(flags, "no-convert");
    //             // TODO: maybe make a function to return an array of IDs at index
    //             // instead of parsing the file every loop
    //             fs::path filename(
    //                 wwtools::bnk::get_wem_id_at_index(indata.str(), idx));
    //             fs::path outpath = outdir / filename;
    //             std::string file_extension = noconvert ? ".wem" : ".ogg";
    //             std::cout << rang::fg::cyan << "[" << idx + 1 << "/" << wems.size()
    //                       << "] " << rang::fg::reset << "Extracting "
    //                       << outpath.string() + file_extension << "..."
    //                       << std::endl;
    //             if (noconvert) {
    //               std::ofstream of(outpath.string() + file_extension, std::ios::binary);
    //               of << wem;
    //               of.close();
    //               idx++;
    //               continue;
    //             }
    //             auto success = convert(wem, outpath.string() + file_extension);
    //             if (!success) {
    //               std::cout << "Failed to convert "
    //                         << outpath.string() + file_extension << std::endl;
    //               // Don't return error because others may succeed
    //             }
    //             idx++;
    //           }
    //         }
    // #pragma endregion BNK
    // #pragma region CACHE
    //       } else if (strcmp(argv[1], "cache") == 0) {
    //         if (argc < 4) {
    //           print_help(
    //               "You must specify whether to read or write as well as the input!",
    //               argv[0]);
    //           return EXIT_FAILURE;
    //         }

    //         if (strcmp(argv[2], "read") != 0 && strcmp(argv[2], "write") != 0) {
    //           print_help("Incorrect value for read or write!", argv[0]);
    //           return EXIT_FAILURE;
    //         }

    //         auto path = std::string(argv[3]);

    //         if (strcmp(argv[2], "read") == 0) {
    //           std::ifstream filein(path, std::ios::binary);
    //           std::stringstream indata;
    //           indata << filein.rdbuf();
    //           if (has_flag(flags, "info")) {
    //             std::cout << wwtools::w3sc::get_info(indata.str());
    //             return 0;
    //           }

    //           kaitai::kstream ks(indata.str());

    //           w3sc_t cache(&ks);

    //           int file_index = 0;
    //           int file_count = cache.file_infos()->size();
    //           for (auto file : *cache.file_infos()) {
    //             file_index++;
    //             if (file->name().substr(file->name().find_last_of(".")) == ".bnk") {
    //               std::cout << rang::fg::cyan << "[" << file_index << "/"
    //                         << file_count << "] " << rang::fg::reset
    //                         << "Extracting " << file->name() << "..." << std::endl;
    //               // Currently unable to read music files
    //               if (file->name().find("music_") != std::string::npos ||
    //                   file->name().find("vo_") != std::string::npos ||
    //                   file->name().find("qu_") != std::string::npos ||
    //                   file->name().find("mutations_") != std::string::npos) {
    //                 continue;
    //               }

    //               kaitai::kstream bnk_ks(file->data());
    //               bnk_t bnk(&bnk_ks);
    //               std::vector<std::string> wems;
    //               // Populate WEMs vector with data
    //               wwtools::bnk::extract(file->data(), wems);
    //               // Create directory with name of bnk file, no extension
    //               fs::create_directory(
    //                   file->name().substr(0, file->name().find_last_of(".")));
    //               int idx = 0;
    //               for (auto wem : wems) {
    //                 fs::path outdir(
    //                     file->name().substr(0, file->name().find_last_of(".")));
    //                 std::stringstream ss;
    //                 // ss << bnk.data_index()->data()->indices()->at(idx)->id();
    //                 bool noconvert = has_flag(flags, "no-convert-bnk");
    //                 fs::path filename(ss.str());
    //                 fs::path outpath = outdir / filename;
    //                 std::string file_extension = noconvert ? ".wem" : ".ogg";
    //                 if (noconvert) {
    //                   std::ofstream of(outpath.string() + file_extension, std::ios::binary);
    //                   of << wem;
    //                   of.close();
    //                   idx++;
    //                   continue;
    //                 }
    //                 auto success = convert(wem, outpath.string() + file_extension);
    //                 if (!success) {
    //                   std::cout
    //                       << rang::fg::yellow << "Failed to convert "
    //                       << outpath.string() + file_extension
    //                       << " (Likely a metadata-only file. This WEM will likely "
    //                          "be found in the cache itself and not the soundbank.)"
    //                       << rang::fg::reset << std::endl;
    //                   // Don't return error because the rest may succeed
    //                 }
    //                 idx++;
    //               }
    //             } else if (file->name().substr(file->name().find_last_of(".")) ==
    //                        ".wem") {
    //               bool noconvert = has_flag(flags, "no-convert-wem");
    //               if (noconvert) {
    //                 std::cout << rang::fg::cyan << "[" << file_index << "/"
    //                           << file_count << "] " << rang::fg::reset
    //                           << "Extracting " << file->name() << "..."
    //                           << rang::fg::reset << std::endl;
    //                 std::ofstream fout(file->name(), std::ios::binary);
    //                 fout << file->data();
    //                 continue;
    //               }
    //               std::string outpath =
    //                   file->name().substr(0, file->name().find_last_of(".")) +
    //                   ".ogg";
    //               std::cout << rang::fg::cyan << "[" << file_index << "/"
    //                         << file_count << "] " << rang::fg::reset
    //                         << "Extracting "
    //                         << file->name().substr(0,
    //                                                file->name().find_last_of(".")) +
    //                                ".ogg"
    //                         << rang::fg::reset << std::endl;
    //               auto success = convert(file->data(), outpath);
    //               if (!success) {
    //                 // TODO: Add more rang usage
    //                 std::cout << "Failed to convert " << path << std::endl;
    //               }
    //             }
    //           }
    //         } else { // write cache file
    //           std::ofstream of("soundspc.cache", std::ios::binary);
    //           std::vector<std::pair<std::string, std::string>> v;
    //           for (const auto &file : fs::directory_iterator(path)) {
    //             std::ifstream ifs(file.path().string(), std::ios::binary);
    //             std::stringstream ss;
    //             ss << ifs.rdbuf();
    //             v.push_back({file.path().filename().string(), ss.str()});
    //           }
    //           wwtools::w3sc::create(v, of);
    //         }
    // #pragma endregion CACHE
    //       } else {
    //         print_help(argv[0]);
    //         return 1;
    //       }
    //     }
    //   }
}
