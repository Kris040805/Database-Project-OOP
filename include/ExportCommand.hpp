#pragma once
#include "Command.hpp"


/**
 * @class ExportCommand
 * @brief Command to export a table from the database to a file.
 *
 * This command writes the structure and data of a specified table to a file in a .csv format.
 */
class ExportCommand : public Command {
public:

    /**
     * @brief Executes the export command.
     * @param args Arguments for the command: table name, file name.
     * @param database Reference to the database containing the table to export.
     * @throws std::invalid_argument If the arguments are incorrect or the table does not exist.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;

};