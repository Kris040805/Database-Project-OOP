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

    if (cmd == "insert")
    {
        cmdInsert(args, database);
    } else {
        throw std::invalid_argument("Unknown command:" + cmd);
    }

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

        ColumnType expectType = tab.getColumntType(i);
        
        if (cell->getType() != ColumnType::Null && cell->getType() != expectType)
        {
            delete cell;
            throw std::invalid_argument("Error: value \"" + args[i + 1] + "\" does not match the type of column \"" + tab.getColumnName(i) + "\".");
        }
        
        row.addCell(cell);
    }

    tab.insertRow(row);
    std::cout << "The row is added successfully." << std::endl;
    
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