#pragma once
#include "Command.hpp"


/**
 * @class CloseCommand
 * @brief Command to close the currently opened database file and clear all loaded data.
 * 
 * After executing this command, only the open, help and exit commands will be available.
 */
class CloseCommand : public Command {
public:

    /**
     * @brief Executes the close command.
     * @param args Arguments for the command (should be empty).
     * @param database Reference to the database to be closed.
     * @throws std::invalid_argument If any arguments are provided.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;

};