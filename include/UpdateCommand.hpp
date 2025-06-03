#pragma once
#include "Command.hpp"


/**
 * @class UpdateCommand
 * @brief Command to update values in a table where a specified column matches a given value.
 *
 * This command searches for rows in a table that match a specific value in a given column and updates another column in those rows with a new value.
 */
class UpdateCommand : public Command {
public:

    /**
     * @brief Executes the update command.
     * @param args Arguments for the command: table name, search column index, search value, target column index, target value.
     * @param database Reference to the database where the command will be executed.
     * @throws std::invalid_argument If the arguments are incorrect, the table does not exist, or the column indices are invalid.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;
};