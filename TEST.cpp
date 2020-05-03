#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include <fstream>
#include <string>
#include "includes/doctest.h"
#include "includes/IDFactory.hpp"
#include "includes/LineParser.hpp"
#include "includes/Generator.hpp"
#include "includes/Tree.hpp"
#include "includes/Node.hpp"
/*#include "IDFactory.cpp"
#include "LineParser.cpp"
#include "Generator.cpp"
#include "Node.cpp"*/

using namespace std;

TEST_CASE("IDFactory")
{
    IDFactory idfactory;
    CHECK(idfactory.getUnique() == "1");
    CHECK(idfactory.getUnique() == "2");
    CHECK(idfactory.getUnique() == "3");
    CHECK(idfactory.isUnique("5"));
    string id = "1", id2 = "1";
    CHECK(idfactory.transformToUnique(id) == "1_2");
    CHECK(idfactory.transformToUnique(id2) == "1_3");
}

TEST_CASE("Line parser")
{
    string parsed_line = LineParser::remove_whitespace("    <person id=\"0\" color=green bread=white>   ");
    CHECK(parsed_line == "<person id=\"0\" color=green bread=white>");
    CHECK(parsed_line.size() == 39);

    Tag tag = LineParser::getOpenTag(parsed_line);
    CHECK(tag.name == "person");
    CHECK(tag.attributes.attr_names.size() == 3);
    CHECK(tag.attributes.attr_names[0] == "id");
    CHECK(tag.attributes.attr_values[0] == "0");
    CHECK(tag.attributes.attr_values[1] == "green");
}
TEST_CASE("TAGS processing")
{
    string line = "<name>kieier</name>";
    CHECK(LineParser::isLeafTag(line) == true);
    string line2 = "<person id=1>";
    CHECK(LineParser::isLeafTag(line2) == false);
}

TEST_CASE("Vector Content")
{
    ifstream xmlfile("test.xml");
    vector<string> content = LineParser::file_content(xmlfile);
    for (int i = 0; i < content.size(); i++)
    {
        cout << content[i] << endl;
    }
}

/*TEST_CASE("Generator and Node") legacy test
{
    ifstream xmlfile("test.xml");
    Node node = Generator::TreeGenerator(xmlfile, 0); //bachka wee
    Node result;
    node.getChild("7", result);
    CHECK(result.getTagName() == "animal");
    xmlfile.close();
}*/

TEST_CASE("Generator, Node, XML Tree")
{
    ifstream xmlfile("test.xml");
    Tree XMLtree = Generator::GenerateTree(xmlfile);
    Node result = XMLtree.find("7");
    CHECK(result.getTagName() == "animal");
    ofstream xmlfileOUT("testOUT.xml");
    xmlfileOUT << XMLtree;
}
int main()
{
    doctest::Context().run();
    return 0;
}