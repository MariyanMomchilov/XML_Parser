#include "includes/SlashOperand.hpp"

SlashOperand::SlashOperand() : name(""), iOperand(-1), astr("") {}

SlashOperand::SlashOperand(const std::string &_name, int _indexOperand, const EqualOperand &_eqOperand)
{
    name = _name;
    iOperand = _indexOperand;
    eqOperand = _eqOperand;
}

SlashOperand::SlashOperand(const std::string &_name, int _indexOperand, const std::string &_astr)
{
    name = _name;
    iOperand = _indexOperand;
    astr = _astr;
}

std::string SlashOperand::getName() const
{
    return name;
}

int SlashOperand::getIOperand() const
{
    return iOperand;
}

bool SlashOperand::hasAstr() const
{
    return astr != "";
}

std::string SlashOperand::getAstr() const
{
    return astr;
}

void SlashOperand::setA(const std::string &str)
{
    astr = str;
}

std::vector<Node> SlashOperand::constructList(std::vector<Node> &previous_list) const
{
    std::vector<Node> list;
    for (int i = 0; i < previous_list.size(); i++)
    {
        previous_list[i].updateChildList(*this, list);
    }
    if (iOperand != -1 && iOperand < list.size())
    {
        return std::vector<Node>{list[iOperand]};
    }
    return list;
}

bool SlashOperand::constraintsPassed(const Node &node) const
{
    if (eqOperand.child_name != "" && eqOperand.text != "")
    {
        for (int i = 0; i < node.getChildSize(); i++)
        {
            Node child = node.getChild(i);
            if (child.getTagName() == eqOperand.child_name && child.getText() == eqOperand.text)
                return true;
        }
    }
    else if (eqOperand.child_name == "" && eqOperand.text == "")
        return true;
    return false;
}