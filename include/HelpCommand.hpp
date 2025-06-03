#pragma once
#include "Command.hpp"


/**
 * @class HelpCommand
 * @brief Command to display information about all supported commands in the program.
 *
 * This command prints a list of all available commands and a short description for each.
 */
class HelpCommand : public Command {
public:

    /**
     * @brief Executes the help command.
     * @param args Arguments for the command (should be empty).
     * @param database Reference to the database (not used).
     * @throws std::invalid_argument If any arguments are provided.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;

};