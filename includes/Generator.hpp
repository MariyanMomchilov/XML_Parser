#ifndef _GEN
#define _GEN
#include "Node.hpp"
#include "Tree.hpp"
#include <fstream>
class Generator
{
public:
    static Tree GenerateTree(std::fstream &in);
    static Node TreeGenerator(const std::vector<std::string> &content, size_t &i);
};

#endif