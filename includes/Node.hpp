#ifndef _NODE
#define _NODE
#include "IDFactory.hpp"
#include "AttributeList.hpp"
#include <iostream>

class SlashOperand;

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
    void _printAttributes(std::ostream &os) const;
    friend class Tree;

public:
    Node() = default;
    Node(const std::string &_tagname, const AttributeList &_attribute_list, std::string _text);
    Node(const Node &other);
    Node &operator=(const Node &other);
    bool operator==(const Node &other) const;
    bool operator!=(const Node &other) const;
    ~Node() = default;

    size_t getChildSize() const;
    Node getChild(int i) const;
    std::string getText() const;
    std::string getTagName() const;
    std::string getAttrValue(const std::string &attr_name) const;
    void addChild(const Node &child);
    void appendText(const std::string &_text);
    void assignUniqueId(IDFactory &factory);
    void getChild(const std::string &id, Node &result) const;
    void setAttribute(const std::string &id, const std::string &key, const std::string &value);
    void deleteAttribute(const std::string &id, const std::string &key);
    void newChild(const std::string &id, const std::string &_tagname);
    void print(std::ostream &os, int spaces) const;
    void updateChildList(const SlashOperand &operand, std::vector<Node> &list) const;
};

#endif