#include "../include/ExitCommand.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

void ExitCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (!args.empty()) {
        throw std::invalid_argument("The \"exit\" command does not take any arguments.");
    }
    std::cout << "Exiting the program..." << std::endl;    
    std::exit(0);
}