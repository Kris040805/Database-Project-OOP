#pragma once
#include "Command.hpp"


/**
 * @class InsertCommand
 * @brief Command to insert a new row into a specified table in the database.
 *
 * This command adds a new row with the provided values to the specified table.
 */
class InsertCommand : public Command {
public:

    /**
     * @brief Executes the insert command to add a new row to a specified table.
     * 
     * @param args Arguments for the command: table name followed by values for each column.
     * @param database Reference to the database where the command will be executed.
     * @throws std::invalid_argument If the table does not exist, or if the number of values does not match the number of columns.
     */ 
    void execute(const std::vector<std::string>& args, Database& database) override;
};