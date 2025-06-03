#pragma once
#include "Command.hpp"


/**
 * @class DescribeCommand
 * @brief Command to display information about the columns of a specified table.
 *
 * This command prints the names and types of all columns in the given table.
 */
class DescribeCommand : public Command {
public:

    /**
     * @brief Executes the describe command.
     * @param args Arguments for the command: table name.
     * @param database Reference to the database where the command will be executed.
     * @throws std::invalid_argument If the arguments are incorrect or the table does not exist.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;
};