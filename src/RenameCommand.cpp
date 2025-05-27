#include "RenameCommand.hpp"
#include "Utilities.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>

void RenameCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (args.size() != 2)
    {
        throw std::invalid_argument("Incorrect arguments for command \"rename\".");
    }
    
    const std::string& oldName = args[0];
    const std::string& newName = args[1];

    if (!database.hasTable(oldName))
    {
        throw std::invalid_argument("Table \"" + oldName + "\" does not exist.");
    }

    if (database.hasTable(newName))
    {
        throw std::invalid_argument("Table \"" + newName + "\" already exists.");
    }

    database.renameTable(oldName, newName);
    std::cout << "Table \"" + oldName + "\" renamed to \"" + newName + "\"." << std::endl;

}