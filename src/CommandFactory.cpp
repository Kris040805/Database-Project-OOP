#include "include\CloseCommand.hpp"
#include "../include/CommandFactory.hpp"
#include "../include/AddColumnCommand.hpp"
#include "../include/AggregateCommand.hpp"
#include "../include/CountCommand.hpp"
#include "../include/DeleteCommand.hpp"
#include "../include/DescribeCommand.hpp"
#include "../include/InsertCommand.hpp"
#include "../include/PrintCommand.hpp"
#include "../include/RenameCommand.hpp"
#include "../include/SelectCommand.hpp"
#include "../include/ShowTablesCommand.hpp"
#include "../include/UpdateCommand.hpp"
#include "../include/ImportCommand.hpp"
#include "../include/InnerJoinCommand.hpp"
#include "../include/ExportCommand.hpp"
#include "../include/OpenCommand.hpp"
#include "../include/CloseCommand.hpp"
#include "../include/HelpCommand.hpp"
#include "../include/ExitCommand.hpp"
#include "../include/SaveCommand.hpp"
#include "../include/SaveasCommand.hpp"


Command* CommandFactory::createCommand(const std::string& commandName) const {
    if (commandName == "addcolumn") {
        return new AddColumnCommand();
    } else if (commandName == "aggregate") {
        return new AggregateCommand();
    } else if (commandName == "count") {
        return new CountCommand();
    } else if (commandName == "delete") {
        return new DeleteCommand();
    } else if (commandName == "describe") {
        return new DescribeCommand();
    } else if (commandName == "insert") {
        return new InsertCommand();
    } else if (commandName == "print") {
        return new PrintCommand();
    } else if (commandName == "rename") {
        return new RenameCommand();
    } else if (commandName == "select") {
        return new SelectCommand();
    } else if (commandName == "showtables") {
        return new ShowTablesCommand();
    } else if (commandName == "update") {
        return new UpdateCommand();
    } else if (commandName == "import") {
        return new ImportCommand();
    } else if (commandName == "innerjoin") {
        return new InnerJoinCommand();
    } else if (commandName == "export") {
        return new ExportCommand();
    } else if (commandName == "open") {
        return new OpenCommand();
    } else if (commandName == "close") {
        return new CloseCommand();
    } else if (commandName == "help") {
        return new HelpCommand();
    } else if (commandName == "exit") {
        return new ExitCommand();
    } else if (commandName == "save") {
        return new SaveCommand();
    } else if (commandName == "saveas") {
        return new SaveasCommand();
    }
    
    
    return nullptr;
}