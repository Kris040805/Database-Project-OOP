#pragma once
#include <string>
#include "ColumnType.hpp"

class Cell {
    public:
    Cell() = default;
    Cell(const Cell&) = default;
    Cell& operator=(const Cell&) = default;
    virtual ~Cell() = default;

    virtual ColumnType getType() const = 0;
    virtual std::string toString() const = 0;
    virtual Cell* clone() const = 0;
};