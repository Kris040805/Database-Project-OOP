#pragma once
#include "Command.hpp"

/**
 * @class ImportCommand
 * @brief Command to import a table from a file into the database.
 *
 * This command reads a table's structure and data from a .csv file and adds it to the database.
 */
class ImportCommand : public Command {
public:

    /**
     * @brief Executes the import command.
     * @param args Arguments for the command: file name to import from.
     * @param database Reference to the database where the table will be imported.
     * @throws std::invalid_argument If the arguments are incorrect, the file cannot be opened, or the table already exists.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;

};
