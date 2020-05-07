#ifndef _XPTH
#define _XPTH
#include "SlashOperand.hpp"
#include "Tree.hpp"

class XpathQueries
{
public:
    static std::vector<SlashOperand> ParseQuery(std::string &query);
    static void getQuery(std::string &query, const Tree &XMLtree);
};

#endif