#include "includes/SlashOperand.hpp"

SlashOperand::SlashOperand() : name(""), iOperand(-1) {}

SlashOperand::SlashOperand(const std::string &_name, int _indexOperand, const EqualOperand &_eqOperand)
{
    name = _name;
    iOperand = _indexOperand;
    eqOperand = _eqOperand;
}

std::string SlashOperand::getName() const
{
    return name;
}

std::vector<Node> SlashOperand::constructList(std::vector<Node> &previous_list) const
{
    std::vector<Node> list;
    for (int i = 0; i < previous_list.size(); i++)
    {
        previous_list[i].updateChildList(*this, list);
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
    else
    {
        return true;
    }
    return false;
}