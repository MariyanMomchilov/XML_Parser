#include "includes/XpathQueries.hpp"

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
                while (query[q_start_index] != '=')
                {
                    equal_childname += query[q_start_index];
                    q_start_index++;
                }
                q_start_index++;
                while (query[q_start_index] != ')')
                {
                    if (query[q_start_index] == '"')
                        q_start_index++;
                    equal_text += query[q_start_index];
                    q_start_index++;
                }
                q_start_index++;
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

void XpathQueries::getQuery(std::string &query, const Tree &XMLtree)
{
    std::vector<Node> prevlist = {XMLtree.getRoot()};
    std::vector<SlashOperand> operands = XpathQueries::ParseQuery(query);
    std::vector<Node> newlist = prevlist;
    for (int i = 0; i < operands.size(); i++)
    {
        newlist = operands[i].constructList(newlist);
    }
    std::cout << '\n'
              << "\n";
    for (int k = 0; k < newlist.size(); k++) // TO DO printing LIST, TESTING and @query
    {
        std::cout << newlist[k].getTagName() << '\n';
    }
}
