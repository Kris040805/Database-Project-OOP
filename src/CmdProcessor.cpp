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
    } else {
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
    if (args.size() != 3)
    {
        throw std::invalid_argument("Incorrect arguments for command \"select\".");
    }

    const std::string& searchColStr = args[0];
    const std::string& searchValue = args[1];
    const std::string& tabName = args[2];
    
    size_t searchColIndex;
    try
    {
        searchColIndex = std::stoul(searchColStr);
    }
    catch(...)
    {
        throw std::invalid_argument("Invalid column index: \"" + searchColStr + "\".");
    }

    if (!database.hasTable(tabName))
    {
        throw std::invalid_argument("Table \"" + tabName + "\" does not exist.");
    }
    const Table& tab = database.getTableByName(tabName);
    if (searchColIndex >= tab.getColumnCount())
    {
        throw std::invalid_argument("Column index out of range.");
    }
    
    const ColumnType searchColType = tab.getColumnType(searchColIndex);
    Cell* searchCell = createCellFromStr(searchValue);
    if (searchCell->getType() != ColumnType::Null && searchCell->getType() != searchColType)
    {
        delete searchCell;
        throw std::invalid_argument("Error: value \"" + searchValue + "\" does not match the type of column \"" + tab.getColumnName(searchColIndex) + "\".");
    }

    std::vector<const Row*> rows;
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




