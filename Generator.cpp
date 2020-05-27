#include "includes/Generator.hpp"
#include "includes/LineParser.hpp"
#include "includes/IDFactory.hpp"

IDFactory factory;

Node Generator::TreeGenerator(const std::vector<std::string> &content, size_t &i)
{
    if (content[i] != "")
    {

        if (LineParser::isLeafTag(content[i]))
        {
            Tag opentag = LineParser::getOpenTag(content[i]);
            size_t index = content[i].find('>');
            if (index != content[i].size() - 1)
            {
                std::string line2 = content[i].substr(index + 1, content[i].size());

                std::string text = line2.substr(0, line2.find('<'));
                Node node(opentag.name, opentag.attributes, text);
                node.assignUniqueId(factory);
                return node;
            }
        }
        Tag opentag = LineParser::getOpenTag(content[i]);
        Node node(opentag.name, opentag.attributes, "");
        node.assignUniqueId(factory);
        while (!LineParser::hasClosingTag(content[i + 1]))
        {
            i += 1;
            if (LineParser::hasOpenTag(content[i]))
                node.addChild(Generator::TreeGenerator(content, i));
            else
                node.appendText(content[i]);
        }
        i++;
        return node;
    }
    return Node();
}

Tree Generator::GenerateTree(std::fstream &in)
{
    std::vector<std::string> content = LineParser::file_content(in);
    size_t i = 0;
    Node root = TreeGenerator(content, i);
    return Tree(root);
}
