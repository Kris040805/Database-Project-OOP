#include "../include/SaveCommand.hpp"
#include "../include/Database.hpp"
#include "../include/Utilities.hpp"
#include "../include/Table.hpp"
#include "../include/ExportCommand.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

void SaveCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (!args.empty()) {
        throw std::invalid_argument("The \"save\" command does not accept any arguments.");
    }
    
    const std::string& catalogFileName = database.getCatalogFileName();
    if (catalogFileName.empty()) {
        throw std::runtime_error("No catalog file is currently open. Please open a catalog file first.");
    }

    // Записване на каталога
    std::ofstream catalogFile(catalogFileName);
    if (!catalogFile.is_open()) {
        throw std::invalid_argument("Failed to open the catalog file for writing: " + catalogFileName);
    }

    std::vector<std::string> tableNames = database.listTableNames();
    for (const std::string& tabName : tableNames)
    {
        std::string tabFile = database.getFileName(tabName);
        catalogFile << tabName << " " << tabFile << "\n";
    }
    catalogFile.close();

    // Записване на данните на таблиците
    ExportCommand exportCmd;
    for (const std::string& tabName : tableNames)        
    {
        std::string tabFile = database.getFileName(tabName);
        exportCmd.execute({tabName, tabFile}, database);
    }
    
    std::cout << "Catalog " << catalogFileName <<  " saved successfully." << std::endl;
}