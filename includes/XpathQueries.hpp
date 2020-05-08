#ifndef _XPTH
#define _XPTH
#include "SlashOperand.hpp"
#include "Tree.hpp"

class XpathQueries
{
private:
    static bool hasAsymbol(int index, const std::string &str); // has @ symbol
public:
    static std::vector<SlashOperand> ParseQuery(std::string &query);
    static void getQuery(const std::string &id, std::string &query, const Tree &XMLtree);
};

#endif