#include "CommandFactory.hpp"
#include "AddColumnCommand.hpp"
#include "AggregateCommand.hpp"
#include "CountCommand.hpp"
#include "DeleteCommand.hpp"
#include "DescribeCommand.hpp"
#include "InsertCommand.hpp"
#include "PrintCommand.hpp"
#include "RenameCommand.hpp"
#include "SelectCommand.hpp"
#include "ShowTablesCommand.hpp"
#include "UpdateCommand.hpp"
#include "ImportCommand.hpp"
#include "InnerJoinCommand.hpp"




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
    }
    
    return nullptr;
}