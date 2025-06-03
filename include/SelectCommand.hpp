#pragma once
#include "Command.hpp"


/**
 * @class SelectCommand
 * @brief Command to select and display rows from a table where a specified column matches a given value.
 *
 * This command searches for rows in a table that match a specific value in a given column and displays them.
 */
class SelectCommand : public Command {
public:

    /**
     * @brief Executes the select command.
     * @param args Arguments for the command: search column index, search value, table name.
     * @param database Reference to the database where the command will be executed.
     * @throws std::invalid_argument If the arguments are incorrect, the table does not exist, or the column index is invalid.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;
};