#pragma once
#include "Table.hpp"
#include <vector>
#include <string>

class Database {
private:
    std::vector<Table> tables;

public:
    void addTable(const Table& table);
    Table& getTableByName(const std::string& name);
    bool hasTable(const std::string& name) const;
    std::vector<std::string> listTableNames() const;
};