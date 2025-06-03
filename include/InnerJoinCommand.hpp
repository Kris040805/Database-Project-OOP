#pragma once
#include "Command.hpp"


/**
 * @class InnerJoinCommand
 * @brief Command to perform an inner join between two tables on specified columns.
 *
 * This command creates a new table by joining two existing tables where the values in the specified columns match.
 * The resulting table contains all columns from the first table and all columns from the second table except the join column.
 */
class InnerJoinCommand : public Command {
public:

    /**
     * @brief Executes the inner join command.
     * @param args Arguments for the command: first table name, first table column index, second table name, second table column index.
     * @param database Reference to the database where the command will be executed.
     * @throws std::invalid_argument If the arguments are incorrect, the tables do not exist, or the column indices/types do not match.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;
};
