#include "includes/Node.hpp"
#include "includes/SlashOperand.hpp"

Node::Node(const std::string &_tagname, const AttributeList &_attribute_list, std::string _text) : tagname(_tagname), attribute_list(_attribute_list), text(_text) {}

Node::Node(const Node &other)
{
    tagname = other.tagname;
    attribute_list = other.attribute_list;
    childs = other.childs;
    text = other.text;
}
Node &Node::operator=(const Node &other)
{
    if (this != &other)
    {
        tagname = other.tagname;
        attribute_list = other.attribute_list;
        childs = other.childs;
        text = other.text;
    }
    return *this;
}

bool Node::operator==(const Node &other) const
{
    return tagname == other.tagname && attribute_list == other.attribute_list && childs == other.childs && text == other.text;
}

bool Node::operator!=(const Node &other) const
{
    return !operator==(other);
}

bool Node::_isUniqueId(int index, const IDFactory &factory) const
{
    return factory.isUnique(attribute_list.attr_values[index]);
}

int Node::_hasId() const
{
    for (int i = 0; i < attribute_list.attr_names.size(); i++)
    {
        if (attribute_list.attr_names[i] == "id")
            return i;
    }
    return -1;
}

size_t Node::getChildSize() const
{
    return childs.size();
}
Node Node::getChild(int i) const
{
    if (i < childs.size())
        return childs[i];
}

std::string Node::getText() const
{
    return text;
}

std::string Node::getTagName() const
{
    return tagname;
}

std::string Node::getAttrValue(const std::string &attr_name) const
{
    for (int i = 0; i < attribute_list.attr_names.size(); i++)
    {
        if (attribute_list.attr_names[i] == attr_name)
        {
            return attribute_list.attr_values[i];
        }
    }
    return "";
}

void Node::addChild(const Node &child)
{
    childs.push_back(child);
}

void Node::appendText(const std::string &_text)
{
    text += _text;
}

void Node::assignUniqueId(IDFactory &factory)
{
    int index = _hasId();
    if (index != -1)
    {
        if (_isUniqueId(index, factory))
        {
            factory.addId(attribute_list.attr_values[index]);
        }
        else
        {
            attribute_list.attr_values[index] = factory.transformToUnique(attribute_list.attr_values[index]);
        }
    }
    else
    {
        std::vector<std::string>::iterator it_names = attribute_list.attr_names.begin();
        std::vector<std::string>::iterator it_values = attribute_list.attr_values.begin();
        attribute_list.attr_names.insert(it_names, "id");
        attribute_list.attr_values.insert(it_values, factory.getUnique());
    }
}

void Node::getChild(const std::string &id, Node &result) const
{
    if (attribute_list.attr_names[0] == "id" && attribute_list.attr_values[0] == id)
    {
        result = *this;
        return;
    }
    for (int i = 0; i < childs.size(); i++)
    {
        childs[i].getChild(id, result);
    }
}

void Node::setAttribute(const std::string &id, const std::string &key, const std::string &value)
{
    if (attribute_list.attr_names[0] == "id" && attribute_list.attr_values[0] == id)
    {
        for (int i = 0; i < attribute_list.attr_names.size(); i++)
        {
            if (attribute_list.attr_names[i] == key)
            {
                attribute_list.attr_values[i] = value;
                std::cout << "Successful" << '\n';
                return;
            }
        }
    }
    for (int i = 0; i < childs.size(); i++)
    {
        childs[i].setAttribute(id, key, value);
    }
}

void Node::deleteAttribute(const std::string &id, const std::string &key)
{
    if (attribute_list.attr_names[0] == "id" && attribute_list.attr_values[0] == id)
    {
        for (int i = 0; i < attribute_list.attr_names.size(); i++)
        {
            if (attribute_list.attr_names[i] == key)
            {
                attribute_list.attr_names.erase(attribute_list.attr_names.begin() + i);
                attribute_list.attr_values.erase(attribute_list.attr_values.begin() + i);
                std::cout << "Successfull" << '\n';
                return;
            }
        }
    }
    for (int i = 0; i < childs.size(); i++)
    {
        childs[i].deleteAttribute(id, key);
    }
}

void Node::_addSpaces(std::ostream &os, int spaces) const
{
    for (int i = 0; i < spaces; i++)
        os << " ";
}

void Node::_printAttributes(std::ostream &os) const
{
    if (attribute_list.attr_names.size() != 0)
        os << " ";
    for (int k = 0; k < attribute_list.attr_names.size(); k++) //print attributes TO DO make this a function
    {
        if (k != attribute_list.attr_names.size() - 1)
            os << attribute_list.attr_names[k] << "=" << '\"' << attribute_list.attr_values[k] << '\"' << " ";
        else
            os << attribute_list.attr_names[k] << "=" << '\"' << attribute_list.attr_values[k] << '\"';
    }
}

void Node::newChild(const std::string &id, const std::string &_tagname)
{
    if (attribute_list.attr_names[0] == "id" && attribute_list.attr_values[0] == id)
    {
        Node child_node;
        child_node.tagname = _tagname;
        child_node.attribute_list.attr_names.push_back("id");
        child_node.attribute_list.attr_values.push_back(attribute_list.attr_values[0] + "_0" + std::to_string(childs.size()));
        childs.push_back(child_node);
        std::cout << "Successfull" << '\n';
        return;
    }
    for (int i = 0; i < childs.size(); i++)
    {
        childs[i].newChild(id, _tagname);
    }
}

void Node::print(std::ostream &os, int spaces) const
{
    _addSpaces(os, spaces); //add indent
    if (childs.size() == 0) // if leaftag
    {
        os << "<" << tagname;
        _printAttributes(os);
        os << ">";
        os << text;
        os << "</" << tagname << ">" << '\n';
        return;
    }
    else
    {
        os << "<" << tagname;
        _printAttributes(os);
        os << ">" << '\n';

        if (text != "") // prints text
        {
            _addSpaces(os, spaces + 4);
            os << text << '\n';
        }

        for (int i = 0; i < childs.size(); i++)
        {
            childs[i].print(os, spaces + 4);
        }
        _addSpaces(os, spaces);
        os << "</" << tagname << ">" << '\n';
    }
}

void Node::updateChildList(const SlashOperand &operand, std::vector<Node> &list) const
{
    for (int i = 0; i < childs.size(); i++)
    {
        if (childs[i].tagname == operand.getName() && operand.constraintsPassed(childs[i]))
        {
            list.push_back(childs[i]);
        }
    }
}
