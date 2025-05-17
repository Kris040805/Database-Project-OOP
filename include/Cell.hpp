#pragma once
#include <string>

class Cell {
    public:
    Cell() = default;
    Cell(const Cell&) = default;
    Cell& operator=(const Cell&) = default;
    virtual ~Cell() = default;

    virtual std::string toString() const = 0;
    virtual Cell* clone() const = 0;
};