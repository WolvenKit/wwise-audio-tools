#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "cxxopts.hpp"
#include "kaitai/kaitaistream.h"
#include "kaitai/structs/bnk.h"
#include "kaitai/structs/w3sc.h"
#include "revorb/revorb.hpp"
#include "util/rang.hpp"
#include "utils.cpp"
#include "ww2ogg/ww2ogg.h"
#include "ww2ogg/wwriff.h"
#include "wwtools/bnk.hpp"
#include "wwtools/util/write.hpp"
#include "wwtools/w3sc.hpp"
#include "wwtools/wwtools.hpp"

namespace fs = std::filesystem;
using std::cout, std::cerr, std::endl, std::string, std::string_view;

enum class OPERATIONS
{
    UNKNOWN,
    WEM,
    BNK,
    CACHE
};

static OPERATIONS ops_to_operation(string_view ops)
{
    if (strcmp_insensitive(ops, "wem") == 0)
    {
        return OPERATIONS::WEM;
    }

    if (strcmp_insensitive(ops, "bnk") == 0)
    {
        return OPERATIONS::BNK;
    }

    if (strcmp_insensitive(ops, "cache") == 0)
    {
        return OPERATIONS::CACHE;
    }

    return OPERATIONS::UNKNOWN;
}

static string operation_to_ops(const OPERATIONS &operation)
{
    switch (operation)
    {
    case OPERATIONS::WEM:
        return "WEM";
    case OPERATIONS::BNK:
        return "BNK";
    case OPERATIONS::CACHE:
        return "CACHE";
    }

    return "UNKNOWN";
}

enum class TASKS
{
    UNKNOWN,
    INFO,
    BNK_EVENT,
    BNK_EXTRACT
};

struct Action
{
    OPERATIONS operation;
    TASKS task;
    std::string args;
};

cxxopts::Options setup_options()
{
    cxxopts::Options options("wwtools",
                             "a simple command line tool used to "
                             "convert Wwise WEM files to OGG files");

    // clang-format just doesn't want to work with chain operators
    // and this pattern is apparently very unique
    // clang-format off
    options.add_options()
        ("ops", "wem|bnk|cache", cxxopts::value<string>())
        // ("task", "(wem:event|extract)(bnk:read|write)", cxxopts::value<string>()->implicit_value(""))
        ("info", "", cxxopts::value<bool>()->default_value("false"))
        ("ipath", "Input Path Positional", 
            cxxopts::value<string>()->default_value(fs::current_path().string())
        )
        ("opath", "Output Path Positional", 
            cxxopts::value<string>()->default_value("")
        )
        ("h,help", "Print usage")
    ;

    options.positional_help(
        "<operation> [task=value] [input file/directory] [output file/directory]");

    options.add_options("bnk")
        ("event", "(task|task=event-id)", cxxopts::value<string>()->implicit_value(""))
        ("extract", "(task|task=event-id)", cxxopts::value<string>()->implicit_value(""))
        ("no-convert", "", cxxopts::value<bool>()->default_value("false"))
    ;

    options.add_options("cache")
        ("read", "(task)", cxxopts::value<bool>()->default_value("false"))
        ("write", "(task)", cxxopts::value<bool>()->default_value("false"))
        ("no-convert-wem", "", cxxopts::value<bool>()->default_value("false"))
        ("no-convert-bnk", "", cxxopts::value<bool>()->default_value("false"))
    ;
    // clang-format on

    options.parse_positional({"ops", "ipath", "opath"});

    return options;
}

static bool is_allowed_op(string_view ops)
{
    return ops_to_operation(ops) != OPERATIONS::UNKNOWN;
}

std::stringstream get_input_file(const fs::path &ifp, const Action &action)
{
    if (action.operation == OPERATIONS::WEM &&
        strcmp_insensitive(ifp.extension().string(), ".wem") != 0)
    {
        throw std::invalid_argument(
            "malformed ipath " + ifp.string() + " for operation " +
            operation_to_ops(action.operation));
    }

    if (action.operation == OPERATIONS::BNK &&
        strcmp_insensitive(ifp.extension().string(), ".bnk") != 0)
    {
        throw std::invalid_argument(
            "malformed ipath " + ifp.string() + " for operation " +
            operation_to_ops(action.operation));
    }

    // TODO: find cache variant

    std::ifstream bnk_in(ifp, std::ios::binary);
    std::stringstream bnk_data;
    bnk_data << bnk_in.rdbuf();

    return bnk_data;
}

std::string do_info(const std::stringstream &ifs, const Action &action)
{

    if (action.operation == OPERATIONS::WEM && action.task == TASKS::INFO)
    {
        return ww2ogg::wem_info(ifs.str());
    }

    if (action.operation == OPERATIONS::BNK && action.task == TASKS::INFO)
    {
        return wwtools::bnk::get_info(ifs.str());
    }

    if (action.operation == OPERATIONS::CACHE && action.task == TASKS::INFO)
    {
        return wwtools::w3sc::get_info(ifs.str());
    }

    return "";
}

/**
 * Converts a wem file to ogg
 */
std::string do_wem_to_ogg(const std::stringstream &ifs)
{
    string outdata = wwtools::wem_to_ogg(ifs.str());
    if (outdata.empty())
    {
        return "";
    }

    return outdata;
}

string do_bnk_event_id_info(const std::stringstream &ifs, const string &eid)
{
    auto result = wwtools::bnk::get_event_id_info(ifs.str(), eid);

    return result;
}

string do_bnk_event_list(const std::stringstream &ifs)
{
    auto result = wwtools::bnk::get_info(ifs.str());

    return result;
}

void write_output_file(const fs::path &ofp, string_view odata)
{
    std::ofstream fout(ofp, std::ios::binary);

    fout << odata;
}

void write_cout(string_view odata)
{
    cout << odata << endl;
}

/**
 * Ensures Output File from potential Folder
 */
fs::path get_ofp_from_op(const fs::path &ifp,
                         const fs::path &op,
                         const Action &action)
{
    if (is_filepath(op.string()))
    {
        return op;
    }

    if (!is_directorypath(op.string()))
    {
        throw std::invalid_argument(
            "malformed opath " + op.string() + " for operation " +
            operation_to_ops(action.operation));
    }

    if (action.operation == OPERATIONS::WEM)
    {
        if (action.task == TASKS::INFO)
        {
            return "";
        }

        auto target_filename =
            fs::path(ifp).replace_extension(fs::path("ogg")).filename();
        return (ifp.parent_path() / target_filename);
    }

    if (action.operation == OPERATIONS::BNK)
    {
        if (action.task == TASKS::INFO)
        {
            return "";
        }

        // list events
        if (action.task == TASKS::BNK_EVENT && action.args.length() == 0)
        {
            return "";
        }
    }

    // TODO: OPERATIONS::CACHE leads to n files output
    // this should probably handled somewhere else

    throw std::logic_error(
        "not implemented operation " + operation_to_ops(action.operation));
}

void process_file(const fs::path &ifp, const fs::path &op, const Action &action)
{
    auto istream = get_input_file(ifp, action);
    auto ofp = get_ofp_from_op(ifp, op, action);

    if (action.task == TASKS::INFO)
    {
        auto odata = do_info(istream, action);
        write_cout(odata);
        return;
    }

    if (action.operation == OPERATIONS::WEM)
    {
        auto odata = do_wem_to_ogg(istream);
        write_output_file(ofp, odata);
        return;
    }

    if (action.operation == OPERATIONS::BNK)
    {
        if (action.task == TASKS::BNK_EVENT && action.args.length() > 0)
        {
            auto odata = do_bnk_event_id_info(istream, action.args);
            write_cout(odata);
        }

        auto odata = do_bnk_event_list(istream);
        write_cout(odata);
        return;
    }

    // TODO: cache
}

int main(int argc, char *argv[])
{
    cxxopts::Options options = setup_options();
    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        cout << options.help() << endl;
        exit(0);
    }

    auto ops = result["ops"].as<string>();

    if (!is_allowed_op(ops))
    {
        cout << ops << " is not a supported operation. Try wem, bnk, or cache."
             << endl;
        return 1;
    }

    string task_args;
    TASKS whichtask = TASKS::UNKNOWN;

    if (result.count("event"))
    {
        whichtask = TASKS::BNK_EVENT;
        task_args = result["event"].as<string>();
    }

    if (result.count("info"))
    {
        whichtask = TASKS::INFO;
        task_args = "";
    }

    auto operation = ops_to_operation(ops);

    Action action = {
        operation, // OPERATIONS
        whichtask, // TASKS
        task_args  // args
    };

    auto ipath = result["ipath"].as<string>();
    auto opath = result["opath"].as<string>();

    try
    {
        if (is_directorypath(ipath))
        {
            for (const auto &file : fs::directory_iterator(ipath))
            {
                process_file(file.path(), fs::path(opath), action);
            }

            return EXIT_SUCCESS;
        }

        if (is_filepath(ipath))
        {
            process_file(fs::path(ipath), fs::path(opath), action);

            return EXIT_SUCCESS;
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_FAILURE;
}
