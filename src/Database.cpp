#include "../include/Database.hpp"
#include "../include/Table.hpp"
#include "../include/Utilities.hpp"
#include <vector>
#include <string>
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

void Database::setCatalogFileName(const std::string& fileName){
    catalogFileName = fileName;
}
    
const std::string& Database::getCatalogFileName() const{
    return catalogFileName;
}

std::vector<std::string> Database::listTableNames() const {
    std::vector<std::string> result;
    for (const Table& tab : tables)
    {
        result.push_back(tab.getName());
    }
    return result;
}

void Database::renameTable(const std::string& oldName, const std::string& newName){
    for (Table& tab : tables)
    {
        if (tab.getName() == oldName)
        {
            tab.setName(newName);
            return;
        }
    }
}

void Database::unregisterTableFile(const std::string& tabName){
    tableNameToFileName.erase(tabName);
}

void Database::registerTableFile(const std::string& tabName, const std::string& fileName){
    tableNameToFileName[tabName] = fileName;
}
    
std::string Database::getFileName(const std::string& tabName) const{
    auto it = tableNameToFileName.find(tabName);
    if (it != tableNameToFileName.end())
    {
        return it->second;
    }
    throw std::invalid_argument("Table \"" + tabName + "\" does not exist");
}
