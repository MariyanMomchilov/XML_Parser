#include "includes/Node.hpp"
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

std::string Node::getTagName() const
{
    return tagname;
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

void Node::_addSpaces(std::ostream &os, int spaces) const
{
    for (int i = 0; i < spaces; i++)
        os << " ";
}

void Node::print(std::ostream &os, int spaces) const
{
    _addSpaces(os, spaces); //add indent
    if (childs.size() == 0) // if leaftag
    {
        os << "<" << tagname << " ";
        for (int k = 0; k < attribute_list.attr_names.size(); k++) //print attributes
        {
            if (k != attribute_list.attr_names.size() - 1)
                os << attribute_list.attr_names[k] << "=" << '\"' << attribute_list.attr_values[k] << '\"' << " ";
            else
                os << attribute_list.attr_names[k] << "=" << '\"' << attribute_list.attr_values[k] << '\"' << ">";
        }
        os << text;
        os << "</" << tagname << ">" << '\n';
        return;
    }
    else
    {
        os << "<" << tagname << " ";
        for (int k = 0; k < attribute_list.attr_names.size(); k++) //print attributes
        {
            if (k != attribute_list.attr_names.size() - 1)
                os << attribute_list.attr_names[k] << "=" << '\"' << attribute_list.attr_values[k] << '\"' << " ";
            else
                os << attribute_list.attr_names[k] << "=" << '\"' << attribute_list.attr_values[k] << '\"' << ">" << '\n';
        }

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