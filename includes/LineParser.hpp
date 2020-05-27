#ifndef _LPARSER
#define _LPARSER
#include <string>
#include <fstream>
#include "Tag.hpp"
#include "AttributeList.hpp"

/// Статичен клас, който се използва за обработката на всеки ред от входния файл

class LineParser
{
public:
    /// Създава vector<string> от редовете на файла, без излишни "space" чрез remove_whitespace()
    /// @param fstream файл
    /// @returns vector<string> редовете на файла, без излишни "space"
    static std::vector<std::string> file_content(std::fstream &file);

    /// Премахва ненужните интервали от даден низ
    /// @param string
    /// @returns string без излишни интервали
    static std::string remove_whitespace(const std::string &line);

    /// Проверява за отварящ XML таг, чрез търсене на символите '<' и '>'
    /// @param string
    /// @returns true ако низа(реда от файла) съдържа отварящ таг, false иначе
    static bool hasOpenTag(const std::string &line);

    /// Проверява за затварящ XML таг, чрез търсене на символите '<' и '>'
    /// @param string
    /// @returns true ако низа(реда от файла) съдържа затварящ таг, false иначе
    static bool hasClosingTag(const std::string &line);

    /// Проверява дали даден елемент е от тип листо(т.е в този елемент няма вложени елементи)
    ///
    /// Пример за таг-листо: <name id="2">John Smith</name>
    /// @param string
    /// @returns true ако низа(реда от файла) съдържа таг-листо, false иначе
    static bool isLeafTag(const std::string &line);

    /// Обработва и извлича атрибутите на даден елемент
    /// @param string низ
    /// @param size_t индекс, указващ откъде да започне с обработката на реда
    /// @returns AttributeList
    static AttributeList parseAttr(const std::string &line, size_t &i);

    /// Обработва и извлича даден таг на елемент, виж също: parseAttr()
    /// @param string низ
    /// @returns Tag
    static Tag getOpenTag(const std::string &line);
};

#endif