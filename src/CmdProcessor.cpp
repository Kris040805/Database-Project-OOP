#include "CmdProcessor.hpp"
#include "Utilities.hpp"
#include <iostream>
#include <stdexcept>

void CmdProcessor::processCommands(const std::string& input, Table& table){
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
        cmdInsert(args, table);
    } 
    else if (cmd == "print")
    {
        std::cout << table.toString();
    }
    else {
        throw std::invalid_argument("Unknown command:" + cmd);
    }

}

void cmdInsert(const std::vector<std::string>& args, Table& table){
    if (args.size() != table.getColumnCount())
    {
        throw std::invalid_argument("The number of values does not match the number of columns.");
    }

    Row row;
    for (size_t i = 0; i < args.size(); i++)
    {
        Cell* cell = createCellFromStr(args[i]);

        ColumnType expectType = table.getColumntType(i);
        
        if (cell->getType() != ColumnType::Null && cell->getType() != expectType)
        {
            delete cell;
            throw std::invalid_argument("Error: value \"" + args[i] + "\" does not match the type of column \"" + table.getColumnName(i) + "\".");
        }
        
        row.addCell(cell);
    }

    table.insertRow(row);
    std::cout << "The row is added successfully." << std::endl;
    
}

std::vector<std::string> splitArgs(const std::string& line){
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