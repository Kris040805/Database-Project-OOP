#pragma once
#include "Command.hpp"


/**
 * @class RenameCommand
 * @brief Command to rename an existing table in the database.
 *
 * This command changes the name of a specified table and updates any associated file mappings.
 */
class RenameCommand : public Command {
public:

    /**
     * @brief Executes the rename command.
     * @param args Arguments for the command: old table name, new table name.
     * @param database Reference to the database where the table will be renamed.
     * @throws std::invalid_argument If the arguments are incorrect, the old table does not exist, or the new name is already taken.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;
};