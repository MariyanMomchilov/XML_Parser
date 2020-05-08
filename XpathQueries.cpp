#include "includes/XpathQueries.hpp"

bool XpathQueries::hasAsymbol(int index, const std::string &str)
{
    if (str[index] == '@')
        return true;
    return false;
}

std::vector<SlashOperand> XpathQueries::ParseQuery(std::string &query)
{
    std::vector<SlashOperand> operands;
    int q_start_index = 0;
    while (q_start_index < query.size())
    {
        int q_stop_index = query.find('/');
        if (q_stop_index == query.npos)
            q_stop_index = query.size();
        std::string operand_name = "";
        std::string equal_childname = "";
        std::string equal_text = "";
        int indexOperand = -1;
        query[q_stop_index] = '|'; // marks "/" symbol mark as visited
        while (q_start_index < q_stop_index && (query[q_start_index] != '(' && query[q_start_index] != '['))
        {
            operand_name += query[q_start_index];
            q_start_index++;
        }
        if (q_start_index < q_stop_index)
        {
            if (query[q_start_index] == '(')
            {
                q_start_index++;

                if (XpathQueries::hasAsymbol(q_start_index, query)) // it will parse the @operator, the program assumes that it is the last operand
                {
                    q_start_index++;
                    std::string astr = "";
                    while (q_start_index < q_stop_index && query[q_start_index] != ')')
                    {
                        astr += query[q_start_index];
                        q_start_index++;
                    }
                    q_start_index++;
                    if (q_start_index < q_stop_index)
                    {
                        std::string index_str = "";
                        while (query[q_start_index] != ']')
                        {
                            index_str += query[q_start_index];
                            q_start_index++;
                        }
                        indexOperand = std::stoi(index_str);
                    }
                    operands.push_back(SlashOperand(operand_name, indexOperand, astr));
                    return operands;
                }
                else
                {
                    while (query[q_start_index] != '=')
                    {
                        equal_childname += query[q_start_index];
                        q_start_index++;
                    }
                    q_start_index++;
                    while (query[q_start_index] != ')')
                    {
                        if (query[q_start_index] == '"')
                        {
                            q_start_index++;
                            continue;
                        }
                        equal_text += query[q_start_index];
                        q_start_index++;
                    }
                    q_start_index++;
                }
            }
            if (query[q_start_index] == '[')
            {
                q_start_index++;
                std::string index_str = "";
                while (query[q_start_index] != ']')
                {
                    index_str += query[q_start_index];
                    q_start_index++;
                }
                indexOperand = std::stoi(index_str);
            }
        }
        q_start_index = q_stop_index + 1;
        operands.push_back(SlashOperand(operand_name, indexOperand, EqualOperand{equal_childname, equal_text}));
    }
    return operands;
}

void XpathQueries::getQuery(const std::string &id, std::string &query, const Tree &XMLtree)
{
    Node target_node;
    XMLtree.getRoot().getChild(id, target_node);
    std::vector<SlashOperand> operands = XpathQueries::ParseQuery(query);
    std::vector<Node> newlist = {target_node};

    for (int i = 0; i < operands.size(); i++)
    {
        newlist = operands[i].constructList(newlist);
    }
    std::cout << '\n'
              << "[";

    int newlist_size = newlist.size();
    int operands_size = operands.size();
    if (operands[operands_size - 1].hasAstr())
    {
        std::string astr = operands[operands_size - 1].getAstr();
        for (int k = 0; k < newlist_size; k++) // TO DO printing LIST, TESTING and @query
        {
            if (k != newlist_size - 1)
                std::cout << newlist[k].getAttrValue(astr) << ", ";
            else
                std::cout << newlist[k].getAttrValue(astr) << "]" << '\n';
        }
    }
    else
    {
        for (int k = 0; k < newlist_size; k++) // TO DO printing LIST, TESTING and @query
        {
            if (k != newlist_size - 1)
                std::cout << newlist[k].getText() << ", ";
            else
                std::cout << newlist[k].getText() << "]" << '\n';
        }
    }
}
