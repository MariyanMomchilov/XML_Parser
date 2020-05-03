#include "includes/Tree.hpp"

Tree::Tree(Node _root) : root(_root) {}
Node Tree::find(const std::string &id) const
{
    Node result;
    root.getChild(id, result);
    return result;
}

Tree::Tree(const Tree &tree)
{
    root = tree.root;
}
Tree &Tree::operator=(const Tree &tree)
{
    if (this != &tree)
    {
        root = tree.root;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Tree &tree)
{
    tree.root.print(os, 0);
    return os;
}