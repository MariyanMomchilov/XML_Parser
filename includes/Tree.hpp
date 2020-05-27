#ifndef _NT
#define _NT
#include "Node.hpp"

/// Класът описва кореновото дърво със всички XML елементи

class Tree
{
private:
    Node root;

    /// Намира Node по id
    Node find(const std::string &id) const;
    friend std::ostream &operator<<(std::ostream &os, const Tree &tree);

public:
    /// Конструктор по подразбиране
    Tree() = default;

    /// Конструктор, който се инициализира с даден Node корен
    /// @param Node
    Tree(Node _root);

    /// Копи-конструктор
    Tree(const Tree &tree);

    /// Предефиниране на =
    Tree &operator=(const Tree &tree);

    /// Деструктор по подразбиране
    ~Tree() = default;

    /// Връща root
    Node getRoot() const;

    /// Извежда стойност на атрибут по даден идентификатор на елемента и ключ на атрибута
    /// @param string id
    /// @param string ключ
    void select(const std::string &id, const std::string &key) const;

    /// Присвояване на стойност на атрибут
    /// @param string id
    /// @param string ключ
    /// @param string стойност
    void set(const std::string &id, const std::string &key, const std::string &value);

    /// Изтриване на атрибут на елемент по ключ
    /// @param string id
    /// @param string ключ
    void deleteAttr(const std::string &id, const std::string &key);

    ///Добавяне на НОВ наследник на елемент. Новият елемент няма никакви атрибути, освен идентификатор и име на таг-а
    /// @param string id
    /// @param string име на таг-а
    void newchild(const std::string &id, const std::string &_tagname);

    /// Извежда на екрана прочетената информация от XML файла
    /// @param string id
    void printText(const std::string &id) const;

    /// Достъп до i-тия наследник на елемент
    /// @param string id
    /// @param size_t i
    void child(const std::string &id, size_t i) const;

    ////Списък с атрибути на вложените елементи
    /// @param string id
    void children(const std::string &id) const;
};

#endif
