#pragma once
#include "Table.hpp"
#include <vector>
#include <string>
#include <unordered_map>

class Database {
private:
    std::vector<Table> tables;
    std::unordered_map<std::string, std::string> tableNameToFileName;

public:
    void addTable(const Table& table);
    Table& getTableByName(const std::string& name);
    bool hasTable(const std::string& name) const;
    std::vector<std::string> listTableNames() const;
    void renameTable(const std::string& oldName, const std::string& newName);

    void registerTableFile(const std::string& tabName, const std::string& fileName);
    std::string getFileName(const std::string& tabName) const;
};