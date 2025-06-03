#pragma once
#include "Command.hpp"


/**
 * @class ShowTablesCommand
 * @brief Command to display the names of all tables in the database.
 *
 * This command prints a list of all table names currently present in the database.
 */
class ShowTablesCommand : public Command {
public:

    /**
     * @brief Executes the showtables command.
     * @param args Arguments for the command (should be empty).
     * @param database Reference to the database whose tables will be listed.
     * @throws std::invalid_argument If any arguments are provided.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;
};