#include "Config.h"

bool Config::OpenFileRead(const std::string &filePath)
{
    std::fstream fileStream;
    fileStream.open("./conf" + filePath, std::ios::in);

    if (!fileStream.is_open())
    {
        Loggers::Error("Can't open file fail:{0} with read", filePath);
        return false;
    }
    return true;
}

bool Config::WriteFile(const std::string &filePath, const std::vector<std::string> &vContent)
{
    std::fstream fileStream;
    fileStream.open("./conf" + filePath, std::ios::out | std::ios::trunc);

    if (!fileStream.is_open())
    {
        Loggers::Error("Can't open file fail:{0} with write", filePath);
        return false;
    }
    for (size_t iIndex = 0; iIndex < vContent.size(); iIndex++)
    {
        fileStream << vContent[iIndex] << std::endl;
    }

    fileStream.close();
    return true;
}

bool Config::FindSection(const std::string &sectionName)
{
    if (content.find('[') != -1)
    {
        std::string sTemp = content.substr(content.find('[') + 1, content.find(']') - content.find('[') - 1);
        if (strcmp(sTemp.c_str(), sectionName.c_str()) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Config::FindKey(const std::string &key)
{
    size_t iDelePlace = content.find('//', 0);
    size_t iFindEqual = content.find('=', 0);
    if ((iDelePlace != -1 && iDelePlace < iFindEqual) || (iDelePlace != -1 && iFindEqual == -1) || iFindEqual == -1)
    {
        return false;
    }

    std::string sKey = content.substr(0, content.find('='));

    if (strcmp(sKey.c_str(), key.c_str()) == 0)
    {
        value = content.substr(content.find('=') + 1, content.length() - content.find('=') - 1);
        return true;
    }
    return false;
}