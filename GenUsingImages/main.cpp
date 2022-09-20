#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <set>
#include <regex>

int main(int argc, char const *argv[])
{
    std::cout << "提取已经使用的文件" << std::endl;
    std::filesystem::path allImageLog = std::filesystem::current_path().parent_path().append("config").append("Compressed Log File.txt");
    if (!std::filesystem::is_regular_file(allImageLog))
    {
        std::cout << "缺少 Compressed Log File.txt" << std::endl;
        exit(1);
    }
    std::ifstream LogFile;
    LogFile.open(allImageLog);
    std::set<std::string> files;
    std::string line;
    std::smatch matches;
    std::regex rgx("/([^/]+\\.(?:png|jpg))$");
    std::regex json("/([^/]+\\.(?:json))$");
    std::regex replaceJson("(.*)json$");
    if (LogFile.is_open())
    {
        while (getline(LogFile, line))
        {

            if (std::regex_search(line, matches, json))
            {
                line = regex_replace(line, replaceJson, "$1png");
            }

            if (std::regex_search(line, matches, rgx))
            {
                for (size_t i = 1; i < matches.size(); ++i)
                {
                    files.insert(matches[i].str());
                }
            }
        }
        LogFile.close();
    }

    std::ofstream myfile;
    std::filesystem::path output = std::filesystem::current_path().parent_path().append("config").append("Using Images.txt");
    myfile.open(output, std::ios::out);
    for (auto &file : files)
    {
        if (file != "")
        {
            myfile << file << std::endl;
        }
    }
    myfile.close();
    return 0;
}