#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <set>

namespace AvbTools
{
    class Utils
    {
    public:
        static std::vector<std::string> SplitPath(const std::string& str, const std::set<char> delimiters);

        static std::tuple<std::string, std::string, std::string> GetPathInfo(const std::string & path);
    };
}