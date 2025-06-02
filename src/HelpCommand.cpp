#include "../include/HelpCommand.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

void HelpCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (!args.empty()) {
        throw std::invalid_argument("The \"help\" command does not accept any arguments.");
    }

    std::cout << "The following commands are supported:\n";
    std::cout << "open <file>\t\topens <file>\n";
    std::cout << "close\t\t\tcloses currently opened file\n";
    std::cout << "save\t\t\tsaves the currently open file\n";
    std::cout << "saveas <file>\t\tsaves the currently open file in <file>\n";
    std::cout << "help\t\t\tprints this information\n";
    std::cout << "exit\t\t\texits the program\n";
}