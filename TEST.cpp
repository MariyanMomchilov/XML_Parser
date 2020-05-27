#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <iostream>
#include <fstream>
/*#include "includes/IDFactory.hpp"
#include "includes/LineParser.hpp"
#include "includes/Generator.hpp"
#include "includes/Tree.hpp"
#include "includes/SlashOperand.hpp"
#include "includes/XpathQueries.hpp"*/
#include "IDFactory.cpp"
#include "LineParser.cpp"
#include "Generator.cpp"
#include "Tree.cpp"
#include "Node.cpp"
#include "SlashOperand.cpp"
#include "XpathQueries.cpp"

using namespace std;
/*
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
    fstream xmlfile("test.xml");
    vector<string> content = LineParser::file_content(xmlfile);
    for (int i = 0; i < content.size(); i++)
    {
        cout << content[i] << endl;
    }
}

TEST_CASE("Generator, Node, XML Tree")
{
    fstream xmlfile("test.xml");
    Tree XMLtree = Generator::GenerateTree(xmlfile);
    xmlfile.close();
    XMLtree.select("7", "color");
    XMLtree.select("80", "color");
    XMLtree.set("7", "color", "blue");
    XMLtree.deleteAttr("7", "id");
    //XMLtree.deleteAttr("7", "color");
    ofstream xmlfileOUT("testOUT.xml");
    XMLtree.newchild("12", "newchild");
    xmlfileOUT << XMLtree;
    xmlfileOUT.close();

    string query = "person(address=\"USA\")/name";
    XpathQueries::getQuery("1", query, XMLtree);
    query = "person[0]/address";
    XpathQueries::getQuery("1", query, XMLtree);
    query = "person/name";
    XpathQueries::getQuery("1", query, XMLtree);
    query = "person(@id)";
    XpathQueries::getQuery("1", query, XMLtree);
}

TEST_CASE("SlashOperand")
{
    fstream xmlfile("test.xml");
    Tree XMLtree = Generator::GenerateTree(xmlfile);
    xmlfile.close();
    XMLtree.select("7", "color");
    XMLtree.select("80", "color");
    XMLtree.set("7", "color", "blue");
    XMLtree.deleteAttr("7", "id");
    XMLtree.deleteAttr("7", "color");
    ofstream xmlfileOUT("testOUT.xml");
    XMLtree.newchild("1", "personTest");
    xmlfileOUT << XMLtree;
    xmlfileOUT.close();

    SlashOperand slashoperand1("person", -1, EqualOperand());
    SlashOperand slashoperand2("name", -1, EqualOperand());

    std::vector<Node> prevlist = {XMLtree.getRoot()};

    std::vector<SlashOperand> operands = {slashoperand1, slashoperand2};
    std::vector<Node> newlist = prevlist;
    for (int i = 0; i < operands.size(); i++)
    {
        newlist = operands[i].constructList(newlist);
        for (int k = 0; k < newlist.size(); k++)
        {
            std::cout << newlist[k].getTagName() << '\n';
        }
    }
}
*/
TEST_CASE("QueryParser and Xpath")
{
    cout << '\n';
    fstream xmlfile("test.xml");
    Tree XMLtree = Generator::GenerateTree(xmlfile);
    string query = "person(address=\"USA\")/name";
    XpathQueries::getQuery("1", query, XMLtree);
    query = "person[0]/address";
    XpathQueries::getQuery("1", query, XMLtree);
    query = "person/name";
    XpathQueries::getQuery("1", query, XMLtree);
    query = "person(@id)";
    XpathQueries::getQuery("1", query, XMLtree);
    query = "person(name=\"John Smith\")/address";
    XpathQueries::getQuery("1", query, XMLtree);
}

int main()
{
    doctest::Context().run();
    return 0;
}