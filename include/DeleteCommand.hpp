#pragma once
#include "Command.hpp"

/**
 * @class DeleteCommand
 * @brief Command to delete rows from a table where a specified column matches a given value.
 *
 * This command allows the user to remove all rows from a table that match a specific value in a given column.
 */
class DeleteCommand : public Command {
public:

    /**
     * @brief Executes the delete command.
     * @param args Arguments for the command: table name, search column index, search value.
     * @param database Reference to the database where the command will be executed.
     * @throws std::invalid_argument If the arguments are incorrect, the table does not exist, or the column index is invalid.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;
};