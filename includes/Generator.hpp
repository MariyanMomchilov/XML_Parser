#ifndef _GEN
#define _GEN
#include "Node.hpp"
#include <fstream>
class Generator
{
public:
    static Node GenerateTree(std::ifstream &in);
    static Node TreeGenerator(const std::vector<std::string> &content, size_t &i);
};

#endif