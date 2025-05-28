#include "../include/Database.hpp"
#include "../include/Table.hpp"
#include "../include/Utilities.hpp"
#include "../include/CommandFactory.hpp"
#include "../include/CmdProcessor.hpp"
#include <iostream>



int main() {

    Database database;
    Table table("example_table");
    database.addTable(table);
    CmdProcessor cmdProcessor;
    while (true)
    {
        std::string input;
        std::cout << "Enter command: ";
        std::getline(std::cin, input);

        try
        {
            cmdProcessor.processCommands(input, database);
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }


    }
    
    

























    // Database database;
    // Table table("example_table");
    // database.addTable(table);

    // //std::cout << table.getName() << std::endl; // "example_table"
    // table.addColumn("id", ColumnType::Int);
    // table.addColumn("name", ColumnType::String);
    // table.addColumn("grade", ColumnType::Double);
    // std::cout << table.getColumnName(0) << std::endl; // "id"
    // std::cout << table.getColumnName(1) << std::endl; // "id"

    // Row row1;
    // Cell* cell1 = createCellFromStr("1");
    // Cell* cell2 = createCellFromStr("\"Alice\"");
    // Cell* cell3 = createCellFromStr("85.5");
    // row1.addCell(cell1);
    // row1.addCell(cell2);
    // row1.addCell(cell3);
    // table.insertRow(row1);
    
    // // std::cout << table.getRow(0).getCell(0)->toString() << std::endl; // "1"
    // // std::cout << table.getRow(0).getCell(1)->toString() << std::endl; // "Alice"
    // // std::cout << table.getRow(0).getCell(2)->toString() << std::endl; // "85.5"
    // // std::cout << table.getRowCount() << std::endl; // 1
    // // std::cout << table.getRow(0).toString() << std::endl; // "1, Alice, 85.5"
    
    // // table.deleteRow(0);
    // // std::cout << table.getRowCount() << std::endl; // 0
    // // std::cout << table.toString() << std::endl; // "example_table: 0 rows"



    return 0;
}