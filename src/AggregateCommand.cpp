#include "AggregateCommand.hpp"
#include "Utilities.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>

void AggregateCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (args.size() != 5)
    {
        throw std::invalid_argument("Incorrect arguments for command \"aggregate\".");
    }
    
    //aggregate <table name> <search column n> <search value> <target column n> <operation>
    const std::string& tabName = args[0];
    const std::string& searchColStr = args[1];
    const std::string& searchValue = args[2];
    const std::string& targetColStr = args[3];
    const std::string& operation = args[4];

    if (!database.hasTable(tabName))
    {
        throw std::invalid_argument("Table \"" + tabName + "\" does not exist.");
    }
    
    const Table& tab = database.getTableByName(tabName);

    size_t searchColIndex, targetColIndex;
    try
    {
        searchColIndex = std::stoul(searchColStr);
        targetColIndex = std::stoul(targetColStr);
    }
    catch(...)
    {
        throw std::invalid_argument("Invalid column index");
    }
    
    if (searchColIndex >= tab.getColumnCount() || targetColIndex >= tab.getColumnCount())
    {
        throw std::invalid_argument("Collumn index out of range");
    }

    const ColumnType searchColType = tab.getColumnType(searchColIndex);
    const ColumnType targetColType = tab.getColumnType(targetColIndex);

    // Проверка дали колоната върху която искаме да агрегираме е числова
    if (targetColType != ColumnType::Int && targetColType != ColumnType::Double)
    {
        throw std::invalid_argument("Target column type must be numeric.");
    }
    
    Cell* searchCell = createCellFromStr(searchValue);
    if (searchCell->getType() != ColumnType::Null && searchCell->getType() != searchColType)
    {
        delete searchCell;
        throw std::invalid_argument("Search value type is different from the type of search column");
    }
    
    // Намираме клетките за агрегиране
    std::vector<const Cell*> targetCells;
    for (size_t i = 0; i < tab.getRowCount(); i++)
    {
        const Row& row = tab.getRow(i);
        const Cell* currCell = row.getCell(searchColIndex);
        
        bool match = false;
        if (searchCell->getType() == ColumnType::Null)
        {
            match = (currCell->getType() == ColumnType::Null);
        }
        else if (currCell->getType() != ColumnType::Null &&
                 currCell->compare(*searchCell) == 0)
        {
            match = true;
        }
        
        if (match)
        {
            const Cell* targetCell = row.getCell(targetColIndex);
            // Проверяваме дали съответната клетка от targetColumn е числова(дали не е NULL)
            if (targetCell->getType() == ColumnType::Double ||
                targetCell->getType() == ColumnType::Int)
            {
                targetCells.push_back(targetCell);   
            }
        }
    }

    delete searchCell;
    if (targetCells.empty())
    {
        std::cout << "No values found for aggregation" << std::endl;
        return;
    }
    
    double result;

    if (operation == "sum")
    {
        result = aggregateSum(targetCells);
    } else if (operation == "product")
    {
        result = aggregateProduct(targetCells);
    } else if (operation == "minimum")
    {
        result = aggregateMin(targetCells);
    } else if (operation == "maximum")
    {
        result = aggregateMax(targetCells);
    } else {
        throw std::invalid_argument("Unknown operation :\"" + operation + "\".");
    }
    
    std::cout << "Aggregate result (" << operation << "): " << result << std::endl;

}