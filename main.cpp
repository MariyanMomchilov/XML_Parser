#include "includes/Commands.hpp"
/*#include "IDFactory.cpp"
#include "LineParser.cpp"
#include "Generator.cpp"
#include "Tree.cpp"
#include "Node.cpp"
#include "SlashOperand.cpp"
#include "XpathQueries.cpp"*/
int main()
{
    Commands shell;

    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line == "exit") // special case for exit
        {
            std::cout << "Exiting the program..." << '\n';
            return 0;
        }
        shell.process(line);
    }

    return 0;
}