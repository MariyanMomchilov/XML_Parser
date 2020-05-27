#ifndef _ATTRL
#define _ATTRL
#include <string>
#include <vector>

/// Класът съдържа атрибутите на даден елемент

struct AttributeList
{
    std::vector<std::string> attr_names;
    std::vector<std::string> attr_values;

    bool operator==(const AttributeList &other) const
    {
        return attr_names == other.attr_names && attr_values == other.attr_values;
    }
};

#endif