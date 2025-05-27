#include "ShowTablesCommand.hpp"
#include "Utilities.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>

void ShowTablesCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (args.size() != 0)
    {
        throw std::invalid_argument("Incorrect arguments for command \"showtables\".");
    }

    std::vector<std::string> tableNames = database.listTableNames();
    if (tableNames.empty())
    {
        std::cout << "No tables in the database." << std::endl;
        return;
    }
    
    std::cout << "Tables in the database:" << std::endl;
    for (const std::string& tableName : tableNames)
    {
        std::cout << "- " << tableName << std::endl;
    }

}