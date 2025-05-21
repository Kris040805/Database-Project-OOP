#pragma once
#include "Row.hpp"
#include "ColumnType.hpp"
#include "NullCell.hpp"
#include <vector>
#include <string>

class Table {
private:
    std::string name;
    std::vector<std::string> columnNames;
    std::vector<ColumnType> columnTypes;
    std::vector<Row> rows;

public:
    Table();
    Table(const std::string& name);

    void setName(const std::string& name);
    const std::string& getName() const;

    void addColumn(const std::string& colName, ColumnType colType);
    void insertRow(const Row& row);
    void deleteRow(size_t index);
    const Row& getRow(size_t index) const;
    Row& getRow(size_t index);
    size_t getRowCount() const;
    size_t getColumnCount() const;
    ColumnType getColumnType(size_t index) const;
    const std::string& getColumnName(size_t index) const;
    size_t getColumnIndex(const std::string& colName) const;
    std::string toString() const;
};