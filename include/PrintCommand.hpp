#pragma once
#include "Command.hpp"


/**
 * @class PrintCommand
 * @brief Command to print the contents of a specified table.
 *
 * This command displays all rows and columns of the given table in a formatted manner.
 */
class PrintCommand : public Command {
public:

    /**
     * @brief Executes the print command.
     * @param args Arguments for the command: table name.
     * @param database Reference to the database containing the table to print.
     * @throws std::invalid_argument If the arguments are incorrect or the table does not exist.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;
};