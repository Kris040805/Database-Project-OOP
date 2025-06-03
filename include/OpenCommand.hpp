#pragma once
#include "Command.hpp"


/**
 * @class OpenCommand
 * @brief Command to open a database catalog file and load its tables.
 *
 * This command opens the specified catalog file, loads all referenced tables into the database,
 * and sets the catalog as the currently opened file.
 */
class OpenCommand : public Command {
public:

    /**
     * @brief Executes the open command.
     * @param args Arguments for the command: catalog file name.
     * @param database Reference to the database where tables will be loaded.
     * @throws std::invalid_argument If the arguments are incorrect or the file cannot be opened.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;
};