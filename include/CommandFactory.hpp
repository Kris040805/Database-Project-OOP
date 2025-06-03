#pragma once
#include "Command.hpp"
#include <string>

/**
 * @class CommandFactory
 * @brief Factory class for creating Command objects by command name.
 * 
 * The CommandFactory is responsible for instantiating the appropriate Command subclass
 * (such as AddColumnCommand, InsertCommand, etc.) based on the provided command name.
 */
class CommandFactory {
public:
    /**
     * @brief Creates a Command object corresponding to the given command name.
     * 
     * @param name The name of the command (e.g., "addcolumn", "insert", "open").
     * @return Pointer to a new Command object, or nullptr if the command is unknown.
     */
    Command* createCommand(const std::string& name) const;
};