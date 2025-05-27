#include "CountCommand.hpp"
#include "Utilities.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>

void CountCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (args.size() != 3)
    {
        throw std::invalid_argument("Incorrect arguments for command \"count\".");
    }

    const std::string& tabName = args[0];
    const std::string& searchColStr = args[1];
    const std::string& searchValue = args[2];

    if (!database.hasTable(tabName))
    {
        throw std::invalid_argument("Table \"" + tabName + "\" does not exist.");
    }
    
    const Table& tab = database.getTableByName(tabName);

    size_t searchColIndex;
    try
    {
        searchColIndex = std::stoul(searchColStr);
    }
    catch(...)
    {
        throw std::invalid_argument("Invalid column index: \"" + searchColStr + "\".");
    }
    
    if (searchColIndex >= tab.getColumnCount())
    {
        throw std::invalid_argument("Column index out of range.");
    }

    const ColumnType searchColType = tab.getColumnType(searchColIndex);
    Cell* searchCell = createCellFromStr(searchValue);
    if (searchCell->getType() != ColumnType::Null && searchCell->getType() != searchColType)
    {
        delete searchCell;
        throw std::invalid_argument("Search value does not match the type of search column.");
    }
    
    size_t matchesCount = 0;
    for (size_t i = 0; i < tab.getRowCount(); i++)
    {
        const Row& row = tab.getRow(i);
        const Cell* currCell = row.getCell(searchColIndex);

        if (searchCell->getType() == ColumnType::Null)
        {
            if (currCell->getType() == ColumnType::Null)
            {
                ++matchesCount;
            }
        } 
        else if (searchCell->getType() != ColumnType::Null &&
                 currCell->compare(*searchCell) == 0)
        {
            ++matchesCount;
        }
    }
    
    delete searchCell;
    std::cout << "Count of rows matching \"" + searchValue + "\" in column \"" + tab.getColumnName(searchColIndex) + "\" of table \"" + tabName + "\": " << matchesCount << std::endl;

}