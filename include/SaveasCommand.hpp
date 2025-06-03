#pragma once
#include "Command.hpp"


/**
 * @class SaveasCommand
 * @brief Command to save the current database state to a specified catalog file.
 *
 * This command writes the catalog and all table data to a new file, as specified by the user.
 */
class SaveasCommand : public Command {
public:

    /**
     * @brief Executes the saveas command.
     * @param args Arguments for the command: new catalog file name.
     * @param database Reference to the database to be saved.
     * @throws std::invalid_argument If the arguments are incorrect or the file cannot be opened for writing.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;

};