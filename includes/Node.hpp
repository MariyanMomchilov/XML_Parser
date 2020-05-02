#ifndef _NODE
#define _NODE
#include <string>
#include <vector>
#include "IDFactory.hpp"
#include "AttributeList.hpp"

class Node
{
private:
    std::string tagname; //identificator
    AttributeList attribute_list;
    std::vector<Node> childs;
    std::string text;
    int _hasId() const;
    bool _isUniqueId(int index, const IDFactory &factory) const;

public:
    Node() = default;
    Node(const std::string &_tagname, const AttributeList &_attribute_list, std::string _text);
    Node(const Node &other);
    Node &operator=(const Node &other);
    ~Node() = default;

    void addChild(const Node &child);
    void appendText(const std::string &_text);
    void assignUniqueId(IDFactory &factory);
};

#endif