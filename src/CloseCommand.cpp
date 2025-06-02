#include "../include/CloseCommand.hpp"
#include "../include/Database.hpp"
#include "../include/Utilities.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

void CloseCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (!args.empty()) {
        throw std::invalid_argument("Incorrect arguments for command \"close\".");
    }

    database = Database();

    std::cout << "Successfully closed " << database.getCatalogFileName() << std::endl;
}