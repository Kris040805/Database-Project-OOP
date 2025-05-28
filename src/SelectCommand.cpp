#include "../include/SelectCommand.hpp"
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

void SelectCommand::execute(const std::vector<std::string>& args, Database& database) {
    // Проверка за правилен брой аргументи
    if (args.size() != 3)
    {
        throw std::invalid_argument("Incorrect arguments for command \"select\".");
    }

    const std::string& searchColStr = args[0];
    const std::string& searchValue = args[1];
    const std::string& tabName = args[2];
    
    size_t searchColIndex;
    // Проверка за валиден индекс на колоната
    try
    {
        searchColIndex = std::stoul(searchColStr);
    }
    catch(...)
    {
        throw std::invalid_argument("Invalid column index: \"" + searchColStr + "\".");
    }

    // Проверка дали таблицата съществува
    if (!database.hasTable(tabName))
    {
        throw std::invalid_argument("Table \"" + tabName + "\" does not exist.");
    }
    const Table& tab = database.getTableByName(tabName);
    if (searchColIndex >= tab.getColumnCount())
    {
        throw std::invalid_argument("Column index out of range.");
    }
    
    // Проверка за валиден тип на колоната
    const ColumnType searchColType = tab.getColumnType(searchColIndex);
    Cell* searchCell = createCellFromStr(searchValue);
    if (searchCell->getType() != ColumnType::Null && searchCell->getType() != searchColType)
    {
        delete searchCell;
        throw std::invalid_argument("Error: value \"" + searchValue + "\" does not match the type of column \"" + tab.getColumnName(searchColIndex) + "\".");
    }

    std::vector<const Row*> rows;
    // Търсене на редовете, които отговарят на критериите
    for (size_t i = 0; i < tab.getRowCount(); i++)
    {
        const Row& row = tab.getRow(i);
        bool match = false;

        if (searchCell->getType() == ColumnType::Null)            
        {
            match = (row.getCell(searchColIndex)->getType() == ColumnType::Null);
        } 
        else 
        {
            if (row.getCell(searchColIndex)->getType() != ColumnType::Null &&
                 row.getCell(searchColIndex)->compare(*searchCell) == 0)
            {
                match = true;
            }
        } 
        
        if (match)
        {
            rows.push_back(&row);
        }
    }
    
    delete searchCell;
    
    if (rows.empty())
    {
        std::cout << "No rows found matching the criteria." << std::endl;
        return;
    }

    printRowsPaged(rows, tab, "Search results for \"" + searchValue + "\" in column \"" + tab.getColumnName(searchColIndex) + "\" of table \"" + tabName + "\".");

}