#pragma once
#include "Command.hpp"
#include <string>

class CommandFactory {
public:
    Command* createCommand(const std::string& name) const;
};