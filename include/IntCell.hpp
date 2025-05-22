#pragma once
#include "Cell.hpp"

class IntCell : public Cell {
private:
    int value;

public:
    IntCell(int value);
    IntCell& operator=(const IntCell& other);
    IntCell(const IntCell& other);

    int compare(const Cell& other) const override;
    int getValue() const;
    ColumnType getType() const override;
    std::string toString() const override;
    Cell* clone() const override;
};