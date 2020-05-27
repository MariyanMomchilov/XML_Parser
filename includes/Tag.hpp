#ifndef _TAG
#define _TAG
#include <string>
#include <vector>
#include "AttributeList.hpp"

/// Класът описва таг-частта на даден Node
struct Tag
{
    std::string name = "";
    AttributeList attributes;
};

#endif