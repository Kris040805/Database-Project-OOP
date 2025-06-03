#pragma once
#include <string>
#include <vector>
#include "Database.hpp"

/**
 * @class Command
 * @brief Abstract base class for all commands in the database management system.
 * 
 * The Command class defines the interface for executing commands with arguments on a Database reference.
 * All specific command classes (such as AddColumnCommand, InsertCommand, etc.) should inherit from this class
 * and implement the execute() method.
 */
class Command {
public:

    /**
     * @brief Virtual destructor for safe polymorphic deletion.
     */
    virtual ~Command() {}

    /**
     * @brief Executes the command with the given arguments on the provided database.
     * 
     * @param args The arguments for the command.
     * @param database Reference to the database on which the command operates.
     */
    virtual void execute(const std::vector<std::string>& args, Database& database) = 0;
};