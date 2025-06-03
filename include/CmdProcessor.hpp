#pragma once
#include "Table.hpp"
#include "Database.hpp"
#include <string>
#include <vector>

/**
 * @class CmdProcessor
 * @brief Processes and executes commands entered by the user.
 * 
 * The CmdProcessor class is responsible for parsing user input, extracting the command and its arguments,
 * and delegating the execution to the appropriate command object.
 */
class CmdProcessor {
public:

    /**
     * @brief Parses and executes command from user input.
     * 
     * @param input The full command line input from the user.
     * @param database Reference to the database on which the command will be executed.
     * @throws std::invalid_argument If the command is not recognized or the arguments are invalid.
     */
    void processCommands(const std::string& input, Database& database);

private:

    /**
     * @brief Splits the input line into command and arguments.
     * 
     * @param line The input line to be split.
     * @return A vector of strings std::vector<std::string> containing the command and its arguments.
     */
    std::vector<std::string> splitArgs(const std::string& line);
    

};
