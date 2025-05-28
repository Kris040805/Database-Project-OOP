#include "../include/AddColumnCommand.hpp"
#include "../include/Utilities.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>

void AddColumnCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (args.size() != 3)
    {
        throw std::invalid_argument("Incorrect arguments for command \"addColumn\".");
    }

    const std::string& tabName = args[0];
    const std::string& colName = args[1];
    const std::string& colTypeStr = args[2];

    if (!database.hasTable(tabName))
    {
        throw std::invalid_argument("Table \"" + tabName + "\" does not exist.");
    }

    ColumnType colType = parseColType(colTypeStr);
    if (colType == ColumnType::Null)
    {
        throw std::invalid_argument("Invalid column type: " + colTypeStr);
    }
    
    Table& tab = database.getTableByName(tabName);
    tab.addColumn(colName, colType);
    std::cout << "Column \"" + colName + "\" of type \"" + colTypeStr + "\" added to table \"" + tabName + "\"." << std::endl;

}