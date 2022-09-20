#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <set>
#include <map>
#include <regex>
std::map<std::string, bool> unUsedImages;
std::filesystem::path red_png;
std::filesystem::path red_jpg;
std::ofstream targetImage;
void replaceFilesInDir(std::filesystem::path path, std::filesystem::path exclude_path)
{
    for (auto &&sub_path : std::filesystem::directory_iterator(path))
    {
        if (sub_path.is_directory() && sub_path != exclude_path)
        {
            if (sub_path.path().filename().string() != "image" && sub_path.path().filename().string() != "animation")
            {
                replaceFilesInDir(sub_path, exclude_path);
            }
        }
        else
        {
            if (sub_path.path().extension().string() == ".png" || sub_path.path().extension().string() == ".jpg")
            {
                if (unUsedImages.find(sub_path.path().filename().string()) != unUsedImages.end())
                {
                    // size += std::filesystem::file_size(sub_path);
                    targetImage.open(sub_path.path(), std::ios::binary);
                    if (targetImage.is_open())
                    {
                        if (sub_path.path().extension().string() == ".png")
                        {
                            std::ifstream png(red_png, std::ios::binary);

                            targetImage << png.rdbuf();
                            png.close();
                        }
                        else
                        {
                            std::ifstream jpg(red_jpg, std::ios::binary);
                            targetImage << jpg.rdbuf();
                            jpg.close();
                        }
                        targetImage.close();
                    }
                }
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    std::filesystem::path UnUsed = std::filesystem::current_path().parent_path().append("config").append("UnUsed Images.txt");
    std::ifstream files(UnUsed);
    if (!files.is_open())
    {
        std::cout << "miss UnUsed Images.txt" << std::endl;
        return 0;
    }
    std::string line = "";
    while (getline(files, line))
    {
        if (line != "")
        {
            unUsedImages.insert(std::make_pair(line, true));
        }
    }
    files.close();
    red_png = std::filesystem::current_path().parent_path().append("a_read_point_to_replace_image_that_unused_release.png");
    red_jpg = std::filesystem::current_path().parent_path().append("a_read_point_to_replace_image_that_unused_release.jpg");
    auto project_path = std::filesystem::current_path().parent_path().parent_path();
    auto tool_path = std::filesystem::current_path().parent_path();
    replaceFilesInDir(project_path, tool_path);

    return 0;
}