#include "Utils.h"

std::vector<std::string> AvbTools::Utils::SplitPath(const std::string & str, const std::set<char> delimiters)
{
    std::vector<std::string> result;

    char const* pch = str.c_str();
    char const* start = pch;
    for (; *pch; ++pch)
    {
        if (delimiters.find(*pch) != delimiters.end())
        {
            if (start != pch)
            {
                std::string str(start, pch);
                result.push_back(str);
            }
            else
            {
                result.push_back("");
            }
            start = pch + 1;
        }
    }
    result.push_back(start);

    return result;
}

std::tuple<std::string, std::string, std::string> AvbTools::Utils::GetPathInfo(const std::string & path)
{
    auto res = SplitPath(path, { '\\' });
    std::string dir;
    for (int i = 0; i <= res.size() - 3; ++i)
    {
        dir += res[i] + "\\";
    }
    dir += res[res.size() - 2];
    std::string name = res.back();
    std::string ext = res.back().substr(res.back().find_last_of(".") + 1);
    return std::make_tuple<std::string, std::string, std::string>(std::string(dir), std::string(name), std::string(ext));
}