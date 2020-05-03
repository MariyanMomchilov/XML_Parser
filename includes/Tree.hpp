#ifndef _NT
#define _NT
#include "Node.hpp"

class Tree
{
private:
    Node root;
    //Node find(const std::string &id) const;
    friend std::ostream &operator<<(std::ostream &os, const Tree &tree);

public:
    Tree() = default;
    Tree(Node _root);
    Tree(const Tree &tree);
    Tree &operator=(const Tree &tree);
    ~Tree() = default;
    Node find(const std::string &id) const; //premesti q private
};

#endif
