#pragma once
#include "Command.hpp"

class HelpCommand : public Command {
public:
    void execute(const std::vector<std::string>& args, Database& database) override;

};