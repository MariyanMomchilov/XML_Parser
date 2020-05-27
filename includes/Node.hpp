#ifndef _NODE
#define _NODE
#include "IDFactory.hpp"
#include "AttributeList.hpp"
#include <iostream>

class SlashOperand;

/// Класът описва елементите на XML документът. Всеки е елемент е част от кореново дърво
class Node
{
private:
    std::string tagname; //identificator
    AttributeList attribute_list;
    std::vector<Node> childs;
    std::string text;

    /// Проверява дали елементът има id
    int _hasId() const;

    /// Проверява дали елементът има уникален id
    bool _isUniqueId(int index, const IDFactory &factory) const;

    void _addSpaces(std::ostream &os, int spaces) const;
    void _printAttributes(std::ostream &os) const;
    friend class Tree;

public:
    /// Конструктор по подразбиране
    Node() = default;
    /// Конструктор, приемащ параметри име на таг, AttributeList, текст
    Node(const std::string &_tagname, const AttributeList &_attribute_list, std::string _text);

    ///Копи-конструктор
    Node(const Node &other);

    /// Предефиниране на =
    Node &operator=(const Node &other);

    /// Предефиниране на ==
    bool operator==(const Node &other) const;

    /// Предефиниране на ==
    bool operator!=(const Node &other) const;

    /// Деструктор по подразбиране
    ~Node() = default;

    /// @returns size_t дължината на вектор с деца
    size_t getChildSize() const;

    /// @returns i-тият елемент от вектора с деца
    Node getChild(int i) const;

    /// @returns string текстът на елемент
    std::string getText() const;

    /// @returns string името на тага
    std::string getTagName() const;

    /// @returns AttributeList списък с атрибути
    AttributeList getAttributes() const;

    /// @param string ключ
    /// @returns string стойност на даден атрибут
    std::string getAttrValue(const std::string &attr_name) const;

    /// Добавя нов елемент към списъка с деца
    /// @param Node дете
    void addChild(const Node &child);

    /// Конкатенира текст към текста на елемента
    /// @param string текст
    void appendText(const std::string &_text);

    /// Добавя уникално id, ако не съществува. Ако съществува id и не е уникално, id-то се заменя с уникално такова
    /// @param IDFactory
    void assignUniqueId(IDFactory &factory);

    /// Намиране даден елемент, чрез рекурсивно търсене
    /// @param string id
    /// @param Node тук се пази резултатът от функцията
    void getChild(const std::string &id, Node &result) const;

    /// Рекурсивен метод за присвояване на стойност на атрибут, чрез търсене по id и стойност на ключ
    /// @param string id
    /// @param string ключ на атрибут
    /// @param string новата стойност
    void setAttribute(const std::string &id, const std::string &key, const std::string &value);

    /// Рекурсивен метод за изтриване на стойност на атрибут, чрез търсене по id и стойност на ключ
    /// @param string id
    /// @param string ключ на атрибут
    void deleteAttribute(const std::string &id, const std::string &key);

    /// Намира чрез рекурсия елемент по id и добавя нов елемент в списъка с деца
    /// @param string id
    /// @param string име на таг
    void newChild(const std::string &id, const std::string &_tagname);

    /// Рекурсивен метод, който извежда информацията във файла
    void print(std::ostream &os, int spaces) const;

    /// TO DO
    void updateChildList(const SlashOperand &operand, std::vector<Node> &list) const;
};

#endif