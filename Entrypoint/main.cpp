#include "../AvbtpToWav/AvtpToWav.h"
#include "../AvbtpToWav/Utils.h"

#include "windows.h"

#include <set>
#include <locale>
#include <codecvt>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <tuple>
#include <algorithm>

const static std::string kCurrentDir(MY_SOLUTIONDIR);
const static std::string kWiresharkBin = kCurrentDir + "HelperTools\\Wireshark\\tshark.exe";
const static std::string kSoxBin = kCurrentDir + "HelperTools\\sox-14-4-2\\sox.exe";
const static std::string kTempDir = kCurrentDir + "__temp__";

bool ListFiles(std::wstring path, std::wstring mask, std::vector<std::wstring>& files)
{
    HANDLE hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA ffd;
    std::wstring spec;
    std::stack<std::wstring> directories;

    directories.push(path);
    files.clear();

    while (!directories.empty())
    {
        path = directories.top();
        spec = path + L"\\" + mask;
        directories.pop();

        hFind = FindFirstFile(spec.c_str(), &ffd);
        if (hFind == INVALID_HANDLE_VALUE)
        {
            return false;
        }

        do
        {
            if (wcscmp(ffd.cFileName, L".") != 0 &&
                wcscmp(ffd.cFileName, L"..") != 0)
            {
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    directories.push(path + L"\\" + ffd.cFileName);
                }
                else
                {
                    files.push_back(path + L"\\" + ffd.cFileName);
                }
            }
        } while (FindNextFile(hFind, &ffd) != 0);

        if (GetLastError() != ERROR_NO_MORE_FILES)
        {
            FindClose(hFind);
            return false;
        }

        FindClose(hFind);
        hFind = INVALID_HANDLE_VALUE;
    }
    return true;
}


int main()
{
    AvbTools::AvtpToWav::getInstance()->init(kTempDir, kWiresharkBin, kSoxBin);

    std::vector<std::wstring> files;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(kTempDir);
    if (ListFiles(wide, L"*", files))
    {
        for (std::vector<std::wstring>::iterator it = files.begin(); it != files.end(); ++it)
        {
            const std::string file = converter.to_bytes(it->c_str());
            const std::tuple<std::string, std::string, std::string> pathInfo = AvbTools::Utils::GetPathInfo(file);
            const std::string dir = std::get<0>(pathInfo);
            
            std::string extension = std::get<2>(pathInfo);
            std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
            if (extension != "pcap")
            {
                continue;
            }

            AvbTools::AvtpToWav::getInstance()->convertToWav(file, dir);
        }
    }

    return 0;
}