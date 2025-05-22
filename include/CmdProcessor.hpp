#pragma once
#include "Table.hpp"
#include "Database.hpp"
#include <string>
#include <vector>


class CmdProcessor {
public:
    void processCommands(const std::string& input, Database& database);

private:
    std::vector<std::string> splitArgs(const std::string& line);
    
    void cmdInsert(const std::vector<std::string>& args, Database& database);
    void cmdPrint(const std::vector<std::string>& args, Database& database);
    void cmdAddColumn(const std::vector<std::string>& args, Database& database);
    void cmdSelect(const std::vector<std::string>& args, Database& database);
    void cmdUpdate(const std::vector<std::string>& args, Database& database);
    void cmdDelete(const std::vector<std::string>& args, Database& database);
    void cmdCount(const std::vector<std::string>& args, Database& database);
    void cmdAggregate(const std::vector<std::string>& args, Database& database);
    void cmdDescribe(const std::vector<std::string>& args, Database& database);
    void cmdShowTables(const std::vector<std::string>& args, Database& database);


};
