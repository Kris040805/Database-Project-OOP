#include "Database.hpp"
#include <stdexcept>

void Database::addTable(const Table& table){
    if (hasTable(table.getName()))
    {
        throw std::invalid_argument("Table \"" + table.getName() + "\" already exists");
    }
    tables.push_back(table);
}
    
Table& Database::getTableByName(const std::string& name){
    for (Table& tab : tables) {
        if (tab.getName() == name)
        {
            return tab;
        }
    }
    throw std::invalid_argument("Table \"" + name + "\" does not exist");
}

bool Database::hasTable(const std::string& name) const {
    for (const Table& tab : tables)
    {
        if (tab.getName() == name)
        {
            return true;
        }
    }
    return false;
}

std::vector<std::string> Database::listTableNames() const {
    std::vector<std::string> result;
    for (const Table& tab : tables)
    {
        result.push_back(tab.getName());
    }
    return result;
}