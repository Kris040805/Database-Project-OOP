#pragma once
#include "Command.hpp"


/**
 * @class AggregateCommand
 * @brief Command to perform aggregation operations (sum, product, minimum, maximum) on a specified column of a table in the database.
 * 
 */
class AggregateCommand : public Command {
public:

    /**
     * @brief Executes the aggregation command on a specified table and column.
     * 
     * @param args Arguments for the command: table name, search column index, search value, target column index, aggregation operation (sum, product, minimum, maximum).
     * @param database Reference to the database where the operation will be performed.
     * @throws std::invalalid_argument If the arguments are incorrect, the table does not exist, or the column indices are out of range.
     */
    void execute(const std::vector<std::string>& args, Database& database) override;
};