#include "../include/ShowTablesCommand.hpp"
#include "../include/Utilities.hpp"
#include "../include/Database.hpp"
#include "../include/Command.hpp"
#include "../include/Table.hpp"
#include "../include/Row.hpp"
#include "../include/Cell.hpp"
#include "../include/ColumnType.hpp"
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