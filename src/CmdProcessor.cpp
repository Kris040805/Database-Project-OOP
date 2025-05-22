#include "CmdProcessor.hpp"
#include "Utilities.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

void CmdProcessor::processCommands(const std::string& input, Database& database){
    std::vector<std::string> args = splitArgs(input);
    
    if (args.empty())
    {
        return;
    }
    
    std::string cmd = args[0];
    //премахваме командата от вектора
    args.erase(args.begin());

    //извикаване на командата
    if (cmd == "insert")
    {
        cmdInsert(args, database);
    } else if (cmd == "print")
    {
        cmdPrint(args, database);
    } else if (cmd == "addcolumn")
    {
        cmdAddColumn(args, database);
    } else if (cmd == "select")
    {
        cmdSelect(args, database);
    } else if (cmd == "update")
    {
        cmdUpdate(args, database);
    } else if (cmd == "delete")
    {
        cmdDelete(args, database);
    } else if (cmd == "count")
    {
        cmdCount(args, database);
    }
     
    else {
        throw std::invalid_argument("Unknown command:" + cmd);
    }

}

std::vector<std::string> CmdProcessor::splitArgs(const std::string& line){
    std::vector<std::string> result;
    std::string current;
    bool inQuotes = false;

    for (char char_ : line) {
        if (char_ == '"')
        {
            inQuotes = !inQuotes;
            current += char_;
        }
        else if (char_ == ' ' && !inQuotes)
        {
            if (!current.empty())
            {
                result.push_back(current);
                current.clear();
            }
        }
        else {
            current += char_;
        }        
    }

    if (!current.empty())
    {
        result.push_back(current);
    }
    
    return result;
}

void CmdProcessor::cmdInsert(const std::vector<std::string>& args, Database& database){
    if (args.empty())
    {
        throw std::invalid_argument("Too few arguments.");
    }
    const std::string& tabName = args[0];
    if (!database.hasTable(tabName))
    {
        throw std::invalid_argument("Table \"" + tabName + "\" does not exist.");
    }
    
    Table& tab = database.getTableByName(tabName);

    //-1 защото първият аргумент е името на таблицата
    if ((args.size() - 1) != tab.getColumnCount())
    {
        throw std::invalid_argument("The number of values does not match the number of columns.");
    }
    
    Row row;
    
    for (size_t i = 0; i < tab.getColumnCount(); i++)
    {
        Cell* cell = createCellFromStr(args[i + 1]);

        ColumnType expectType = tab.getColumnType(i);
        
        if (cell->getType() != ColumnType::Null && cell->getType() != expectType)
        {
            delete cell;
            throw std::invalid_argument("Error: value \"" + args[i + 1] + "\" does not match the type of column \"" + tab.getColumnName(i) + "\".");
        }
        
        row.addCell(cell);
    }

    tab.insertRow(row);
    std::cout << "The row is added successfully into table\"" + tabName + "\".\n" << std::endl;
    
}

void CmdProcessor::cmdPrint(const std::vector<std::string>& args, Database& database){
    if (args.size() != 1)
    {
        throw std::invalid_argument("Incorrect arguments for command \"print\".");
    }
    const std::string& tabName = args[0];
    if (!database.hasTable(tabName))
    {
        throw std::invalid_argument("Table \"" + tabName + "\" does not exist.");
    }
    
    const Table& tab = database.getTableByName(tabName);

    //Проверка за празна таблица
    if (tab.getRowCount() == 0)
    {
        std::cout << "The table \"" + tabName + "\" is empty." << std::endl;
        return;
    }

    std::vector<const Row*> rows;
    for (size_t i = 0; i < tab.getRowCount(); i++)
    {
        rows.push_back(&tab.getRow(i));
    }
    printRowsPaged(rows, tab, "Table: " + tabName);
}

void CmdProcessor::cmdAddColumn(const std::vector<std::string>& args, Database& database){
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

void CmdProcessor::cmdSelect(const std::vector<std::string>& args, Database& database){
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

void CmdProcessor::cmdUpdate(const std::vector<std::string>& args, Database& database){
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

void CmdProcessor::cmdDelete(const std::vector<std::string>& args, Database& database){
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

void CmdProcessor::cmdCount(const std::vector<std::string>& args, Database& database){
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

void CmdProcessor::cmdAggregate(const std::vector<std::string>& args, Database& database){
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



