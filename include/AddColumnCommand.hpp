#pragma once
#include "Command.hpp"

/**
 * @class AddColumnCommand
 * @brief Command to add a new column to a table in the database. 
 * 
 */
class AddColumnCommand : public Command {
public:


    /**
     * @brief Executes the command to add a new column to a specified table in the database.
     * 
     * @param args Arguments for the command: table name, column name, column type.
     * @param database Reference to the database where the command will be executed.
     * @throws std::invalid_argument If the table does not exist, or if the column already exists, or if the column type is invalid.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;
};