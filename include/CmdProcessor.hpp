#pragma once
#include "Table.hpp"
#include <string>
#include <vector>


class CmdProcessor {
public:
    void processCommands(const std::string& input, Table& table);

private:
    std::vector<std::string> splitArgs(const std::string& line);
    
    void cmdInsert(const std::vector<std::string>& args, Table& table);

    

};
