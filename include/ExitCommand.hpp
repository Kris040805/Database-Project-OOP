#pragma once
#include "Command.hpp"


/**
 * @class ExitCommand
 * @brief Command to exit the database management program.
 *
 * This command terminates the application when executed.
 */
class ExitCommand : public Command {
public:

    /**
     * @brief Executes the exit command.
     * @param args Arguments for the command (should be empty).
     * @param database Reference to the database (not used).
     * @throws std::invalid_argument If any arguments are provided.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;
};