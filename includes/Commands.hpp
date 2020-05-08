#ifndef CMD_H
#define CMD_H

#include <iostream>
#include <fstream>
#include "Tree.hpp"
#include "XpathQueries.hpp"
class Commands
{
private:
    std::fstream file;
    std::string filename;
    void _open(std::string &, int &);
    std::string getNextCMD(std::string &, int &);
    Tree XMLtree;

public:
    Commands() = default;
    Commands(const std::string &) = delete;
    void process(std::string &);
    void write();
    void read();
    void write(std::ostream &is);
    ~Commands() = default;
};

#endif