#include "ImportCommand.hpp"
#include "Utilities.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <vector>

void ImportCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (args.size() != 1)
    {
        throw std::invalid_argument("Incorrect arguments for command \"import\".");
    }
    
    const std::string& fileName = args[0];
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::invalid_argument("Failed to open file: " + fileName);
    }

    std::string tableName;
    std::getline(file, tableName);
    if (tableName.empty()) {
        throw std::invalid_argument("File does not contain a table name.");
    }

    if (database.hasTable(tableName)) {
        throw std::invalid_argument("Table with name \"" + tableName + "\" already exists.");
    }

    std::string columnNamesLine,
                columnTypesLine;
    if (!std::getline(file, columnNamesLine) || !std::getline(file, columnTypesLine)) {
        throw std::invalid_argument("File does not contain column names or types.");
    }

    std::vector<std::string> columnNames = parseCSVLine(columnNamesLine);
    std::vector<std::string> columnTypes = parseCSVLine(columnTypesLine);

    if (columnNames.size() != columnTypes.size()) {
        throw std::invalid_argument("Number of column names does not match number of column types.");
    }

    Table newTable(tableName);
    for (size_t i = 0; i < columnNames.size(); ++i) {
        ColumnType colType = parseColType(columnTypes[i]);
        if (colType == ColumnType::Null) {
            throw std::invalid_argument("Invalid column type: " + columnTypes[i]);
        }

        newTable.addColumn(columnNames[i], colType);
    }

    std::string rowLine;
    while (std::getline(file, rowLine))
    {
        if (rowLine.empty()) {
            continue; // Пропускаме празни редове
        }
        std::vector<std::string> rowValues = parseCSVLine(rowLine);
        if (rowValues.size() != columnNames.size()) {
            throw std::invalid_argument("Row does not match column count: " + rowLine);
        }
        
        Row newRow;
        for (size_t i = 0; i < rowValues.size(); i++)
        {
            Cell* cell = createCellFromStr(rowValues[i]);
            ColumnType expectedType = newTable.getColumnType(i);
            if (cell->getType() != expectedType && expectedType != ColumnType::Null) {
                delete cell;
                throw std::invalid_argument("Cell type does not match expected type for column " + newTable.getColumnName(i) + ": " + rowValues[i]);
            }
            newRow.addCell(cell);
        }
        newTable.insertRow(newRow);
    }
    
    database.addTable(newTable);
    database.registerTableFile(tableName, fileName);

    std::cout << "Table \"" << tableName << "\" imported successfully from file: " << fileName << std::endl;

}