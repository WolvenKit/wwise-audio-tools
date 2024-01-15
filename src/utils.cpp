#include <algorithm>
#include <filesystem>
#include <string>

using std::filesystem::path;

inline std::string normalize_path(const std::string &x)
{
    path p(x);
    auto canonical = std::filesystem::weakly_canonical(p);
    return canonical.make_preferred().string();
}

inline bool is_filepath(const std::string &x)
{
    auto npath = path(normalize_path(x));

    return !npath.extension().empty();
}

inline bool is_directorypath(const std::string &x)
{
    auto npath = path(normalize_path(x));

    return npath.extension().empty();
}

inline int strcmp_insensitive(const std::string &x, const std::string &y)
{
    // * this is not the greatest implementation, no. It is just a tribute.
    // most correct way to implement this is probably via
    // https://icu.unicode.org/ we will use this to ward off the most
    // surface-level differences something like 'WEM' and 'wem' should be
    // treated equal if you get '𝔴𝔢𝔪' or 'ⓦⓔⓜ' from your OS - you have worse
    // problems than this

    std::string xlow, ylow;

    std::transform(x.begin(), x.end(), std::back_inserter(xlow),
                   [](unsigned char c) { return std::tolower(c); });
    std::transform(y.begin(), y.end(), std::back_inserter(ylow),
                   [](unsigned char c) { return std::tolower(c); });

    return x.compare(y);
}