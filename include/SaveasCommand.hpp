#pragma once
#include "Command.hpp"

class SaveasCommand : public Command {
public:
    void execute(const std::vector<std::string>& args, Database& database) override;

};