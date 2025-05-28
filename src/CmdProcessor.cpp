#include "../include/CmdProcessor.hpp"
#include "../include/Utilities.hpp"
#include "../include/CommandFactory.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>


void CmdProcessor::processCommands(const std::string& input, Database& database){
    std::vector<std::string> args = splitArgs(input);
    
    if (args.empty())
    {
        return;
    }
    
    std::string cmd = args[0];
    //премахваме командата от вектора
    args.erase(args.begin());

    CommandFactory factory;
    Command* command = factory.createCommand(cmd);
    if (command)
    {
        command->execute(args, database);
        delete command;
    } else {
        throw std::invalid_argument("Unknown command: \"" + cmd + "\".");
    }
}


std::vector<std::string> CmdProcessor::splitArgs(const std::string& line){
    std::vector<std::string> result;
    std::string current;
    bool inQuotes = false;

    for (char char_ : line) {
        if (char_ == '"')
        {
            inQuotes = !inQuotes;
            current += char_;
        }
        else if (char_ == ' ' && !inQuotes)
        {
            if (!current.empty())
            {
                result.push_back(current);
                current.clear();
            }
        }
        else {
            current += char_;
        }        
    }

    if (!current.empty())
    {
        result.push_back(current);
    }
    
    return result;
}


