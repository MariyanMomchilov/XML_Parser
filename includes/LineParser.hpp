#ifndef _LPARSER
#define _LPARSER
#include <string>
#include <fstream>
#include "Tag.hpp"
#include "AttributeList.hpp"

class LineParser
{
public:
    static std::vector<std::string> file_content(std::ifstream &file);
    static std::string remove_whitespace(const std::string &line);
    static bool hasOpenTag(const std::string &line);
    static bool hasClosingTag(const std::string &line);
    static bool isLeafTag(const std::string &line);
    static AttributeList parseAttr(const std::string &line, size_t &i);
    static Tag getOpenTag(const std::string &line);
};

#endif