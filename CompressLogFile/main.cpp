#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <set>
#include <regex>
std::set<std::string> files;

void compressLogFiles(std::filesystem::path log_path)
{
    std::ifstream LogFile;
    for (auto &&log_file : std::filesystem::directory_iterator(log_path))
    {
        if (log_file.is_regular_file() && log_file.path().extension().string() == ".txt")
        {
            LogFile.open(log_file.path());
            std::string line;
            if (LogFile.is_open())
            {
                while (getline(LogFile, line))
                {
                    files.insert(line);
                }
                LogFile.close();
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    // std::cout << "处理日志文件" << std::endl;
    std::cout << "处理日志文件" << std::endl;
    if (!std::filesystem::is_directory(std::filesystem::current_path().parent_path().append("log")))
    {
        std::filesystem::create_directory(std::filesystem::current_path().parent_path().append("log"));
    }
    if (!std::filesystem::is_directory(std::filesystem::current_path().parent_path().append("config")))
    {
        std::filesystem::create_directory(std::filesystem::current_path().parent_path().append("config"));
    }
    if (std::filesystem::is_regular_file(std::filesystem::current_path().parent_path().append("config").append("Compressed Log File.txt")))
    {
        if (std::filesystem::is_regular_file(std::filesystem::current_path().parent_path().append("log").append("Compressed Log File.txt")))
        {
            std::filesystem::remove(std::filesystem::current_path().parent_path().append("log").append("Compressed Log File.txt"));
        }

        std::filesystem::copy_file(
            std::filesystem::current_path().parent_path().append("config").append("Compressed Log File.txt"),
            std::filesystem::current_path().parent_path().append("log").append("Compressed Log File.txt"),
            std::filesystem::copy_options::overwrite_existing);
    }

    compressLogFiles(std::filesystem::current_path().parent_path().append("log"));
    std::ofstream myfile;
    myfile.open(std::filesystem::current_path().parent_path().append("config").append("Compressed Log File.txt"), std::ios::out);
    std::smatch matches;
    std::regex rgx("/");
    for (auto &&file : files)
    {
        if (std::regex_search(file, matches, rgx))
        {
            myfile << file << std::endl;
        }
    }
    myfile.close();
    return 0;
}