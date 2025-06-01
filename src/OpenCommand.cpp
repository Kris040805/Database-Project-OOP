#include "../include/OpenCommand.hpp"
#include "../include/Database.hpp"
#include "../include/Utilities.hpp"
#include "../include/ImportCommand.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <sstream>

void OpenCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (args.size() != 1) {
        throw std::invalid_argument("Incorrect arguments for command \"open\".");
    }
    const std::string& catalogFile = args[0];
    
    std::ifstream file(catalogFile);
    if (!file.is_open()) {
        std::ofstream newFile(catalogFile);
        if (!newFile.is_open()) {
            throw std::runtime_error("Failed to create file: " + catalogFile);
        }
        newFile.close();
        std::cout << "Successfully created and opened " << catalogFile << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) 
    {
        if (line.empty()) 
        {
            continue;
        }
        std::istringstream iss(line);
        std::string tableName, tableFile;
        if (!(iss >> tableName >> tableFile)) 
        {
            std::cerr << "Invalid line in catalog file: " << line << std::endl;
            std::exit(1);
        }

        try
        {
            ImportCommand importCmd;
            importCmd.execute({tableFile}, database);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error processing table \"" << tableName << "\": " << e.what() << std::endl;
            std::exit(1);
        }
    }
    file.close();
    std::cout << "Successfully opened catalog file: " << catalogFile << std::endl;
}