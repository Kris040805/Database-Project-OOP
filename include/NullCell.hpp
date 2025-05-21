#pragma once
#include "Cell.hpp"
#include <string>

class NullCell : public Cell {
public:
    NullCell() = default;
    int compare(const Cell& other) const override;
    ColumnType getType() const override;
    std::string toString() const override;
    Cell* clone() const override;
};