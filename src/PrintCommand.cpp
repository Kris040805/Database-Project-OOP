#include "PrintCommand.hpp"
#include "Utilities.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>

void PrintCommand::execute(const std::vector<std::string>& args, Database& database) {
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