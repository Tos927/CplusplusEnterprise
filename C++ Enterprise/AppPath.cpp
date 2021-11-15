#include <iostream>

#include <SFML/Graphics.hpp>
#include <windows.h> 

std::string getAppPath()
{
    char cExeFilePath[256];
    GetModuleFileNameA(NULL, cExeFilePath, 256);
    std::string exeFilePath = cExeFilePath;
    int exeNamePos = exeFilePath.find_last_of("\\/");
    std::string appPath = exeFilePath.substr(0, exeNamePos + 1);

    return appPath;
}

std::string getAssetsPath()
{
    std::string assetsPath = getAppPath() + ("\\Assets/");
    return assetsPath;
}

sf::Font SetupAnyFont(std::string font)
{
    sf::Font arialttf;
    arialttf.loadFromFile(getAssetsPath() + font);

    return arialttf;
}