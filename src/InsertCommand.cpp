#include "InsertCommand.hpp"
#include "Utilities.hpp"
#include <stdexcept>
#include <iostream>

void InsertCommand::execute(const std::vector<std::string>& args, Database& database) {
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
