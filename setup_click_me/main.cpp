#include <iostream>
int main(int argc, char const *argv[])
{

#if defined(_WIN64) || defined(_WIN32) || defined(__CYGWIN__)
    system("chcp 65001");
#endif

    if (!system(".\\GetAllFilesInProject.exe"))
    {

        std::cout << "GetAllFilesInProject.exe 完成" << std::endl;
    }
    else
    {
        exit(1);
    }
    if (!system(".\\CompressLogFile.exe"))
    {

        std::cout << "CompressLogFile.exe 完成" << std::endl;
    }
    else
    {
        exit(1);
    }
    if (!system(".\\GenUsingImages.exe"))
    {

        std::cout << "GenUsingImages.exe 完成" << std::endl;
    }
    else
    {
        exit(1);
    }
    if (!system(".\\FilterUnusedImages.exe"))
    {

        std::cout << "FilterUnusedImages.exe 完成" << std::endl;
    }
    else
    {
        exit(1);
    }

    std::cout << "把 config 目录加入 git 暂存区" << std::endl;
    system("git add ..\\config");
    std::cout << "提交 config 目录 save_config" << std::endl;
    system("git commit -m save_config");

    std::cout << "完成" << std::endl;
    std::cout << "请手动点击 ReplaceAnimation.exe" << std::endl;
    system("pause");
    return 0;
}