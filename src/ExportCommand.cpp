#include "../include/ExportCommand.hpp"
#include "../include/Database.hpp"
#include "../include/Table.hpp"
#include "../include/Row.hpp"
#include "../include/Cell.hpp"
#include "../include/ColumnType.hpp"
#include "../include/Utilities.hpp"
#include <vector>
#include <stdexcept>
#include <fstream>
#include <iostream>


void ExportCommand::execute(const std::vector<std::string>& args, Database& database) {
    if (args.size() != 2) {
        throw std::invalid_argument("Incorrect arguments for command \"export\".");
    }

    const std::string& tabName = args[0];
    const std::string& fileName = args[1];

    if (!database.hasTable(tabName)) {
        throw std::invalid_argument("Table \"" + tabName + "\" does not exist.");
    }

    const Table& table = database.getTableByName(tabName);
    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw std::invalid_argument("Failed to open file \"" + fileName + "\" for writing.");
    }

    // Името на таблицата
    file << table.getName() << "\n";

    // Име на колоните и техните типове
    for (size_t i = 0; i < table.getColumnCount(); i++)
    {
        file << table.getColumnName(i);
        if (i < table.getColumnCount() - 1) {
            file << ",";
        }
    }
    file << "\n";

    for (size_t i = 0; i < table.getColumnCount(); i++)
    {
        file << colTypeToString(table.getColumnType(i));
        if (i < table.getColumnCount() - 1) {
            file << ",";
        }
    }
    file << "\n";

    // Данни
    for (size_t i = 0; i < table.getRowCount(); i++) {
        const Row& row = table.getRow(i);
        for (size_t j = 0; j < table.getColumnCount(); j++) {
            const Cell* cell = row.getCell(j);
            std::string cellValue = cell->toString();

            if (cell->getType() == ColumnType::String) {
                file << '"';
                for (char c : cellValue) {
                    if (c == '"') file << "\"\"";
                    else file << c;
                }
                file << '"';
            } else {
                file << cellValue;
            }

            if (j < table.getColumnCount() - 1) file << ",";
        }
        file << "\n";
    }

    file.close();
    std::cout << "Table \"" << tabName << "\" exported to file: " << fileName << std::endl;
}

