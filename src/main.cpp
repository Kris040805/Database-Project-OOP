#include "../include/Database.hpp"
#include "../include/Table.hpp"
#include "../include/Utilities.hpp"
#include "../include/CommandFactory.hpp"
#include "../include/CmdProcessor.hpp"
#include <iostream>



int main() {

    Database database;
    Table table("example_table");
    database.addTable(table);
    CmdProcessor cmdProcessor;
    while (true)
    {
        std::string input;
        std::cout << "Enter command: ";
        std::getline(std::cin, input);

        try
        {
            cmdProcessor.processCommands(input, database);
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }


    }
    

    return 0;
}