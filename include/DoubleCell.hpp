#pragma once
#include "Cell.hpp"

class DoubleCell : public Cell {
private:
    double value;

public:
    DoubleCell(double value);
    DoubleCell(const DoubleCell& other);
    DoubleCell& operator=(const DoubleCell& other);
    
    int compare(const Cell& other) const override;
    double getValue() const;
    ColumnType getType() const override;
    std::string toString() const override;
    Cell* clone() const override;
};