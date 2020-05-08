#ifndef _SLASHOPERAND
#define _SLASHOPERAND
#include "EqualOperand.hpp"
#include "Node.hpp"

class SlashOperand
{
private:
    std::string name;
    int iOperand;
    std::string astr;
    EqualOperand eqOperand;

public:
    SlashOperand();
    SlashOperand(const std::string &_name, int _indexOperand, const EqualOperand &_eqOperand);
    SlashOperand(const std::string &_name, int _indexOperand, const std::string &_astr);

    std::string getName() const;
    int getIOperand() const;
    bool hasAstr() const;
    std::string getAstr() const;
    void setA(const std::string &str);
    std::vector<Node> constructList(std::vector<Node> &previous_list) const;
    bool constraintsPassed(const Node &node) const;
};

#endif