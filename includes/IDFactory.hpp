#ifndef _IDFACTORY
#define _IDFACTORY
#include <vector>
#include <string>

class IDFactory
{
private:
    std::vector<std::string> id_container;
    int id_number;
    std::vector<int> id_occurences;

public:
    IDFactory();
    void init();
    bool isUnique(const std::string &id) const;
    std::string getUnique();
    std::string transformToUnique(std::string &id);
    void addId(std::string &id);
    ~IDFactory() = default;
};

#endif