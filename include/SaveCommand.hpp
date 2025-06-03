#pragma once
#include "Command.hpp"


/**
 * @class SaveCommand
 * @brief Command to save the current database state to the currently opened catalog file.
 *
 * This command writes the catalog and all table data to the file that was opened with the open command.
 */
class SaveCommand : public Command {
public:

    /**
     * @brief Executes the save command.
     * @param args Arguments for the command (should be empty).
     * @param database Reference to the database to be saved.
     * @throws std::invalid_argument If any arguments are provided.
     * @throws std::invalid_argument If no catalog file is open or the file cannot be written.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;
};