#include "../include/SaveasCommand.hpp"
#include "../include/Database.hpp"
#include "../include/ExportCommand.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

void SaveasCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (args.size() != 1) {
        throw std::invalid_argument("Incorrect arguments for command \"saveas\".");
    }

    const std::string& newCatalogFileName = args[0];

    // Записване в новия каталог
    std::ofstream catalogFile(newCatalogFileName);
    if (!catalogFile.is_open()) {
        throw std::runtime_error("Failed to open catalog file for writing: " + newCatalogFileName);
    }

    std::vector<std::string> tableNames = database.listTableNames();
    for (const std::string& tableName : tableNames)
    {
        std::string tabFile = database.getFileName(tableName);
        catalogFile << tableName << " " << tabFile << "\n";
    }
    catalogFile.close();

    // Записване на таблиците във файлвете като те не се сменят
    ExportCommand exportCmd;
    for (const std::string& tabName : tableNames) 
    {
        std::string tabFile = database.getFileName(tabName);
        exportCmd.execute({tabName, tabFile}, database);
    }

    std::cout << "Saved " << newCatalogFileName << " successfully." << std::endl;
}