#ifndef _NODE
#define _NODE
#include "IDFactory.hpp"
#include "AttributeList.hpp"
#include <iostream>

class Node
{
private:
    std::string tagname; //identificator
    AttributeList attribute_list;
    std::vector<Node> childs;
    std::string text;
    int _hasId() const;
    bool _isUniqueId(int index, const IDFactory &factory) const;
    void _addSpaces(std::ostream &os, int spaces) const;

public:
    Node() = default;
    Node(const std::string &_tagname, const AttributeList &_attribute_list, std::string _text);
    Node(const Node &other);
    Node &operator=(const Node &other);
    ~Node() = default;

    std::string getTagName() const;
    void addChild(const Node &child);
    void appendText(const std::string &_text);
    void assignUniqueId(IDFactory &factory);
    void getChild(const std::string &id, Node &result) const;
    void print(std::ostream &os, int spaces) const;
};

#endif