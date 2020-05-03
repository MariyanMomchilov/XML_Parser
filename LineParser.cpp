#include "includes/LineParser.hpp"
#include <iostream>
std::string LineParser::remove_whitespace(const std::string &line)
{
    int back_index = line.size() - 1;
    int front_index = 0;
    std::string result = "";
    while ((line[front_index] == ' ' || line[back_index] == ' ') && front_index <= back_index)
    {
        if (line[front_index] == ' ' && line[back_index] == ' ')
        {
            front_index++;
            back_index--;
        }
        else if (line[front_index] == ' ' || line[back_index] == ' ')
        {
            if (line[front_index] == ' ')
            {
                front_index++;
            }
            else
                back_index--;
        }
    }
    for (int i = front_index; i <= back_index; i++)
    {
        result += line[i];
    }
    return result;
}

std::vector<std::string> LineParser::file_content(std::ifstream &file)
{
    std::vector<std::string> content;
    std::string line;
    while (!file.eof())
    {
        getline(file, line);
        content.push_back(LineParser::remove_whitespace(line));
    }
    return content;
}

Tag LineParser::getOpenTag(const std::string &line)
{
    if (line[0] != '<')
        return Tag({""});
    std::string identificator = ""; //tagname
    AttributeList attributes;
    size_t index = 1;
    while (line[index] != ' ' && line[index] != '>')
    {
        identificator += line[index];
        index++;
    }
    std::cout << identificator << std::endl;
    attributes = LineParser::parseAttr(line, index);
    return Tag({identificator, attributes});
}

AttributeList LineParser::parseAttr(const std::string &line, size_t &i)
{

    AttributeList list;
    if (line[i] == ' ')
        i++;
    while (line[i] != '>')
    {
        std::string attr_name = "";
        std::string attr_val = "";
        while (line[i] != '=')
        {
            if (line[i] == '\"')
            {
                i++;
                continue;
            }
            attr_name += line[i];
            i++;
        }
        i++;
        while (line[i] != ' ' && line[i] != '>')
        {
            if (line[i] == '\"')
            {
                i++;
                continue;
            }
            attr_val += line[i];
            i++;
        }

        list.attr_names.push_back(attr_name);
        list.attr_values.push_back(attr_val);

        if (line[i] == '>')
            break;
        i++;
    }
    return list;
}

bool LineParser::hasOpenTag(const std::string &line)
{
    size_t index = line.find('<');
    return index != std::string::npos && line[index + 1] != '/' && line.find('>') != std::string::npos;
}

bool LineParser::hasClosingTag(const std::string &line)
{
    size_t index = line.find('<');
    return index != std::string::npos && line[index + 1] == '/' && line.find('>') != std::string::npos;
}

bool LineParser::isLeafTag(const std::string &line)
{
    if (LineParser::hasOpenTag(line))
    {
        size_t index = line.find('>');
        if (index != line.size() - 1)
        {
            std::string line2 = line.substr(index + 1, line.size());
            if (LineParser::hasClosingTag(line2))
            {
                return true;
            }
        }
        else
            return false;
    }
}