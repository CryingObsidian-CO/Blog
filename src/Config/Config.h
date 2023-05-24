#ifndef _CONFIG_H
#define _CONFIG_H

#include <vector>
#include <fstream>
#include "logger.hpp"

class Config
{
    bool FindKey(const std::string &key);
    bool FindSection(const std::string &sectionName);

private:
    bool OpenFileRead(const std::string &filePath);
    bool WriteFile(const std::string &filePath, const std::vector<std::string> &vContent);

private:
    std::string value;
    std::string content;
    std::fstream fileStream;
    std::string filePath;
    bool canRead;
};

#endif