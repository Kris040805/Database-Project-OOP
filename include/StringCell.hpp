#pragma once
#include "Cell.hpp"
#include <string>

class StringCell : public Cell {
private:
    std::string str;

public:
    StringCell(const std::string& str);
    StringCell(const StringCell& other);
    StringCell& operator=(const StringCell& other);

    int compare(const Cell& other) const override;
    ColumnType getType() const override;
    std::string toString() const override;
    Cell* clone() const override;
};