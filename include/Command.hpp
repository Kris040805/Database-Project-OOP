#pragma once
#include <string>
#include <vector>
#include "Database.hpp"

class Command {
public:
    virtual ~Command() {}
    virtual void execute(const std::vector<std::string>& args, Database& database) = 0;
};