#pragma once
#include "Command.hpp"

/**
 * @class CountCommand
 * @brief Command to count the number of rows in a table where a specified column matches a given value.
 *
 * This command allows the user to count how many rows in a table have a specific value in a given column.
 */
class CountCommand : public Command {
public:

    /**
     * @brief Executes the count command.
     * @param args Arguments for the command: table name, search column index, search value.
     * @param database Reference to the database where the command will be executed.
     * @throws std::invalid_argument If the arguments are incorrect, the table does not exist, or the column index is invalid.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;
};