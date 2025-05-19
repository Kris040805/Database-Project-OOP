#include "Table.hpp"
#include <stdexcept>

Table::Table() {}

Table::Table(const std::string& name) : name(name) {}

void Table::setName(const std::string& name){
    this->name = name;
}

const std::string& Table::getName() const{
    return name;
}


void Table::addColumn(const std::string& colName, ColumnType colType){
    columnNames.push_back(colName);
    columnTypes.push_back(colType);

    for (size_t i = 0; i < rows.size(); i++)
    {
        rows[i].addCell(new NullCell());
    }
}

void Table::insertRow(const Row& row){
    rows.push_back(row);
}

const Row& Table::getRow(size_t index) const{
    return rows[index];
}

size_t Table::getRowCount() const{
    return rows.size();
}

size_t Table::getColumnCount() const{
    return columnNames.size();
}

ColumnType Table::getColumntType(size_t index) const{
    //Няма значение дали ще взимаме размера на columnNames или columnTypes - и на двете е еднакво
    if (index >= columnNames.size())
    {
        throw std::out_of_range("Column index out of bounds.");
    }
    return columnTypes[index];
}

const std::string& Table::getColumnName(size_t index) const{
    if (index >= columnNames.size())
    {
        throw std::out_of_range("Column index out of bounds.");
    }
    return columnNames[index];
}

std::string Table::toString() const{
    std::string result;

    for (size_t i = 0; i < columnNames.size(); i++)
    {
        result += columnNames[i];
        if (i < columnNames.size() - 1)
        {
            result += " | ";
        }       
    }
    
    result += "\n";

    for (size_t i = 0; i < rows.size(); i++)
    {
        result += rows[i].toString();
        result += "\n";
    }
    
    return result;
}
