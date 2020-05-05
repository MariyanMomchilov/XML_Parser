#ifndef _NT
#define _NT
#include "Node.hpp"

class Tree
{
private:
    Node root;
    Node find(const std::string &id) const;
    friend std::ostream &operator<<(std::ostream &os, const Tree &tree);

public:
    Tree() = default;
    Tree(Node _root);
    Tree(const Tree &tree);
    Tree &operator=(const Tree &tree);
    ~Tree() = default;
    void select(const std::string &id, const std::string &key) const;
    void set(const std::string &id, const std::string &key, const std::string &value);
    void deleteAttr(const std::string &id, const std::string &key);
    void newchild(const std::string &id, const std::string &_tagname);
};

#endif
