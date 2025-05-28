#include "../include/DeleteCommand.hpp"
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

void DeleteCommand::execute(const std::vector<std::string>& args, Database& database) {
    // Проверка за правилен брой аргументи
    if (args.size() != 3)
    {
        throw std::invalid_argument("Incorrect arguments for command \"delete\".");
    }
    
    //delete <table name> <search column n> <search value>
    const std::string& tabName = args[0];
    const std::string& searchColStr = args[1];
    const std::string& searchValue = args[2];

    // Проверка дали таблицата съществува
    if (!database.hasTable(tabName))
    {
        throw std::invalid_argument("Table \"" + tabName + "\" does not exist.");
    }
    
    Table& tab = database.getTableByName(tabName);
    
    // Проверка за валиден индекс на колоната
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
    
    // Проверка дали типовете на клетките съвпадат с типовете на колоните
    if (searchCell->getType() != ColumnType::Null && searchCell->getType() != searchColType)
    {
        delete searchCell;
        throw std::invalid_argument("Search value does not match the type of search column.");
    }

    size_t deletedRowsCount = 0;
    // Обхождане на редовете отзад напред, за да не се нарушава индексът при изтриване
    for (int i = static_cast<int>(tab.getRowCount()) - 1; i >= 0; i--)
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
            tab.deleteRow(i);
            ++deletedRowsCount;
        }
    }
    delete searchCell;
    std::cout << deletedRowsCount << " rows deleted from table \"" + tabName + "\"." << std::endl;
}