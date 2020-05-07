#ifndef _SLASHOPERAND
#define _SLASHOPERAND
#include "EqualOperand.hpp"
#include "Node.hpp"

class SlashOperand
{
private:
    std::string name;
    int iOperand;
    EqualOperand eqOperand;

public:
    SlashOperand();
    SlashOperand(const std::string &_name, int _indexOperand, const EqualOperand &_eqOperand);
    std::string getName() const;
    std::vector<Node> constructList(std::vector<Node> &previous_list) const;
    bool constraintsPassed(const Node &node) const;
};

#endif