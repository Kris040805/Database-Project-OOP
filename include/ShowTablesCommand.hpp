#pragma once
#include "Command.hpp"

class ShowTablesCommand : public Command {
public:
    void execute(const std::vector<std::string>& args, Database& database) override;
};