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

Node Tree::getRoot() const
{
    return root;
}

void Tree::select(const std::string &id, const std::string &key) const
{
    Node child;
    root.getChild(id, child);
    if (child != Node())
    {
        for (int i = 1; i < child.attribute_list.attr_names.size(); i++) //id is always at index 0
        {
            if (key == child.attribute_list.attr_names[i])
            {
                std::cout << child.attribute_list.attr_values[i] << '\n';
                return;
            }
        }
        std::cout << "No such key" << '\n';
    }
    else
    {
        std::cout << "No such id" << '\n';
    }
}

void Tree::set(const std::string &id, const std::string &key, const std::string &value)
{
    root.setAttribute(id, key, value);
}
void Tree::deleteAttr(const std::string &id, const std::string &key)
{
    if (key != "id")
        root.deleteAttribute(id, key);
    else
        std::cout << "You cannot delete id" << '\n';
}

void Tree::newchild(const std::string &id, const std::string &_tagname)
{
    root.newChild(id, _tagname);
}

std::ostream &operator<<(std::ostream &os, const Tree &tree)
{
    tree.root.print(os, 0);
    return os;
}