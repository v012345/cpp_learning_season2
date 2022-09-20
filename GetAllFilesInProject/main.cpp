#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <set>
namespace fs = std::filesystem;

std::set<std::string> files;

void getFilesInDir(fs::path path, fs::path exclude_path)
{
    for (auto &&sub_path : fs::directory_iterator(path))
    {
        if (sub_path.is_directory() && sub_path != exclude_path)
        {
            getFilesInDir(sub_path, exclude_path);
        }
        else
        {
            if (sub_path.path().extension().string() == ".png" || sub_path.path().extension().string() == ".jpg")
            {
                files.insert(sub_path.path().filename().string());
            }
        }
    }
}

int main()
{
    std::cout << "递归项目目录 , 除tools文件夹" << std::endl;
    // std::cout << fs::current_path().string() << std::endl;

    auto project_path = fs::current_path().parent_path().parent_path();
    auto tool_path = fs::current_path().parent_path();

    getFilesInDir(project_path, tool_path);

    auto config_path = tool_path;
    config_path.append("config");
    if (!fs::is_directory(config_path))
    {
        fs::create_directory(config_path);
    }

    auto log_path = tool_path;
    log_path.append("log");
    if (!fs::is_directory(log_path))
    {
        fs::create_directory(log_path);
    }

    std::ofstream myfile;
    auto output = config_path;
    output.append("All Files.txt");
    myfile.open(output, std::ios::out);
    for (auto &file : files)
    {
        myfile << file << std::endl;
    }
    myfile.close();
    return 0;
}