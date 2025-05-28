#include "InnerJoinCommand.hpp"
#include "Utilities.hpp"
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iostream>

void InnerJoinCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (args.size() != 4)
    {
        throw std::invalid_argument("Incorrect arguments for command \"innerjoin\".");
    }
    
    const std::string& table1 = args[0];
    const std::string& col1Str = args[1];
    const std::string& table2 = args[2];
    const std::string& col2Str = args[3];

    if (!database.hasTable(table1) || !database.hasTable(table2)) {
        throw std::invalid_argument("One or both tables do not exist.");
    }

    const Table& t1 = database.getTableByName(table1);
    const Table& t2 = database.getTableByName(table2);

    size_t col1, col2;
    try {
        col1 = std::stoul(col1Str);
        col2 = std::stoul(col2Str);
    } catch (...) {
        throw std::invalid_argument("Invalid column index");
    }

    if (col1 >= t1.getColumnCount() || col2 >= t2.getColumnCount())
    {
        throw std::invalid_argument("Column index out of range.");
    }

    // Проверка за съвместимост на типовете на колоните за join
    if (t1.getColumnType(col1) != t2.getColumnType(col2))
    {
        throw std::invalid_argument("Column types do not match.");
    }
    
    std::string joinedTableName = t1.getName() + "_join_" + t2.getName();
    Table joinedTable(joinedTableName);

    // Добавяне на колони от първата таблица
    for (size_t i = 0; i < t1.getColumnCount(); i++)
    {
        joinedTable.addColumn(t1.getColumnName(i), t1.getColumnType(i));
    }
    // Добавяне на колони от втората таблица, с изключение на join колоната
    for (size_t i = 0; i < t2.getColumnCount(); i++)
    {
        if (i != col2) // Пропускаме join колоната
        {
            joinedTable.addColumn(t2.getColumnName(i), t2.getColumnType(i));
        }
    }
        
    // join
    for (size_t i = 0; i < t1.getColumnCount(); i++)
    {
        const Row& row1 = t1.getRow(i);
        const Cell* cell1 = row1.getCell(col1);

        for (size_t j = 0; j < t2.getColumnCount(); j++)
        {
            const Row& row2 = t2.getRow(j);
            const Cell* cell2 = row2.getCell(col2);

            if (cell1->compare(*cell2) == 0) 
            {
                Row newRow;

                for (size_t k = 0; k < t1.getColumnCount(); k++)
                {
                    newRow.addCell(row1.getCell(k)->clone());
                }

                for (size_t k = 0; k < t2.getColumnCount(); k++)
                {
                    if (k != col2) // Пропускаме join колоната
                    {
                        newRow.addCell(row2.getCell(k)->clone());
                    }
                }
                joinedTable.insertRow(newRow);
            }
        }
    }
    
    database.addTable(joinedTable);
    std::cout << "Inner join completed. New table: " << joinedTableName << std::endl;
}

