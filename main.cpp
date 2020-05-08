#include "includes/Commands.hpp"

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