#include "../include/UpdateCommand.hpp"
#include "../include/Utilities.hpp"
#include "../include/Database.hpp"
#include "../include/Command.hpp"
#include "../include/Table.hpp"
#include "../include/Row.hpp"
#include "../include/Cell.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>

void UpdateCommand::execute(const std::vector<std::string>& args, Database& database) {
    // Проверка за правилен брой аргументи
    if (args.size() != 5)
    {
        throw std::invalid_argument("Incorrect arguments for command \"update\".");
    }
    
    //update <table name> <search column n> <search value> <target column n> <target value>
    const std::string& tabName = args[0];
    const std::string& searchColStr = args[1];
    const std::string& searchValue = args[2];
    const std::string& targetColStr = args[3];
    const std::string& targetValue = args[4];

    // Проверка дали таблицата съществува
    if (!database.hasTable(tabName))
    {
        throw std::invalid_argument("Table \"" + tabName + "\" does not exist.");
    }
    
    Table& tab = database.getTableByName(tabName);
    // Проверка за валидни индекси на колоните
    size_t searchColIndex, targetColIndex;
    try
    {
        searchColIndex = std::stoul(searchColStr);
        targetColIndex = std::stoul(targetColStr);
    }
    catch(...)
    {
        throw std::invalid_argument("Invalid column index: \"" + searchColStr + "\" or \"" + targetColStr + "\".");
    }

    // Проверка дали индексите на колоните са в допустимия диапазон
    if (searchColIndex >= tab.getColumnCount() || targetColIndex >= tab.getColumnCount())
    {
        throw std::invalid_argument("Column index out of range.");
    }

    const ColumnType searchColType = tab.getColumnType(searchColIndex);
    const ColumnType targetColType = tab.getColumnType(targetColIndex);

    Cell* searchCell = createCellFromStr(searchValue);
    Cell* targetCell = createCellFromStr(targetValue);

    // Проверка дали типовете на клетките съвпадат с типовете на колоните
    if (searchCell->getType() != ColumnType::Null && searchCell->getType() != searchColType)
    {
        delete searchCell;
        delete targetCell;
        throw std::invalid_argument("Search value does not match the type of search column.");
    }
    
    if (targetCell->getType() != ColumnType::Null && targetCell->getType() != targetColType)
    {
        delete searchCell;
        delete targetCell;
        throw std::invalid_argument("Target value does not match the type of target column.");
    }
    
    size_t updatedRowsCount = 0;

    for (size_t i = 0; i < tab.getRowCount(); i++)
    {
        Row& row = tab.getRow(i);
        Cell* currCell = row.getCell(searchColIndex);
        bool match = false;

        if (searchCell->getType() == ColumnType::Null)            
        {
            match = (currCell->getType() == ColumnType::Null);
        } 
        else 
        {
            if (searchCell->getType() != ColumnType::Null &&
                currCell->compare(*searchCell) == 0)
            {
                match = true;
            }
        } 

        if (match)
        {
            row.setCell(targetColIndex, targetCell->clone());
            ++updatedRowsCount;
        }
    }
    delete searchCell;
    delete targetCell;
    std::cout << updatedRowsCount << " rows updated in table \"" + tabName + "\"." << std::endl;

}