#include "includes/IDFactory.hpp"

IDFactory::IDFactory() : id_number(1) {}

void IDFactory::addId(std::string &id)
{
    id_container.push_back(id);
    id_occurences.push_back(1);
}

bool IDFactory::isUnique(const std::string &id) const
{
    for (int i = 0; i < id_container.size(); i++)
    {
        if (id_container[i] == id)
            return false;
    }
    return true;
}
std::string IDFactory::getUnique()
{
    id_container.push_back(std::to_string(id_number));
    id_occurences.push_back(1);
    id_number++;
    return std::to_string(id_number - 1);
}
std::string IDFactory::transformToUnique(std::string &id)
{
    for (int i = 0; i < id_container.size(); i++)
    {
        if (id_container[i] == id)
        {
            id_occurences[i]++;
            id += ("_" + std::to_string(id_occurences[i]));
            return id;
        }
    }
    return id;
}