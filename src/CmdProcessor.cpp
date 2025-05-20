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

    const size_t rowsPerPage = 10;
    size_t currentPage = 0;
    size_t totalPages = (tab.getRowCount() + rowsPerPage - 1) / rowsPerPage;
    size_t rowCount = tab.getRowCount();

    std::string input;

    while (true)
    {
        //От интернет
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        std::cout << "~~~ Table: " << tabName << " | " 
                 << "Page: " << (currentPage + 1) << " of " << (totalPages == 0 ? 1 : totalPages) << " ~~~\n\n";
        
        //Принтиране на имена на колоните
        std::cout << "№ | ";
        for (size_t i = 0; i < tab.getColumnCount(); i++)
        {
            std::cout << tab.getColumnName(i);
            if (i < tab.getColumnCount() - 1)
            {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;

        //Принтиране на редовете
        size_t start = currentPage * rowsPerPage;
        size_t end = std::min(start + rowsPerPage, rowCount);

        for (size_t i = start; i < end; i++)
        {
            std::cout << i + 1 << ". " << tab.getRow(i).toString() << std::endl;
        }
        std::cout << std::endl;
        
        while (true)
        {
            std::cout << "[n]ext, [p]revious, [e]xit";
            std::getline(std::cin, input);

            if (input == "n" || input == "next")
            {
                if (currentPage < totalPages - 1)
                {
                    currentPage++;
                }
                else
                {
                    std::cout << "You are already on the last page." << std::endl;
                }
                break;
            }
            else if (input == "p" || input == "previous")
            {
                if (currentPage > 0)
                {
                    currentPage--;
                }
                else
                {
                    std::cout << "You are already on the first page." << std::endl;
                }
                break;
            }
            else if (input == "e" || input == "exit")
            {
                return;
            }
            else
            {
                std::cout << "Invalid input. Please enter next, prev or exit." << std::endl;
            }
        }
    }
}