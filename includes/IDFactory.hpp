#ifndef _IDFACTORY
#define _IDFACTORY
#include <vector>
#include <string>

/// Класът описва фабрика за създаване и поддръжка на уникални id-та

class IDFactory
{
private:
    std::vector<std::string> id_container;
    int id_number;
    std::vector<int> id_occurences;

public:
    /// Конструктор по подразбиране
    IDFactory();

    /// Проверя дали низ id
    /// @param string id
    /// @returns true ако е уникален, false иначе
    bool isUnique(const std::string &id) const;

    /// Връща уникално id
    /// @returns string
    std::string getUnique();

    /// Трансформира низ в уникален низ
    /// @param string id
    /// @returns string
    std::string transformToUnique(std::string &id);

    /// Добавя ново id в списъка
    void addId(std::string &id);

    /// Деструктор по подразбиране
    ~IDFactory() = default;
};

#endif