#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <set>
#include <map>
#include <regex>
std::set<std::string> files;

int main(int argc, char const *argv[])
{

    std::cout << "过滤不使用的图片" << std::endl;

    std::map<std::string, bool> allImages;
    std::filesystem::path allImageLog = std::filesystem::current_path().parent_path().append("config").append("All Files.txt");

    if (!std::filesystem::is_regular_file(allImageLog))
    {
        std::cout << "缺少 All Files.txt" << std::endl;
        exit(1);
    }
    std::ifstream txtFile;
    txtFile.open(allImageLog);
    std::string line;
    if (txtFile.is_open())
    {
        while (getline(txtFile, line))
        {
            if (line != "")
            {
                allImages.insert(std::make_pair(line, false));
            }
        }
        txtFile.close();
    }

    std::filesystem::path usingImageLog = std::filesystem::current_path().parent_path().append("config").append("Using Images.txt");
    if (!std::filesystem::is_regular_file(usingImageLog))
    {
        std::cout << "缺少 Using Images.txt" << std::endl;
        exit(1);
    }
    std::map<std::string, bool>::iterator it;

    std::ifstream uesedFiles;
    uesedFiles.open(usingImageLog);

    if (uesedFiles.is_open())
    {
        while (getline(uesedFiles, line))
        {
            it = allImages.find(line);
            if (it != allImages.end())
            {
                it->second = true;
            }
        }
        uesedFiles.close();
    }

    std::ofstream unUsingImages;
    std::filesystem::path unusedImageLog = std::filesystem::current_path().parent_path().append("config").append("UnUsed Images.txt");
    unUsingImages.open(unusedImageLog, std::ios::out);
    for (auto &image : allImages)
    {
        if (!image.second)
        {
            unUsingImages << image.first << std::endl;
        }
    }
    unUsingImages.close();
    return 0;
}