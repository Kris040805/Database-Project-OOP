#include "../include/Database.hpp"
#include "../include/Table.hpp"
#include "../include/Utilities.hpp"
#include "../include/CommandFactory.hpp"
#include "../include/CmdProcessor.hpp"
#include <iostream>



int main() {

    bool isOpen = false;
    Database database;
    CmdProcessor cmdProcessor;
    while (true)
    {
        std::string input;
        std::cout << "> ";
        std::getline(std::cin, input);

        std::string cmd = input.substr(0, input.find(' '));

        if (!isOpen && cmd != "open") {
            std::cout << "Database is not open. Please open a database first." << std::endl;
            continue;
        }  

        try
        {
            cmdProcessor.processCommands(input, database);
            if (cmd == "open") {
                isOpen = true;
            } else if (cmd == "close") {
                isOpen = false;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    
    return 0;
}