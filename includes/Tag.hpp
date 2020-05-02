#ifndef _TAG
#define _TAG
#include <string>
#include <vector>
#include "AttributeList.hpp"
struct Tag
{
    std::string name = "";
    AttributeList attributes;
};

#endif