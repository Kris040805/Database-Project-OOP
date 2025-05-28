#include "../include/DescribeCommand.hpp"
#include "../include/Utilities.hpp"
#include "../include/Database.hpp"
#include "../include/Command.hpp"
#include "../include/Table.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>

void DescribeCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (args.size() != 1)
    {
        throw std::invalid_argument("Incorrect arguments for command \"describe\".");
    }
    
    const std::string& tabName = args[0];
    if (!database.hasTable(tabName))
    {
        throw std::invalid_argument("Table \"" + tabName + "\" does not exist.");
    }
    const Table& tab = database.getTableByName(tabName);
    
    // Проверка за празна таблица
    if (tab.getColumnCount() == 0)
    {
        std::cout << "Table \"" << tabName << "\" has no columns." << std::endl;
        return;
    }
    
    // Извеждане на информация за колоните
    std::cout << "Table \"" + tabName + "\" description:" << std::endl;
    for (size_t i = 0; i < tab.getColumnCount(); i++)
    {
        std::cout << i << tab.getColumnName(i) << ": " << colTypeToString(tab.getColumnType(i)) << std::endl;
    }
}