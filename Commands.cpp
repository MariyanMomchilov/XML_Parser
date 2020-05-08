#include "includes/Commands.hpp"
#include "includes/Generator.hpp"
std::string Commands::getNextCMD(std::string &str, int &i)
{
    std::string command;
    int k = i + 1;
    if (str[k] == '\"' || str[k] == '\'')
    {
        if (str[k] == '\"')
        {
            str[k] = '|';
            i = str.find('\"');
        }

        else if (str[k] == '\'')
        {
            str[k] = '|';
            i = str.find('\'');
        }

        if (i == -1)
        {
            return command;
        }
        else
        {
            str[i] = '|';
            k++;
            while (k != i)
            {
                command += str[k];
                if (str[k] == ' ')
                    str[k] = '|';
                k++;
            }
        }
    }
    else
    {
        i = str.find(' ');
        if (i != -1)
        {
            if (i == k) // само когато предната параметър е завършил със "
            {
                str[i] = '|';
                k++;
                if (str[k] == '\"')
                {
                    str[k] = '|';
                    k++;
                    i = str.find('\"');
                }
                else
                    i = str.find(' ');
            }
            if (i == -1)
            {
                command = str.substr(k, str.length());
                i = str.length();
            }
            else
            {
                str[i] = '|';
                while (k != i)
                {
                    command += str[k];
                    if (str[k] == ' ')
                        str[k] = '|';
                    k++;
                }
            }
        }
        else
        {
            command = str.substr(k, str.length());
            i = str.length();
        }
    }
    //std::cout << command << '\n';
    return command;
}

void Commands::_open(std::string &str, int &i)
{
    if (i == str.length())
    {
        std::cout << "Error: no parameter given" << '\n';
        return;
    }
    std::string parameter = getNextCMD(str, i);
    if (file.is_open())
    {
        std::cout << "A file is already open" << std::endl;
    }
    else if (parameter.length() != 0)
    {
        filename = parameter;
        this->file.open(filename);
        XMLtree = Generator::GenerateTree(file);
    }
    else
    {
        std::cout << "Error: undefined argument" << '\n';
    }
}

void Commands::process(std::string &command)
{
    int i = -1; // tracks the (start - 1) of the upcomming command
    std::string next_cmd = getNextCMD(command, i);
    if (next_cmd == "open")
    {
        _open(command, i); //_open parses the rest of the command
    }
    else if (next_cmd == "close")
    {
        if (this->file.is_open())
        {
            this->file.close();
            std::cout << "Successfully closed" << '\n';
        }
        else
        {
            std::cout << "There is no opened file!" << '\n';
        }
    }
    else if (next_cmd == "save")
    {
        if (this->file.is_open())
        {
            file.close();
            file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
            write();
        }
    }
    else if (next_cmd == "saveas")
    {
        std::string filename = getNextCMD(command, i);
        std::ofstream newfile(filename);
        write(newfile);
        if (newfile.good())
        {
            std::cout << "Successful " << '\n';
        }
        else
        {
            std::cout << "Unsuccessful " << '\n';
        }
    }
    else if (next_cmd == "help")
    {
        std::cout << "The following commands are supported:'\n'"
                  << "open <file>         opens <file>'\n'"
                  << "close               closes currently opened file'\n'"
                  << "save                saves the currently opened file'\n'"
                  << "saveas <file>       saves the currently opened file in <file>'\n'"
                  << "help                prints this information'" << std::endl;
    }

    else
    {
        if (next_cmd == "print")
        {
            std::cout << XMLtree;
        }
        else if (next_cmd == "select")
        {
            std::string id = getNextCMD(command, i);
            std::string key = getNextCMD(command, i);
            XMLtree.select(id, key);
        }
        else if (next_cmd == "set")
        {
            std::string id = getNextCMD(command, i);
            std::string key = getNextCMD(command, i);
            std::string value = getNextCMD(command, i);
            XMLtree.set(id, key, value);
        }
        else if (next_cmd == "children")
        {
            std::string id = getNextCMD(command, i);
            XMLtree.children(id);
        }
        else if (next_cmd == "child")
        {
            std::string id = getNextCMD(command, i);
            int n = std::stoi(getNextCMD(command, i));
            XMLtree.child(id, n);
        }
        else if (next_cmd == "text")
        {
            std::string id = getNextCMD(command, i);
            XMLtree.printText(id);
        }
        else if (next_cmd == "delete")
        {
            std::string id = getNextCMD(command, i);
            std::string key = getNextCMD(command, i);
            XMLtree.deleteAttr(id, key);
        }
        else if (next_cmd == "newchild")
        {
            std::string id = getNextCMD(command, i);
            std::string tagname = getNextCMD(command, i);
            XMLtree.newchild(id, tagname);
        }
        else if (next_cmd == "xpath")
        {
            std::string id = getNextCMD(command, i);
            std::string query = getNextCMD(command, i);
            XpathQueries::getQuery(id, query, XMLtree);
        }
    }
}

void Commands::write()
{
    file << XMLtree;
}

void Commands::write(std::ostream &os)
{
    os << XMLtree;
}